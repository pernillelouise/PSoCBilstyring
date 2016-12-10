/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/
#include <project.h>
#include <stdio.h>
#include "regulering.h"

static uint32 i=0; 
static uint32 dis=0; 

char value[20]; 
char * p2; 
char test_string1[] = "Hello World1\n\r"; 
char test_string2[] = "Hello World2\n\r"; 

CY_ISR(Timer_ISR_handler)
{
    //at 1MHz clock each count is 1 micro second 
    Timer_ClearInterrupt(Timer_INTR_MASK_CC_MATCH); 
    
    i = Timer_ReadCounter(); 
    
    if((i/58) <= 399 && (i/58) != 4)
    {
        dis = (i/58);
        UART_print_UartPutString(test_string1);
    }
    else if((i/58) == 4 || (i/58) > 399)
    {
        dis = 0; 
        UART_print_UartPutString(test_string2);
    }
    
    //Test. Print afstand. 
    p2=value; 
    sprintf(value, "%lu",dis);
    UART_print_UartPutString(p2); 
    UART_print_UartPutString("  \n\r   "); 
    CyDelay(100); 
    
//    if(dis<10)
//    {
//        LED_Write(0);
//    }
}

int distanceToObject()
{
    CyGlobalIntEnable; 
    Timer_Start(); 
    
    ISR_StartEx(Timer_ISR_handler); 
    
    //char test_string[] = "Hello World\n\r"; 
    //UART_print_Start(); 
    //UART_print_UartPutString(test_string); 
    
    if(distanceFlag == 1)
    {
        //LED_Write(1);        
        CyDelay(50); 
        Trig_Write(1); 
        CyDelayUs(10); 
        Trig_Write(0); 
        distanceFlag = 0;
    }
    
    return dis; 
}

/* [] END OF FILE */
