/*
 * Project: 1-Solution.X
 * File:    main.c
 */

#include "xc.h"
#include <rtcc.h>
//#include <PwrMgnt.h>

_CONFIG1( JTAGEN_OFF        // disable JTAG interface
        & GCP_OFF           // disable general code protection
        & GWRP_OFF          // disable flash write protection
        & ICS_PGx2          // ICSP interface (2=default)
        & FWDTEN_OFF)       // disable watchdog timer

// no need to enable the external 8MHz crystal osc and PLL
// to save power, use the internal oscillator (default) and rely on the RTCC
// for accurate timing

//_CONFIG2( PLL_96MHZ_ON      // enable USB PLL module
//        & PLLDIV_DIV2       // 8MHz/2 = 4Mhz input to USB PLL
//        & IESO_OFF          // two speed start up disabled
//        & FCKSM_CSDCMD      // disable clock-switching/monitor
//        & FNOSC_PRIPLL      // primary oscillator: enable PLL
//        & POSCMOD_XT)       // primary oscillator: XT mode

/**************/

#define LED_BLED                _RD2
#define ConfigureBacklight()    _TRISD2 = 0

#define __RTCC_ISR    __attribute__((interrupt, shadow, no_auto_psv))

void __RTCC_ISR  _RTCCInterrupt( void)
{
    LED_BLED = 1 - LED_BLED;    // toggle LED_BLED output
    _RTCIF = 0;
}

int main( void )
{
    // 1. init I/O and timer
    ConfigureBacklight();       // configure I/O as output
    RtccInitClock();            // init 32KHz oscillator

    __builtin_write_RTCWEN();   // unlock RTCC registers
    mRtccOn();                  // enables rtcc, also clears alarm cfg
    ALCFGRPT = 0xc000;          // enable alarm, chime, 1/2 second period
    _RTCIE = 1;                 // enable alarm interrupts

    // 2. main loop
    while( 1)
    {
        Sleep(); //mPWRMGNT_GotoSleepMode();   // go to sleep

    } // main loop

} // main
