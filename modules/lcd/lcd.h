//=====[#include guards - begin]===============================================

#ifndef _LCD_H_
#define _LCD_H_

//=====[Declaration of public defines]=========================================

//=====[Declaration of public data types]======================================

//=====[Declarations (prototypes) of public functions]=========================

void lcdInit( void );
 
void lcdCharPositionWrite( uint8_t charPositionX, uint8_t charPositionY );

void lcdStringWrite( const char * str );

//=====[#include guards - end]=================================================

#endif // _LCD_H_