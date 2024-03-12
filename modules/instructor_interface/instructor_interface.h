//=====[#include guards - begin]===============================================

#ifndef _INSTRUCTOR_INTERFACE_H_
#define _INSTRUCTOR_INTERFACE_H_

//=====[Declaration of public defines]=========================================

//=====[Declaration of public data types]======================================

//=====[Declarations (prototypes) of public functions]=========================

/**
 * @param code a string 
 * @return true if the code is for an instructor
            false otherwise
 */
bool isCodeForInstructor(char* code);

/**
 * @return true if the instructor has signified they are done
            false otherwise
 */
bool isInstructorDone();

/**
 * Initializes the instructor interface 
 */
void instructorInterfaceInit();

/**
 * Prepares the instructor interface to be launched 
 * anew.
 */
void instructorInterfaceReset();

/**
 * Updates the instructor interface. Handling button presses,
 * releases, and holds. Also updates the display. Changes class
 * time when keypad is used. 
 */
void instructorInterfaceUpdate();

//=====[#include guards - end]=================================================

#endif // _INSTRUCTOR_INTERFACE_H_