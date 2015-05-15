/**
 * @file Uart1.c
 * @author
 * @brief UART library for dsPIC33EP.
 *
 * Transmission and reception are interrupt-driven to empty or fill software
 * buffers in the background.
 *
 * U1_RX_BUFFER_SIZE, U1_TX_BUFFER_SIZE and U1_INTERRUPT_PRIORITY may be changed
 * as required by the application.
 */

//------------------------------------------------------------------------------
// Includes
#include "Uart1.h"
#include "Uart2.h"
#include <xc.h>

//------------------------------------------------------------------------------
// Definitions

#define U2_RX_BUFFER_SIZE 256 // must be a 2^n number, e.g. 256, 512, 1024, ...
#define U2_TX_BUFFER_SIZE 128 // must be a 2^n number, e.g. 256, 512, 1024, ...
#define U2_INTERRUPT_PRIORITY 2

//------------------------------------------------------------------------------
// Variables

static volatile char gps_rxBuffer[U2_RX_BUFFER_SIZE];
static volatile unsigned int gps_rxBufferIn = 0; // only written to by interrupt
static volatile unsigned int gps_rxBufferOut = 0;
static volatile bool gps_rxBufferOverrun = false;
static volatile char gps_txBuffer[U2_TX_BUFFER_SIZE];
static volatile unsigned int gps_txBufferIn = 0;
static volatile unsigned int gps_txBufferOut = 0; // only written to by interrupt

//------------------------------------------------------------------------------
// Functions

/**
 * @brief Initialises the UART module.
 *
 * Initialises the UART module with specified UART settings. This function can
 * be used to reinitialise the module with new settings if it has already been
 * initialised.
 *
 * Example use:
 * @code
 * UartSettings uartSettings = DEFAULT_UART_SETTINGS;
 * uartSettings.baudRate = 9600;
 * uartSettings.ctsRtsEnabled = true;
 * Uart1Initialise(&uartSettings);
 * @endcode
 *
 * @param uartSettings UartSettings structure.
 */
void Uart2Initialise(const UartSettings * const uartSettings) {

    // Ensure default register states
    Uart2Disable();
    PMD1bits.U2MD = 0; // enable peripheral

    // Configure module
    if (uartSettings->ctsRtsEnabled) {
        U2MODEbits.UEN = 0b10; // UxTX, UxRX, UxCTS and UxRTS pins are enabled and used
    }
    if (uartSettings->invertDataLines) {
        U2MODEbits.RXINV = 1; // UxRX Idle state is '0'
        U2STAbits.UTXINV = 1; // UxTX Idle state is '0'
    }
    U2MODEbits.PDSEL = uartSettings->parityAndData;
    U2MODEbits.STSEL = uartSettings->stopBits;
    U2MODEbits.BRGH = 1; // BRG generates 4 clocks per bit period (4x baud clock, High-Speed mode)
    U2STAbits.UTXISEL1 = 1; // Interrupt when a character is transferred to the Transmit Shift Register (TSR), and as a result, the transmit buffer becomes empty
    U2BRG = CALCULATE_UXBRG(38400);
    U2MODEbits.UARTEN = 1; // UART1 enabled
    U2STAbits.UTXEN = 1; // UARTx transmitter is enabled. UxTX pin is controlled by UARTx (if ON = 1)
    _U2RXIP = U2_INTERRUPT_PRIORITY; // set RX interrupt priority
    _U2TXIP = U2_INTERRUPT_PRIORITY; // set TX interrupt priority
    _U2RXIF = 0; // clear RX interrupt flag
    _U2RXIE = 1; // RX interrupt enabled
}

/**
 * @brief Disable the UART module.
 *
 * UART registers are set to their default values.  UART pins are controlled by
 * corresponding bits in  the PORTx, TRISx and LATx registers.  Power
 * consumption is minimal.
 *
 * Example use:
 * @code
 * Uart1Disable();
 * @endcode
 */
void Uart2Disable() {

    // Disable module and ensure default register states
    U2MODE = 0x0000;
    U2STA = 0x0000;
    _U2RXIF = 0; // clear RX interrupt flag
    _U2TXIF = 0; // clear TX interrupt flag
    PMD1bits.U2MD = 1; // disable peripheral

    // Clear software buffers
    Uart2ClearRxBuffer();
    Uart2ClearTxBuffer();
}

/**
 * @brief Returns the number of bytes available in the software receive buffer.
 *
 * This function also polls the RX hardware buffer and triggers and 'manually'
 * triggers an interrupt to fetch unprocessed bytes.  If the RX hardware buffer
 * overrun flag is set, it will be cleared to re-enabled the UART module.
 * Uart1GetRxBufferOverrunFlag may be used to determine if a hardware or
 * software buffer receive buffer overrun has occurred.
 *
 * Example use:
 * @code
 * while(Uart1IsGetReady() > 0) {
 *     char byte = Uart1GetChar();
 *     printf("%c", byte);
 * }
 * @endcode
 *
 * @return Number of bytes available in software receive buffer.
 */
size_t Uart2IsGetReady() {
    if (U2STAbits.URXDA) { // trigger interrupt if data available
        _U2RXIF = 1;
    }
    if (U2STAbits.OERR) {
        U2STAbits.OERR = 0; // clear flag and re-enable UART if hardware buffer overrun
        gps_rxBufferOverrun = true;
    }
    return (gps_rxBufferIn - gps_rxBufferOut) & (U2_RX_BUFFER_SIZE - 1);
}

/**
 * @brief Returns next byte available in the software receive buffer.
 *
 * This function should only be called if bytes are available.  Call
 * Uart1IsGetReady to determine the number of bytes in the software receive
 * buffer.
 *
 * Example use:
 * @code
 * while(Uart1IsGetReady() > 0) {
 *     char byte = Uart1GetChar();
 *     printf("%c", byte);
 * }
 * @endcode
 *
 * @return Next byte available in the software receive buffer.
 */
char Uart2GetChar() {
    const char byte = gps_rxBuffer[gps_rxBufferOut++];
    gps_rxBufferOut &= (U2_RX_BUFFER_SIZE - 1); // overflow index at buffer size
    return byte;
}

/**
 * @brief Returns the space available in the software transmit buffer.
 *
 * Example use:
 * @code
 * if(Uart1IsPutReady() > 0) {
 *     Uart1PutChar('a');
 * }
 * @endcode
 *
 * @return Space available (number of bytes) in the software transmit buffer.
 */
size_t Uart2IsPutReady() {
    return (U2_TX_BUFFER_SIZE - 1) - ((gps_txBufferIn - gps_txBufferOut) & (U2_TX_BUFFER_SIZE - 1));
}

/**
 * @brief Loads byte into software transmit buffer starts interrupt-driven
 * transmission.
 *
 * This function should only be called if space is available.  Call
 * Uart1IsPutReady to determine the number of bytes that may be loaded into the
 * software transmit buffer.
 *
 * Example use:
 * @code
 * if(Uart1IsPutReady() > 0) {
 *     Uart1PutChar('a');
 * }
 * @endcode
 *
 * @param byte Byte to be buffered for transmission.
 */
void Uart2PutChar(const char byte) {
    gps_txBuffer[gps_txBufferIn++] = byte;
    gps_txBufferIn &= (U2_TX_BUFFER_SIZE - 1); // overflow index at buffer size
    if (!_U2TXIE) {
        _U2TXIF = 1; // set TX interrupt flag
        _U2TXIE = 1; // enable TX interrupt
    }
}

/**
 * @brief Loads byte array into software transmit buffer starts interrupt-driven
 * transmission.
 *
 * This function should only be called if space is available.  Call
 * Uart1IsPutReady to determine the number of bytes that may be loaded into the
 * software transmit buffer.
 *
 * Example use:
 * @code
 * char array[] = { 1, 2, 3 };
 * if(Uart1IsPutReady() > sizeof(array)) {
 *     Uart1PutCharArray(array, sizeof(array));
 * }
 * @endcode
 *
 * @param source Address of byte array.
 * @param numberOfBytes Number of bytes in byte array.
 * @return 0 if successful.
 */
int Uart2PutCharArray(const char* const source, const size_t numberOfBytes) {
    if (numberOfBytes > Uart2IsPutReady()) {
        return 1; // error: not enough space in buffer
    }
    int i;
    for (i = 0; i < numberOfBytes; i++) {
        Uart2PutChar(source[i]);
    }
    return 0;
}

/**
 * @brief Loads string into software transmit buffer starts interrupt-driven
 * transmission.
 *
 * This function should only be called if space is available.  Call
 * Uart1IsPutReady to determine the number of bytes that may be loaded into the
 * software transmit buffer.  The terminating null character will not be sent.
 *
 * Example use:
 * @code
 * char string[] = "Hello World!";
 * if(Uart1IsPutReady() > sizeof(string) - 1) {
 *     Uart1PutString(string);
 * }
 * @endcode
 *
 * @param string
 */
void Uart2PutString(const char* string) {
    while (*string != '\0') {
        Uart2PutChar(*string++);
    }
}

/**
 * @brief Clears software receive buffer and receive buffer overrun flag.
 *
 * Example use:
 * @code
 * Uart1ClearRxBuffer();
 * @endcode
 */
void Uart2ClearRxBuffer() {
    gps_rxBufferOut = gps_rxBufferIn;
    gps_rxBufferOverrun = false;
}

/**
 * @brief Clears transmit receive buffer.
 *
 * Example use:
 * @code
 * Uart1ClearTxBuffer();
 * @endcode
 */
void Uart2ClearTxBuffer() {
    gps_txBufferIn = gps_txBufferOut;
}

/**
 * @brief Returns receive buffer overrun flag.
 *
 * The receive buffer overrun flag indicates if either a hardware or software
 * receive buffer overrun has occurred.  If either receive buffer has overrun
 * then one or more bytes will have been discarded.  This flag must be cleared
 * using Uart1ClearRxBufferOverrunFlag.
 *
 * Example use:
 * @code
 * if(Uart1GetRxBufferOverrunFlag()){
 *     printf("Receive buffer overrun occurred!");
 *     Uart1ClearRxBufferOverrunFlag();
 * }
 * @endcode
 *
 * @return Receive buffer overrun flag.
 */
bool Uart2GetRxBufferOverrunFlag() {
    return gps_rxBufferOverrun;
}

/**
 * @brief Clears receive buffer overrun flag.
 *
 * The receive buffer overrun flag indicates if either a hardware or software
 * receive buffer overrun has occurred.  If either receive buffer has overrun
 * then one or more bytes will have been discarded.
 *
 * Example use:
 * @code
 * if(Uart1GetRxBufferOverrunFlag()){
 *     printf("Receive buffer overrun occurred!");
 *     Uart1ClearRxBufferOverrunFlag();
 * }
 * @endcode
 *
 * @return Receive buffer overrun flag.
 */
void Uart2ClearRxBufferOverrunFlag() {
    gps_rxBufferOverrun = false;
}

/**
 * @brief Returns true if interrupt-driven transmission is complete.
 *
 * Example use:
 * @code
 * Uart1PutString("Hello World!");
 * printf("Transmitting...");
 * while(Uart1TxIsIdle());
 * printf("Transmission complete.");
 * @endcode
 *
 * @return true if interrupt-driven transmission is complete.
 */
bool Uart2TxIsIdle() {
    return !_U2TXIE;
}

//------------------------------------------------------------------------------
// Functions - Interrupts

/**
 * @brief UART RX interrupt service routine.
 */
void __attribute__((interrupt, auto_psv))_U2RXInterrupt(void) {
    while (U2STAbits.URXDA) { // repeat while data available
        const char newByte = U2RXREG; // fetch byte from hardware buffer
        Uart1PutChar(newByte);
        if (gps_rxBufferIn == gps_rxBufferOut - 1) {
            gps_rxBufferOverrun = true; // set flag and discard byte if rxBuffer overrun
        } else {
            gps_rxBuffer[gps_rxBufferIn++] = newByte; // add to buffer and increment index
            gps_rxBufferIn &= (U2_RX_BUFFER_SIZE - 1); // overflow index at buffer size
        }
    }
    _U2RXIF = 0; // data received immediately before clearing UxRXIF will be unhandled, URXDA therefore must be polled to 'manually' set UxRXIF
}

/**
 * @brief UART TX interrupt service routine.
 */
void __attribute__((interrupt, auto_psv))_U2TXInterrupt(void) {
    _U2TXIE = 0; // disable interrupt to avoid nested interrupt
    _U2TXIF = 0; // clear interrupt flag
    while (!U2STAbits.UTXBF) { // repeat while hardware buffer not full
        if (gps_txBufferOut == gps_txBufferIn) { // if txBuffer empty
            return;
        }
        U1TXREG = gps_txBuffer[gps_txBufferOut++]; // send data to hardware buffer and increment index
        gps_txBufferOut &= (U2_TX_BUFFER_SIZE - 1); // overflow index at buffer size
    }
    _U2TXIE = 1; // re-enable interrupt
}

//------------------------------------------------------------------------------
// End of file
