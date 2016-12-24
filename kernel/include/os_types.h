/*=====================================================================

os_types.c - OrchOS The Real-Time Kernel

Copyright (c) 2016 Weidong Sun.  All right reserved.

Contact information
 -------------------
 Weidong Sun, China
 Web      :  under construction yet
 e-mail   :  swdswd28@gmail.com

This file is part of the OrchOS project
======================================================================*/

/**
 * This file declares all of the types that would be used in OrchOS
 */
 
#ifndef __OS_TYPES_H__
#define __OS_TYPES_H__


#include "os_cpu_types.h"

//#include "os_config"

/**
 * 
 */
 
typedef struct OSTaskControlBlock OSTaskControlBlock_t;

typedef struct OSGlobalControlBlock OSGlobalControlBlock_t;

typedef struct OSStatisticsBlock OSStatisticsBlock_t;

typedef struct OSTaskReadyTableNode OSTaskReadyTableNode_t;

struct OSTaskControlBlock
{
	//==== Field concerning stacks starts here ====//
	
	//stackTopPointer points to the top of the stack of a task
	OSStack_t* stackTopPointer;

	OSStack_t* stackBasePointer;

	OSStackSize_t stackSize;

	//==== Field concerning stacks ends here ====//

    OSChar_t* taskName;

    OSTaskAddress_t taskEntryAddress;

    struct OSTaskControlBlock* next;
    struct OSTaskControlBlock* previous;
	
};

struct OSGlobalControlBlock
{
	OSChar_t* OSName;

	OSChar_t* OSVersion;

	OSChar_t* OSDeveloper;

	OSUint32_t numberOfTasks;
	
	OSTaskControlBlock_t* currentTask;

	OSTaskControlBlock_t* tasksList;

};

struct OSStatisticsBlock
{
	char c;
};

struct OSTaskReadyTableNode
{
	OSUint32_t numberOfTasks;

	OSTaskControlBlock_t* tasksListHeadPointer;

	OSTaskControlBlock_t* tasksListTailPointer;
	
};


#endif /* __OS_TYPES_H__ */
