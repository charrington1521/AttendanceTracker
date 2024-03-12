//=====[Libraries]=============================================================

#include "attendance_tracking_system.h"
#include "lcd.h"
#include "mbed.h"
#include "arm_book_lib.h"

#include "matrix_keypad.h"
// #include "zbar.h"
// #include "ov7670.h"

// using namespace zbar;


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

//static zbar_decoder_t decoder = zbar_decoder_create();

//static zbar_image_t newestImage = zbar_image_create();

// static OV7670 camera {
//      Pins. .. . 
// }

// static ImageScanner scanner;

// static Image image;

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

    // scanner.set_config(ZBAR_NONE, ZBAR_CFG_ENABLE, 1);
    // scanner.set_config(ZBAR_EAN8, ZBAR_CFG_ENABLE, 1);

    // camera.CaptureNext();

    // image.set_data(,);
    // scanner.recycle_image(image);
    // SymbolSet results = scanner.get_results();
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
            char keypadOutput[2] = "";
            keypadOutput[0] = matrixKeypadUpdate();
            switch (keypadOutput[0])
            {
                case '\0': case '*': //And other ignore cases. . .

                    break;
                case '#':
                    memcpy(code, &tempCode, sizeof tempCode);
                    code_delegate_state = WAITING;
                    break;
                default:
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
