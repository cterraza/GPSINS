/*
 * @file Main.h
 * @author xxxxxxxxxxxx
 *
 * Device:
 * dsPIC33EP512GM604
 *
 * Compiler:
 * MPLAB XC16 v1.24
 *
 * Peripherals used:
 * INT1                 Imu.c
 * Timer 1,2            Timer.c
 * I2C1                 I2C1.c
 * UART1                Uart1.c
 * UART1                Uart2.c
 *
 *
 * Interrupt priorities (nesting enabled):
 * 7.
 * 6.
 * 5. TMR1 (Timer.c)
 * 4. I2C1 (I2C1.c)
 * 3. INT1 (Imu.c)
 * 2. UART1 (Uart1.c)
 * 1.
 */

//------------------------------------------------------------------------------
// Includes

#include "Imu/Imu.h"
#include "Receive/Receive.h"
#include "Send/Send.h"
#include <stdbool.h>
#include "SystemDefinitions.h"
#include "Timer/Timer.h"
#include "Uart/Uart1.h"
#include "Uart/Uart2.h"
#include <libpic30.h>        // __delayXXX() functions macros defined here
#include <xc.h>
#include <pps.h>

//------------------------------------------------------------------------------
// Configuration Bits

_FICD(JTAGEN_OFF); // JTAG is disabled
_FWDT(FWDTEN_OFF); // Watchdog timer enabled/disabled by user software
_FOSC(FCKSM_CSECME & POSCMD_HS); // Clock switching is enabled,Fail-safe Clock Monitor is disabled; HS Crystal Oscillator Mode
_FOSCSEL(FNOSC_PRIPLL & IESO_ON)


//------------------------------------------------------------------------------
// Function prototypes

static void Initialise(void);

//------------------------------------------------------------------------------
// Functions

/**
 * @brief Firmware entry point.
 * @return This function should never return.
 */
int main(void) {
    // Initialise oscillator and I/O
    Initialise();

    // Initialise drivers and middleware modules
    TimerInitialise();
    ImuInitialise();
    const UartSettings uartSettings = DEFAULT_UART_SETTINGS;
    Uart1Initialise(&uartSettings);
    Uart2Initialise(&uartSettings);

    // Start up application tasks
    SendReset();
    SendFirmwareVersion();

    // Main loop
    while (true) {

        // Application tasks
        //SendDoTasks();
        //ReceiveDoTasks();
        __delay_ms(500);
        LED2_LAT = ~LED2_LAT;
        
    }
}

/**
 * @brief Initialise oscillator and I/O.
 */
static void Initialise(void) {

    // 10 = HS Crystal Oscillator mode (10 MHz to 60 MHz)
    // 01 = XT Crystal Oscillator mode (3.5 MHz to 10 MHz)
    // 00 = EC (External Clock) mode (0 MHz to 60 MHz)

    // Configure oscillator for 70 MIPS (140 MHz) with 12 MHz external crystal
    // Fosc = Fin*M/(N1*N2), Fcy=Fosc/2
    // Where: (Source datasheet page 145 Osc configuration)
    // N1 = PLLPRE<4:0> + 2
    // N2 = 2*(PLLPOST<1:0>+1)
    // M = PLLDIV<8:0> + 2
    // Fosc= 12Mhz*(16)/(2*3)=1400Mhz for HSPLL, Fcy = 40Mhz */

    /* Configure PLL prescaler, PLL postscaler, PLL divisor */
    PLLFBD = 68; // M = 70
    CLKDIVbits.PLLPOST = 0; // N2 = 2
    CLKDIVbits.PLLPRE = 1;  // N1 = 3
    while(_LOCK==0)

    // Disable analogue inputs
    ANSELA = 0x0000;
    ANSELB = 0x0000;
    ANSELC = 0x0000;

    // Configure IMU I/O
    IMU_INT_MAP();

    // Configure UART I/O
    UART1_RX_MAP();
    UART1_TX_MAP();

    UART2_RX_MAP();
    UART2_TX_MAP();
    //__builtin_write_OSCCONL(OSCCON & ~(0x40));		// Habilitamos escritura sobre registros RPINRx y RPORX.
    //iPPSOutput(OUT_PIN_PPS_RP43,OUT_FN_PPS_U1TX);	//PIN RP43 COMO TX UART1
    //iPPSInput(IN_FN_PPS_U1RX,IN_PIN_PPS_RPI44);		//PIN RPI43 COMO RX UART1
    //__builtin_write_OSCCONL(OSCCON |0x40);			// Bloqueamos escritura sobre registros RPINRx y RPORX.

    // Configure Test pin I/O
    LED1_TRIS = 0;  //LED1 as output
    LED2_TRIS = 0;  //LED2 as output
    LED1_LAT = 1;   // LED1 ON
}

//------------------------------------------------------------------------------
// End of file