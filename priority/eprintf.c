/*=====================================================================

eprintf.c - Embedded String I/O Library

Copyright (c) 2016 Weidong Sun.  All right reserved.

Contact information
 -------------------
 Weidong Sun, China
 Web      :  under construction yet
 e-mail   :  swdswd28@gmail.com

This file is part of the Embedded String I/O library
======================================================================*/
#define TRACE 0

#include "eprintf.h"

#if TRACE
#include "stdio.h"
#endif

//declare user-implemented output function
void (*eUserputchar)(unsigned char);

static char* outputPointer = (char*)0;

static int sizeActual = 0;
static int sizeLimit = 0;
static int sizeLimitEnabled = 0; //default is 0

void eputchar(int character)
{
	if (character == '\n' && CONVERT_CR_TO_CRLF_ENABLED)
		eputchar('\r');

	if (outputPointer == (char*)0) //writes to user-defined output
		eUserputchar((unsigned char) character);
	else //writes to string buffer
	{
		if (sizeLimitEnabled)
		{
			if (sizeActual >= sizeLimit)
			{
				sizeActual; //do nothing
				*outputPointer = '\0'; //end the string
			}
			else //not arrived at limit
			{
				sizeActual++;
				*outputPointer++ = (unsigned char)character;
			}
		}
		else //no size limit
			*outputPointer++ = (unsigned char)character;
	}

}


void eputs(const char* string)
{
	while (*string != '\0')
		eputchar(*string++);
}


/**
 * Print a formatted string to default I/O
 * @param formatStringPointer Pointer to the format string
 */
void eprintf (const char* formatStringPointer, ...)
{
	va_list argumentsPointer;

	va_start(argumentsPointer, formatStringPointer);
	evprintf(formatStringPointer, argumentsPointer);
	va_end(argumentsPointer);
}


/**
 * [evprintf description]
 * @param formatStringPointer [description]
 * @param argumentsPointer    [description]
 * @note The syntax for a format placeholder is:
 *       %[parameter][flags][width][.precision][length]type
 *
 *       for whole description refer to:
 *       https://en.wikipedia.org/wiki/Printf_format_string#Syntax
 *
 *       syntax supported in this version is as follows:
 *       >[parameter] is not in C99 and is currently not supported
 *
 *       >[flags] characters supported in this field can be zero or more (in any order) of:
 *                characters 	description
 *                 -(minus)		Left-align the output(the default is Right-align)
 *                  0(zero)		Use '0' as padding(the default padding is ' ')
 *
 *       >[width] This field may be omitted, or a numeric integer value. dynamic value like '*' is currently not supported
 *
 *       >[.precision] This field is currently not supported
 *
 *       >[length] characters supported in this field can be any of:
 *                 characters	description
 *                    l 		For integer types, causes the string to expect a long-sized integer argument.
 *
 *       >type characters supported in this field can be any of:
 *             characters	description
 *                 b 		Print int as a signed binary number
 *                 %		Print a literal %
 *                d, i 		Print int as a signed decimal number
 *                 u 		Print decimal unsigned int
 *                x, X 		Print unsigned int as a hexadecimal number
 *                 o 		Print unsigned int as a octal number
 *                 s 		Print a null-terminated string
 *                 c 		Print one character
 *
 */
void evprintf (const char*	formatStringPointer,
               va_list      argumentsPointer)
{
	char nextCharacter;

	char parameterField; //currently not in use

#define FLAGS_ALIGNMENT_RIGHT 0x00
#define FLAGS_ALIGNMENT_LEFT 0x01
#define FLAGS_ZERO_PADDING_DISABLED 0x00
#define FLAGS_ZERO_PADDING_ENABLED 0x02
	//set [flags] to default
	char flagsField = FLAGS_ALIGNMENT_RIGHT | FLAGS_ZERO_PADDING_DISABLED;

	unsigned int widthField = 0;

	char precisionField; //currently not in use

#define LENGTH_NONE 0x00
#define LENGTH_LONG_INTEGER 0x01
	char lengthField = LENGTH_NONE;

	char typeField = 0;

	char paddingCharacter = ' ';

	unsigned int stringLength = 0;
	char* stringPointer = (char*) 0;

	unsigned long number = 0;

#define NUMBER_SIGN_POSITIVE 0x00
#define NUMBER_SIGN_NEGATIVE 0x01
	char numberSignFlag = NUMBER_SIGN_POSITIVE;
	unsigned int remainder = 0;
	unsigned int divider = 1;
	char numeralString[NUMERAL_STRING_MAX_LENGTH] = {'\0'};
	unsigned int i = 0; //iterator

#if TRACE
	//trace for [flags]
	if (flagsField & 0x01) //trace alignment
		printf("trace: flags, Left-align\n");
	else
		printf("trace: flags, Right-align\n");
	if (flagsField & 0x02) //trace padding
		printf("trace: flags, Zero-padding\n");
	else
		printf("trace: flags, Space-padding\n");
	//trace for [flags]
#endif //TRACE

	while (1)
	{
		//clear all fields
		parameterField = parameterField;
		flagsField = FLAGS_ALIGNMENT_RIGHT | FLAGS_ZERO_PADDING_DISABLED;
		widthField = 0;
		precisionField = precisionField;
		lengthField = LENGTH_NONE;
		typeField = 0;

		//clear all helper variables
		paddingCharacter = ' ';

		stringLength = 0;
		stringPointer = (char*) 0;

		number = 0;
		numberSignFlag = NUMBER_SIGN_POSITIVE;
		remainder = 0;
		divider = 1;
		numeralString[0] = '\0';
		i = 0;

		nextCharacter = *formatStringPointer++; //get next char

		if (nextCharacter == '\0') //end of the string
			break;

		if (nextCharacter != '%') //not a format placeholder
		{
			eputchar(nextCharacter);
			continue;
		}

		//start extracting format info
		nextCharacter = *formatStringPointer++; //skip the '%'

		//step1. extract [parameter]
		//currently not supported

		//step2. extract [flags]
		while (nextCharacter == '-' ||
		        nextCharacter == '+' ||
		        nextCharacter == ' ' ||
		        nextCharacter == ' ' ||
		        nextCharacter == '0' ||
		        nextCharacter == '#')
		{
			switch (nextCharacter)
			{
			case '-':
				flagsField |= FLAGS_ALIGNMENT_LEFT;
				break;
			case '+':
				//currently not supported
				eprintf("'%c' is not supported", nextCharacter);
				break;
			case ' ':
				//currently not supported
				eprintf("'%c' is not supported", nextCharacter);
				break;
			case '0':
				flagsField |= FLAGS_ZERO_PADDING_ENABLED;
				break;
			case '#':
				//currently not supported
				eprintf("'%c' is not supported", nextCharacter);
				break;
			}
			nextCharacter = *formatStringPointer++;
		}

#if TRACE
		if (flagsField != FLAGS_ALIGNMENT_RIGHT | FLAGS_ZERO_PADDING_DISABLED)
		{
			printf("trace: flag changed\n");

			if (flagsField & 0x01) //trace alignment
				printf("trace: flags, Left-align\n");
			else
				printf("trace: flags, Right-align\n");
			if (flagsField & 0x02) //trace padding
				printf("trace: flags, Zero-padding\n");
			else
				printf("trace: flags, Space-padding\n");
		}
#endif

		//step3. extract [width]
		for (widthField = 0; nextCharacter >= '0' && nextCharacter <= '9'; nextCharacter = *formatStringPointer++)
		{
			widthField = widthField * 10 + nextCharacter - '0';
		}

#if TRACE
		printf("trace: width, width = %d\n", widthField);
#endif

		//step4. extract [.precision]
		//currently not supported


		//step5. extract [length]
		if (nextCharacter == 'l' || nextCharacter == 'L')
		{
			lengthField = LENGTH_LONG_INTEGER;
			nextCharacter = *formatStringPointer++;
		}
#if TRACE
		if (lengthField == LENGTH_NONE)
			printf("trace: length, default\n");
		else if (lengthField == LENGTH_LONG_INTEGER)
			printf("trace: length, expect long integer\n");
#endif

		//step6. all the selectable fields are checked, now check if the
		//format string unexpectedly ends
		if (nextCharacter == '\0')
		{
#if TRACE
			printf("trace: error, unexpected end of format string\n");
#endif
			break;
		}

		//step7. extract type
		typeField = nextCharacter;
#if TRACE
		printf("formatStringPointer points to: %c\n", *formatStringPointer);
		printf("trace: type, typeField = %c\n", typeField);
#endif

		switch (typeField)
		{
		//Print int as a signed binary numbe
		case 'b':
			divider = 2;
			break;

		//Print a literal %
		case '%':
			eputchar('%');
			continue;

		//Print int as a signed decimal number
		case 'd':
		case 'i':
			divider = 10;
			break;

		//Print decimal unsigned int
		case 'u':
			divider = 10;
			break;

		case 'f':
		case 'F':
		//currently no supported

		case 'e':
		case 'E':
		//currently no supported

		case 'g':
		case 'G':
			//currently no supported
			eprintf("'%c' is not supported", typeField);
			continue;

		//Print unsigned int as a hexadecimal number
		case 'x':
		case 'X':
			divider = 16;
			break;

		//Print unsigned int as a octal number
		case 'o':
			divider = 8;
			break;

		//Print a null-terminated string
		case 's':
			stringPointer = va_arg(argumentsPointer, char*);

			stringLength = 0;
			while (*(stringPointer + stringLength) != '\0')
				stringLength++;

			//width can not be smaller than stringLength
			widthField = widthField > stringLength ? widthField : stringLength;

			paddingCharacter = ' ';
			//Right-align, then pad in the left
			if (!(flagsField & 0x01))
			{
				while (widthField - stringLength > 0)
				{
					eputchar(paddingCharacter);
					stringLength++;
				}
			}

			//print string
			while (*stringPointer != '\0')
			{
				eputchar(*stringPointer);
				stringPointer++;
			}

			//Left-align, then pad in the Right
			if (flagsField & 0x01)
			{
				while (widthField - stringLength > 0)
				{
					eputchar(paddingCharacter);
					stringLength++;
				}
			}
			continue;

		//Print one character
		case 'c':
			eputchar((char)va_arg(argumentsPointer, int));
			continue;

		case 'p':
		//currently no supported

		case 'a':
		case 'A':
		//currently no supported

		case 'n':
			//currently no supported
			eprintf("'%c' is not supported", typeField);
			continue;

		default: //unkown type, print it anyway
#if TRACE
			printf("trace: type, unkown type!");
#endif
			eprintf("'%c' is not supported", typeField);
			continue;
		}

		//end extracting format info

		//step8. print numeral string
#if TRACE
		printf("your divider = %d\n", divider);
#endif

		//get the number
		number = 0;
		if (typeField == 'd' || typeField == 'i') //type:integer
		{
			if (lengthField == LENGTH_LONG_INTEGER) //long integer
			{
				number = va_arg(argumentsPointer, long);
			}
			else
			{
				number = va_arg(argumentsPointer, int);
			}
			//positive or negative?
			if (number & 0x80000000)
			{
				numberSignFlag = NUMBER_SIGN_NEGATIVE;
				number = 0 - number;
#if TRACE
				printf("trace: minus number detected\n");
#endif
			}
		}
		else if ( typeField == 'u' ||
		          typeField == 'o' ||
		          typeField == 'x' || typeField == 'X' ||
		          typeField == 'b' )
		{
			number = va_arg(argumentsPointer, unsigned int);
		}
		else
		{
#if TRACE
			printf("trace: numeral print, unkown type: %c", typeField);
#endif
		}

		i = 0;
		do
		{
			remainder = (char)(number % divider);
			number = number / divider;

			if (remainder > 9) //convert 10~15 => a~f/A~F
			{
				if (typeField == 'x')
					remainder += 0x27;
				else
					remainder += 0x07;
			}

			numeralString[i] = remainder + '0';
			i++;

		} while (number != 0 && i < (sizeof(numeralString) / sizeof(numeralString[0])));

		stringLength = i;
		if (numberSignFlag == NUMBER_SIGN_NEGATIVE)
			stringLength += 1; //space for minus sign '-'

#if TRACE
		printf("trace: stringLength = %d\n", stringLength);
#endif

		//width can not be smaller than stringLength
		widthField = widthField > stringLength ? widthField : stringLength;

		//set padding character
		if (flagsField & 0x02) //zero padding
			paddingCharacter = '0';
		else //space padding
			paddingCharacter = ' ';

		//Right-align, then pad in the left
		if (!(flagsField & 0x01))
		{
			while (widthField - stringLength > 0)
			{
				eputchar(paddingCharacter);
				stringLength++;
			}
		}

		//print sign
		if (numberSignFlag == NUMBER_SIGN_NEGATIVE)
			eputchar('-');
		//print 0x or 0X for hex numbers
//		if (typeField == 'x' || typeField == 'X')
//		{
//			eputchar('0');
//			eputchar(typeField);
//		}

		//print numeral string
		do
		{
			eputchar(numeralString[--i]);
		} while (i > 0);

		//Left-align, then pad in the Right
		if (flagsField & 0x01)
		{
			while (widthField - stringLength > 0)
			{
				eputchar(paddingCharacter);
				stringLength++;
			}
		}
	}
}

/**
 * Print a formatted string to default I/O
 * @param formatStringPointer Pointer to the format string
 */
void esprintf (char *buffer, const char *formatStringPointer, ... )
{
	va_list argumentsPointer;

	va_start(argumentsPointer, formatStringPointer);
	evsprintf(buffer, formatStringPointer, argumentsPointer);
	va_end(argumentsPointer);

}

void evsprintf(char *buffer, const char *formatStringPointer,
               va_list argumentsPointer)
{
	//re-direct output to buffer
	outputPointer = buffer;

	evprintf(formatStringPointer, argumentsPointer);

	//end buffer with '\0'
	*outputPointer = '\0';

	//restore output
	outputPointer = (char*)0;
}

void esnprintf(char* buffer, int size, const char* formatStringPointer, ... )
{
	va_list argumentsPointer;

	//size limit enable
	sizeActual = 0;
	sizeLimit = size;
	sizeLimitEnabled = 1;

	va_start(argumentsPointer, formatStringPointer);
	evsprintf(buffer, formatStringPointer, argumentsPointer);
	va_end(argumentsPointer);

	//size limit disable
	sizeActual = 0;
	sizeLimit = 0;
	sizeLimitEnabled = 0;
}