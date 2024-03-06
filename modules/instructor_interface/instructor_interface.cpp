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

#define INSTRUCTOR_CODE             "abc123"

#define EXIT_PRESS_TIME_MS              3000

//=====[Declaration of private data types]=====================================

//=====[Declaration and initialization of public global objects]===============

//=====[Declaration of external public global variables]=======================

//=====[Declaration and initialization of public global variables]=============

//=====[Declaration and initialization of private global variables]============

static bool instructorDone = true;
static int buttonPressTime = 0; 

//=====[Declarations (prototypes) of private functions]========================

//=====[Implementations of public functions]===================================

bool isCodeForInstructor(char* code)
{
    //Will this compare char* with a string literal???
    return strcmp(code, INSTRUCTOR_CODE) == 0; //What does strcmp return. . .
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
    debounceButtonInit(D13); //Needs correct pin number
}

/**
 *  The instructor interface needs to check 
 *      If the instructor is scrolling (Press/Release Button)
 *      If the instructor is entering a new class start time (Using Keypad)
 *      If the instrcutor is finished with the interface  (Hold Button)
 */
void instructorInterfaceUpdate()
{
    if (matrixKeypadUpdate() == '#')
    {
        //Setting the date and time. . . 
    }
    else
    {
        switch (debounceButtonUpdate())
        {
            case BUTTON_DOWN:
                buttonPressTime += TIME_INCREMENT_MS;
                if (buttonPressTime >= EXIT_PRESS_TIME_MS)
                {
                    instructorDone = true;
                }
                break;
            case BUTTON_RISING:
                if (buttonPressTime > 0)
                {
                    //Scroll to the next student
                }
                buttonPressTime = 0;
                break;
            default:
                buttonPressTime = 0;
                break;
        }

    }
}

//=====[Implementations of private functions]==================================
