
#include "os_priority.h"
#include "eprintf.h"
#include "stdio.h"

//two tables, all functions in this file are for the operation on these two
//tables

OSCPUData_t OSPriorityReadyTable[OS_CONFIG_PRIORITY_READY_TABLE_SIZE];

OSTaskReadyTableNode_t OSTaskReadyTable[PRIORITY_MAX_NUMBER];

//functions operates on OSPriorityReadyTable

void OSPriorityReadyTablePrint(void)
{
	OSUint32_t i = 0;

	//LINK_USER_OUTPUT(putchar);

	for (i = 0; i < OS_CONFIG_PRIORITY_READY_TABLE_SIZE; ++i)
	{
		eprintf("%032b\n", OSPriorityReadyTable[i]);
	}
}

void OSPriorityReadyTableInitialize(void)
{
	OSUint32_t i = 0;

	for (i = 0; i < OS_CONFIG_PRIORITY_READY_TABLE_SIZE; i++)
	{
		OSPriorityReadyTable[i] = (OSCPUData_t)0;
	}
}

OSPriority_t OSGetHighestPriority(void)
{
	OSUint32_t i = 0, j = 0;
	OSCPUData_t priorityMask = 1 << (sizeof(OSCPUData_t) * 8 - 1);
	OSPriority_t highestPriority = (OSPriority_t)0;

	//while priority is not in this field
	while (OSPriorityReadyTable[i] == (OSCPUData_t)0)
	{
		//prevent i from exceeding boundary
		if (i >= OS_CONFIG_PRIORITY_READY_TABLE_SIZE - 1)
			break;

		highestPriority += PRIORITY_READY_TABLE_ENTRY_SIZE;

		i++;
	}


	while (!(OSPriorityReadyTable[i] & priorityMask))
	{
		highestPriority++;
		priorityMask = priorityMask >> 1;

		eprintf("pm = %032b\n", priorityMask);
		eprintf("hpe = %d\n", highestPriority);

		//prevent priorityMask from shifting over boundary
		if (priorityMask == (OSCPUData_t)0)
		{
			eprintf("equal");
			break;
		}
	}

	return highestPriority;
}

void OSPrioritySetReady(OSPriority_t priority)
{
	OSCPUData_t priorityMask = 1 << (PRIORITY_READY_TABLE_ENTRY_SIZE - 1);

	//argument check, can not exceed the largest priority
	if (priority > PRIORITY_MAX_NUMBER - 1)
		priority = PRIORITY_MAX_NUMBER - 1;

	//insert
	OSPriorityReadyTable[priority / PRIORITY_READY_TABLE_ENTRY_SIZE] |=
	    (priorityMask >> (priority % PRIORITY_READY_TABLE_ENTRY_SIZE));

}

void OSPriorityClearReady(OSPriority_t priority)
{
	OSCPUData_t priorityMask = 1 << (PRIORITY_READY_TABLE_ENTRY_SIZE - 1);

	//argument check, can not exceed the largest priority
	if (priority > PRIORITY_MAX_NUMBER - 1)
		priority = PRIORITY_MAX_NUMBER - 1;

	//clear
	OSPriorityReadyTable[priority / PRIORITY_READY_TABLE_ENTRY_SIZE] &=
	    ~(priorityMask >> (priority % PRIORITY_READY_TABLE_ENTRY_SIZE));

}


//functions operates on OSTaskReadyTable

void OSTaskReadyTablePrint(void)
{
	;
}


void OSTaskReadyTableEntryPrint(OSPriority_t priority)
{
	OSUint32_t i = 0;
	OSTaskControlBlock_t* p = (OSTaskControlBlock_t*)0;

	//argument check
	if (priority >= PRIORITY_MAX_NUMBER)
		priority = PRIORITY_MAX_NUMBER - 1;

	eprintf("print tasks under priority No.%d\n", priority);
	//print numberOfTasks
	eprintf("number of tasks: %d\n", OSTaskReadyTable[priority].numberOfTasks);

	//print tasks using the forward trasverse of a linked list
	i = 1;
	p = OSTaskReadyTable[priority].taskListPointer;

	while (p != (OSTaskControlBlock_t*)0)
	{
		eprintf("Task No.%d: %c\n", i++, p->c);
		p = p->next;
	}
}

void OSTaskReadyTableInitialize(void)
{
	OSUint32_t i = 0;

	for (i = 0; i < PRIORITY_MAX_NUMBER; i++)
	{
		OSTaskReadyTable[i].numberOfTasks = (OSUint32_t)0;

		OSTaskReadyTable[i].taskListPointer = (OSTaskControlBlock_t*) 0;
	}
}

void OSTaskReadyTableInsert(OSTaskControlBlock_t* taskControlBlock)
{
	OSTaskReadyTableInsertTail(taskControlBlock);
//	OSTaskReadyTableInsertHead(taskControlBlock);
}

void OSTaskReadyTableInsertHead(OSTaskControlBlock_t* taskControlBlock)
{
	OSPriority_t priority = taskControlBlock->priority;

	//argument check
	if (priority >= PRIORITY_MAX_NUMBER)
		priority = PRIORITY_MAX_NUMBER - 1;

	//insert right at the head!
	OSTaskReadyTable[priority].numberOfTasks++;
	taskControlBlock->next = OSTaskReadyTable[priority].taskListPointer;
	OSTaskReadyTable[priority].taskListPointer = taskControlBlock;

}

void OSTaskReadyTableInsertTail(OSTaskControlBlock_t* taskControlBlock)
{
	OSPriority_t priority = taskControlBlock->priority;
	OSTaskControlBlock_t* p = (OSTaskControlBlock_t*)0;

	//argument check
	if (priority >= PRIORITY_MAX_NUMBER)
		priority = PRIORITY_MAX_NUMBER - 1;

	//get to the tail and insert it!
	//the list is empty
	OSTaskReadyTable[priority].numberOfTasks++;
	if (OSTaskReadyTable[priority].taskListPointer == (OSTaskControlBlock_t*)0)
	{
		OSTaskReadyTable[priority].taskListPointer = taskControlBlock;
	}
	else //the list is not empty
	{
		p = OSTaskReadyTable[priority].taskListPointer;

		while (p->next != (OSTaskControlBlock_t*)0)
			p = p->next;

		p->next = taskControlBlock;
	}

	taskControlBlock->next = (OSTaskControlBlock_t*)0;
}

void OSTaskReadyTableMoveHeadToTail(OSPriority_t priority)
{
	OSTaskControlBlock_t* TCBNeedMove = (OSTaskControlBlock_t*)0;

	//argument check
	if (priority >= PRIORITY_MAX_NUMBER)
		priority = PRIORITY_MAX_NUMBER - 1;

	//get the task list
	TCBNeedMove = OSTaskReadyTable[priority].taskListPointer;

	//move the fucking tcb!
	if (TCBNeedMove != (OSTaskControlBlock_t*)0)
	{
		OSTaskReadyTable[priority].taskListPointer = TCBNeedMove->next;
		OSTaskReadyTableInsertTail(TCBNeedMove);
		OSTaskReadyTable[priority].numberOfTasks--;
	}
}

void OSTaskReadyTableRemove(OSTaskControlBlock_t* taskNeedRemove)
{
	OSPriority_t priority = taskNeedRemove->priority;
	OSTaskControlBlock_t* traversePointer = (OSTaskControlBlock_t*)0;
	OSTaskControlBlock_t* traversePreviousPointer = (OSTaskControlBlock_t*)0;

	//argument check
	if (taskNeedRemove == (OSTaskControlBlock_t*) 0)
		return;
	if (priority >= PRIORITY_MAX_NUMBER)
		priority = PRIORITY_MAX_NUMBER - 1;

	//if empty list ,return directly
	if (OSTaskReadyTable[priority].taskListPointer == (OSTaskControlBlock_t*) 0)
		return;

	//find a match using the very ID of task
	traversePointer = OSTaskReadyTable[priority].taskListPointer;

	//found a match at the very beginning
	if (traversePointer->c == taskNeedRemove->c)
	{
		//remove the task from the list and return
		OSTaskReadyTable[priority].taskListPointer = taskNeedRemove->next;
		OSTaskReadyTable[priority].numberOfTasks--;
		return;
	}
	//match is not at the begining, use another pointer to help
	traversePreviousPointer = traversePointer;
	traversePointer = traversePointer->next;
	while (traversePointer != (OSTaskControlBlock_t*)0)
	{
		//find a match!
		if (traversePointer->c == taskNeedRemove->c)
		{
			traversePreviousPointer->next = traversePointer->next;
			OSTaskReadyTable[priority].numberOfTasks--;
			return;
		}

		traversePreviousPointer = traversePreviousPointer->next;
		traversePointer = traversePointer->next;
	}

}





