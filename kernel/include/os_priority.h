
#ifndef __OS_PRIORITY_H__
#define __OS_PRIORITY_H__ 

//functions operates on OSPriorityReadyTable

void OSPriorityReadyTableInitialize(void);

OSPriority_t OSGetHighestPriority(void);

void OSPrioritySetReady(OSPriority_t priority);

void OSPriorityClearReady(OSPriority_t priority);


//functions operates on OSTaskReadyTable
void OSTaskReadyTableInitialize(void);

void OSTaskReadyTableInsert(OSTaskControlBlock_t* taskControlBlock);

void OSTaskReadyTableInsertHead(OSTaskControlBlock_t* taskControlBlock);

void OSTaskReadyTableInsertTail(OSTaskControlBlock_t* taskControlBlock);

void OSTaskReadyTableMoveHeadToTail(void);

void OSTaskReadyTableRemove(OSTaskControlBlock_t* taskControlBlock);


#endif /* __OS_PRIORITY_H__ */