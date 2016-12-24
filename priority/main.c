
#include "os_priority.h"
#include "eprintf.h"
#include "play.h"
#include "stdio.h"

void tcbInit(OSTaskControlBlock_t* tcb, OSChar_t c, OSPriority_t priority);

OSTaskControlBlock_t t1, t2, t3, t4, t5, t6, t7;

int main(int argc, char const *argv[])
{
	LINK_USER_OUTPUT(putchar);

	tcbInit(&t1, 'a', 0);
	tcbInit(&t2, 'b', 0);
	tcbInit(&t3, 'c', 0);
	tcbInit(&t4, 'd', 0);
	tcbInit(&t5, 'e', 1);
	tcbInit(&t6, 'f', 2);
	tcbInit(&t7, 'g', 2);

	OSPriorityReadyTableInitialize();
	OSTaskReadyTableInitialize();

//	OSPriorityReadyTablePrint();
//	OSTaskReadyTableEntryPrint(0);

	OSTaskReadyTableInsertTail(&t1);
	OSTaskReadyTableInsertTail(&t2);
	OSTaskReadyTableInsertTail(&t3);
	OSTaskReadyTableInsertTail(&t4);

	printAll(&t1);

	return 0;
}

void tcbInit(OSTaskControlBlock_t* tcb, OSChar_t c, OSPriority_t priority)
{
	tcb->c = c;
	tcb->priority = priority;
	tcb->next = (OSTaskControlBlock_t*)0;
	tcb->previous = (OSTaskControlBlock_t*)0;
}

