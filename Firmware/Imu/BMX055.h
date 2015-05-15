/**
 * @file Bmx055.h
 * @author Seb Madgwick
 * @brief Definitions for Bosch BMX055 gyroscope and accelerometer register
 * addresses and values.  Magnetometer should be interfaced to using the Bosch
 * API (https://github.com/BoschSensortec/BMM050_driver).
 */

#ifndef BMX055_H
#define BMX055_H

//------------------------------------------------------------------------------
// Definitions - Accelerometer

#define BMX055_ACC_ADDRESS          0x18 // I2C address (SD01 = GND)

#define BMX055_ACC_BGW_CHIPID       0x00 // accelerometer registers
#define BMX055_ACC_ACCD_X_LSB       0x02
#define BMX055_ACC_ACCD_X_MSB       0x03
#define BMX055_ACC_ACCD_Y_LSB       0x04
#define BMX055_ACC_ACCD_Y_MSB       0x05
#define BMX055_ACC_ACCD_Z_LSB       0x06
#define BMX055_ACC_ACCD_Z_MSB       0x07
#define BMX055_ACC_ACCD_TEMP        0x08
#define BMX055_ACC_INT_STATUS_0     0x09
#define BMX055_ACC_INT_STATUS_1     0x0A
#define BMX055_ACC_INT_STATUS_2     0x0B
#define BMX055_ACC_INT_STATUS_3     0x0C
#define BMX055_ACC_FIFO_STATUS      0x0E
#define BMX055_ACC_PMU_RANGE        0x0F
#define BMX055_ACC_PMU_BW           0x10
#define BMX055_ACC_PMU_LPW          0x11
#define BMX055_ACC_PMU_LOW_POWER    0x12
#define BMX055_ACC_ACCD_HBW         0x13
#define BMX055_ACC_BGW_SOFTRESET    0x14
#define BMX055_ACC_INT_EN_0         0x16
#define BMX055_ACC_INT_EN_1         0x17
#define BMX055_ACC_INT_EN_2         0x18
#define BMX055_ACC_INT_MAP0         0x19
#define BMX055_ACC_INT_MAP1         0x1A
#define BMX055_ACC_INT_MAP2         0x1B
#define BMX055_ACC_INT_SRC          0x1E
#define BMX055_ACC_INT_OUT_CTRL     0x20
#define BMX055_ACC_INT_RST_LATCH    0x21
#define BMX055_ACC_INT_0            0x22
#define BMX055_ACC_INT_1            0x23
#define BMX055_ACC_INT_2            0x24
#define BMX055_ACC_INT_3            0x25
#define BMX055_ACC_INT_4            0x26
#define BMX055_ACC_INT_5            0x27
#define BMX055_ACC_INT_6            0x28
#define BMX055_ACC_INT_7            0x29
#define BMX055_ACC_INT_8            0x2A
#define BMX055_ACC_INT_9            0x2B
#define BMX055_ACC_INT_A            0x2C
#define BMX055_ACC_INT_B            0x2D
#define BMX055_ACC_INT_C            0x2E
#define BMX055_ACC_INT_D            0x2F
#define BMX055_ACC_FIFO_CONFIG_0    0x30
#define BMX055_ACC_PMU_SELF_TEST    0x32
#define BMX055_ACC_TRIM_NVM_CTRL    0x33
#define BMX055_ACC_BGW_SPI3_WDT     0x34
#define BMX055_ACC_OFC_CTRL         0x36
#define BMX055_ACC_OFC_SETTING      0x37
#define BMX055_ACC_OFC_OFFSET_X     0x38
#define BMX055_ACC_OFC_OFFSET_Y     0x39
#define BMX055_ACC_OFC_OFFSET_Z     0x3A
#define BMX055_ACC_TRIM_GP0         0x3B
#define BMX055_ACC_TRIM_GP1         0x3C
#define BMX055_ACC_FIFO_CONFIG_1    0x3E
#define BMX055_ACC_FIFO_DATA        0x3F

#define BMX055_ACC_RANGE_16G        0b00001100 // ACC_PMU_RANGE

#define BMX055_ACC_UPDATE_64MS      0b00001000 // ACC_PMU_BW
#define BMX055_ACC_UPDATE_32MS      0b00001001
#define BMX055_ACC_UPDATE_16MS      0b00001010
#define BMX055_ACC_UPDATE_8MS       0b00001011
#define BMX055_ACC_UPDATE_4MS       0b00001100
#define BMX055_ACC_UPDATE_2MS       0b00001101
#define BMX055_ACC_UPDATE_1MS       0b00001110
#define BMX055_ACC_UPDATE_0_5MS     0b00001111

#define BMX055_ACC_SLOPE_EN_ZYX     0b00000111 // BMX055_ACC_INT_EN_0 and BMX055_ACC_INT_EN_1

#define BMX055_ACC_INT1_SLOPE       0b00000100 // BMX055_ACC_INT_MAP0

//------------------------------------------------------------------------------
// Definitions - Gyroscope

#define BMX055_GYR_ADDRESS          0x68 // I2C address (SD02 = GND)

#define BMX055_GYR_CHIPID           0x00 // gyroscope registers
#define BMX055_GYR_RATE_X_LSB       0x02
#define BMX055_GYR_RATE_X_MSB       0x03
#define BMX055_GYR_RATE_Y_LSB       0x04
#define BMX055_GYR_RATE_Y_MSB       0x05
#define BMX055_GYR_RATE_Z_LSB       0x06
#define BMX055_GYR_RATE_Z_MSB       0x07
#define BMX055_GYR_INT_STATUS_0     0x09
#define BMX055_GYR_INT_STATUS_1     0x0A
#define BMX055_GYR_INT_STATUS_2     0x0B
#define BMX055_GYR_INT_STATUS_3     0x0C
#define BMX055_GYR_FIFO_STATUS      0x0E
#define BMX055_GYR_RANGE            0x0F
#define BMX055_GYR_BW               0x10
#define BMX055_GYR_LPM1             0x11
#define BMX055_GYR_LPM2             0x12
#define BMX055_GYR_RATE_HBW         0x13
#define BMX055_GYR_BGW_SOFTRESET    0x14
#define BMX055_GYR_INT_EN_0         0x15
#define BMX055_GYR_INT_EN_1         0x16
#define BMX055_GYR_INT_MAP0         0x17
#define BMX055_GYR_INT_MAP1         0x18
#define BMX055_GYR_INT_MAP2         0x19
#define BMX055_GYR_INT_RST_LATCH    0x21
#define BMX055_GYR_HIGH_TH_X        0x22
#define BMX055_GYR_HIGH_DUR_X       0x23
#define BMX055_GYR_HIGH_TH_Y        0x24
#define BMX055_GYR_HIGH_DUR_Y       0x25
#define BMX055_GYR_HIGH_TH_Z        0x26
#define BMX055_GYR_HIGH_DUR_Z       0x27
#define BMX055_GYR_SOC              0x31
#define BMX055_GYR_A_FOC            0x32
#define BMX055_GYR_TRIM_NVM_CTRL    0x33
#define BMX055_GYR_BGW_SPI3_WDT     0x34
#define BMX055_GYR_OFC1             0x36
#define BMX055_GYR_OFC2             0x37
#define BMX055_GYR_OFC3             0x38
#define BMX055_GYR_OFC4             0x39
#define BMX055_GYR_TRIM_GP0         0x3A
#define BMX055_GYR_TRIM_GP1         0x3B
#define BMX055_GYR_BIST1            0x3C
#define BMX055_GYR_FIFO_CONFIG_1    0x3D
#define BMX055_GYR_FIFO_CONFIG_2    0x3E

#define BMX055_GYR_ODR100_FB32      0b00000111 // GYR_BW
#define BMX055_GYR_ODR200_FB64      0b00000110
#define BMX055_GYR_ODR100_FB12      0b00000101
#define BMX055_GYR_ODR200_FB23      0b00000100
#define BMX055_GYR_ODR400_FB47      0b00000011
#define BMX055_GYR_ODR1000_FB116    0b00000010
#define BMX055_GYR_ODR2000_FB230    0b00000001
#define BMX055_GYR_ODR2000_FB523    0b00000000

#define BMX055_GYR_DATA_EN          0b10000000 // GYR_INT_EN_0

#define BMX055_GYR_INT1_LVL         0b00000001 // GYR_INT_EN_1

#define BMX055_GYR_INT1_DATA        0b00000001 // GYR_INT_MAP1

#endif

//------------------------------------------------------------------------------
// End of file
