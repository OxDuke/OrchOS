#ifndef __OS_SCHEDULE_H__
#define __OS_SCHEDULE_H__ 

#include "os_types.h"

void  OSCtxSw              (void);
void  OSStartHighRdy       (void);
void  OS_CPU_PendSVHandler (void);

void OSStart(OSTaskControlBlock_t* OSTaskControlBlock);
void OSSchedule(OSTaskControlBlock_t* taskControlBlockNow,OSTaskControlBlock_t* taskControlBlockNext);

#endif /* __OS_SCHEDULE_H__ */
