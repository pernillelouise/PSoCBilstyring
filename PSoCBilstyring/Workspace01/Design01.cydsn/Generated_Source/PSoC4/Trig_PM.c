/*******************************************************************************
* File Name: Trig.c  
* Version 2.20
*
* Description:
*  This file contains APIs to set up the Pins component for low power modes.
*
* Note:
*
********************************************************************************
* Copyright 2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "cytypes.h"
#include "Trig.h"

static Trig_BACKUP_STRUCT  Trig_backup = {0u, 0u, 0u};


/*******************************************************************************
* Function Name: Trig_Sleep
****************************************************************************//**
*
* \brief Stores the pin configuration and prepares the pin for entering chip 
*  deep-sleep/hibernate modes. This function must be called for SIO and USBIO
*  pins. It is not essential if using GPIO or GPIO_OVT pins.
*
* <b>Note</b> This function is available in PSoC 4 only.
*
* \return 
*  None 
*  
* \sideeffect
*  For SIO pins, this function configures the pin input threshold to CMOS and
*  drive level to Vddio. This is needed for SIO pins when in device 
*  deep-sleep/hibernate modes.
*
* \funcusage
*  \snippet Trig_SUT.c usage_Trig_Sleep_Wakeup
*******************************************************************************/
void Trig_Sleep(void)
{
    #if defined(Trig__PC)
        Trig_backup.pcState = Trig_PC;
    #else
        #if (CY_PSOC4_4200L)
            /* Save the regulator state and put the PHY into suspend mode */
            Trig_backup.usbState = Trig_CR1_REG;
            Trig_USB_POWER_REG |= Trig_USBIO_ENTER_SLEEP;
            Trig_CR1_REG &= Trig_USBIO_CR1_OFF;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(Trig__SIO)
        Trig_backup.sioState = Trig_SIO_REG;
        /* SIO requires unregulated output buffer and single ended input buffer */
        Trig_SIO_REG &= (uint32)(~Trig_SIO_LPM_MASK);
    #endif  
}


/*******************************************************************************
* Function Name: Trig_Wakeup
****************************************************************************//**
*
* \brief Restores the pin configuration that was saved during Pin_Sleep().
*
* For USBIO pins, the wakeup is only triggered for falling edge interrupts.
*
* <b>Note</b> This function is available in PSoC 4 only.
*
* \return 
*  None
*  
* \funcusage
*  Refer to Trig_Sleep() for an example usage.
*******************************************************************************/
void Trig_Wakeup(void)
{
    #if defined(Trig__PC)
        Trig_PC = Trig_backup.pcState;
    #else
        #if (CY_PSOC4_4200L)
            /* Restore the regulator state and come out of suspend mode */
            Trig_USB_POWER_REG &= Trig_USBIO_EXIT_SLEEP_PH1;
            Trig_CR1_REG = Trig_backup.usbState;
            Trig_USB_POWER_REG &= Trig_USBIO_EXIT_SLEEP_PH2;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(Trig__SIO)
        Trig_SIO_REG = Trig_backup.sioState;
    #endif
}


/* [] END OF FILE */
