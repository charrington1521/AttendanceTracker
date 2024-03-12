//=====[#include guards - begin]===============================================

#ifndef _STUDENT_INTERFACE_H_
#define _STUDENT_INTERFACE_H_

//=====[Declaration of public defines]=========================================

//=====[Declaration of public data types]======================================

//=====[Declarations (prototypes) of public functions]=========================

/**
 * @param code a string
 * @return true if the code represents a student
            false otherwise
 */
bool isCodeForAStudent(char* code);

/**
 *  Initializes the student interface
 */
void studentInterfaceInit();

/**
 * Updates the student interface: 
 * checks in students and gives feedback
 */
void studentInterfaceUpdate(char* code);

//=====[#include guards - end]=================================================

#endif // _STUDENT_INTERFACE_H_