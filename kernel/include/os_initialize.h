#ifndef __OS__INITIALIZE_H__
#define __OS__INITIALIZE_H__ 

#include "os_types.h"


void OSTaskCreate(OSGlobalControlBlock_t* OSGlobalController,
	              OSTaskControlBlock_t* taskControlBlock,
                  OSChar_t*                taskName,
                  OSTaskAddress_t          taskEntryAddress,
                  OSStack_t*               stackBasePointer,
                  OSStackSize_t            stackSize);

//OSTaskCreate helper functions starts here
void OSTaskControlBlockClear(
    OSTaskControlBlock_t* taskControlBlock);

void OSTaskControlBlockAddToGlobal(
	OSGlobalControlBlock_t* OSGlobalController,
    OSTaskControlBlock_t* taskControlBlock);
//OSTaskCreate helper functions ends here


void OSGlobalControlBlockInitialize(
	OSGlobalControlBlock_t* OSGlobalController);

                  
#endif /*  __OS__INITIALIZE_H__  */
