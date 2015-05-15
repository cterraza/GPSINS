/**
 * @file I2CCommon.h
 * @author Seb Madgwick
 * @brief I2C master library for dsPIC33EP.
 */

#ifndef I2C_COMMON_H
#define I2C_COMMON_H

//------------------------------------------------------------------------------
// Includes

#include "SystemDefinitions.h" // FCY

//------------------------------------------------------------------------------
// Definitions

/**
 * @brief Calculates I2CXBRG value for a specified baud rate and defined device
 * operating frequency (FCY).
 * @see Page 19 of chapter "Inter-Integrated Circuit (I2C))" in the
 * "dsPIC33/PIC24 Family Reference Manual".
 */
#define CALCULATE_I2CXBRG(fscl) (int) (((float) FCY / (float) baud) - 1.0f - ((float) FCY * 0.000000130f))

/**
 * @brief Macro for creating the I2C write address from an I2C slave address.
 */
#define I2C_WRITE_ADDRESS(address) ((address << 1) | 0)

/**
 * @brief Macro for creating the I2C read address from an I2C slave address.
 */
#define I2C_READ_ADDRESS(address) ((address << 1) | 1)

#endif

//------------------------------------------------------------------------------
// End of file