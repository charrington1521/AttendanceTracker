//=====[#include guards - begin]===============================================

#ifndef _STUDENT_INTERFACE_H_
#define _STUDENT_INTERFACE_H_

//=====[Declaration of public defines]=========================================

//=====[Declaration of public data types]======================================

//=====[Declarations (prototypes) of public functions]=========================

/**
 *  Returns true if the given code is for a student,
 *      false otherwise
 */
bool isCodeForAStudent(char* code);

void checkInStudent(char* code);

void studentInterfaceInit();

/**
 * Updates the student interface: 
 * checks in students and gives feedback
 */
void studentInterfaceUpdate(char* code);

//=====[#include guards - end]=================================================

#endif // _STUDENT_INTERFACE_H_