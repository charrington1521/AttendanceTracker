//=====[Libraries]=============================================================

#include "mbed.h"
#include "arm_book_lib.h"
#include "lcd.h"

//=====[Declaration of private defines]========================================

#define LCD_IR_CLEAR_DISPLAY   0b00000001
#define LCD_IR_ENTRY_MODE_SET  0b00000100
#define LCD_IR_DISPLAY_CONTROL 0b00001000
#define LCD_IR_FUNCTION_SET    0b00100000
#define LCD_IR_SET_DDRAM_ADDR  0b10000000

#define LCD_IR_ENTRY_MODE_SET_INCREMENT 0b00000010
#define LCD_IR_ENTRY_MODE_SET_DECREMENT 0b00000000
#define LCD_IR_ENTRY_MODE_SET_SHIFT     0b00000001
#define LCD_IR_ENTRY_MODE_SET_NO_SHIFT  0b00000000

#define LCD_IR_DISPLAY_CONTROL_DISPLAY_ON  0b00000100
#define LCD_IR_DISPLAY_CONTROL_DISPLAY_OFF 0b00000000
#define LCD_IR_DISPLAY_CONTROL_CURSOR_ON   0b00000010
#define LCD_IR_DISPLAY_CONTROL_CURSOR_OFF  0b00000000
#define LCD_IR_DISPLAY_CONTROL_BLINK_ON    0b00000001
#define LCD_IR_DISPLAY_CONTROL_BLINK_OFF   0b00000000

#define LCD_IR_FUNCTION_SET_8BITS    0b00010000
#define LCD_IR_FUNCTION_SET_4BITS    0b00000000
#define LCD_IR_FUNCTION_SET_2LINES   0b00001000
#define LCD_IR_FUNCTION_SET_1LINE    0b00000000
#define LCD_IR_FUNCTION_SET_5x10DOTS 0b00000100
#define LCD_IR_FUNCTION_SET_5x8DOTS  0b00000000

#define LCD_20x4_LINE1_FIRST_CHARACTER_ADDRESS 0
#define LCD_20x4_LINE2_FIRST_CHARACTER_ADDRESS 64
#define LCD_20x4_LINE3_FIRST_CHARACTER_ADDRESS 20
#define LCD_20x4_LINE4_FIRST_CHARACTER_ADDRESS 84

#define LCD_RS_INSTRUCTION 0
#define LCD_RS_DATA        1

#define LCD_RW_WRITE 0
#define LCD_RW_READ  1

#define LCD_PIN_RS  4
#define LCD_PIN_RW  5
#define LCD_PIN_EN  6
#define LCD_PIN_D0  7  
#define LCD_PIN_D1  8  
#define LCD_PIN_D2  9  
#define LCD_PIN_D3 10
#define LCD_PIN_D4 11
#define LCD_PIN_D5 12 
#define LCD_PIN_D6 13 
#define LCD_PIN_D7 14 

//=====[Declaration of private data types]=====================================

//=====[Declaration and initialization of public global objects]===============

DigitalOut lcdD0( D0 );
DigitalOut lcdD1( D1 );
DigitalOut lcdD2( D2 );
DigitalOut lcdD3( D3 );
DigitalOut lcdD4( D4 );
DigitalOut lcdD5( D5 );
DigitalOut lcdD6( D6 );
DigitalOut lcdD7( D7 );
DigitalOut lcdRs( D8 );
DigitalOut lcdEn( D9 );

//=====[Declaration of external public global variables]=======================

//=====[Declaration and initialization of public global variables]=============

//=====[Declaration and initialization of private global variables]============

//=====[Declarations (prototypes) of private functions]========================

static void lcdPinWrite( uint8_t pinName, int value );
static void lcdDataBusWrite( uint8_t dataByte );
static void lcdCodeWrite( bool type, uint8_t dataBus );

//=====[Implementations of public functions]===================================

void lcdInit()
{
    delay( 50 );
    
    lcdCodeWrite( LCD_RS_INSTRUCTION, 
                      LCD_IR_FUNCTION_SET | 
                      LCD_IR_FUNCTION_SET_8BITS );
    delay( 5 );
            
    lcdCodeWrite( LCD_RS_INSTRUCTION, 
                      LCD_IR_FUNCTION_SET | 
                      LCD_IR_FUNCTION_SET_8BITS );
    delay( 1 ); 

    lcdCodeWrite( LCD_RS_INSTRUCTION, 
                      LCD_IR_FUNCTION_SET | 
                      LCD_IR_FUNCTION_SET_8BITS );
    delay( 1 );  

    lcdCodeWrite( LCD_RS_INSTRUCTION, 
                      LCD_IR_FUNCTION_SET | 
                      LCD_IR_FUNCTION_SET_8BITS | 
                      LCD_IR_FUNCTION_SET_2LINES |
                      LCD_IR_FUNCTION_SET_5x8DOTS );
    delay( 1 );         

    lcdCodeWrite( LCD_RS_INSTRUCTION, 
                      LCD_IR_DISPLAY_CONTROL |
                      LCD_IR_DISPLAY_CONTROL_DISPLAY_OFF |      
                      LCD_IR_DISPLAY_CONTROL_CURSOR_OFF |       
                      LCD_IR_DISPLAY_CONTROL_BLINK_OFF );       
    delay( 1 );          

    lcdCodeWrite( LCD_RS_INSTRUCTION, 
                      LCD_IR_CLEAR_DISPLAY );       
    delay( 1 ); 

    lcdCodeWrite( LCD_RS_INSTRUCTION, 
                      LCD_IR_ENTRY_MODE_SET |
                      LCD_IR_ENTRY_MODE_SET_INCREMENT |       
                      LCD_IR_ENTRY_MODE_SET_NO_SHIFT );                  
    delay( 1 );           

    lcdCodeWrite( LCD_RS_INSTRUCTION, 
                      LCD_IR_DISPLAY_CONTROL |
                      LCD_IR_DISPLAY_CONTROL_DISPLAY_ON |      
                      LCD_IR_DISPLAY_CONTROL_CURSOR_OFF |    
                      LCD_IR_DISPLAY_CONTROL_BLINK_OFF );    
    delay( 1 );  
}

void lcdCharPositionWrite( uint8_t charPositionX, uint8_t charPositionY )
{    
    switch( charPositionY ) {
        case 0:
            lcdCodeWrite( LCD_RS_INSTRUCTION, 
                              LCD_IR_SET_DDRAM_ADDR |
                              ( LCD_20x4_LINE1_FIRST_CHARACTER_ADDRESS +
                                charPositionX ) );
            delay( 1 );         
        break;
       
        case 1:
            lcdCodeWrite( LCD_RS_INSTRUCTION, 
                              LCD_IR_SET_DDRAM_ADDR |
                              ( LCD_20x4_LINE2_FIRST_CHARACTER_ADDRESS +
                                charPositionX ) );
            delay( 1 );         
        break;
       
        case 2:
            lcdCodeWrite( LCD_RS_INSTRUCTION, 
                              LCD_IR_SET_DDRAM_ADDR |
                              ( LCD_20x4_LINE3_FIRST_CHARACTER_ADDRESS +
                                charPositionX ) );
            delay( 1 );         
        break;

        case 3:
            lcdCodeWrite( LCD_RS_INSTRUCTION, 
                              LCD_IR_SET_DDRAM_ADDR |
                              ( LCD_20x4_LINE4_FIRST_CHARACTER_ADDRESS +
                                charPositionX ) );
            delay( 1 );         
        break;
    }
}

void lcdStringWrite( const char * str )
{
    while (*str) {
        lcdCodeWrite(LCD_RS_DATA, *str++);
    }
}

void lcdClear()
{
    lcdCharPositionWrite( 0,0 );
    lcdStringWrite("                ");
    lcdCharPositionWrite( 0,1 );
    lcdStringWrite("                ");
}


//=====[Implementations of private functions]==================================

static void lcdCodeWrite( bool type, uint8_t dataBus )
{
    if ( type == LCD_RS_INSTRUCTION ) 
        lcdPinWrite( LCD_PIN_RS, LCD_RS_INSTRUCTION);
    else
        lcdPinWrite( LCD_PIN_RS, LCD_RS_DATA);
    lcdPinWrite( LCD_PIN_RW, LCD_RW_WRITE );
    lcdDataBusWrite( dataBus );
}

static void lcdPinWrite( uint8_t pinName, int value )
{
    switch( pinName ) {
        case LCD_PIN_D0: lcdD0 = value;   break;
        case LCD_PIN_D1: lcdD1 = value;   break;
        case LCD_PIN_D2: lcdD2 = value;   break;
        case LCD_PIN_D3: lcdD3 = value;   break;
        case LCD_PIN_D4: lcdD4 = value;   break;
        case LCD_PIN_D5: lcdD5 = value;   break;
        case LCD_PIN_D6: lcdD6 = value;   break;
        case LCD_PIN_D7: lcdD7 = value;   break;
        case LCD_PIN_RS: lcdRs = value;   break;
        case LCD_PIN_EN: lcdEn = value;   break;
        case LCD_PIN_RW: break; 
        default: break;
    }
}

static void lcdDataBusWrite( uint8_t dataBus )
{
    lcdPinWrite( LCD_PIN_EN, OFF );
    lcdPinWrite( LCD_PIN_D7, dataBus & 0b10000000 );
    lcdPinWrite( LCD_PIN_D6, dataBus & 0b01000000 );
    lcdPinWrite( LCD_PIN_D5, dataBus & 0b00100000 );
    lcdPinWrite( LCD_PIN_D4, dataBus & 0b00010000 );
    lcdPinWrite( LCD_PIN_D3, dataBus & 0b00001000 );
    lcdPinWrite( LCD_PIN_D2, dataBus & 0b00000100 );  
    lcdPinWrite( LCD_PIN_D1, dataBus & 0b00000010 );      
    lcdPinWrite( LCD_PIN_D0, dataBus & 0b00000001 );
    lcdPinWrite( LCD_PIN_EN, ON );              
    delay( 1 );
    lcdPinWrite( LCD_PIN_EN, OFF );  
    delay( 1 );                   
}