//=====[Libraries]=============================================================

#include "lcd.h"
#include "matrix_keypad.h"
#include "mbed.h"
#include "arm_book_lib.h"

#include "matrix_keypad.h"
#include "attendance_tracking_system.h"
#include "instructor_interface.h"
#include "student_interface.h"
#include "code_delegate.h"
#include "date_and_time.h"

//=====[Declaration of private defines]========================================

//=====[Declaration of private data types]=====================================

//=====[Declaration and initialization of public global objects]===============

//=====[Declaration of external public global variables]=======================

//=====[Declaration and initialization of public global variables]=============

//=====[Declaration and initialization of private global variables]============

bool isInstructorInterface = false;

//=====[Declarations (prototypes) of private functions]========================

//=====[Implementations of public functions]===================================

void attendanceTrackingInit()
{
    matrixKeypadInit(TIME_INCREMENT_MS);
    char year[5] = "";
    char month[3] = "";
    char day[3] = "";
    char hour[3] = "";
    char minute[3] = "";
    char second[3] = "";
    int i = 0;
    while (i < 4)
    {
        char read = matrixKeypadUpdate();
        if (read == '\0')
        {
            delay(TIME_INCREMENT_MS);
        }
        else
        {
            year[i] = read;
            i++;
        }
    }
    i = 0;
    while (i < 2)
    {
        char read = matrixKeypadUpdate();
        if (read == '\0')
        {
            delay(TIME_INCREMENT_MS);
        }
        else
        {
            month[i] = read;
            i++;
        }
    }
    i = 0;
    while (i < 2)
    {
        char read = matrixKeypadUpdate();
        if (read == '\0')
        {
            delay(TIME_INCREMENT_MS);
        }
        else
        {
            day[i] = read;
            i++;
        }
    }
    i = 0;
    while (i < 2)
    {
        char read = matrixKeypadUpdate();
        if (read == '\0')
        {
            delay(TIME_INCREMENT_MS);
        }
        else
        {
            hour[i] = read;
            i++;
        }
    }
    i = 0;
    while (i < 2)
    {
        char read = matrixKeypadUpdate();
        if (read == '\0')
        {
            delay(TIME_INCREMENT_MS);
        }
        else
        {
            minute[i] = read;
            i++;
        }
    }
    i = 0;
    while (i < 2)
    {
        char read = matrixKeypadUpdate();
        if (read == '\0')
        {
            delay(TIME_INCREMENT_MS);
        }
        else
        {
            second[i] = read;
            i++;
        }
    }
    dateAndTimeWrite(atoi(year), atoi(month), atoi(day), atoi(hour), atoi(minute), atoi(second));
    lcdInit();
    codeDelegateInit();
    instructorInterfaceInit();
    studentInterfaceInit();
}

void attendanceTrackingUpdate()
{
    if (isInstructorInterface)
    {
        instructorInterfaceUpdate();
        if (isInstructorDone())
        {
            isInstructorInterface = false;
        }
    }
    else
    {
        codeDelegateUpdate();

        char* newestCode = getNewestCode(); 

        if (isCodeForInstructor(newestCode))
        {
            isInstructorInterface = true;
            instructorInterfaceReset();
        }
        else
        {
            studentInterfaceUpdate(newestCode);
        }
    }

    delay (TIME_INCREMENT_MS);
}

//=====[Implementations of private functions]==================================
