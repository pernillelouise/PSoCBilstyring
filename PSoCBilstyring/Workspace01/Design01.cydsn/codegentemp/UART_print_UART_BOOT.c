/*******************************************************************************
* File Name: UART_print_UART_BOOT.c
* Version 3.10
*
* Description:
*  This file provides the source code of the bootloader communication APIs
*  for the SCB Component UART mode.
*
* Note:
*
********************************************************************************
* Copyright 2013-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "UART_print_BOOT.h"
#include "UART_print_SPI_UART.h"

#if defined(CYDEV_BOOTLOADER_IO_COMP) && (UART_print_UART_BTLDR_COMM_ENABLED)

/*******************************************************************************
* Function Name: UART_print_UartCyBtldrCommStart
********************************************************************************
*
* Summary:
*  Starts the UART component.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void UART_print_UartCyBtldrCommStart(void)
{
    UART_print_Start();
}


/*******************************************************************************
* Function Name: UART_print_UartCyBtldrCommStop
********************************************************************************
*
* Summary:
*  Disables the UART component.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void UART_print_UartCyBtldrCommStop(void)
{
    UART_print_Stop();
}


/*******************************************************************************
* Function Name: UART_print_UartCyBtldrCommReset
********************************************************************************
*
* Summary:
*  Resets the receive and transmit communication buffers.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void UART_print_UartCyBtldrCommReset(void)
{
    /* Clear RX and TX buffers */
    UART_print_SpiUartClearRxBuffer();
    UART_print_SpiUartClearTxBuffer();
}


/*******************************************************************************
* Function Name: UART_print_UartCyBtldrCommRead
********************************************************************************
*
* Summary:
*  Allows the caller to read data from the bootloader host (the host writes the
*  data). The function handles polling to allow a block of data to be completely
*  received from the host device.
*
* Parameters:
*  pData:    Pointer to storage for the block of data to be read from the
*            bootloader host
*  size:     Number of bytes to be read.
*  count:    Pointer to the variable to write the number of bytes actually
*            read.
*  timeOut:  Number of units in 10 ms to wait before returning because of a
*            timeout.
*
* Return:
*  Returns CYRET_SUCCESS if no problem was encountered or returns the value
*  that best describes the problem. For more information refer to the
*  "Return Codes" section of the System Reference Guide.
*
*******************************************************************************/
cystatus UART_print_UartCyBtldrCommRead(uint8 pData[], uint16 size, uint16 * count, uint8 timeOut)
{
    cystatus status;
    uint32 byteCount;
    uint32 timeoutMs;
    uint32 i;

    status = CYRET_BAD_PARAM;

    if ((NULL != pData) && (size > 0u))
    {
        status = CYRET_TIMEOUT;
        timeoutMs = ((uint32) 10u * timeOut); /* Convert from 10mS check to 1mS checks */

        /* Wait with timeout 1mS for packet end */
        byteCount = 0u;
        do
        {
            /* Check packet start */
            if (0u != UART_print_SpiUartGetRxBufferSize())
            {
                /* Wait for end of packet */
                do
                {
                    byteCount = UART_print_SpiUartGetRxBufferSize();
                    CyDelayUs(UART_print_UART_BYTE_TO_BYTE);
                }
                while (byteCount != UART_print_SpiUartGetRxBufferSize());

                byteCount = UART_print_BYTES_TO_COPY(byteCount, size);
                *count = (uint16) byteCount;
                status = CYRET_SUCCESS;

                break;
            }

            CyDelay(UART_print_WAIT_1_MS);
            --timeoutMs;
        }
        while (0u != timeoutMs);

        /* Get data from RX buffer into bootloader buffer */
        for (i = 0u; i < byteCount; ++i)
        {
            pData[i] = (uint8) UART_print_SpiUartReadRxData();
        }
    }

    return (status);
}


/*******************************************************************************
* Function Name: UART_print_UartCyBtldrCommWrite
********************************************************************************
*
* Summary:
*  Allows the caller to write data to the bootloader host (the host reads the
*  data). The function does not use timeout and returns after data has been
*  copied into the transmit buffer. The data transmission starts immediately
*  after the first data element is written into the buffer and lasts until all
*  data elements from the buffer are sent.
*
* Parameters:
*  pData:    Pointer to the block of data to be written to the bootloader host.
*  size:     Number of bytes to be written.
*  count:    Pointer to the variable to write the number of bytes actually
*            written.
*  timeOut:  The timeout is not used by this function. The function returns
*            as soon as data is copied into the transmit buffer.
*
* Return:
*  Returns CYRET_SUCCESS if no problem was encountered or returns the value
*  that best describes the problem. For more information refer to the
*  "Return Codes" section of the System Reference Guide.
*
*******************************************************************************/
cystatus UART_print_UartCyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut)
{
    cystatus status;

    status = CYRET_BAD_PARAM;

    if ((NULL != pData) && (size > 0u))
    {
        /* Transmit data. This function does not wait until data is sent. */
        UART_print_SpiUartPutArray(pData, (uint32) size);

        *count = size;
        status = CYRET_SUCCESS;

        if (0u != timeOut)
        {
            /* Suppress compiler warning */
        }
    }

    return (status);
}

#endif /* defined(CYDEV_BOOTLOADER_IO_COMP) && (UART_print_UART_BTLDR_COMM_ENABLED) */


/* [] END OF FILE */
