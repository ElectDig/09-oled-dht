/*
 *  oled_ruts.h
 *      Wrapper for text only routines of oled display
 *
 *      Austral - Electronica Digital - EAM - 2023
 */

enum size_text
{
    LITTLE_TEXT = 1, MEDIUM_TEXT, LARGE_TEXT
};

enum align
{
    LEFT_ALIGN = 1, CENTER_ALIGN, RIGHT_ALIGN
};

/*
 *  oled_init:
 *      Inits oled display and selects colors
 */

void oled_init(void);

/*
 *  oled_open:
 *      begin a new buffer to display
 *      receives and remember text_size
 *      clear display and sets text_size
 */

void oled_open(int size_text);

/*
 *  oled_line:
 *      Stores a new line to display
 *      align: which type of alignment
 *      line: line number from 0 to max
 *      text: text to display
 */


void oled_line( int align, unsigned line, const char text[] );

/*
 *  oled_close:
 *      displays buffer in oled display
 */

void oled_close(void);

