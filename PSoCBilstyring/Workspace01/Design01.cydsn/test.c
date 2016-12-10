#include <project.h>
#include "I2Cslave.h"
#include <stdbool.h>
#include <stdio.h>
#include "distance.h"
#include "regulering.h"

#define size 3
#define MODE_FOLG_OBJEKT 0xE1
#define MODE_FOLG_LYD 0xE2
#define OBJEKT_LIGEUD 0xFB
#define OBJEKT_VENSTRE 0xFA
#define OBJEKT_HOJRE 0xC2
#define OBJEKT_IKKE_FUNDET 0xC3
#define START 0xC4

uint8 buffer = 0;
int i=0;
bool readObjData = false;
int mode=0;
bool start=false;
int16 result;
uint8 dataRdy;
volatile int16 V;
volatile float32 Volt;
const int setDistance = 50;
int distanceFlag = 1;

char test1[] = "Hello from folg lyd \n\r"; 
char test2[] = "Hello from folg objekt \n\r"; 
char test3[] = "Hello from objekt ligeud \n\r"; 
char test4[] = "Hello from objekt venstre \n\r"; 
char test5[] = "Hello from objekt hojre \n\r"; 
char test6[] = "Hello from objekt ikke fundet \n\r"; 
char test7[] = "Hello from start \n\r"; 
char test8[] = "Hello from readObject \n\r"; 

int main()
{
    CyGlobalIntEnable; /* Enable global interrupts. */
    I2C_1_Start();
    
       // ADC_IRQ_Enable();
    ADC_Start();
    ADC_StartConvert();
    UART_print_Start(); 

//    PWM_venstre_WriteCompare(127);
//    PWM_hojre_WriteCompare(127);

 // Init the slave buffers
    initReceiveData();
    //DebugLEDBlue_Write(0u); 
    
    for(;;)
    {
        receiveData(&buffer);
        
        volatile int distance;       
        distance = distanceToObject();
        
        
        
        //uint8 refBuf = buffer;
        switch(buffer)
        {
            case MODE_FOLG_OBJEKT:
                //Mode folg objekt
                
                mode=MODE_FOLG_OBJEKT;
                
                UART_print_UartPutString(test2);
                CyDelay(1000); 
               
                break;
            case MODE_FOLG_LYD:
                //Mode folg lyd
                mode = MODE_FOLG_LYD; 
                
                UART_print_UartPutString(test1);
                CyDelay(1000); 
                break;
        if (readObjData)
        {
            PWM_hojre_Start();
            PWM_venstre_Start();
            case OBJEKT_LIGEUD :
                // Objektretning ligeud
                //UART_print_UartPutString("Object lige ud");
                
                UART_print_UartPutString(test3);
                CyDelay(1000); 
                regulateDistance(distance,setDistance);
                
                break;
            case OBJEKT_VENSTRE:
                //Objetkretning venstre
                UART_print_UartPutString(test4);
                CyDelay(1000); 
                regulateDistance(distance,setDistance);
                                
                break;
            case OBJEKT_HOJRE:
                //Objektretning hojre
                UART_print_UartPutString(test5);
                CyDelay(1000); 
                regulateDistance(distance,setDistance);
                
                break;
            case OBJEKT_IKKE_FUNDET:
                //Objekt ikke fundet
                UART_print_UartPutString(test6);
                CyDelay(1000); 
                stop(); 
                break;
        }
            case START:
                UART_print_UartPutString(test7);
                CyDelay(1000); 
                start=!start;
                if (start)
                {
                    if (mode == MODE_FOLG_LYD)
                    {
                        // follow sound
                    }
                    else if (mode == MODE_FOLG_OBJEKT)
                    {
                        // read data
                        readObjData = true;
                        UART_print_UartPutString(test8);
                    }
                }
                else 
                {
                    // stop car
                    stop(); 
                }
                break;
            default: 
                break; 
        } // END OF SWITCH STATEMENT
        
    }
    
    
    
} // end of main