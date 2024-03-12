//=====[Libraries]=============================================================

#include "attendance_tracking_system.h"
#include "date_and_time.h"
#include "lcd.h"
#include "mbed.h"
#include "arm_book_lib.h"

#include "instructor_interface.h"
#include "class_info.h"
#include "matrix_keypad.h"
#include "debounce_button.h"

//=====[Declaration of private defines]========================================

#define INSTRUCTOR_CODE             "ABC123"

#define EXIT_PRESS_TIME_MS              3000

//=====[Declaration of private data types]=====================================

typedef enum
{
    VIEWING_STUDENTS,
    SETTING_TIME
} instructor_interface_state_t;

//=====[Declaration and initialization of public global objects]===============

//=====[Declaration of external public global variables]=======================

//=====[Declaration and initialization of public global variables]=============

//=====[Declaration and initialization of private global variables]============

static bool instructorDone = false;
static int buttonPressTime = 0; 
static int lcdWriteDelayMs = 0;
static int studentViewIndex = 0;
static int dateTimeIndex = 0;

static instructor_interface_state_t state;
static char newClassTime[4];

//=====[Declarations (prototypes) of private functions]========================

/**
 *  Expected input is only characters that may be received from the keypad.
 */
static bool isDigit(char some_char);

//=====[Implementations of public functions]===================================

bool isCodeForInstructor(char* code)
{
    return strcmp(code, INSTRUCTOR_CODE) == 0;
}

bool isInstructorDone()
{
    return instructorDone;
}

void instructorInterfaceInit()
{
    classInfoInit();
    lcdInit();
    matrixKeypadInit(TIME_INCREMENT_MS);
    debounceButtonInit(D13);
}

void instructorInterfaceReset()
{
    dateTimeIndex = 0;
    state = VIEWING_STUDENTS;
    lcdWriteDelayMs = 1000;
    studentViewIndex = 0;
    instructorDone = false;
}

/**
 *  The instructor interface needs to check 
 *      If the instructor is scrolling (Press/Release Button)
 *      If the instructor is entering a new class start time (Using Keypad)
 *      If the instrcutor is finished with the interface  (Hold Button)
 */
void instructorInterfaceUpdate()
{
    switch (state)
    {
        case VIEWING_STUDENTS:
            if (matrixKeypadUpdate() == '#')
            {
                dateTimeIndex = 0;
                memcpy(newClassTime, 0, sizeof newClassTime);
                state = SETTING_TIME;
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
                            studentViewIndex++;
                            studentViewIndex %= NUM_STUDENTS;
                        }
                        buttonPressTime = 0;
                        break;
                    default:
                        buttonPressTime = 0;
                        break;
                }

                lcdWriteDelayMs += TIME_INCREMENT_MS;
                if (lcdWriteDelayMs >= 1000) 
                {
                    lcdClear();
                    lcdCharPositionWrite( 0,0 );
                    lcdStringWrite(studentByIndex(studentViewIndex)->name);
                    lcdCharPositionWrite( 0,1 );
                    switch (studentByIndex(studentViewIndex)->timeResult)
                    {
                        case EARLY:
                            lcdStringWrite("Student Early");
                        break;

                        case ON_TIME:
                            lcdStringWrite("Student On Time");
                        break;

                        case LATE:
                            lcdStringWrite("Student Late");
                        break;

                        default:
                            lcdStringWrite("Not Checked In");
                        break;
                    }
                    lcdWriteDelayMs = 0;
                }
            }
        break;

        case SETTING_TIME:
            static char newClassTime[4] = "";
            lcdWriteDelayMs += TIME_INCREMENT_MS;
            if (lcdWriteDelayMs >= 1000) 
            {
                lcdClear();
                lcdCharPositionWrite( 0,0 );
                lcdStringWrite("New Class Time: ");
                lcdCharPositionWrite( 0,1 );
                lcdStringWrite("(HH:MM)   :     ");
                lcdCharPositionWrite( 8,1 );
                char str[3] = ""; str[0] = newClassTime[0]; str[1] = newClassTime[1];
                lcdStringWrite(str); 
                lcdCharPositionWrite( 11,1 ); 
                char str2[3] = ""; str2[0] = newClassTime[2]; str2[1] = newClassTime[3];
                lcdStringWrite(str2); 
                lcdWriteDelayMs = 0;
            }
            //Display the new date and time entry. . . ?
            //lcdCharPositionWrite( 8,1 );
            char keypadEntry[] = {matrixKeypadUpdate()};
            if (isDigit(keypadEntry[0]) && dateTimeIndex < 4)
            {
                newClassTime[dateTimeIndex] = keypadEntry[0];
                dateTimeIndex++;
                if (dateTimeIndex == 4)
                {
                    char hour[3] = "";
                    char min[3] = "";
                    hour[0] = newClassTime[0]; hour[1] = newClassTime[1];
                    min[0]  = newClassTime[2]; min[1]  = newClassTime[3];
                    setClassStartTime(atoi(hour), atoi(min));
                    state = VIEWING_STUDENTS;
                }
            }
        break;
    }

}

//=====[Implementations of private functions]==================================

bool isDigit(char someChar)
{
    switch(someChar)
    {
        case 'A': case 'B': case 'C': case 'D': case '*': case '#': case '\0':
            return false;
        default:
            return true;

    }
}