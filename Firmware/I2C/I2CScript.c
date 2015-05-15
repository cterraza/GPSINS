/**
 * @file I2CScript.c
 * @author Seb Madgwick
 * @brief I2C master library for dsPIC33EP.
 */

//------------------------------------------------------------------------------
// Includes

#include "I2CScript.h"
#include <stddef.h> // NULL

//------------------------------------------------------------------------------
// Functions

/**
 * @brief Initialises an I2CScript structure.  A I2CScript structure must be
 * initialised before use.
 * @param i2cScript Address of I2CScript structure.
 */
void I2CScriptInitialise(I2CScript * const i2cScript) {
    i2cScript->command[0] = I2CScriptCommandEndOfScript;
    i2cScript->index = 0;
    i2cScript->scriptCompleteTasks = NULL;
}

/**
 * @brief Adds a start event to the I2C script.
 * @param i2cScript Address of I2CScript structure.
 * @return 0 if successful.
 */
int I2CScriptAddStart(I2CScript * const i2cScript) {
    if (i2cScript->index >= MAX_I2C_SCRIPT_LENGTH) {
        return 1; // error: script at maximum length
    }
    i2cScript->command[i2cScript->index] = I2CScriptCommandStart;
    i2cScript->command[++i2cScript->index] = I2CScriptCommandEndOfScript;
    return 0;
}

/**
 * @brief Adds a restart event to the I2C script.
 * @param i2cScript Address of I2CScript structure.
 * @return 0 if successful.
 */
int I2CScriptAddRestart(I2CScript * const i2cScript) {
    if (i2cScript->index >= MAX_I2C_SCRIPT_LENGTH) {
        return 1; // error: script at maximum length
    }
    i2cScript->command[i2cScript->index] = I2CScriptCommandRestart;
    i2cScript->command[++i2cScript->index] = I2CScriptCommandEndOfScript;
    return 0;
}

/**
 * @brief Adds a stop event to the I2C script.
 * @param i2cScript Address of I2CScript structure.
 * @return 0 if successful.
 */
int I2CScriptAddStop(I2CScript * const i2cScript) {
    if (i2cScript->index >= MAX_I2C_SCRIPT_LENGTH) {
        return 1; // error: script at maximum length
    }
    i2cScript->command[i2cScript->index] = I2CScriptCommandStop;
    i2cScript->command[++i2cScript->index] = I2CScriptCommandEndOfScript;
    return 0;
}

/**
 * @brief Adds a send event to the I2C script.
 * @param i2cScript Address of I2CScript structure.
 * @param data Byte to send.
 * @return 0 if successful.
 */
int I2CScriptAddSend(I2CScript * const i2cScript, const char data) {
    if (i2cScript->index >= MAX_I2C_SCRIPT_LENGTH) {
        return 1; // error: script at maximum length
    }
    i2cScript->data[i2cScript->index] = data;
    i2cScript->command[i2cScript->index] = I2CScriptCommandSend;
    i2cScript->command[++i2cScript->index] = I2CScriptCommandEndOfScript;
    return 0;
}

/**
 * @brief Adds a receive event to the I2C script.
 * @param i2cScript Address of I2CScript structure.
 * @return 0 if successful.
 */
int I2CScriptAddReceive(I2CScript * const i2cScript) {
    if (i2cScript->index >= MAX_I2C_SCRIPT_LENGTH) {
        return 1; // error: script at maximum length
    }
    i2cScript->command[i2cScript->index] = I2CScriptCommandReceive;
    i2cScript->command[++i2cScript->index] = I2CScriptCommandEndOfScript;
    return 0;
}

/**
 * @brief Adds a ACK event to the I2C script.
 * @param i2cScript Address of I2CScript structure.
 * @param destination Destination address to store received byte.
 * @return 0 if successful.
 */
int I2CScriptAddAck(I2CScript * const i2cScript, char* const destination) {
    if (i2cScript->index >= MAX_I2C_SCRIPT_LENGTH) {
        return 1; // error: script at maximum length
    }
    i2cScript->destination[i2cScript->index] = destination;
    i2cScript->command[i2cScript->index] = I2CScriptCommandAck;
    i2cScript->command[++i2cScript->index] = I2CScriptCommandEndOfScript;
    return 0;
}

/**
 * @brief Adds a NACK event to the I2C script.
 * @param i2cScript Address of I2CScript structure.
 * @param destination Destination address to store received byte.
 * @return 0 if successful.
 */
int I2CScriptAddNack(I2CScript * const i2cScript, char* const destination) {
    if (i2cScript->index >= MAX_I2C_SCRIPT_LENGTH) {
        return 1; // error: script at maximum length
    }
    i2cScript->destination[i2cScript->index] = destination;
    i2cScript->command[i2cScript->index] = I2CScriptCommandNack;
    i2cScript->command[++i2cScript->index] = I2CScriptCommandEndOfScript;
    return 0;
}

//------------------------------------------------------------------------------
// End of file
