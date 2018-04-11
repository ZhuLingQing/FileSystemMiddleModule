#ifndef _FSMID_PORT_H_
#define _FSMID_PORT_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>


#ifndef __cplusplus
extern "C" {
#endif


#define fsmid_delayMs(ms)			Sleep(ms)

// #define fsmid_malloc(typ,sz)		(typ *)malloc((sz)*sizeof(typ))
// #define fsmid_free(ptr)				free(ptr)
extern void* test_malloc(unsigned int);
extern void test_free(void *);
#define fsmid_malloc(typ,sz)		(typ *)test_malloc((sz)*sizeof(typ))
#define fsmid_free(ptr)				test_free(ptr)

#define fsmid_assert(cond,func,line)		do{if(!(cond)){printf("[ASSERT] %s(%d).\n",func,line);while(1);}}while(0)
#define fsmid_warning(str,func,line)		printf(str)//
#define fsmid_info(s,...)					printf(s,##__VA_ARGS__)

#define FSMID_MUTEX					HANDLE//xSemaphoreHandle
#define fsmid_mutex_create(mtx)		mtx = CreateMutex(NULL,FALSE,#mtx)//vSemaphoreCreateBinary(mtx)
#define fsmid_mutex_lock(mtx)		WaitForSingleObject(mtx,INFINITE)//xSemaphoreTake(mtx,portMAX_DELAY)
#define fsmid_mutex_unlock(mtx)		ReleaseMutex(mtx)//xSemaphoreGive(mtx)
#define fsmid_mutex_release(mtx)	CloseHandle(mtx)//vSemaphoreRelease(mtx)

#define fsmid_get_systime(tm)		//(tm)

unsigned int db_GetInfoAddressLength();

const char *db_GetTerminalID();

#ifndef __cplusplus
};
#endif

#endif
