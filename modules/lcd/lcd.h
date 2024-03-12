//=====[#include guards - begin]===============================================

#ifndef _LCD_H_
#define _LCD_H_

#include "stdint.h"

//=====[Declaration of public defines]=========================================

//=====[Declaration of public data types]======================================

//=====[Declarations (prototypes) of public functions]=========================

/**
 * initializes the lcd screen
 */
void lcdInit();
 
/**
 * sets the "cursor" of the lcd, where info will be printed
 */
void lcdCharPositionWrite( uint8_t charPositionX, uint8_t charPositionY );

/**
 * prints a string to the lcd string
 * @param str the string to print
 */
void lcdStringWrite( const char * str );

/**
 * clears out the display
 */
void lcdClear();

//=====[#include guards - end]=================================================

#endif // _LCD_H_