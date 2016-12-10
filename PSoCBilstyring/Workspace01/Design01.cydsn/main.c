//#include <project.h>
//#include "regulering.h"
//#include "distance.h"
//
//int16 result;
//uint8 dataRdy;
//volatile int16 V;
//volatile float32 Volt;
//const int setDistance = 50;
//int distanceFlag = 1;
//
//int main()
//{
//   // CyGlobalIntEnable; /* Enable global interrupts. */
//   // int16 newReading = 0;
//
//   // ADC_IRQ_Enable();
//    ADC_Start();
//    ADC_StartConvert();
//    PWM_hojre_Start();
//    PWM_venstre_Start();
//    PWM_venstre_WriteCompare(127);
//    PWM_hojre_WriteCompare(127);
//    
//
//    for(;;)
//    {
//        /* Place your application code here. */
//        ADC_IsEndConversion(ADC_WAIT_FOR_RESULT);    
//        V = ADC_GetResult16(0);
//        Volt = ADC_CountsTo_Volts(0,V);
//        
//        if(Volt > 3)
//        {
//            Pin_1_Write(1);
//        }
//        else
//        {
//            Pin_1_Write(0);
//        }
//               
//        int distance;       
//        distance = distanceToObject();
//        
//        regulateDistance(distance,setDistance);
//        
//        
//    }  
//}
//    
////    
////    CY_ISR(ADC_ISR) 
////    {
////     uint32 intr_status;   
////     intr_status = ADC_SAR_INTR_REG;
////        
////     result = ADC_CountsTo_mVolts(1,0);
////     dataRdy = 1;
////     ADC_SAR_INTR_REG = intr_status;
////    }
////    
//
///* [] END OF FILE */
//