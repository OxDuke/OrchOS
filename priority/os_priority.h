
#ifndef __OS_PRIORITY_H__
#define __OS_PRIORITY_H__

typedef char OSChar_t;

typedef unsigned int OSPriority_t;

typedef unsigned int OSCPUData_t;

typedef unsigned int OSUint32_t;

struct OSTaskControlBlock
{
	OSChar_t c;
	OSPriority_t priority;
	struct OSTaskControlBlock* next;
	struct OSTaskControlBlock* previous;
};

typedef struct OSTaskControlBlock OSTaskControlBlock_t;


struct OSTaskReadyTableNode
{
	OSUint32_t numberOfTasks;

	OSTaskControlBlock_t* taskListPointer;

};

typedef struct OSTaskReadyTableNode OSTaskReadyTableNode_t;

#define OS_CONFIG_PRIORITY_READY_TABLE_SIZE 3
//size of every entry in priority ready table in bits
#define PRIORITY_READY_TABLE_ENTRY_SIZE (sizeof(OSCPUData_t)*8)
#define PRIORITY_MAX_NUMBER (PRIORITY_READY_TABLE_ENTRY_SIZE*OS_CONFIG_PRIORITY_READY_TABLE_SIZE)


//functions operates on OSPriorityReadyTable

void OSPriorityReadyTablePrint(void);

void OSPriorityReadyTableInitialize(void);

OSPriority_t OSGetHighestPriority(void);

void OSPrioritySetReady(OSPriority_t priority);

void OSPriorityClearReady(OSPriority_t priority);


//functions operates on OSTaskReadyTable

void OSTaskReadyTablePrint(void);

void OSTaskReadyTableEntryPrint(OSPriority_t priority);

void OSTaskReadyTableInitialize(void);

void OSTaskReadyTableInsert(OSTaskControlBlock_t* taskControlBlock);

void OSTaskReadyTableInsertHead(OSTaskControlBlock_t* taskControlBlock);

void OSTaskReadyTableInsertTail(OSTaskControlBlock_t* taskControlBlock);

void OSTaskReadyTableMoveHeadToTail(OSPriority_t priority);

void OSTaskReadyTableRemove(OSTaskControlBlock_t* taskNeedRemove);


#endif /* __OS_PRIORITY_H__ */