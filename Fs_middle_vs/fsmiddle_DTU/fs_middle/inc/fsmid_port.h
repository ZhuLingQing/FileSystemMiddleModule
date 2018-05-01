#ifndef _FSMID_PORT_H_
#define _FSMID_PORT_H_

#ifndef CPU_MK64FN1M0VMD12
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#else
#include <stdint.h>

#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"

#include "fsl_common.h"
#include "board.h"

#include "commonDefEx.h"
#include "sysTimerV1.h"
#include "dbmsV1.h"
#endif

#if (defined(WIN32) && !defined(__cplusplus))
extern "C" {
#endif

#ifndef CPU_MK64FN1M0VMD12

#define fsmid_delayMs(ms)			Sleep(ms)

// #define fsmid_malloc(typ,sz)		(typ *)malloc((sz)*sizeof(typ))
// #define fsmid_free(ptr)				free(ptr)
extern void* test_malloc(unsigned int);
extern void test_free(void *);
#define fsmid_malloc(typ,sz)		(typ *)test_malloc((sz)*sizeof(typ))
#define fsmid_free(ptr)				test_free(ptr)

#define fsmid_assert(cond,func,line)		do{if(!(cond)){printf("[ASSERT] %s(%d).\r\n",func,line);while(1);}}while(0)
#define fsmid_warning(str,func,line)		printf(str)//
#define fsmid_info(s,...)					printf(s,##__VA_ARGS__)

#define FSMID_MUTEX					HANDLE
#define fsmid_mutex_create(mtx)		mtx = CreateMutex(NULL,FALSE,#mtx)
#define fsmid_mutex_lock(mtx)		WaitForSingleObject(mtx,INFINITE)
#define fsmid_mutex_unlock(mtx)		ReleaseMutex(mtx)
#define fsmid_mutex_release(mtx)	CloseHandle(mtx)

//#define fsmid_get_systime(tm)		//(tm)
#else
    
#define fsmid_delayMs(ms)               vTaskDelay(ms)
    
#define fsmid_malloc(typ,sz)            (typ *)pvPortMalloc((sz)*sizeof(typ))
#define fsmid_free(ptr)                 vPortFree(ptr)
    
#define fsmid_assert(cond,func,line)	do{if(!(cond)){PRINTF("!FSMID_ASSERT at %s, %d\r\n",func,line);while(1);}}while(0)
#define fsmid_warning(str,func,line)	PRINTF("!FSMID_WARNING %s at %s,%d\r\n",str,func,line);
#define fsmid_info(s,...)				printf(s,__VA_ARGS__)
    
extern QueueHandle_t fsmid_mutex;
#define FSMID_MUTEX                     QueueHandle_t*
#define fsmid_mutex_create(mtx)         mtx = &fsmid_mutex;
#define fsmid_mutex_lock(mtx)           xSemaphoreTake(*mtx,portMAX_DELAY)
#define fsmid_mutex_unlock(mtx)         xSemaphoreGive(*mtx)
#define fsmid_mutex_release(mtx)        mtx = NULL;

//#define fsmid_get_systime(tm)			//(tm)

#endif    

unsigned int db_GetInfoAddressLength();

const char *db_GetTerminalID();

#if (defined(WIN32) && !defined(__cplusplus))
};
#endif

#endif
