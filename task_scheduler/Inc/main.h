/*
 * main.h
 *
 *  Created on: 21-Jun-2025
 *      Author: Tejas Sawant
 */

#ifndef MAIN_H_
#define MAIN_H_

//Some memory calculation [MACROS]
#define SIZE_TASK_STACK              1024U  // 1 kb of stack size
#define SIZE_SCHEDULER_STACK         1024U

#define SRAM_START                   0x20000000
#define SRAM_SIZE                    ((128) * (1024))
#define SRAM_END                     ((SRAM_START)+(SRAM_SIZE))

#define T1_STACK_START               SRAM_END
#define T2_STACK_START               SRAM_END - SIZE_TASK_STACK
#define T3_STACK_START               SRAM_END - (2 * SIZE_TASK_STACK)
#define T4_STACK_START               SRAM_END - (3 * SIZE_TASK_STACK)
#define SCHEDULER_STACK_START        SRAM_END - (4 * SIZE_TASK_STACK)

#define TICK_HZ                      1000U
#define SYSTICK_TIMER_CLK            16000000U
#define MAX_TASK                     4
#define DUMMY_XPSR                   0x01000000U

#endif /* MAIN_H_ */
