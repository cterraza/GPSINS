/*
 * @file Send.c
 * @author Seb Madgwick
 * @brief Application tasks and functions for sending messages.
 */
//------------------------------------------------------------------------------
// Includes

#include <stdint.h> // int32_t
#include <stdio.h> // sprintf
#include <string.h> // strcpy, strcat
#include "SystemDefinitions.h" // TEST_LAT
#include "Timer/Timer.h"
#include "Uart/Uart1.h"
#include "Uart/Uart2.h"
#include <xc.h>

//------------------------------------------------------------------------------
// Definitions

#define SEND_FREQUENCY  50 // messages per second

//------------------------------------------------------------------------------
// Function prototypes

static void SendMeasurements();

//------------------------------------------------------------------------------
// Functions

/**
 * @brief Do tasks.  This function should be called repeatedly within the main
 * program loop.
 */
void SendDoTasks() {
    const Ticks32 currentTicks = TimerGetTicks32();
    static Ticks32 previousTicks;
    if ((currentTicks.value - previousTicks.value) >= (TIMER_TICKS_PER_SECOND / SEND_FREQUENCY)) {
        previousTicks = currentTicks;
    }
}


void SendGPS() {
    char string[80];
    //sprintf(string, "Altura: %4.1f\r\n",GPS_altitude/100.0f);
    Uart1PutString(string);
}

/**
 * @brief Sends confirmation of zero.
 */
void SendZero() {
    Uart1PutString("Zero\r\n");
}

/**
 * @brief Sends confirmation of reset.
 */
void SendReset() {
    Uart1PutString("Reset\r\n");
}

/**
 * @brief Sends firmware version.
 */
void SendFirmwareVersion() {
    char string[64];
    strcpy(string, "Firmware ");
    strcat(string, FIRMWARE_VERSION);
    strcat(string, "\r\n");
    Uart1PutString(string);
}

//------------------------------------------------------------------------------
// End of file
