/*******************************************************************************
* File Name: .h
* Version 3.10
*
* Description:
*  This private file provides constants and parameter values for the
*  SCB Component.
*  Please do not use this file or its content in your project.
*
* Note:
*
********************************************************************************
* Copyright 2013-2015, Cypress Semiconductor Corporation. All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_SCB_PVT_UART_print_H)
#define CY_SCB_PVT_UART_print_H

#include "UART_print.h"


/***************************************
*     Private Function Prototypes
***************************************/

/* APIs to service INTR_I2C_EC register */
#define UART_print_SetI2CExtClkInterruptMode(interruptMask) UART_print_WRITE_INTR_I2C_EC_MASK(interruptMask)
#define UART_print_ClearI2CExtClkInterruptSource(interruptMask) UART_print_CLEAR_INTR_I2C_EC(interruptMask)
#define UART_print_GetI2CExtClkInterruptSource()                (UART_print_INTR_I2C_EC_REG)
#define UART_print_GetI2CExtClkInterruptMode()                  (UART_print_INTR_I2C_EC_MASK_REG)
#define UART_print_GetI2CExtClkInterruptSourceMasked()          (UART_print_INTR_I2C_EC_MASKED_REG)

#if (!UART_print_CY_SCBIP_V1)
    /* APIs to service INTR_SPI_EC register */
    #define UART_print_SetSpiExtClkInterruptMode(interruptMask) \
                                                                UART_print_WRITE_INTR_SPI_EC_MASK(interruptMask)
    #define UART_print_ClearSpiExtClkInterruptSource(interruptMask) \
                                                                UART_print_CLEAR_INTR_SPI_EC(interruptMask)
    #define UART_print_GetExtSpiClkInterruptSource()                 (UART_print_INTR_SPI_EC_REG)
    #define UART_print_GetExtSpiClkInterruptMode()                   (UART_print_INTR_SPI_EC_MASK_REG)
    #define UART_print_GetExtSpiClkInterruptSourceMasked()           (UART_print_INTR_SPI_EC_MASKED_REG)
#endif /* (!UART_print_CY_SCBIP_V1) */

#if(UART_print_SCB_MODE_UNCONFIG_CONST_CFG)
    extern void UART_print_SetPins(uint32 mode, uint32 subMode, uint32 uartEnableMask);
#endif /* (UART_print_SCB_MODE_UNCONFIG_CONST_CFG) */


/***************************************
*     Vars with External Linkage
***************************************/

#if (UART_print_SCB_IRQ_INTERNAL)
#if !defined (CY_REMOVE_UART_print_CUSTOM_INTR_HANDLER)
    extern cyisraddress UART_print_customIntrHandler;
#endif /* !defined (CY_REMOVE_UART_print_CUSTOM_INTR_HANDLER) */
#endif /* (UART_print_SCB_IRQ_INTERNAL) */

extern UART_print_BACKUP_STRUCT UART_print_backup;

#if(UART_print_SCB_MODE_UNCONFIG_CONST_CFG)
    /* Common configuration variables */
    extern uint8 UART_print_scbMode;
    extern uint8 UART_print_scbEnableWake;
    extern uint8 UART_print_scbEnableIntr;

    /* I2C configuration variables */
    extern uint8 UART_print_mode;
    extern uint8 UART_print_acceptAddr;

    /* SPI/UART configuration variables */
    extern volatile uint8 * UART_print_rxBuffer;
    extern uint8   UART_print_rxDataBits;
    extern uint32  UART_print_rxBufferSize;

    extern volatile uint8 * UART_print_txBuffer;
    extern uint8   UART_print_txDataBits;
    extern uint32  UART_print_txBufferSize;

    /* EZI2C configuration variables */
    extern uint8 UART_print_numberOfAddr;
    extern uint8 UART_print_subAddrSize;
#endif /* (UART_print_SCB_MODE_UNCONFIG_CONST_CFG) */


/***************************************
*        Conditional Macro
****************************************/

#if(UART_print_SCB_MODE_UNCONFIG_CONST_CFG)
    /* Defines run time operation mode */
    #define UART_print_SCB_MODE_I2C_RUNTM_CFG     (UART_print_SCB_MODE_I2C      == UART_print_scbMode)
    #define UART_print_SCB_MODE_SPI_RUNTM_CFG     (UART_print_SCB_MODE_SPI      == UART_print_scbMode)
    #define UART_print_SCB_MODE_UART_RUNTM_CFG    (UART_print_SCB_MODE_UART     == UART_print_scbMode)
    #define UART_print_SCB_MODE_EZI2C_RUNTM_CFG   (UART_print_SCB_MODE_EZI2C    == UART_print_scbMode)
    #define UART_print_SCB_MODE_UNCONFIG_RUNTM_CFG \
                                                        (UART_print_SCB_MODE_UNCONFIG == UART_print_scbMode)

    /* Defines wakeup enable */
    #define UART_print_SCB_WAKE_ENABLE_CHECK       (0u != UART_print_scbEnableWake)
#endif /* (UART_print_SCB_MODE_UNCONFIG_CONST_CFG) */

/* Defines maximum number of SCB pins */
#if (!UART_print_CY_SCBIP_V1)
    #define UART_print_SCB_PINS_NUMBER    (7u)
#else
    #define UART_print_SCB_PINS_NUMBER    (2u)
#endif /* (!UART_print_CY_SCBIP_V1) */

#endif /* (CY_SCB_PVT_UART_print_H) */


/* [] END OF FILE */
