/******************************************************************************
Filename   : rmp_platform_TMS570LC4357.h
Author     : pry
Date       : 24/06/2017
Licence    : The Unlicense; see LICENSE for details.
Description: The configuration file for TMS570LC4357.
******************************************************************************/

/* Defines *******************************************************************/
/* The HAL library */
#include "HL_sys_common.h"
#include "HL_system.h"
#include "HL_rti.h"
#include "HL_sci.h"

/* The maximum number of preemption priority levels in the system.
 * This parameter must be divisible by the word length - 32 is usually sufficient */
#define RMP_MAX_PREEMPT_PRIO         32
/* The maximum number of slices allowed */
#define RMP_MAX_SLICES               100000
/* The maximum number of semaphore counts allowed */
#define RMP_SEM_MAX_NUM              1000
/* Are we using custom hooks? */
#define RMP_USE_HOOKS                RMP_FALSE
/* The stzck size of the init thread */
#define RMP_INIT_STACK_SIZE          1024
/* The mask/unmask interrupt operations */
#define RMP_MASK_INT()               RMP_Disable_Int()
#define RMP_UNMASK_INT()             RMP_Enable_Int()

#define RMP_CRX_SYSTICK_VAL          3750

/* Other low-level initialization stuff - clock and serial. 
 * This is the default initialization sequence. If you wish to supply
 * your own, just redirect this macro to a custom function, or do your
 * initialization stuff in the initialization hook (RMP_Start_Hook). */
#define RMP_CRX_LOW_LEVEL_INIT() \
do \
{ \
    /* The TI library is in charge of all the initialization of interrupts and clocks */\
    rtiInit(); \
    rtiSetPeriod(rtiREG1, rtiCOMPARE0, RMP_CRX_SYSTICK_VAL); \
    rtiEnableNotification(rtiREG1, rtiNOTIFICATION_COMPARE0); \
    rtiStartCounter(rtiREG1, rtiCOUNTER_BLOCK0); \
    /* Enable SCI */ \
    sciInit(); \
} \
while(0)

/* This is for debugging output */
#define RMP_CRX_PUTCHAR(CHAR) \
do \
{ \
    sciSendByte(sciREG1,(CHAR)); \
} \
while(0)
/* End Defines ***************************************************************/

/* End Of File ***************************************************************/

/* Copyright (C) Evo-Devo Instrum. All rights reserved ***********************/
