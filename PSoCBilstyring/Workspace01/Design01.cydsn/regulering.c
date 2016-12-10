#include "Regulering.h"
#include "PWM_hojre.h"
#include "PWM_venstre.h"
#include "ADC.h"

// Regulering: 
// Returns: Double 
// Parameter: int 
// a and b arrays is compensator coeffecients
//    double a[2] = {7.331, -15.24};
//    double b[2] = {1, -2};
//    int y;
//    int m;
//           
//    int Regulering(int x)
//    {
//        int res;
//        res = (x-b[1]*m)*a[0]+a[1]*m;
//        
//        y = res;
//        m = x;
//        
//        return y;
//    }
    
volatile int reg;
volatile int16 V_reg;

    float convertVtoSpeed()
    {
        float speed;
        V_reg = ADC_GetResult16(1);
        reg = ADC_CountsTo_mVolts(1,V_reg)*1.5;
   
        speed = 0.024*reg;
        
        return speed;
    }
       
    int regulateDistance(int distance, int setDistance)
    {
        distanceFlag = 1;
        int pwmReadVal_left;
        int pwmReadVal_right;
        int pwmSetVal_left;
        int pwmSetVal_right;
        if(distance+5 > setDistance)
        {
            pwmReadVal_left = PWM_venstre_ReadCompare();
            pwmReadVal_right = PWM_hojre_ReadCompare();
            pwmSetVal_left = (pwmReadVal_left+1.525*5 == 255 ? 255 : pwmReadVal_left+1.525*5);
            pwmSetVal_right = (pwmReadVal_right+1.525*5 == 255 ? 255 : pwmReadVal_right+1.525*5);
            start_left(pwmSetVal_left);
            start_right(pwmSetVal_right);
        }  
        else if(distance-5 < setDistance)
        {
            pwmReadVal_left = PWM_venstre_ReadCompare();
            pwmReadVal_right = PWM_hojre_ReadCompare();
            pwmSetVal_left = (pwmReadVal_left-1.525*10 < 10  ? 5 : pwmReadVal_left-1.525*10);
            pwmSetVal_right = (pwmReadVal_right-1.525*10 < 10  ? 5 : pwmReadVal_right-1.525*10);
            PWM_venstre_WriteCompare(pwmSetVal_left);
            //start_left(pwmSetVal_left);
            //start_right(pwmSetVal_right);
        }
        else if(distance < distance+5 && distance > distance-5)
        {
            pwmReadVal_left = PWM_venstre_ReadCompare();
            pwmReadVal_right = PWM_hojre_ReadCompare();
            start_left(pwmReadVal_left);
            start_right(pwmReadVal_right);
        }
        else if(distance < 10)
        {
            stop();
        }         
     return 0;
    }
    
    // turns on right dc motor
    // duty cycle is regulering (0-100% 0-255)
    int start_right(unsigned int regulering)
    {
        if(regulering > 0 && regulering < 255)
        {   
            PWM_hojre_WriteCompare(regulering);
            return 1;
        }
        else    
        return -1;
    }

    
    // turns on left dc motor
    // duty cycle is controlled by regulering
    int start_left(unsigned int regulering)
    {
        
        if(regulering > 0 && regulering < 255)
        {   
            PWM_venstre_Start();
            PWM_venstre_WriteCompare(regulering);
            return 1;
        }
        else    
        return -1;
    }
//    NOT IN USE
//    int regulatePWM(int setSpeed,int measuredSpeed)
//    {
//        float regulateSpeed;        
//        if(setSpeed > measuredSpeed)
//        {
//            setSpeed = (setSpeed > 0 ? setSpeed : 1);
//            regulateSpeed = (measuredSpeed/setSpeed)*setSpeed;
//            start_left(regulateSpeed);
//            start_right(regulateSpeed);
//        }
//        else if(setSpeed < measuredSpeed)
//        {
//            measuredSpeed = (measuredSpeed > 0 ? measuredSpeed : 1);
//            regulateSpeed = (setSpeed/measuredSpeed)*setSpeed;
//            start_left(regulateSpeed);
//            start_right(regulateSpeed);            
//        }
//        return 0;
//    }
    
    
    int stop()
    {
    PWM_hojre_WriteCompare(0);
    PWM_venstre_WriteCompare(0);
     return 0;        
    }
    
    // Search for sound direction
    int direction(int dir)
    {
        int i = 0;
        for(i = 0; i<5;i++)
        {
        switch(dir)
        {
            case 12: 
            start_left(100);
            i++;
            break;
            case 21: 
            start_left(150);
            CyDelay(200);
            stop();
            i++;
            break;
            case 23: 
            start_left(200);
            CyDelay(200);
            stop();
            i++;
            break;
            case 32: 
            start_left(200);
            CyDelay(200);
            stop();
            i++;
            case 34: 
            start_right(200);
            CyDelay(200);
            stop();
            i++;
            break; 
            case 43: 
            start_right(200);
            CyDelay(200);
            stop();
            i++;
            break;
            case 41: 
            start_right(150);
            CyDelay(200);
            stop();
            i++;
            break;
            case 14:
            start_right(100);
            CyDelay(200);
            stop();
            i++;
            break;
            default:
            stop();
        }
        }
    return 0;
    }
    
  
     
/* [] END OF FILE */
