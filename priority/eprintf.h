/*=====================================================================

eprintf.h - Embedded String I/O Library

Copyright (c) 2016 Weidong Sun.  All right reserved.

Contact information
 -------------------
 Weidong Sun, China
 Web      :  under construction yet
 e-mail   :  swdswd28@gmail.com

This file is part of the Embedded String I/O library
======================================================================*/

#ifndef __EPRINTF_H__
#define __EPRINTF_H__

#include "stdarg.h"

/**
 * @warning: user shall always remember to use the LINK_USER_OUTPUT() Macro
 *           to link the one-byte output function
 *           e.g. LINK_USER_OUTPUT(UART1_PrintOneByte);
 *                LINK_USER_OUTPUT(LCD_PrintOneByte);
 */

//set the max width of correct integer output in eprintf, evprintf, esprintf
#define NUMERAL_STRING_MAX_LENGTH 32

//set to 1 when you want to convert \n ==> \r\n in the output
#define CONVERT_CR_TO_CRLF_ENABLED 0

//------------user-concern functions-----------------//



//------------input functions-----------------//




//------------output functions-----------------//
#define LINK_USER_OUTPUT(userOutput) eUserputchar = (void(*)(unsigned char))(userOutput)
extern void (*eUserputchar)(unsigned char);

void eputchar(int character);
void eputs(const char* string);

void eprintf (const char* formatStringPointer, ...);
void esprintf(char* buffer, const char* formatStringPointer, ... );
void esnprintf(char* buffer, int size, const char* formatStringPointer, ... );

void evprintf (const char*	formatStringPointer, va_list argumentsPointer);
void evsprintf(char *buffer, const char *formatStringPointer, va_list argumentsPointer);

#endif /* __EPRINTF_H__ */
