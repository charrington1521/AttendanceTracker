//=====[Libraries]=============================================================

#include "mbed.h"
#include "arm_book_lib.h"

#include "student_interface.h"
#include "class_info.h"
#include "lcd.h"
#include "led.h"

//=====[Declaration of private defines]========================================

//=====[Declaration of private data types]=====================================

//=====[Declaration and initialization of public global objects]===============

//=====[Declaration of external public global variables]=======================

//=====[Declaration and initialization of public global variables]=============

//=====[Declaration and initialization of private global variables]============

//=====[Declarations (prototypes) of private functions]========================

//=====[Implementations of public functions]===================================

/**
 *  Returns true if the given code is for a student,
 *      false otherwise
 */
bool isCodeForAStudent(char* code)
{
    //Should this be public???
    return false;
}

//Should this be public???
void checkInStudent(char* code)
{
    //Should simply use the class_info modules check in
}

void studentInterfaceInit()
{
    classInfoInit();
    lcdInit();
    ledInit(D1, D2, D3);
}

/**
 * Updates the student interface: 
 * checks in students and gives feedback
 */
void studentInterfaceUpdate(char * code)
{
    // Should check if code belongs to a student, and if it does
    // Should blink the led, check the student in, and display some
    // message to the LCD 
}

//=====[Implementations of private functions]==================================
