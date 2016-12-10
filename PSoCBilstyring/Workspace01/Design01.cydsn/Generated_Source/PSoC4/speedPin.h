/*******************************************************************************
* File Name: speedPin.h  
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

#if !defined(CY_PINS_speedPin_H) /* Pins speedPin_H */
#define CY_PINS_speedPin_H

#include "cytypes.h"
#include "cyfitter.h"
#include "speedPin_aliases.h"


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
} speedPin_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   speedPin_Read(void);
void    speedPin_Write(uint8 value);
uint8   speedPin_ReadDataReg(void);
#if defined(speedPin__PC) || (CY_PSOC4_4200L) 
    void    speedPin_SetDriveMode(uint8 mode);
#endif
void    speedPin_SetInterruptMode(uint16 position, uint16 mode);
uint8   speedPin_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void speedPin_Sleep(void); 
void speedPin_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(speedPin__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define speedPin_DRIVE_MODE_BITS        (3)
    #define speedPin_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - speedPin_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the speedPin_SetDriveMode() function.
         *  @{
         */
        #define speedPin_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define speedPin_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define speedPin_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define speedPin_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define speedPin_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define speedPin_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define speedPin_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define speedPin_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define speedPin_MASK               speedPin__MASK
#define speedPin_SHIFT              speedPin__SHIFT
#define speedPin_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in speedPin_SetInterruptMode() function.
     *  @{
     */
        #define speedPin_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define speedPin_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define speedPin_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define speedPin_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(speedPin__SIO)
    #define speedPin_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(speedPin__PC) && (CY_PSOC4_4200L)
    #define speedPin_USBIO_ENABLE               ((uint32)0x80000000u)
    #define speedPin_USBIO_DISABLE              ((uint32)(~speedPin_USBIO_ENABLE))
    #define speedPin_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define speedPin_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define speedPin_USBIO_ENTER_SLEEP          ((uint32)((1u << speedPin_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << speedPin_USBIO_SUSPEND_DEL_SHIFT)))
    #define speedPin_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << speedPin_USBIO_SUSPEND_SHIFT)))
    #define speedPin_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << speedPin_USBIO_SUSPEND_DEL_SHIFT)))
    #define speedPin_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(speedPin__PC)
    /* Port Configuration */
    #define speedPin_PC                 (* (reg32 *) speedPin__PC)
#endif
/* Pin State */
#define speedPin_PS                     (* (reg32 *) speedPin__PS)
/* Data Register */
#define speedPin_DR                     (* (reg32 *) speedPin__DR)
/* Input Buffer Disable Override */
#define speedPin_INP_DIS                (* (reg32 *) speedPin__PC2)

/* Interrupt configuration Registers */
#define speedPin_INTCFG                 (* (reg32 *) speedPin__INTCFG)
#define speedPin_INTSTAT                (* (reg32 *) speedPin__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define speedPin_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(speedPin__SIO)
    #define speedPin_SIO_REG            (* (reg32 *) speedPin__SIO)
#endif /* (speedPin__SIO_CFG) */

/* USBIO registers */
#if !defined(speedPin__PC) && (CY_PSOC4_4200L)
    #define speedPin_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define speedPin_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define speedPin_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define speedPin_DRIVE_MODE_SHIFT       (0x00u)
#define speedPin_DRIVE_MODE_MASK        (0x07u << speedPin_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins speedPin_H */


/* [] END OF FILE */
