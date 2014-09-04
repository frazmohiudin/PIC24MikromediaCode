/*
 * File:   main.c
 * 
 * Chapter 3: Graphic Resources - Color Splashscreen
 * 
 */

#include "xc.h"
#include "PICconfig.h"
#include "Graphics/Graphics.h"
#include "Graphics/GOL.h"

#include "resources.h"
#include "uMedia.h"

int main( void )
{
    SHORT w1, w2, pad;
    char s[] = "Fonts and Bitmaps";

    // 1. init
    InitGraph();                    // init graphics library
    SetColor( WHITE);               // set background color
    ClearDevice();                  // clear display contents
    DisplayBacklightOn();           // turn on the backlight

    // 2. display centered banner
    SetColor( BRIGHTRED);           // set color
    SetFont( (void*) &GOLFontDefault);
    w1 = GetTextWidth( s, (void*) &GOLFontDefault);
    OutTextXY( (GetMaxX()-w1)/2 , 0, s);

    // 3. display  centered bitmaps
    w1 = GetImageWidth( (void*)&fingerprint);
    w2 = GetImageWidth( (void*)&flower);
    pad = (GetMaxX()- w1 - w2) / 3;
    PutImage( pad, 60, (void*) &fingerprint, IMAGE_NORMAL);
    PutImage( pad + w1 + pad, 60, (void*) &flower, IMAGE_NORMAL);

//    // capture screen
//    uMBInit();
//    FSInit();
//    ScreenCapture( "3-COLOR.SCR");


    // main loop
    while( 1)
    {

    } // main loop
}
