//=====[Libraries]=============================================================

#include "attendance_tracking_system.h"
#include "mbed.h"
#include "arm_book_lib.h"

#include "instructor_interface.h"
#include "lcd.h"
#include "class_info.h"
#include "matrix_keypad.h"
#include "debounce_button.h"

//=====[Declaration of private defines]========================================

//=====[Declaration of private data types]=====================================

//=====[Declaration and initialization of public global objects]===============

//=====[Declaration of external public global variables]=======================

//=====[Declaration and initialization of public global variables]=============

//=====[Declaration and initialization of private global variables]============

//=====[Declarations (prototypes) of private functions]========================

//=====[Implementations of public functions]===================================

bool isCodeForInstructor(char* code)
{
    return false;
}

bool isInstructorDone()
{
    return false;
}

void instructorInterfaceInit()
{
    classInfoInit();
    lcdInit();
    matrixKeypadInit(TIME_INCREMENT_MS);
    debounceButtonInit(D0); //Needs correct pin number
}

/**
 *  The instructor interface needs to check 
 *      If the instructor is scrolling (Press/Release Button)
 *      If the instructor is entering a new class start time (Using Keypad)
 *      If the instrcutor is finished with the interface  (Hold Button)
 */
void instructorInterfaceUpdate()
{

}

//=====[Implementations of private functions]==================================
