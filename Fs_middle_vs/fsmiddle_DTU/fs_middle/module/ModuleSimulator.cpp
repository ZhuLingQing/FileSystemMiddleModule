#include "dbmsV1.h"
#include "dpa10x.h"
#include "fsmid_port.h"
#include "fsmid_util.h"

#include <windows.h>
#include <time.h>
#include <conio.h>
#include <ctype.h>
#include <stdio.h>
#include <direct.h>
#include "ModuleSimulator.h"

#define TEST_UNIT_NUMBER		128//1024
#define TEST_UNIT_SIZE			128//16
#define TEST_BLOCK_SIZE			4096

#define SIM_FLASH_SIZE			(16<<20)
#define FLASH_FILE_NAME			"simDTU_FLASH.bin"
extern FILE* sim_flash_file;

#define START_INF				100
#define START_SYSPNT			10

#if NUM_TEST_MEASURE
float test_measure[NUM_TEST_MEASURE];
#else
float *test_measure = NULL;
#endif
#if NUM_TEST_FROZEN
float test_frozen[NUM_TEST_FROZEN];
#else
float *test_frozen = NULL;
#endif

bool bUlogUpdate = false;
bool bPrtlogUpdate = false;
bool bSoeUpdate = false;
bool bTrdUpdate = false;
ULOGEVENT test_ulog;
PRTLOGEVENT test_prtlog;
SOEEVENT test_soe;
TRDEVENT test_trd;

HANDLE test_lock;


extern int write_flash(unsigned int address, const void* data, unsigned int length);
extern int read_flash(unsigned int address, void* data, unsigned int length);
extern int erase_flash(unsigned int address, unsigned int length);

FSLOG_INTERFACE intrFslog = {
	write_flash,
	read_flash,
	erase_flash,
};

struDpa10xApp dpa101appl = {0};

unsigned int heapUsage = 0;
unsigned int maxHeapUsage = 0;

void *test_malloc(unsigned int size)
{
	unsigned char *p = new unsigned char[size + 4];
	*(unsigned int*)p = size;
	heapUsage += size;
	if(heapUsage > maxHeapUsage)
		maxHeapUsage = heapUsage;
	return (p + 4);
}

void test_free(void *pBuf)
{
	unsigned char *p = (unsigned char *)pBuf;
	p -= 4;
	heapUsage -= *(unsigned int*)p;
	delete [] p;
}

unsigned int db_GetInfoAddressLength()
{
	return 3;
}

const char *db_GetTerminalID()
{
	return "DTU_DEVICE_12345678";
}

uint8 db_GetDcaHand()
{
	return 1;
}

uint8 db_GetDpaHand()
{
	return 1;
}

void glb_GetDateTime( SYS_TIME64 *tm64)
{
	SYSTEMTIME sys; 
	GetLocalTime( &sys );

	tm64->year = sys.wYear - 2000;
	tm64->mon = sys.wMonth;
	tm64->day = sys.wDay;
	tm64->hour = sys.wHour;
	tm64->min = sys.wMinute;
	tm64->sec = sys.wSecond;
	tm64->msec = sys.wMilliseconds;
}

uint8 db_GetDi( int16 pnt)
{
	return 0;
}

SOEEVENT *db_GetSoe(uint8 hand)
{
	SOEEVENT *event = NULL;
	WaitForSingleObject(test_lock,INFINITE);
	if(bSoeUpdate)
		event = &test_soe;
	bSoeUpdate = false;
	ReleaseMutex(test_lock);
	return event;
}

TRDEVENT *db_GetTrd(uint8 hand)
{
	TRDEVENT *event = NULL;
	WaitForSingleObject(test_lock,INFINITE);
	if(bTrdUpdate)
		event = &test_trd;
	bTrdUpdate = false;
	ReleaseMutex(test_lock);
	return event;
}

PRTLOGEVENT *db_GetPrtLog(uint8 who)
{
	PRTLOGEVENT *event = NULL;
	WaitForSingleObject(test_lock,INFINITE);
	if(bPrtlogUpdate)
		event = &test_prtlog;
	bPrtlogUpdate = false;
	ReleaseMutex(test_lock);
	return event;
}

ULOGEVENT *db_GetULog(uint8 who)
{
	ULOGEVENT *event = NULL;
	WaitForSingleObject(test_lock,INFINITE);
	if(bUlogUpdate)
		event = &test_ulog;
	bUlogUpdate = false;
	ReleaseMutex(test_lock);
	return event;
}

float db_GetAi(uint8 dpaH, int16 pnt)
{
	float res;
	fsmid_assert(pnt>=START_SYSPNT && pnt < START_SYSPNT + NUM_TEST_MEASURE,__FILE__,__LINE__);

	WaitForSingleObject(test_lock,INFINITE);
	res = test_measure[pnt-START_SYSPNT];
	ReleaseMutex(test_lock);
	return res;
}

float db_GetPa(int16 pnt)
{
	float res;
	fsmid_assert(pnt>=START_SYSPNT + NUM_TEST_MEASURE && pnt < START_SYSPNT + NUM_TEST_MEASURE + NUM_TEST_FROZEN,__FILE__,__LINE__);

	WaitForSingleObject(test_lock,INFINITE);
	res = test_frozen[pnt-START_SYSPNT-NUM_TEST_MEASURE];
	ReleaseMutex(test_lock);
	return res;
}

void* dpa10x_SearchSyspntInFrms(struDpa10xPort *pport, int16 syspnt, enumTYPID_GRP typgrp, int8 *frm, int16 *pnt, int16 *otherpnt, uint32 *inf)
{
	*frm = 0;
	*pnt = syspnt;
	*otherpnt = 0;
	*inf = syspnt * 10;
	return NULL;
}


void init_dpa_dca_frame()
{
	int i;
	uint32 inf = START_INF;
	int16 syspnt = START_SYSPNT;

	dpa101appl.pport = new struDpa10xPort;
	ZeroMemory(dpa101appl.pport,sizeof(struDpa10xPort));
	dpa101appl.pport->frmnum = NUM_TEST_FROZEN + NUM_TEST_MEASURE;
	if(dpa101appl.pport->frmnum)
	{
		dpa101appl.pport->pfrm = new struDpa10xFrm[NUM_TEST_FROZEN + NUM_TEST_MEASURE];
		ZeroMemory(dpa101appl.pport->pfrm,sizeof(struDpa10xFrm)*(NUM_TEST_FROZEN + NUM_TEST_MEASURE));
	}
	for(i = 0; i < NUM_TEST_MEASURE; i++ )
	{
		dpa101appl.pport->pfrm[i].pcfg = new struDpa10xFrm_Cfg;
		dpa101appl.pport->pfrm[i].pcfg->frmtype = M_ME_NC_1;
		dpa101appl.pport->pfrm[i].pcfg->frminf = inf++;
		dpa101appl.pport->pfrm[i].pntnum = 1;
		dpa101appl.pport->pfrm[i].ppntcfg = (void*)new int16;
		*(int16*)dpa101appl.pport->pfrm[i].ppntcfg = syspnt++;
	}
	for(i = 0; i < NUM_TEST_FROZEN; i++ )
	{
		dpa101appl.pport->pfrm[NUM_TEST_MEASURE+i].pcfg = new struDpa10xFrm_Cfg;
		dpa101appl.pport->pfrm[NUM_TEST_MEASURE+i].pcfg->frmtype = M_IT_NB_1;
		dpa101appl.pport->pfrm[NUM_TEST_MEASURE+i].pcfg->frminf = inf++;
		dpa101appl.pport->pfrm[NUM_TEST_MEASURE+i].pntnum = 1;
		dpa101appl.pport->pfrm[NUM_TEST_MEASURE+i].ppntcfg = (void*)new int16;
		*(int16*)dpa101appl.pport->pfrm[NUM_TEST_MEASURE+i].ppntcfg = syspnt++;
	}
}
