/**
 * @file UartCommon.h
 * @author Seb Madgwick
 * @brief UART library for dsPIC33EP.
 */

#ifndef UART_COMMON_H
#define UART_COMMON_H

//------------------------------------------------------------------------------
// Includes

#include "stdbool.h" // bool, true, false
#include <stdint.h> // uint16_t, uint32_t
#include "SystemDefinitions.h" // PBCLK

//------------------------------------------------------------------------------
// Definitions

/**
 * @brief UART parity and data enumeration.  Values equal to PDSEL bits of
 * UxMODE register.
 */
typedef enum {
    EightBitNoParity,
    EightBitEvenParity,
    EightBitOddParity,
    NineBitNoParity,
} UartParityAndData;

/**
 * @brief UART stop bits enumeration.  Values equal to STSEL bits of UxMODE
 * register.
 */
typedef enum {
    OneStopBit,
    TwoStopBits,
} UartStopBits;

/**
 * @brief UART settings structure.
 */
typedef struct {
    uint32_t baudRate;
    bool ctsRtsEnabled;
    UartParityAndData parityAndData;
    UartStopBits stopBits;
    bool invertDataLines;
} UartSettings;

/**
 * @brief Default UART settings.  Can be used to initialised a UartSettings
 * structure.
 */
#define DEFAULT_UART_SETTINGS ((UartSettings) { \
        .baudRate = 115200, \
        .ctsRtsEnabled = false, \
        .parityAndData = EightBitNoParity, \
        .stopBits = OneStopBit, \
        .invertDataLines = false })

/**
 * @brief Calculates ideal UXBRG value as a float for a specified baud rate and
 * defined instruction cycle clock frequency (FP).  Assumes BRGH = 0.
 * @see Page 12 of chapter "Universal Asynchronous Receiver Transmitter (UART)"
 * in the "dsPIC33/PIC24 Family Reference Manual".
 */
#define CALCULATE_UXBRG_FLOAT(baudRate) ((float) FP / (4.0f * (float) baudRate) - 1.0f)

/**
 * @brief Calculates UXBRG value as the rounded result of CALCULATE_UXBRG_FLOAT
 * for a specified baud rate and defined instruction cycle clock frequency (FP).
 */
#define CALCULATE_UXBRG(baudRate) ((uint16_t) (CALCULATE_UXBRG_FLOAT(baudRate) + 0.5f))

/**
 * @brief Calculates baud rate percentage error for a specified baud rate and
 * defined peripheral clock (FP).
 */
#define CALCULATE_UART_BAUD_ERROR(baudRate) (100.0f * ((float) CALCULATE_UXBRG(baudRate) / CALCULATE_UXBRG_FLOAT(baudRate)) - 100.0f)

#endif

//------------------------------------------------------------------------------
// End of file
