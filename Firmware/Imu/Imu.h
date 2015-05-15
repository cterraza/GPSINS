/*
 * @file Imu.h
 * @author Seb Madgwick
 * @brief IMU module for providing measurement of azimuth, elevation, and
 * angular velocity norm of chord.
 */

#ifndef IMU_H
#define IMU_H

//------------------------------------------------------------------------------
// Definitions

typedef struct {
    float azimuth;
    float elevation;
    float angularVelocityNorm;
} ImuMeasurement;

//------------------------------------------------------------------------------
// Function prototypes

void ImuInitialise();
void ImuGetMeasurement(ImuMeasurement * const imuMeasurement);
void ImuZero();

#endif

//------------------------------------------------------------------------------
// End of file
