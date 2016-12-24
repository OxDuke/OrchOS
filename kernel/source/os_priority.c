
#include "os_priority.h"

#include "os_types.h"

//two tables, all functions in this file are for the operation on these two
//tables

OSCPUData_t OSPriorityReadyTable[OS_CONFIG_PRIORITY_READY_TABLE_SIZE];

OSTaskReadyTableNode_t OSTaskReadyTable[OS_CONFIG_NUMBER_OF_PRIORITY];



