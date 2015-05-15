/**
 * @file Uart1.h
 * @brief UART library for dsPIC33EP.
 */

#ifndef UART1_H
#define UART1_H

//------------------------------------------------------------------------------
// Includes

#include "stdbool.h" // bool, true, false
#include <stddef.h> // size_t
#include "UartCommon.h"

//------------------------------------------------------------------------------
// Function prototypes

void Uart1Initialise(const UartSettings * const uartSettings);
void Uart1Disable();
size_t Uart1IsGetReady();
char Uart1GetChar();
size_t Uart1IsPutReady();
void Uart1PutChar(const char byte);
int Uart1PutCharArray(const char* const source, const size_t numberOfBytes);
void Uart1PutString(const char* string);
void Uart1ClearRxBuffer();
void Uart1ClearTxBuffer();
bool Uart1GetRxBufferOverrunFlag();
void Uart1ClearRxBufferOverrunFlag();
bool Uart1TxIsIdle();

#endif

//------------------------------------------------------------------------------
// End of file
