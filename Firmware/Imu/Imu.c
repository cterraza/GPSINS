/*
 * @file Imu.c
 * @author Seb Madgwick
 * @brief IMU module for providing measurement of azimuth, elevation, and
 * angular velocity norm of cord.
 */

//------------------------------------------------------------------------------
// Includes

#include "BMX055.h"
#include "I2C\I2C1.h"
#include "Imu.h"
#include <math.h> // atan2, sqrt
#include <stdint.h> // uint16_t
#include "SystemDefinitions.h"
#include "Timer/Timer.h"
#include <xc.h>

//------------------------------------------------------------------------------
// Definitions

/**
 * @brief 16-bit ADC result used to contain the signed axis measurements from
 * the gyroscope or accelerometer.
 */
typedef union {
    int16_t value;

    struct {
        char lsb;
        char msb;
    };
} Adc16Bit;

/**
 * @brief Triple-axis 16-bit ADC result used to contain the gyroscope or
 * accelerometer.
 */
typedef struct {
    Adc16Bit x;
    Adc16Bit y;
    Adc16Bit z;
} AdcXyz;

/**
 * @brief Three-dimensional spacial vector.
 */
typedef union {
    float array[3];

    struct {
        float x;
        float y;
        float z;
    } axis;
} Vector3;

/**
 * @brief Quaternion.  This library uses the conversion of placing the 'w'
 * element as the first element.  Other implantations may place the 'w' element
 * as the last element.
 */
typedef union {
    float array[4];

    struct {
        float w;
        float x;
        float y;
        float z;
    } element;
} Quaternion;

/**
 * @brief Quaternion identity definition to represent an aligned of
 * orientation.  May be used for initialisation.
 */
#define QUATERNION_IDENTITY ((Quaternion){ .array = {1.0f, 0.0f, 0.0f, 0.0f} })

/**
 * @brief High-pass filter gain to attenuate drift in measured orientation.
 */
#define HIGH_PASS_FILTER_GAIN 0.05f

/**
 * @brief Definition of M_PI.  Some compilers may not define this in math.h.
 */
#ifndef M_PI
#define	M_PI 3.14159265358979323846
#endif

/**
 * @brief Macro for converting degrees to radians.
 */
#define DEGREES_TO_RADIANS(degrees) ((float)(degrees) * (M_PI / 180.0f))

/**
 * @brief Macro for converting radians to degrees.
 */
#define RADIANS_TO_DEGREES(radians) ((float)(radians) * (180.0f / M_PI))

//------------------------------------------------------------------------------
// Variables

static I2CScript i2cScript;
static void ScriptCompleteTasks();
static volatile Ticks64 adcTimestamp;
static volatile AdcXyz gyroAdc;
static volatile Vector3 gyroDps;
static volatile Quaternion quaternion = QUATERNION_IDENTITY;

//------------------------------------------------------------------------------
// Function prototypes

static inline __attribute__((always_inline)) float FastInverseSqrt(const float x);

//------------------------------------------------------------------------------
// Functions

/**
 * @brief Initialises module.  This function should be called once on system
 * start up.
 */
void ImuInitialise() {

    // Power cycle BMX055

    // Initialise I2C module
    I2C1Initialise(400000);
    TimerDelay(10);

    // Setup BMX055 gyroscope
    I2C1Start();
    I2C1Send(I2C_WRITE_ADDRESS(BMX055_GYR_ADDRESS));
    I2C1Send(BMX055_GYR_BW);
    I2C1Send(BMX055_GYR_ODR400_FB47);
    I2C1Restart();
    I2C1Send(I2C_WRITE_ADDRESS(BMX055_GYR_ADDRESS));
    I2C1Send(BMX055_GYR_INT_EN_0);
    I2C1Send(BMX055_GYR_DATA_EN);
    I2C1Restart();
    I2C1Send(I2C_WRITE_ADDRESS(BMX055_GYR_ADDRESS));
    I2C1Send(BMX055_GYR_INT_EN_1);
    I2C1Send(BMX055_GYR_INT1_LVL);
    I2C1Restart();
    I2C1Send(I2C_WRITE_ADDRESS(BMX055_GYR_ADDRESS));
    I2C1Send(BMX055_GYR_INT_MAP1);
    I2C1Send(BMX055_GYR_INT1_DATA);
    I2C1Stop();

    // Compose I2C script
    I2CScriptInitialise(&i2cScript);
    I2CScriptAddStart(&i2cScript);
    I2CScriptAddSend(&i2cScript, I2C_WRITE_ADDRESS(BMX055_GYR_ADDRESS));
    I2CScriptAddSend(&i2cScript, BMX055_GYR_RATE_X_LSB);
    I2CScriptAddRestart(&i2cScript);
    I2CScriptAddSend(&i2cScript, I2C_READ_ADDRESS(BMX055_GYR_ADDRESS));
    I2CScriptAddReceive(&i2cScript);
    I2CScriptAddAck(&i2cScript, (char*) &gyroAdc.x.lsb);
    I2CScriptAddReceive(&i2cScript);
    I2CScriptAddAck(&i2cScript, (char*) &gyroAdc.x.msb);
    I2CScriptAddReceive(&i2cScript);
    I2CScriptAddAck(&i2cScript, (char*) &gyroAdc.y.lsb);
    I2CScriptAddReceive(&i2cScript);
    I2CScriptAddAck(&i2cScript, (char*) &gyroAdc.y.msb);
    I2CScriptAddReceive(&i2cScript);
    I2CScriptAddAck(&i2cScript, (char*) &gyroAdc.z.lsb);
    I2CScriptAddReceive(&i2cScript);
    I2CScriptAddNack(&i2cScript, (char*) &gyroAdc.z.msb);
    I2CScriptAddStop(&i2cScript);
    i2cScript.scriptCompleteTasks = ScriptCompleteTasks;

    // Initialise data ready interrupt
    _INT1IP = 3; // set interrupt priority
    _INT1IF = 0; // clear interrupt flag
    _INT1IE = 1; // enable interrupt
}

/**
 * @brief Function executed upon completion of I2C script.  Updates quaternion
 * based on integrated gyroscope measurements and high-pass filter convergence.
 */
static void ScriptCompleteTasks() {

    // Calculate sample period
    static Ticks32 previousTicks;
    float samplePeriod = (float) (adcTimestamp.ticks32.value - previousTicks.value) * (1.0f / (float) TIMER_TICKS_PER_SECOND);
    previousTicks = adcTimestamp.ticks32;

    // Calculate degrees per second
    gyroDps.axis.x = (float) gyroAdc.y.value * (1.0f / 16.4f); // swap x and y axis
    gyroDps.axis.y = (float) gyroAdc.x.value * (1.0f / 16.4f);
    gyroDps.axis.z = (float) -gyroAdc.z.value * (1.0f / 16.4f);

    // Calculate radians per second
    Vector3 g = {
        .axis.x = DEGREES_TO_RADIANS(gyroDps.axis.x),
        .axis.y = DEGREES_TO_RADIANS(gyroDps.axis.y),
        .axis.z = DEGREES_TO_RADIANS(gyroDps.axis.z),
    };

    // Adjust for convergence to alignment
    g.axis.y -= 2.0f * (quaternion.element.x * quaternion.element.z + quaternion.element.w * quaternion.element.y) * HIGH_PASS_FILTER_GAIN;
    g.axis.z += 2.0f * (quaternion.element.x * quaternion.element.y - quaternion.element.w * quaternion.element.z) * HIGH_PASS_FILTER_GAIN;

    // Integrate to yield quaternion
    Quaternion q = quaternion;
    g.axis.x *= (0.5f * samplePeriod); // pre-multiply common factors
    g.axis.y *= (0.5f * samplePeriod);
    g.axis.z *= (0.5f * samplePeriod);
    quaternion.element.w += (-q.element.x * g.axis.x - q.element.y * g.axis.y - q.element.z * g.axis.z);
    quaternion.element.x += (q.element.w * g.axis.x + q.element.y * g.axis.z - q.element.z * g.axis.y);
    quaternion.element.y += (q.element.w * g.axis.y - q.element.x * g.axis.z + q.element.z * g.axis.x);
    quaternion.element.z += (q.element.w * g.axis.z + q.element.x * g.axis.y - q.element.y * g.axis.x);

    // Normalise quaternion
    float reciprocalNorm = FastInverseSqrt(quaternion.element.w * quaternion.element.w
            + quaternion.element.x * quaternion.element.x
            + quaternion.element.y * quaternion.element.y
            + quaternion.element.z * quaternion.element.z);
    quaternion.element.w *= reciprocalNorm;
    quaternion.element.x *= reciprocalNorm;
    quaternion.element.y *= reciprocalNorm;
    quaternion.element.z *= reciprocalNorm;
}

/**
 * @brief Calculates the reciprocal of the square root.
 * @see http://en.wikipedia.org/wiki/Fast_inverse_square_root
 * @param x Operand.
 * @return Reciprocal of the square root of x.
 */
static inline __attribute__((always_inline)) float FastInverseSqrt(const float x) {
    float halfx = 0.5f * x;
    float y = x;
    int32_t i = *(int32_t*) & y;
    i = 0x5f3759df - (i >> 1);
    y = *(float*) &i;
    y = y * (1.5f - (halfx * y * y));
    return y;
}

/**
 * @brief Gets most recent IMU measurements.  This function must not be called
 * from an interrupt with a priority greater than the I2C interrupt.
 * @param imuMeasurement Address of ImuMeasurement structure to be written to.
 */
void ImuGetMeasurement(ImuMeasurement * const imuMeasurement) {

    // Sample current values
    Ticks64 sampledAdcTimestamp;
    Quaternion sampledQuaternion;
    Vector3 sampledGyroDps;
    do {
        sampledAdcTimestamp = adcTimestamp;
        sampledQuaternion = quaternion;
        sampledGyroDps = gyroDps;
    } while (sampledAdcTimestamp.value != adcTimestamp.value); // avoid asynchronous update hazard

    // Calculate required quantities
    float x = 2.0f * sampledQuaternion.element.w * sampledQuaternion.element.w - 1.0f + 2.0f * sampledQuaternion.element.x * sampledQuaternion.element.x;
    float y = 2.0f * (sampledQuaternion.element.x * sampledQuaternion.element.y - sampledQuaternion.element.w * sampledQuaternion.element.z);
    float z = 2.0f * (sampledQuaternion.element.x * sampledQuaternion.element.z + sampledQuaternion.element.w * sampledQuaternion.element.y);
    imuMeasurement->azimuth = RADIANS_TO_DEGREES(atan2(y, x));
    imuMeasurement->elevation = RADIANS_TO_DEGREES(atan2(x, z)) - 90.0f;
    imuMeasurement->angularVelocityNorm = sqrt(sampledGyroDps.axis.x * sampledGyroDps.axis.x
            + sampledGyroDps.axis.y * sampledGyroDps.axis.y
            + sampledGyroDps.axis.z * sampledGyroDps.axis.z);
}

/**
 * @brief Zeros the IMU orientation.  This function is unsafe because quaternion
 * is also written within an interrupt!
 */
void ImuZero() {
    quaternion = QUATERNION_IDENTITY;
}

//------------------------------------------------------------------------------
// Functions - Interrupt

/**
 * @brief Gyroscope data ready interrupt to store timestamp and start background
 * I2C data acquisition.
 */
void __attribute__((interrupt, auto_psv))_INT1Interrupt(void) {
    adcTimestamp = TimerGetTicks64();
    I2C1RunScript(&i2cScript); // read sensor data
    _INT1IF = 0; // clear interrupt flag
}

//------------------------------------------------------------------------------
// End of file
