/**
 * @file Timer.c
 * @author Seb Madgwick
 * @brief Timer library for dsPIC33EP.
 *
 * Provides measurements of time in processor ticks where one tick = 14.286 ns
 * for FCY = 70 MIPS.  Ticks32 overflows every 61.357 seconds.  Ticks64
 * overflows every 8350.772 years.
 */

//------------------------------------------------------------------------------
// Includes

#include <stdint.h> // UINT32_MAX
#include "Timer.h"
#include <xc.h>

//------------------------------------------------------------------------------
// Variable declarations

static volatile Ticks64 timerOverflowCounter;

//------------------------------------------------------------------------------
// Functions

/**
 * @brief Initialises module.  This function should be called once on system
 * start up.
 */
void TimerInitialise() {

    // Enable peripheral
    PMD1bits.T4MD = 0;
    PMD1bits.T5MD = 0;

    // Setup 32-bit timer
    T4CONbits.T32 = 1;
    T4CONbits.TON = 1; // start timer
    _T5IP = 5; // set interrupt priority
    _T5IF = 0; // clear interrupt flag
    _T5IE = 1; // enable interrupt
}

/**
 * @brief Disables the module for minimal power consumption.
 */
void TimerDisable() {

    // Disable timer
    T4CONbits.TON = 0; // stop timer
    _T5IE = 0; // disable interrupt

    // Disable peripheral
    PMD1bits.T4MD = 1;
    PMD1bits.T5MD = 1;
}

/**
 * @brief Gets 32-bit timer value.  This function call is quicker than
 * TimerGetTicks64 and so may be preferable if the 32-bit ticks overflow period
 * is not too short.
 * @return 32-bit timer value.
 */
Ticks32 TimerGetTicks32() {
    Ticks32 ticks32;
    ticks32.word0 = TMR4;
    ticks32.word1 = TMR5HLD;
    return ticks32;
}

/**
 * @brief Gets 64-bit timer value.
 * @return 64-bit timer value.
 */
Ticks64 TimerGetTicks64() {
    Ticks64 sampledTimerOverflowCounter;
    Ticks64 ticks64;
    do {
        sampledTimerOverflowCounter = timerOverflowCounter;
        ticks64.word0 = TMR4;
        ticks64.word1 = TMR5HLD;
        ticks64.dword1 = 0;
    } while (sampledTimerOverflowCounter.dword0 != timerOverflowCounter.dword0); // avoid seconds overflow hazard
    ticks64.value += sampledTimerOverflowCounter.value;
    return ticks64;
}

/**
 * @brief Bocking delay in milliseconds.
 * @param milliseconds Delay in milliseconds.
 */
void TimerDelay(uint32_t milliseconds) {
    Ticks64 previousTicks = TimerGetTicks64();
    Ticks64 newTicks;
    do {
        newTicks = TimerGetTicks64();
    } while (newTicks.value - previousTicks.value < (milliseconds * (TIMER_TICKS_PER_SECOND / 1000)));
}

//------------------------------------------------------------------------------
// Functions - Interrupts

/**
 * @brief Timer overflow interrupt to increment overflow counter.
 */
void __attribute__((interrupt, auto_psv))_T5Interrupt(void) {
    timerOverflowCounter.value += (uint64_t) UINT32_MAX;
    _T5IF = 0; // clear interrupt flag
}

//------------------------------------------------------------------------------
// End of file
