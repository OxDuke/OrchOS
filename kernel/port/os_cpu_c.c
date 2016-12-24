
#include "os_cpu_c.h"

#define __FPU_PRESENT 1
#define __FPU_USED 1

void OSTaskReturn(void)
{
	int i;
	i = 1;
	i++;
	while(1);
}

OSStack_t* OSTaskStackInitialize (
	OSTaskAddress_t taskEntryAddress,
                         void*     argumentsPointer,
                         OSStack_t*       stackBasePointer,
                         OSStack_t*       stackLimitPointer,
                         OSStackSize_t   stackSize)
{
    OSStack_t* stackTopPointer;


    stackTopPointer = &stackBasePointer[stackSize];                              /* Load stack pointer                                     */
                                                                /* Align the stack to 8-bytes.                            */
    stackTopPointer = (OSStack_t*)((OSStack_t)(stackTopPointer) & 0xFFFFFFF8);

#if (__FPU_PRESENT==1)&&(__FPU_USED==1)     	/* Registers stacked as if auto-saved on exception        */
	*(--stackTopPointer) = (OSStack_t)0x00000000u; //No Name Register  
	*(--stackTopPointer) = (OSStack_t)0x00001000u; //FPSCR
	*(--stackTopPointer) = (OSStack_t)0x00000015u; //s15
	*(--stackTopPointer) = (OSStack_t)0x00000014u; //s14
	*(--stackTopPointer) = (OSStack_t)0x00000013u; //s13
	*(--stackTopPointer) = (OSStack_t)0x00000012u; //s12
	*(--stackTopPointer) = (OSStack_t)0x00000011u; //s11
	*(--stackTopPointer) = (OSStack_t)0x00000010u; //s10
	*(--stackTopPointer) = (OSStack_t)0x00000009u; //s9
	*(--stackTopPointer) = (OSStack_t)0x00000008u; //s8
	*(--stackTopPointer) = (OSStack_t)0x00000007u; //s7
	*(--stackTopPointer) = (OSStack_t)0x00000006u; //s6
	*(--stackTopPointer) = (OSStack_t)0x00000005u; //s5
	*(--stackTopPointer) = (OSStack_t)0x00000004u; //s4
	*(--stackTopPointer) = (OSStack_t)0x00000003u; //s3
	*(--stackTopPointer) = (OSStack_t)0x00000002u; //s2
	*(--stackTopPointer) = (OSStack_t)0x00000001u; //s1
	*(--stackTopPointer) = (OSStack_t)0x00000000u; //s0
#endif
	
	*(--stackTopPointer) = (OSStack_t)0x01000000u;                            /* xPSR                                                   */
    *(--stackTopPointer) = (OSStack_t)taskEntryAddress;                       /* Entry Point                                            */
    *(--stackTopPointer) = (OSStack_t)OSTaskReturn;                        /* R14 (LR)                                               */
//    *(--stackTopPointer) = (OSStack_t)0x14141414u;
	*(--stackTopPointer) = (OSStack_t)0x12121212u;                            /* R12                                                    */
    *(--stackTopPointer) = (OSStack_t)0x03030303u;                            /* R3                                                     */
    *(--stackTopPointer) = (OSStack_t)0x02020202u;                            /* R2                                                     */
//    *(--stackTopPointer) = (OSStack_t)p_stk_limit;                          /* R1                                                     */
    *(--stackTopPointer) = (OSStack_t)stackLimitPointer;                      /* R1                                                     */
    *(--stackTopPointer) = (OSStack_t)argumentsPointer;                       /* R0 : argument                                          */

#if (__FPU_PRESENT==1)&&(__FPU_USED==1)
	*(--stackTopPointer) = (OSStack_t)0x00000031u; //s31
	*(--stackTopPointer) = (OSStack_t)0x00000030u; //s30
	*(--stackTopPointer) = (OSStack_t)0x00000029u; //s29
	*(--stackTopPointer) = (OSStack_t)0x00000028u; //s28
	*(--stackTopPointer) = (OSStack_t)0x00000027u; //s27
	*(--stackTopPointer) = (OSStack_t)0x00000026u; //s26	
	*(--stackTopPointer) = (OSStack_t)0x00000025u; //s25
	*(--stackTopPointer) = (OSStack_t)0x00000024u; //s24
	*(--stackTopPointer) = (OSStack_t)0x00000023u; //s23
	*(--stackTopPointer) = (OSStack_t)0x00000022u; //s22
	*(--stackTopPointer) = (OSStack_t)0x00000021u; //s21
	*(--stackTopPointer) = (OSStack_t)0x00000020u; //s20
	*(--stackTopPointer) = (OSStack_t)0x00000019u; //s19
	*(--stackTopPointer) = (OSStack_t)0x00000018u; //s18
	*(--stackTopPointer) = (OSStack_t)0x00000017u; //s17
	*(--stackTopPointer) = (OSStack_t)0x00000016u; //s16
#endif
                                                                /* Remaining registers saved on process stack             */
    *(--stackTopPointer) = (OSStack_t)0x11111111u;                            /* R11                                                    */
    *(--stackTopPointer) = (OSStack_t)0x10101010u;                            /* R10                                                    */
    *(--stackTopPointer) = (OSStack_t)0x09090909u;                            /* R9                                                     */
    *(--stackTopPointer) = (OSStack_t)0x08080808u;                            /* R8                                                     */
    *(--stackTopPointer) = (OSStack_t)0x07070707u;                            /* R7                                                     */
    *(--stackTopPointer) = (OSStack_t)0x06060606u;                            /* R6                                                     */
    *(--stackTopPointer) = (OSStack_t)0x05050505u;                            /* R5                                                     */
    *(--stackTopPointer) = (OSStack_t)0x04040404u;                            /* R4                                                     */

    return (stackTopPointer);
}
