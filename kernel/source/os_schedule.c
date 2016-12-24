/*=====================================================================

os_schedule.c - OrchOS The Real-Time Kernel

Copyright (c) 2016 Weidong Sun.  All right reserved.

Contact information
 -------------------
 Weidong Sun, China
 Web      :  under construction yet
 e-mail   :  swdswd28@gmail.com

This file is part of the OrchOS project
======================================================================*/

/**
 * This file
 */

#include "os_schedule.h"

extern OSTaskControlBlock_t* OSTCBCurPtr;              
extern OSTaskControlBlock_t* OSTCBHighRdyPtr;

void OSStart(OSTaskControlBlock_t* taskControlBlock)
{
	OSTCBCurPtr = taskControlBlock;				 
	OSTCBHighRdyPtr = taskControlBlock;
	OSStartHighRdy();
}

void OSSchedule(OSTaskControlBlock_t* taskControlBlockNow, OSTaskControlBlock_t* taskControlBlockNext)
{
	OSTCBCurPtr = taskControlBlockNow;
	OSTCBHighRdyPtr = taskControlBlockNext;
	OSCtxSw();
}

