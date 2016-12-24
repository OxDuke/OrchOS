
#include "play.h"
#include "eprintf.h"

int strlen(const char* string)
{
	int length = 0;

	while (*string++ != '\0')
	{
		length++;
		if (length == 0xffffffff)
			break;
	}

	return length;
}

void printAll(OSTaskControlBlock_t* tcb)
{
	int remainingNumberOfBlocks = 0;
	int index = 0;
	int i = 0;
	int numberOfBlocksNeedToPrint = 0;
	OSTaskControlBlock_t* currentTCB = (OSTaskControlBlock_t*)0;
	//the +1 is to give space for the '\0', the string shall at most hold
	//TASK_BLOCK_WIDTH characters
	char tempString[TASK_BLOCK_WIDTH + 1] = {'\0'};

	//calculate numbers of blocks
	currentTCB = tcb;
	while (currentTCB != (OSTaskControlBlock_t*)0)
	{
		remainingNumberOfBlocks++;
		currentTCB = currentTCB->next;
	}
	currentTCB = (OSTaskControlBlock_t*)0;

	while (remainingNumberOfBlocks > 0)
	{

		//calculate the numver of blocks needed to print this time
		numberOfBlocksNeedToPrint =
		    (remainingNumberOfBlocks >= NUMBER_OF_TASKS_PER_COLUMN) ?
		    NUMBER_OF_TASKS_PER_COLUMN : remainingNumberOfBlocks;

		remainingNumberOfBlocks -= numberOfBlocksNeedToPrint;

		for (i = 0; i < numberOfBlocksNeedToPrint; ++i)
		{
			printOneLineEdge();
		}
		eputchar('\n');

		for (i = 0; i < numberOfBlocksNeedToPrint; ++i)
		{
			currentTCB = getTCB(tcb, index + i);
			esprintf(tempString, "Name: %c", currentTCB->c);
			printOneLineContent(tempString);
		}
		eputchar('\n');

		for (i = 0; i < numberOfBlocksNeedToPrint; ++i)
		{
			currentTCB = getTCB(tcb, index + i);
			esnprintf(tempString, TASK_BLOCK_WIDTH, "priority: %d", currentTCB->priority);
			printOneLineContent(tempString);
		}
		eputchar('\n');

		index += NUMBER_OF_TASKS_PER_COLUMN;

		for (i = 0; i < numberOfBlocksNeedToPrint; ++i)
		{
			printOneLineEdge();
		}
		eputchar('\n');
	}

	eprintf("\n");
}

void printOneLineEdge(void)
{
	int i;

	eputchar(TASK_BLOCK_STYLE_CORNER);

	for (i = 0; i < TASK_BLOCK_WIDTH; ++i)
		eputchar(TASK_BLOCK_STYLE_HORIZONTAL_EDGE);

	eputchar(TASK_BLOCK_STYLE_CORNER);

//	eputchar('\n');
}

void printOneLineContent(const char* string)
{
	int i;
	int stringLength = strlen(string);

	//print left edge
	eputchar(TASK_BLOCK_STYLE_VERTICAL_EDGE);

	//truncate the string to fit in the block
	if (stringLength > TASK_BLOCK_WIDTH)
	{
		for ( i = 0; i < TASK_BLOCK_WIDTH; ++i)
		{
			eputchar(*string++);
			eprintf("truncate: i = %d", i);
			if (i > 10)
				return;
		}
	}
	else //pad the output to fit in the block
	{
		while (*string != '\0')
			eputchar(*string++);
		for (int i = 0; i < TASK_BLOCK_WIDTH - stringLength; ++i)
		{
			eputchar(' ');
		}
	}

	//print right edge
	eputchar(TASK_BLOCK_STYLE_VERTICAL_EDGE);
}

/**
 * [getTCB description]
 * @param  baseTCB [description]
 * @param  offset  offset starts from baseTCB, while =0 means baseTCB itself
 * @return         [description]
 */
OSTaskControlBlock_t* getTCB(OSTaskControlBlock_t* baseTCB, int offset)
{
	int numberOfBlocks = 0;
	OSTaskControlBlock_t* currentTCB = (OSTaskControlBlock_t*)0;

	currentTCB = baseTCB;

	while (currentTCB != (OSTaskControlBlock_t*)0)
	{
		numberOfBlocks++;
		currentTCB = currentTCB->next;
	}

	if (offset > numberOfBlocks - 1 )
	{
		offset = numberOfBlocks - 1;
	}

	currentTCB = baseTCB;

	for (int i = 0; i < 10; ++i)
	{
		if (offset == 0)
			return currentTCB;

		offset--;
		currentTCB = currentTCB->next;
	}
}