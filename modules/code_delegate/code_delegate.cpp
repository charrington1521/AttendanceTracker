//=====[Libraries]=============================================================

#include "attendance_tracking_system.h"
#include "lcd.h"
#include "mbed.h"
#include "arm_book_lib.h"

#include "matrix_keypad.h"
//#include "qr_code.h"


//=====[Declaration of private defines]========================================

typedef enum
{
    WAITING,
    SCANNING
} code_delegate_state_t;

//=====[Declaration of private data types]=====================================

//=====[Declaration and initialization of public global objects]===============

//=====[Declaration of external public global variables]=======================

//=====[Declaration and initialization of public global variables]=============

//=====[Declaration and initialization of private global variables]============

static char code[100];

static char tempCode[100];

static code_delegate_state_t code_delegate_state = WAITING;


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
    switch(code_delegate_state)
    {
        case WAITING:
            if (matrixKeypadUpdate() == '#')
            {
                memset(code, 0, sizeof code);
                memset(tempCode, 0, sizeof tempCode);
                code_delegate_state = SCANNING;
            }
            break;
        case SCANNING:
            char keypadOutput[] = {matrixKeypadUpdate()};
            switch (keypadOutput[0])
            {
                case '\0': case '*': //And other ignore cases. . .

                    break;
                case '#':
                    memcpy(code, &tempCode, sizeof tempCode);
                    code_delegate_state = WAITING;
                    break;
                default:
                    keypadOutput[1] = '\0'; //For some reason the chars DX are appended to the keypadOutput
                    strcat(tempCode, keypadOutput);
                    break;
            }
            break;
    }
    
}

char* getNewestCode()
{
    static char toReturn[100];
    memset(toReturn, 0, sizeof toReturn);
    memcpy(toReturn, &code, sizeof code);
    memset(code, 0, sizeof code);
    return toReturn;
}

//=====[Implementations of private functions]==================================
