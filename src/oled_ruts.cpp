/*
 *  oled_ruts.cpp
 *      Wrapper for text only routines of oled display
 *
 *      Austral - Electronica Digital - EAM - 2023
 */

#include <Arduino.h>
#include <Adafruit_SSD1306.h>

#include "oled_ruts.h"

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1 // no reset pin

#define forever for(;;)
#define XCHGEN      6
#define YCHGEN      8


Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

static int size;        //  Remember text size defined in oled_open

static int chars_line[] = { 21, 10, 7 };    //  Max number of chars per line for text_size-1
static int lines_display[] = { 8, 4, 2 };   //  Max number of lines to display for text_size-1

/*
 *  oled_init:
 *      Inits oled display and selects colors
 */

void
oled_init()
{

    if( !display.begin(SSD1306_SWITCHCAPVCC, 0x3C) ) // 0x3C for clone SSD1306. 0x3D for Adafruit's version.
        forever
        ;

    display.clearDisplay();
    display.setTextColor(SSD1306_WHITE);

}

/*
 *  oled_open:
 *      begin a new buffer to display
 *      receives and remember text_size
 *      clear display and sets text_size
 */

void
oled_open(int size_text)
{
    if( size_text > LARGE_TEXT || size_text < LITTLE_TEXT )
        size_text = LITTLE_TEXT;
    size = size_text;
    display.clearDisplay();
    display.setTextSize(size_text);
}

/*
 *  oled_line:
 *      Stores a new line to display
 *      align: which type of alignment
 *      line: line number from 0 to max
 *      text: text to display
 */


void
oled_line(int align, unsigned line, const char text[] )
{
    char buffer[150];
    int x;

    if( align > RIGHT_ALIGN || align < LEFT_ALIGN )
        align = LEFT_ALIGN;
    if( line >= lines_display[size-1] )
        return;

    strncpy(buffer, text, sizeof(buffer)-1 );
    buffer[chars_line[size-1]] = '\0';
    x = chars_line[size-1] - strlen(buffer);
    switch(align)
    {
        case LEFT_ALIGN:
            x = 0;
            break;
        case CENTER_ALIGN:
            x /= 2; 
            break;
    }
    display.setCursor(x*XCHGEN*size,line*YCHGEN*size);
    display.print(buffer);
}

/*
 *  oled_close:
 *      displays buffer in oled display
 */

void
oled_close(void)
{
    display.display();
}



