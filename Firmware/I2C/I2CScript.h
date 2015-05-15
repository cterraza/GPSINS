/**
 * @file I2CScript.h
 * @author Seb Madgwick
 * @brief I2C master library for dsPIC33EP.
 */


#ifndef I2C_SCRIPT_H
#define I2C_SCRIPT_H

//------------------------------------------------------------------------------
// Includes

#include "stdbool.h" // bool

//------------------------------------------------------------------------------
// Definitions

/**
 * @brief Maximum length of an I2C script.  This value may be adjusted as
 * required by the application.
 */
#define MAX_I2C_SCRIPT_LENGTH 128

/**
 * @brief Enumeration of I2C script commands used internally to the library when
 * composing and executing an interrupt serviced script.
 */
typedef enum {
    I2CScriptCommandStart,
    I2CScriptCommandRestart,
    I2CScriptCommandStop,
    I2CScriptCommandSend,
    I2CScriptCommandReceive,
    I2CScriptCommandAck,
    I2CScriptCommandNack,
    I2CScriptCommandEndOfScript,
} I2CScriptCommand;

/**
 * @brief I2C script structure.  Must be initialised using I2CScriptInitialise
 * before use.
 */
typedef struct {
    char command[MAX_I2C_SCRIPT_LENGTH + 1]; // extra command for I2CScriptCommandEndOfScript
    char data[MAX_I2C_SCRIPT_LENGTH];
    char* destination[MAX_I2C_SCRIPT_LENGTH];
    void (*scriptCompleteTasks)();
    int index;
} I2CScript;

//------------------------------------------------------------------------------
// Function prototypes

void I2CScriptInitialise(I2CScript * const i2cScript);
int I2CScriptAddStart(I2CScript * const i2cScript);
int I2CScriptAddRestart(I2CScript * const i2cScript);
int I2CScriptAddStop(I2CScript * const i2cScript);
int I2CScriptAddSend(I2CScript * const i2cScript, const char data);
int I2CScriptAddReceive(I2CScript * const i2cScript);
int I2CScriptAddAck(I2CScript * const i2cScript, char* const destination);
int I2CScriptAddNack(I2CScript * const i2cScript, char* const destination);

#endif

//------------------------------------------------------------------------------
// End of file
