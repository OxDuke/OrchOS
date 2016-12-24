
#ifndef __OS_INFO_H__
#define __OS_INFO_H__ 

#include "os_types.h"

void OSPrintGlobalInfo(OSGlobalControlBlock_t* OSGlobalController);

void OSPrintAllTasksInfo(OSGlobalControlBlock_t* OSGlobalController);

void OSPrintSingleTaskInfo(OSTaskControlBlock_t* taskControlBlock);

#endif /* __OS_INFO_H__ */
