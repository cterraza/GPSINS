/**
 * @file SystemDefinitions.h
 * @author XXXXXXXXXX
 * @brief Global system definitions.  All I/O pin assignments and timing
 * calculations must be derived from this file.
 */

#ifndef SYSTEM_DEFINITIONS_H
#define SYSTEM_DEFINITIONS_H

//------------------------------------------------------------------------------
// Includes

#include <xc.h>



//------------------------------------------------------------------------------
// Definitions - System clock

#define FOSC    140000000ul
#define FP      (FOSC >> 1)
#define FCY     FP 

#include <libpic30.h>        // __delayXXX() functions macros defined here

//------------------------------------------------------------------------------
// Definitions - I/O assignments

// IMU
#define IMU_INT_MAP()   _INT1R = 0

// UART1
#define UART1_RX_MAP()   _U1RXR = 44
#define UART1_TX_MAP()   _RP43R = 0b000001

// UART2
#define UART2_RX_MAP()   _U2RXR = 24
#define UART2_TX_MAP()   _RP36R = 0b000011


// LED1
#define LED1_TRIS       _TRISA4
#define LED1_LAT        _LATA4

// LED2
#define LED2_TRIS       _TRISA9
#define LED2_LAT        _LATA9


//------------------------------------------------------------------------------
// Definitions - Firmware version

#define FIRMWARE_VERSION "v0.0" " (" __DATE__ " " __TIME__ ")"

#endif

//------------------------------------------------------------------------------
// End of file
