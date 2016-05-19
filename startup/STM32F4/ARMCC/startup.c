/*******************************************************************************
@file     startup.c
@author   Rajmund Szymanski
@date     18.05.2016
@brief    STM32F4xx startup file.
          After reset the Cortex-M4 processor is in thread mode,
          priority is privileged, and the stack is set to main.
*******************************************************************************/

#if defined(__CC_ARM)

#include <stm32f4xx.h>

/*******************************************************************************
 Specific definitions for the chip
*******************************************************************************/

#define __ccm_start 0x10000000
#define __ccm_end   0x10010000
#define __ram_start 0x20000000
#define __ram_end   0x20020000

/*******************************************************************************
 Configuration of stacks
*******************************************************************************/

#ifndef main_stack_size
#define main_stack_size 1024 // <- default size of main stack
#endif
#define main_stack (((main_stack_size)+7)&(~7))

#if     main_stack_size > 0
char  __main_stack[main_stack] __attribute__ ((used, section(".stack"), zero_init));
#endif

#ifndef proc_stack_size
#define proc_stack_size 1024 // <- default size of process stack
#endif
#define proc_stack (((proc_stack_size)+7)&(~7))

#if     proc_stack_size > 0
char  __proc_stack[proc_stack] __attribute__ ((used, section(".stack"), zero_init));
#endif

/*******************************************************************************
 Configuration of stacks and heap
*******************************************************************************/

__attribute__ ((section(".stack")))
__asm void __user_stack_config( void )
{
#if main_stack_size > 0
__initial_msp   EQU     __ram_start + main_stack
#else
__initial_msp   EQU     __ram_end
#endif
__initial_psp   EQU     __ram_start + main_stack + proc_stack
#if proc_stack_size > 0
#ifndef __MICROLIB
                IMPORT  __use_two_region_memory
#endif
__initial_sp    EQU     __initial_psp
#else
__initial_sp    EQU     __initial_msp
#endif
                EXPORT  __initial_msp
                EXPORT  __initial_psp
                EXPORT  __initial_sp
}

__attribute__ ((section(".heap")))
__asm void __user_heap_config( void )
{
__heap_base     EQU     .
__heap_limit    EQU     __ram_end

                EXPORT  __heap_base
                EXPORT  __heap_limit
}

/*******************************************************************************
 Initial process stack pointer
*******************************************************************************/

extern char __initial_psp[];

/*******************************************************************************
 Prototypes of external functions
*******************************************************************************/

void __main( void ) __attribute__ ((noreturn));

/*******************************************************************************
 Default reset handler
*******************************************************************************/

void Reset_Handler( void )
{
#if proc_stack_size > 0
	/* Initialize the process stack pointer */
	__set_PSP((unsigned)__initial_psp);
	__set_CONTROL(CONTROL_SPSEL_Msk);
#endif
#if __FPU_USED
    /* Set CP10 and CP11 Full Access */
	SCB->CPACR = 0x00F00000U;
#endif
#ifndef __NO_SYSTEM_INIT
	/* Call the system clock intitialization function */
	SystemInit();
#endif
	/* Call the application's entry point */
	__main();
}

/******************************************************************************/

#endif // __CC_ARM