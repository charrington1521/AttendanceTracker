//=====[#include guards - begin]===============================================

#ifndef _CODE_DELEGATE_H_
#define _CODE_DELEGATE_H_

//=====[Declaration of public defines]=========================================

//=====[Declaration of public data types]======================================

//=====[Declarations (prototypes) of public functions]=========================

/**
 * Retrieves and "consumes" the most recent code scanned
 * @return the most recently received code
            an empty string if there is no new code
 */
char* getNewestCode();

/**
 * Initializes the code delegate
 */
void codeDelegateInit();

/**
 *  Updates the code delegate
 */
void codeDelegateUpdate();

//=====[#include guards - end]=================================================

#endif // _CODE_DELEGATE_H_