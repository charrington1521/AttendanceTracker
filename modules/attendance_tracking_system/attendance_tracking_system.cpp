//=====[Libraries]=============================================================

#include "mbed.h"
#include "arm_book_lib.h"

#include "attendance_tracking_system.h"
#include "instructor_interface.h"
#include "student_interface.h"
#include "code_delegate.h"

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
    codeDelegateInit();
    instructorInterfaceInit();
    studentInterfaceInit();
}

void attendanceTrackingUpdate()
{
    codeDelegateUpdate();

    char* newestCode = getNewestCode(); //The book would just use the uodate to return this

    if (isCodeForInstructor(newestCode))
    {
        isInstructorInterface = true;
    }
    else
    {
        //And some other stuff. . .
        studentInterfaceUpdate(newestCode);
    }
    if (isInstructorInterface)
    {
        instructorInterfaceUpdate();
        if (isInstructorDone())
        {
            isInstructorInterface = false;
        }
    }
    
    delay (TIME_INCREMENT_MS);
}

//=====[Implementations of private functions]==================================
