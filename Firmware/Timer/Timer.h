/**
 * @file Timer.h
 * @author Seb Madgwick
 * @brief Timer library for dsPIC33EP.
 */

#ifndef TIMER_H
#define TIMER_H

//------------------------------------------------------------------------------
// Includes

#include <stdint.h> // uint16_t, uint32_t, uint64_t
#include "SystemDefinitions.h" // FCY

//------------------------------------------------------------------------------
// Definitions

/**
 * @bief Number of timer ticks per second.  Necessary for timing calculations.
 */
#define TIMER_TICKS_PER_SECOND FCY

/**
 * @brief 32-bit timer ticks type.
 */
typedef union {
    uint32_t value;

    struct {
        uint16_t word0; // least-significant word
        uint16_t word1; // most-significant word
    };
} Ticks32;

/**
 * @brief 64-bit timer ticks type.
 */
typedef union {
    uint64_t value;

    struct {
        uint16_t word0; // least-significant word
        uint16_t word1;
        uint16_t word2;
        uint16_t word3; // most-significant word
    };

    struct {

        union {
            uint32_t dword0;
            Ticks32 ticks32;
        }; // least-significant dword
        uint32_t dword1; // most-significant dword
    };
} Ticks64;

//------------------------------------------------------------------------------
// Function prototypes

void TimerInitialise();
void TimerDisable();
Ticks32 TimerGetTicks32();
Ticks64 TimerGetTicks64();
void TimerDelay(uint32_t milliseconds);

#endif

//------------------------------------------------------------------------------
// End of file
