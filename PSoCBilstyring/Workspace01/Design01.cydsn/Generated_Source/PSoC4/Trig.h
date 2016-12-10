/*******************************************************************************
* File Name: Trig.h  
* Version 2.20
*
* Description:
*  This file contains Pin function prototypes and register defines
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_Trig_H) /* Pins Trig_H */
#define CY_PINS_Trig_H

#include "cytypes.h"
#include "cyfitter.h"
#include "Trig_aliases.h"


/***************************************
*     Data Struct Definitions
***************************************/

/**
* \addtogroup group_structures
* @{
*/
    
/* Structure for sleep mode support */
typedef struct
{
    uint32 pcState; /**< State of the port control register */
    uint32 sioState; /**< State of the SIO configuration */
    uint32 usbState; /**< State of the USBIO regulator */
} Trig_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   Trig_Read(void);
void    Trig_Write(uint8 value);
uint8   Trig_ReadDataReg(void);
#if defined(Trig__PC) || (CY_PSOC4_4200L) 
    void    Trig_SetDriveMode(uint8 mode);
#endif
void    Trig_SetInterruptMode(uint16 position, uint16 mode);
uint8   Trig_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void Trig_Sleep(void); 
void Trig_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(Trig__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define Trig_DRIVE_MODE_BITS        (3)
    #define Trig_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - Trig_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the Trig_SetDriveMode() function.
         *  @{
         */
        #define Trig_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define Trig_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define Trig_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define Trig_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define Trig_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define Trig_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define Trig_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define Trig_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define Trig_MASK               Trig__MASK
#define Trig_SHIFT              Trig__SHIFT
#define Trig_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in Trig_SetInterruptMode() function.
     *  @{
     */
        #define Trig_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define Trig_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define Trig_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define Trig_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(Trig__SIO)
    #define Trig_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(Trig__PC) && (CY_PSOC4_4200L)
    #define Trig_USBIO_ENABLE               ((uint32)0x80000000u)
    #define Trig_USBIO_DISABLE              ((uint32)(~Trig_USBIO_ENABLE))
    #define Trig_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define Trig_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define Trig_USBIO_ENTER_SLEEP          ((uint32)((1u << Trig_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << Trig_USBIO_SUSPEND_DEL_SHIFT)))
    #define Trig_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << Trig_USBIO_SUSPEND_SHIFT)))
    #define Trig_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << Trig_USBIO_SUSPEND_DEL_SHIFT)))
    #define Trig_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(Trig__PC)
    /* Port Configuration */
    #define Trig_PC                 (* (reg32 *) Trig__PC)
#endif
/* Pin State */
#define Trig_PS                     (* (reg32 *) Trig__PS)
/* Data Register */
#define Trig_DR                     (* (reg32 *) Trig__DR)
/* Input Buffer Disable Override */
#define Trig_INP_DIS                (* (reg32 *) Trig__PC2)

/* Interrupt configuration Registers */
#define Trig_INTCFG                 (* (reg32 *) Trig__INTCFG)
#define Trig_INTSTAT                (* (reg32 *) Trig__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define Trig_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(Trig__SIO)
    #define Trig_SIO_REG            (* (reg32 *) Trig__SIO)
#endif /* (Trig__SIO_CFG) */

/* USBIO registers */
#if !defined(Trig__PC) && (CY_PSOC4_4200L)
    #define Trig_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define Trig_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define Trig_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define Trig_DRIVE_MODE_SHIFT       (0x00u)
#define Trig_DRIVE_MODE_MASK        (0x07u << Trig_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins Trig_H */


/* [] END OF FILE */
