
#include "os_info.h"

#include "stdio.h"

void OSPrintGlobalInfo(OSGlobalControlBlock_t* OSGlobalController)
{
	printf("----------OrchOS----------\n");
	printf("---The Real-Time Kernel---\n");
	printf("Now printing global info\n");

	printf("OS Name: %s\n", OSGlobalController->OSName);
	printf("OS Version: %s\n", OSGlobalController->OSVersion);
	printf("OS Developer: %s\n", OSGlobalController->OSDeveloper);

	//print info of all tasks
	printf("Now printing info of every single task\n");
	OSPrintAllTasksInfo(OSGlobalController);

}

void OSPrintAllTasksInfo(OSGlobalControlBlock_t* OSGlobalController)
{
	OSTaskControlBlock_t* p = OSGlobalController->tasksList;
	while (p != (OSTaskControlBlock_t*)0)
	{
		OSPrintSingleTaskInfo(p);
		p = p->next;
	}

}

void OSPrintSingleTaskInfo(OSTaskControlBlock_t* TCB)
{
	OSStackSize_t stackUsage;
	//@todo why top-base, not base -top
	stackUsage = 
	    (OSStackSize_t)(&TCB->stackBasePointer[TCB->stackSize - 1] - TCB->stackTopPointer) + 1;
	printf("\n----------------------\n");
	printf("now printing: %s\n", TCB->taskName);
	printf("stack size: %d\n", TCB->stackSize);
	printf("stack base at: %x\n", (&TCB->stackBasePointer[TCB->stackSize - 1]));
	printf("stack top at: %x\n", TCB->stackTopPointer);
	printf("stack limit at: %x\n", TCB->stackBasePointer);
	printf("stack usage: %d\n", stackUsage);
	printf("----------------------\n");
}
