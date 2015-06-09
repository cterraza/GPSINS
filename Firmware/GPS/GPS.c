
#include "GPS/gps.h"
#include "Uart/uart2.h"
#include <stdint.h> // uint16_t
// **********************
// GPS
// **********************

NAV_POSLLH posllh;

const unsigned char UBX_HEADER[] = { 0xB5, 0x62 };
static int fpos = 0;
static unsigned char checksum[2];
const int payloadSize = sizeof(NAV_POSLLH);

uint32_t GPS_altitude=0;


int GPSDoTasks(void) {
    char c=0;
    while (Uart2IsGetReady() > 0) {
        c=Uart2GetChar();
        if ( fpos < 2 ) {
            if ( c == UBX_HEADER[fpos] )
                fpos++;
            else
                fpos = 0;
        }
    else {
            if ( (fpos-2) < payloadSize ) {
                ((unsigned char*)(&posllh))[fpos-2] = c;
                fpos++;
            }
            if ( fpos == (payloadSize+2) ) {
                calcChecksum(checksum);
            }
            else if ( fpos == (payloadSize+3) ) {
                if ( c != checksum[0] )
                    fpos = 0;
            }
            else if ( fpos == (payloadSize+4) ) {
                fpos = 0;
                if ( c == checksum[1] ) {
                    GPS_altitude = posllh.height;
                    return true;
                }
            }
            else if ( fpos > (payloadSize+4) ) {
                fpos = 0;
            }
    }
    }
    return false;
}

void calcChecksum(unsigned char* CK) {
    int i = 0;
    for (i = 0; i < (int)sizeof(NAV_POSLLH); i++) {
        CK[0] += ((unsigned char*)(&posllh))[i];
        CK[1] += CK[0];
    }
}