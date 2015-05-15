/**
 * @file I2C1.h
 * @author Seb Madgwick
 * @brief I2C master library for dsPIC33EP.
 */

#ifndef I2C1_H
#define I2C1_H

//------------------------------------------------------------------------------
// Includes

#include "I2CCommon.h"
#include "I2CScript.h"
#include "stdbool.h" // bool
#include <stdint.h> // uint32_t

//------------------------------------------------------------------------------
// Function prototypes

void I2C1Initialise(const uint32_t baud);
void I2C1Disable();
void I2C1Start();
void I2C1Restart();
void I2C1Stop();
void I2C1Send(char byte);
bool I2C1AckFailed();
char I2C1Receive();
void I2C1Ack();
void I2C1Nack();
int I2C1RunScript(I2CScript * const i2cScript);
bool I2C1IsScriptRunning();

#endif

//------------------------------------------------------------------------------
// End of file