/*
 * uMedia.c
 *
 * PIC24 Mikromedia 
 */

#include "uMedia.h"

#define __T3_ISR    __attribute__((interrupt, shadow, no_auto_psv))

#ifdef _TOUCH
void __T3_ISR _T3Interrupt(void)
{
   // Clear flag
   IFS0bits.T3IF = 0;

   TouchDetectPosition();
}


#define TICK_PERIOD( ms)  (GetPeripheralClock() * (ms)) / 8000

void TickInit( unsigned period_ms)
{
   // Initialize Timer3
   TMR3 = 0;
   PR3 = TICK_PERIOD( period_ms);
   T3CONbits.TCKPS = 1;        // Set prescale to 1:8
   IFS0bits.T3IF = 0;          // Clear flag
   IEC0bits.T3IE = 1;          // Enable interrupt
   T3CONbits.TON = 1;          // Run timer
}
#endif


void uMBInit( void)
{
#ifdef _SFLASH
    DRV_SPI_INIT_DATA spi_config = SPI_FLASH_CONFIG;
#endif
    // 1. disable analog inputs
    AD1PCFG = 0xFFFF;   // all inputs digital

    // 2. configure PPS for PIC24 Mikromedia
    PPSUnLock;

    // 3. SPI2
    PPSInput( PPS_SDI2,  PPS_RP26);     // SDI2 =RP26 G7/pin 11
    PPSOutput( PPS_RP21, PPS_SCK2OUT);  // SCK2 =RP21 G6/pin 10
    PPSOutput( PPS_RP19, PPS_SDO2);     // SDO2 =RP19 G8/pin 12

// 4. UART
//    PPSInput( PPS_U2RX,  PPS_RP10);     // U2RX =RP10 F4/pin 49
//    PPSInput( PPS_U2CTS, PPS_RPI32);    // U2CTS=RP32 F12/pin40
//    PPSOutput( PPS_RP17, PPS_U2TX);     // U2TX =RP17 F5/pin 50
//    PPSOutput( PPS_RP31, PPS_U2RTS);    // U2RTS=RP31 F13pin 39


//    PPSOutput( PPS_RP23, PPS_OC1);      // OC1 =RP23 D2/pin 77

    // Done, lock the PPS configuration
    //    PPSLock;

#ifdef _SFLASH
    // Initialize the serial Flash CS I/O
    SST25_CS_LAT = 1;
    SST25_CS_TRIS = 0;
    FlashInit( &spi_config);
#endif
} // uMBInit


#ifdef _SCREENCAPTURE
void ScreenCapture( char *filename)
{
    FSFILE *fp;
    GFX_COLOR Row[ 320];
    int i, j;

    // open file
    fp = FSfopen( filename, FS_WRITE);
    if ( fp != NULL)
    {
        // dump contents of the screen
        for(j=0; j<=GetMaxY(); j++)
        {
            // row by row
            for( i=0; i<=GetMaxX(); i++)
            {
                Row[ i] = GetPixel( i, j);
            }

            // write buffer to file
            FSfwrite( Row, sizeof(Row), 1, fp);
        }

        // close file
        FSfclose( fp);

    }
}
#endif // _SCREENCAPTURE
 