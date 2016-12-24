
#ifndef __OS_CPU_C_H__
#define __OS_CPU_C_H__ 

#include "os_cpu_types.h"

#include "os_types.h"

OSStack_t* OSTaskStackInitialize (
	OSTaskAddress_t taskEntryAddress,
                         void*     argumentsPointer,
                         OSStack_t*       stackBasePointer,
                         OSStack_t*       stackLimitPointer,
                         OSStackSize_t   stackSize);

#endif /* __OS_CPU_C_H__  */

