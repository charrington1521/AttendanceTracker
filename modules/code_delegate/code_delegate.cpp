//=====[Libraries]=============================================================

#include "attendance_tracking_system.h"
#include "mbed.h"
#include "arm_book_lib.h"

#include "matrix_keypad.h"
//#include "qr_code.h"


//=====[Declaration of private defines]========================================

//=====[Declaration of private data types]=====================================

//=====[Declaration and initialization of public global objects]===============

//=====[Declaration of external public global variables]=======================

//=====[Declaration and initialization of public global variables]=============

//=====[Declaration and initialization of private global variables]============

char code[100];

//=====[Declarations (prototypes) of private functions]========================

//=====[Implementations of public functions]===================================

/**
 *  Checks if a new code has been entered
 *  If a new code has been entered, it replaces the newest code
 */
void codeDelegateInit()
{
    matrixKeypadInit(TIME_INCREMENT_MS);
}

void codeDelegateUpdate()
{
    
}

char* getNewestCode()
{
    return code;
}

//=====[Implementations of private functions]==================================
