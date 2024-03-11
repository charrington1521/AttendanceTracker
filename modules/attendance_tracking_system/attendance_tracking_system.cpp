//=====[Libraries]=============================================================

#include "lcd.h"
#include "mbed.h"
#include "arm_book_lib.h"

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
    dateAndTimeWrite(2024, 03, 10, 8, 10, 00);
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

        //lcdStringWrite("Newest Code");
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
