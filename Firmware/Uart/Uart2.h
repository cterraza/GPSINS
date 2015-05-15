/**
 * @file Uart1.h
 * @brief UART library for dsPIC33EP.
 */

#ifndef UART2_H
#define UART2_H

//------------------------------------------------------------------------------
// Includes

#include "stdbool.h" // bool, true, false
#include <stddef.h> // size_t
#include "UartCommon.h"

//------------------------------------------------------------------------------
// Function prototypes

void Uart2Initialise(const UartSettings * const uartSettings);
void Uart2Disable();
size_t Uart2IsGetReady();
char Uart2GetChar();
size_t Uart2IsPutReady();
void Uart2PutChar(const char byte);
int Uart2PutCharArray(const char* const source, const size_t numberOfBytes);
void Uart2PutString(const char* string);
void Uart2ClearRxBuffer();
void Uart2ClearTxBuffer();
bool Uart2GetRxBufferOverrunFlag();
void Uart1ClearRxBufferOverrunFlag();
bool Uart1TxIsIdle();

#endif

//------------------------------------------------------------------------------
// End of file
