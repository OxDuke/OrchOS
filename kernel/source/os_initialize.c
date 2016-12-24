/*=====================================================================

os_initialize.c - OrchOS The Real-Time Kernel

Copyright (c) 2016 Weidong Sun.  All right reserved.

Contact information
 -------------------
 Weidong Sun, China
 Web      :  under construction yet
 e-mail   :  swdswd28@gmail.com

This file is part of the OrchOS project
======================================================================*/

#include "os_initialize.h"
#include "os_cpu_c.h"

#include "stdio.h"

/**
 * This file contains functions doing initialzing works
 */

void OSTaskCreate(OSGlobalControlBlock_t* OSGlobalController,
                  OSTaskControlBlock_t* taskControlBlock,
                  OSChar_t*                taskName,
                  OSTaskAddress_t          taskEntryAddress,
                  OSStack_t*               stackBasePointer,
                  OSStackSize_t            stackSize)
{
	//step.1 clear taskControlBlock
	OSTaskControlBlockClear(taskControlBlock);

	//step.2 deal with the stack stuff

	taskControlBlock->stackTopPointer = OSTaskStackInitialize(
	                                        taskEntryAddress,
	                                        (void*) 0,
	                                        stackBasePointer,
	                                        (void*) 0,
	                                        stackSize);
	//step3. set other fields
	taskControlBlock->stackBasePointer = stackBasePointer;

	taskControlBlock->stackSize = stackSize;

	taskControlBlock->taskName = taskName;

	taskControlBlock->taskEntryAddress = taskEntryAddress;

	//step4. add taskControlBlock to GlobalController
	OSTaskControlBlockAddToGlobal(OSGlobalController, taskControlBlock);
}

/**
 * clear all the fields in a taskControlBlock
 * @param taskControlBlock [description]
 */
void OSTaskControlBlockClear(
    OSTaskControlBlock_t* taskControlBlock)
{
	taskControlBlock->stackTopPointer = (OSStack_t*) 0;

	taskControlBlock->stackBasePointer = (OSStack_t*) 0;

	taskControlBlock->stackSize = (OSStackSize_t) 0;

	taskControlBlock->taskName = (OSChar_t*) 0;

	taskControlBlock->taskEntryAddress = (OSTaskAddress_t) 0;

	taskControlBlock->next = (OSTaskControlBlock_t*)0;

	taskControlBlock->previous = (OSTaskControlBlock_t*)0;
}

void OSTaskControlBlockAddToGlobal(
    OSGlobalControlBlock_t* OSGlobalController,
    OSTaskControlBlock_t* taskControlBlock)
{
	OSTaskControlBlock_t* p = OSGlobalController->tasksList;

//@todo add connection to previous blocks
	if (p == (OSTaskControlBlock_t*)0) //the list is empty
	{
		OSGlobalController->tasksList = taskControlBlock;
		printf("first\n");
		printf("created task name: %s\n", taskControlBlock->taskName);
	
	}
	else
	{
		printf("not first\n");
		while (p->next != (OSTaskControlBlock_t*)0)
		{
			p = p->next;
		}

		p->next = taskControlBlock;
		printf("created task name: %s\n", taskControlBlock->taskName);
	}

	OSGlobalController->numberOfTasks++;
	printf("number of tasks: %d\n", OSGlobalController->numberOfTasks);
}


void OSGlobalControlBlockInitialize(
    OSGlobalControlBlock_t* OSGlobalController)
{
	OSGlobalController->OSName = "OrchOS - OrchestraOS The Real-Time Kernel";

	OSGlobalController->OSVersion = "v0.51";

	OSGlobalController->OSDeveloper = "Weidong Sun";

	OSGlobalController->numberOfTasks = 0;

	OSGlobalController->currentTask = (OSTaskControlBlock_t*)0;

	OSGlobalController->tasksList = (OSTaskControlBlock_t*)0;

}
