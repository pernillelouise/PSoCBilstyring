/*******************************************************************************
* File Name: PWM_hojre_PM.c
* Version 3.30
*
* Description:
*  This file provides the power management source code to API for the
*  PWM.
*
* Note:
*
********************************************************************************
* Copyright 2008-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "PWM_hojre.h"

static PWM_hojre_backupStruct PWM_hojre_backup;


/*******************************************************************************
* Function Name: PWM_hojre_SaveConfig
********************************************************************************
*
* Summary:
*  Saves the current user configuration of the component.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  PWM_hojre_backup:  Variables of this global structure are modified to
*  store the values of non retention configuration registers when Sleep() API is
*  called.
*
*******************************************************************************/
void PWM_hojre_SaveConfig(void) 
{

    #if(!PWM_hojre_UsingFixedFunction)
        #if(!PWM_hojre_PWMModeIsCenterAligned)
            PWM_hojre_backup.PWMPeriod = PWM_hojre_ReadPeriod();
        #endif /* (!PWM_hojre_PWMModeIsCenterAligned) */
        PWM_hojre_backup.PWMUdb = PWM_hojre_ReadCounter();
        #if (PWM_hojre_UseStatus)
            PWM_hojre_backup.InterruptMaskValue = PWM_hojre_STATUS_MASK;
        #endif /* (PWM_hojre_UseStatus) */

        #if(PWM_hojre_DeadBandMode == PWM_hojre__B_PWM__DBM_256_CLOCKS || \
            PWM_hojre_DeadBandMode == PWM_hojre__B_PWM__DBM_2_4_CLOCKS)
            PWM_hojre_backup.PWMdeadBandValue = PWM_hojre_ReadDeadTime();
        #endif /*  deadband count is either 2-4 clocks or 256 clocks */

        #if(PWM_hojre_KillModeMinTime)
             PWM_hojre_backup.PWMKillCounterPeriod = PWM_hojre_ReadKillTime();
        #endif /* (PWM_hojre_KillModeMinTime) */

        #if(PWM_hojre_UseControl)
            PWM_hojre_backup.PWMControlRegister = PWM_hojre_ReadControlRegister();
        #endif /* (PWM_hojre_UseControl) */
    #endif  /* (!PWM_hojre_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: PWM_hojre_RestoreConfig
********************************************************************************
*
* Summary:
*  Restores the current user configuration of the component.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  PWM_hojre_backup:  Variables of this global structure are used to
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void PWM_hojre_RestoreConfig(void) 
{
        #if(!PWM_hojre_UsingFixedFunction)
            #if(!PWM_hojre_PWMModeIsCenterAligned)
                PWM_hojre_WritePeriod(PWM_hojre_backup.PWMPeriod);
            #endif /* (!PWM_hojre_PWMModeIsCenterAligned) */

            PWM_hojre_WriteCounter(PWM_hojre_backup.PWMUdb);

            #if (PWM_hojre_UseStatus)
                PWM_hojre_STATUS_MASK = PWM_hojre_backup.InterruptMaskValue;
            #endif /* (PWM_hojre_UseStatus) */

            #if(PWM_hojre_DeadBandMode == PWM_hojre__B_PWM__DBM_256_CLOCKS || \
                PWM_hojre_DeadBandMode == PWM_hojre__B_PWM__DBM_2_4_CLOCKS)
                PWM_hojre_WriteDeadTime(PWM_hojre_backup.PWMdeadBandValue);
            #endif /* deadband count is either 2-4 clocks or 256 clocks */

            #if(PWM_hojre_KillModeMinTime)
                PWM_hojre_WriteKillTime(PWM_hojre_backup.PWMKillCounterPeriod);
            #endif /* (PWM_hojre_KillModeMinTime) */

            #if(PWM_hojre_UseControl)
                PWM_hojre_WriteControlRegister(PWM_hojre_backup.PWMControlRegister);
            #endif /* (PWM_hojre_UseControl) */
        #endif  /* (!PWM_hojre_UsingFixedFunction) */
    }


/*******************************************************************************
* Function Name: PWM_hojre_Sleep
********************************************************************************
*
* Summary:
*  Disables block's operation and saves the user configuration. Should be called
*  just prior to entering sleep.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  PWM_hojre_backup.PWMEnableState:  Is modified depending on the enable
*  state of the block before entering sleep mode.
*
*******************************************************************************/
void PWM_hojre_Sleep(void) 
{
    #if(PWM_hojre_UseControl)
        if(PWM_hojre_CTRL_ENABLE == (PWM_hojre_CONTROL & PWM_hojre_CTRL_ENABLE))
        {
            /*Component is enabled */
            PWM_hojre_backup.PWMEnableState = 1u;
        }
        else
        {
            /* Component is disabled */
            PWM_hojre_backup.PWMEnableState = 0u;
        }
    #endif /* (PWM_hojre_UseControl) */

    /* Stop component */
    PWM_hojre_Stop();

    /* Save registers configuration */
    PWM_hojre_SaveConfig();
}


/*******************************************************************************
* Function Name: PWM_hojre_Wakeup
********************************************************************************
*
* Summary:
*  Restores and enables the user configuration. Should be called just after
*  awaking from sleep.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  PWM_hojre_backup.pwmEnable:  Is used to restore the enable state of
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void PWM_hojre_Wakeup(void) 
{
     /* Restore registers values */
    PWM_hojre_RestoreConfig();

    if(PWM_hojre_backup.PWMEnableState != 0u)
    {
        /* Enable component's operation */
        PWM_hojre_Enable();
    } /* Do nothing if component's block was disabled before */

}


/* [] END OF FILE */
