/*
 * @file Send.c
 * @author Seb Madgwick
 * @brief Application tasks and functions for sending messages.
 */
//------------------------------------------------------------------------------
// Includes

#include "Imu/Imu.h"
#include "Send.h"
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
        SendMeasurements();
    }
}

/**
 * @brief Sends current encoder and IMU measurements.
 */
static void SendMeasurements() {
    char string[1024];
    ImuMeasurement imuMeasurement;
    ImuGetMeasurement(&imuMeasurement);
    sprintf(string, "%ld,%ld,%ld\r\n",
            (int32_t) (100.0f * imuMeasurement.azimuth),
            (int32_t) (100.0f * imuMeasurement.elevation),
            (int32_t) (100.0f * imuMeasurement.angularVelocityNorm));
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
