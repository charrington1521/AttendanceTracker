//=====[Libraries]=============================================================

#include "attendance_tracking_system.h"
#include "mbed.h"
#include "arm_book_lib.h"

#include "student_interface.h"
#include "class_info.h"
#include "led.h"

//=====[Declaration of private defines]========================================

//=====[Declaration of private data types]=====================================

//=====[Declaration and initialization of public global objects]===============

//=====[Declaration of external public global variables]=======================

//=====[Declaration and initialization of public global variables]=============

//=====[Declaration and initialization of private global variables]============

int lcd_write_delay_ms;

//=====[Declarations (prototypes) of private functions]========================

void checkInMessage();

//=====[Implementations of public functions]===================================

/**
 *  Returns true if the given code is for a student,
 *      false otherwise
 */
bool isCodeForAStudent(char* code)
{

    return isCodeAStudent(code);
}

//Should this be public???
void checkInStudent(char* code)
{
    checkInStudentByCode(code);
}

void studentInterfaceInit()
{
    classInfoInit();
    ledInit(PB_4, PA_0, PD_12);
    setColor(NO_COLOR);
}

/**
 * Updates the student interface: 
 * checks in students and gives feedback
 */
void studentInterfaceUpdate(char * code)
{
    lcd_write_delay_ms += TIME_INCREMENT_MS;
    if (lcd_write_delay_ms >= 1000)
    {
        lcdClear();
        lcdCharPositionWrite( 0,0 );
        lcdStringWrite("Awaiting Student");
        lcd_write_delay_ms = 0;
    }
    if (isCodeForAStudent(code))
    {
        checkInStudent(code);
        // set the color. . .
        blinkLed();
        checkInMessage();
    }

    ledUpdate();
}

//=====[Implementations of private functions]==================================

void checkInMessage()
{
    lcdClear();
    lcdCharPositionWrite( 0,0 );
    lcdStringWrite("Welcome. . .    ");
}