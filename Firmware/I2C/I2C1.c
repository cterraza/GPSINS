/**
 * @file I2C1.c
 * @author Seb Madgwick
 * @brief I2C master library for dsPIC33EP.
 *
 * Communication may be achieved using either blocking functions or by composing
 * and then executing an interrupt serviced script.
 *
 * I2C1_INTERRUPT_PRIORITY may be changed as required by the application.
 */

//------------------------------------------------------------------------------
// Includes

#include "I2C1.h"
#include "I2CCommon.h"
#include <stddef.h> // NULL
#include <xc.h>

//------------------------------------------------------------------------------
// Definitions

#define I2C1_INTERRUPT_PRIORITY 4

//------------------------------------------------------------------------------
// Variables

static volatile I2CScript* i2cScriptAddress = NULL;

//------------------------------------------------------------------------------
// Functions

/**
 * @brief Initialises the I2C module.
 *
 * Initialises the I2C module in master mode with specified baud rate.  This
 * function can be used to reinitialise the module with new settings if it has
 * already been initialised.
 *
 * @param baud Baud rate.
 */
void I2C1Initialise(const uint32_t baud) {

    // Ensure default register states
    I2C1Disable();
    PMD1bits.I2C1MD = 0; // enable peripheral

    // Configure module
    I2C1BRG = CALCULATE_I2CXBRG(baud);
    _DISSLW = 1; // Slew rate control disabled
    _SMEN = 1; // Enable I/O pin thresholds compliant with SMBus specification
    _I2CEN = 1; // Enables the I2C module and configures the SDA and SCL pins as serial port pins
    _MI2C1IP = I2C1_INTERRUPT_PRIORITY; // set interrupt priority
}

/**
 * @brief Disable the I2C module.
 *
 * I2C registers are set to their default values.  All I2C pins are controlled
 * by PORT functions.  The peripheral is put in a minimum power consumption
 * state.
 */
void I2C1Disable() {
    I2C1CON = 0x0000;
    I2C1STAT = 0x0000;
    _MI2C1IE = 0; // disable interrupt
    _MI2C1IF = 0; // clear interrupt flag
    PMD1bits.I2C1MD = 1; // disable peripheral
}

/**
 * @brief Execute I2C start event.  This is a blocking function.
 */
void I2C1Start() {
    _SEN = 1;
    while (_SEN);
}

/**
 * @brief Execute I2C restart event.  This is a blocking function.
 */
void I2C1Restart() {
    _RSEN = 1;
    while (_RSEN);
}

/**
 * @brief Execute I2C stop event.  This is a blocking function.
 */
void I2C1Stop() {
    _PEN = 1;
    while (_PEN);
}

/**
 * @brief Execute I2C send event.  This is a blocking function.
 * @param byte Byte to send.
 */
void I2C1Send(char byte) {
    I2C1TRN = byte;
    while (I2C1STATbits.TRSTAT);
}

/**
 * @brief Returns true if the slave failed to acknowledge the I2C send.
 * @return True if the slave failed to acknowledge the I2C send.
 */
bool I2C1AckFailed() {
    return I2C1STATbits.ACKSTAT;
}

/**
 * @brief Execute I2C receive event.  This is a blocking function.
 */
char I2C1Receive() {
    _RCEN = 1;
    while (_RCEN);
    return I2C1RCV;
}

/**
 * @brief Execute I2C ACK event.  This is a blocking function.
 */
void I2C1Ack() {
    _ACKDT = 0;
    _ACKEN = 1;
    while (_ACKEN);
}

/**
 * @brief Execute I2C NACK event.  This is a blocking function.
 */
void I2C1Nack() {
    _ACKDT = 1;
    _ACKEN = 1;
    while (_ACKEN);
}

/**
 * @brief Runs interrupt serviced I2C script in background.  This function will
 * have no effect if the script if it is already running.
 * @param i2cScript Address of I2CScript.
 * @return 0 if successful.
 */
int I2C1RunScript(I2CScript * const i2cScript) {
    if (I2C1IsScriptRunning()) {
        return 1; // error: script is still running
    }
    i2cScriptAddress = i2cScript;
    i2cScript->index = 0;
    _MI2C1IF = 1; // set interrupt flag
    _MI2C1IE = 1; // enable interrupt
    return 0;
}

/**
 * @brief Returns true if interrupt serviced I2C script is still running.
 * @return True if interrupt serviced I2C script is still running.
 */
bool I2C1IsScriptRunning() {
    return _MI2C1IE;
}

//------------------------------------------------------------------------------
// Functions - Interrupt

/**
 * I2C interrupt service routine.
 */
void __attribute__((interrupt, auto_psv))_MI2C1Interrupt(void) {
    _MI2C1IF = 0; // clear interrupt flag
    const int index = i2cScriptAddress->index++;
    switch (i2cScriptAddress->command[index]) {
        case I2CScriptCommandStart:
            _SEN = 1;
            break;
        case I2CScriptCommandRestart:
            _RSEN = 1;
            break;
        case I2CScriptCommandStop:
            _PEN = 1;
            break;
        case I2CScriptCommandSend:
            I2C1TRN = i2cScriptAddress->data[index];
            break;
        case I2CScriptCommandReceive:
            _RCEN = 1;
            break;
        case I2CScriptCommandAck:
            *i2cScriptAddress->destination[index] = I2C1RCV;
            _ACKDT = 0;
            _ACKEN = 1;
            break;
        case I2CScriptCommandNack:
            *i2cScriptAddress->destination[index] = I2C1RCV;
            _ACKDT = 1;
            _ACKEN = 1;
            break;
        case I2CScriptCommandEndOfScript:
        default:
            _MI2C1IE = 0; // disable interrupts
            if (i2cScriptAddress->scriptCompleteTasks != NULL) {
                i2cScriptAddress->scriptCompleteTasks();
            }
            break;
    }
}

//------------------------------------------------------------------------------
// End of file
