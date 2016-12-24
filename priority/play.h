#ifndef __PLAY_H__
#define __PLAY_H__ 

#include "os_priority.h"

//CSS
#define TASK_BLOCK_STYLE_CORNER          '+'
#define TASK_BLOCK_STYLE_HORIZONTAL_EDGE '-'
#define TASK_BLOCK_STYLE_VERTICAL_EDGE   '|'

#define NUMBER_OF_TASKS_PER_COLUMN 2
#define TASK_BLOCK_WIDTH 12

void printAll(OSTaskControlBlock_t* );
void printOneLineContent(const char* string);
void printOneLineEdge(void);
OSTaskControlBlock_t* getTCB(OSTaskControlBlock_t* baseTCB, int offset);

#endif /*  __PLAY_H__ */