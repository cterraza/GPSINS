/* 
 * File:   GPS.h
 * Author: Carlos
 *
 * Created on 21 de mayo de 2015, 11:26 PM
 */
#ifndef GPS_H
#define GPS_H

#include <stdint.h> // uint16_t

#define LAT 0
#define LON 1

#define GPS_DEGREES_DIVIDER 10000000L

void calcChecksum(unsigned char* CK);
int GPSDoTasks(void);

extern uint32_t GPS_altitude;

typedef union
     {
         struct
         {
          unsigned char cls;
          unsigned char id;
          unsigned short len;
          unsigned long iTOW;
          long lon;
          long lat;
          long height;
          long hMSL;
          unsigned long hAcc;
          unsigned long vAcc;
         };
         unsigned char S0_7;
     }NAV_POSLLH;

#endif


