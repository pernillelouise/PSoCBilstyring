/*******************************************************************************
* File Name: PWM_venstre_PM.c
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

#include "PWM_venstre.h"

static PWM_venstre_backupStruct PWM_venstre_backup;


/*******************************************************************************
* Function Name: PWM_venstre_SaveConfig
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
*  PWM_venstre_backup:  Variables of this global structure are modified to
*  store the values of non retention configuration registers when Sleep() API is
*  called.
*
*******************************************************************************/
void PWM_venstre_SaveConfig(void) 
{

    #if(!PWM_venstre_UsingFixedFunction)
        #if(!PWM_venstre_PWMModeIsCenterAligned)
            PWM_venstre_backup.PWMPeriod = PWM_venstre_ReadPeriod();
        #endif /* (!PWM_venstre_PWMModeIsCenterAligned) */
        PWM_venstre_backup.PWMUdb = PWM_venstre_ReadCounter();
        #if (PWM_venstre_UseStatus)
            PWM_venstre_backup.InterruptMaskValue = PWM_venstre_STATUS_MASK;
        #endif /* (PWM_venstre_UseStatus) */

        #if(PWM_venstre_DeadBandMode == PWM_venstre__B_PWM__DBM_256_CLOCKS || \
            PWM_venstre_DeadBandMode == PWM_venstre__B_PWM__DBM_2_4_CLOCKS)
            PWM_venstre_backup.PWMdeadBandValue = PWM_venstre_ReadDeadTime();
        #endif /*  deadband count is either 2-4 clocks or 256 clocks */

        #if(PWM_venstre_KillModeMinTime)
             PWM_venstre_backup.PWMKillCounterPeriod = PWM_venstre_ReadKillTime();
        #endif /* (PWM_venstre_KillModeMinTime) */

        #if(PWM_venstre_UseControl)
            PWM_venstre_backup.PWMControlRegister = PWM_venstre_ReadControlRegister();
        #endif /* (PWM_venstre_UseControl) */
    #endif  /* (!PWM_venstre_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: PWM_venstre_RestoreConfig
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
*  PWM_venstre_backup:  Variables of this global structure are used to
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void PWM_venstre_RestoreConfig(void) 
{
        #if(!PWM_venstre_UsingFixedFunction)
            #if(!PWM_venstre_PWMModeIsCenterAligned)
                PWM_venstre_WritePeriod(PWM_venstre_backup.PWMPeriod);
            #endif /* (!PWM_venstre_PWMModeIsCenterAligned) */

            PWM_venstre_WriteCounter(PWM_venstre_backup.PWMUdb);

            #if (PWM_venstre_UseStatus)
                PWM_venstre_STATUS_MASK = PWM_venstre_backup.InterruptMaskValue;
            #endif /* (PWM_venstre_UseStatus) */

            #if(PWM_venstre_DeadBandMode == PWM_venstre__B_PWM__DBM_256_CLOCKS || \
                PWM_venstre_DeadBandMode == PWM_venstre__B_PWM__DBM_2_4_CLOCKS)
                PWM_venstre_WriteDeadTime(PWM_venstre_backup.PWMdeadBandValue);
            #endif /* deadband count is either 2-4 clocks or 256 clocks */

            #if(PWM_venstre_KillModeMinTime)
                PWM_venstre_WriteKillTime(PWM_venstre_backup.PWMKillCounterPeriod);
            #endif /* (PWM_venstre_KillModeMinTime) */

            #if(PWM_venstre_UseControl)
                PWM_venstre_WriteControlRegister(PWM_venstre_backup.PWMControlRegister);
            #endif /* (PWM_venstre_UseControl) */
        #endif  /* (!PWM_venstre_UsingFixedFunction) */
    }


/*******************************************************************************
* Function Name: PWM_venstre_Sleep
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
*  PWM_venstre_backup.PWMEnableState:  Is modified depending on the enable
*  state of the block before entering sleep mode.
*
*******************************************************************************/
void PWM_venstre_Sleep(void) 
{
    #if(PWM_venstre_UseControl)
        if(PWM_venstre_CTRL_ENABLE == (PWM_venstre_CONTROL & PWM_venstre_CTRL_ENABLE))
        {
            /*Component is enabled */
            PWM_venstre_backup.PWMEnableState = 1u;
        }
        else
        {
            /* Component is disabled */
            PWM_venstre_backup.PWMEnableState = 0u;
        }
    #endif /* (PWM_venstre_UseControl) */

    /* Stop component */
    PWM_venstre_Stop();

    /* Save registers configuration */
    PWM_venstre_SaveConfig();
}


/*******************************************************************************
* Function Name: PWM_venstre_Wakeup
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
*  PWM_venstre_backup.pwmEnable:  Is used to restore the enable state of
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void PWM_venstre_Wakeup(void) 
{
     /* Restore registers values */
    PWM_venstre_RestoreConfig();

    if(PWM_venstre_backup.PWMEnableState != 0u)
    {
        /* Enable component's operation */
        PWM_venstre_Enable();
    } /* Do nothing if component's block was disabled before */

}


/* [] END OF FILE */
