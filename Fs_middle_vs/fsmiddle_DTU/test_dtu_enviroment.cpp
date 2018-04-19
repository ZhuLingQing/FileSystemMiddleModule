#include "dbmsV1.h"
#include "dpa10x.h"
#include "fs_middle.h"
#include <windows.h>
#include <time.h>
#include <conio.h>
#include <ctype.h>
#include <stdio.h>
#include <direct.h>

#define TEST_UNIT_NUMBER		128//1024
#define TEST_UNIT_SIZE			128//16
#define TEST_BLOCK_SIZE			4096

#define SIM_FLASH_SIZE			(16<<20)
#define FLASH_FILE_NAME			"simDTU_FLASH.bin"
extern FILE* sim_flash_file;

#define NUM_TEST_MEASURE		10
#define NUM_TEST_FROZEN			5

#define START_INF				100
#define START_SYSPNT			10

extern float test_measure[NUM_TEST_MEASURE];
extern float test_frozen[NUM_TEST_FROZEN];

extern bool bUlogUpdate;
extern bool bPrtlogUpdate;
extern bool bSoeUpdate;
extern bool bTrdUpdate;
extern ULOGEVENT test_ulog;
extern PRTLOGEVENT test_prtlog;
extern SOEEVENT test_soe;
extern TRDEVENT test_trd;

extern HANDLE test_lock;
HANDLE hDtuPipe = INVALID_HANDLE_VALUE;



#include "fsmid_def.h"
#include "fsmid_log.h"

void __create_folder(const char *fileName)
{
	const char *tag;
	for(tag=fileName;*tag;tag++)
	{
		if (*tag=='\\')
		{
			char buf[MAX_PATH],path[MAX_PATH];
			strcpy(buf,fileName);
			buf[strlen(fileName)-strlen(tag)+1]=NULL;
			strcpy(path,buf);
			if (chdir(path)==-1)
			{
				mkdir(path);
			}
		}
	}
}

void printLog(FSLOG *pLog)
{
	SYS_TIME64 tm64;
	if(!pLog)
	{
		printf("!LOG pointer is NULL.\n");
		return;
	}

	printf("Name:%s.\n",pLog->name);
	if(pLog->timeCreateUnix)
	{
		time_unix2sys(pLog->timeCreateUnix,&tm64);
		printf("Create:20%02d-%02d-%02d\n",tm64.year,tm64.mon,tm64.day);
	}
	else
		printf("Create: -N\\A-\n");
	printf("ItemCount:%5d. FormatSize:%8d.\n",pLog->unitNumber,pLog->formatedSize);
}

void two_sec_delay(SYS_TIME64 *tm64)
{
	SYS_TIME64 _tm64;
	do{
		fsmid_delayMs(100);
		glb_GetDateTime(&_tm64);
	}while(!(_tm64.sec != tm64->sec && _tm64.msec > 500 && !(_tm64.sec%2)));
}

float f_gen_rand(float range)
{
	float r = rand();
	r /= range;
	return r;
}

int i_gen_rand(int range)
{
	int r = rand();
	r %= range;
	return r;
}

static FILE* f_test_open(const char *path, const char *file)
{
	int i;
	char fPathName[MAX_PATH];
	FILE* fresult;

	i = sprintf(fPathName,"%s%s",path,file);
	fPathName[i] = 0;
	__create_folder(fPathName);
	fresult = fopen(fPathName,"ab+");
	if(fresult == NULL)
	{
		printf("fopen return NULL, error=%d/n", GetLastError());
		while(1);
	}
	fseek(fresult,0,SEEK_END);
	return fresult;
}

void __write_time(FILE *file, SYS_TIME64 *tm64)
{
	char buf[64];
	int i = sprintf(buf,"20%02d-%02d-%02d %02d:%02d:%02d",
		tm64->year,tm64->mon,tm64->day,
		tm64->hour,tm64->min,tm64->sec);
	fwrite(buf,i,1,file);
}

void __write_eol(FILE *file)
{
	const char buf[] = "\r\n";
	fwrite(buf,2,1,file);
}

extern char exeFullPath[256];

void __write_fixpt(/*FILE *file,*/ SYS_TIME64 *tm64, float value[])
{
	char buf[128];
	int i,j;
	FILE *file = f_test_open(exeFullPath,"\\raw\\FIXPT.csv");

	__write_time(file,tm64);
	for(j = 0; j < NUM_TEST_MEASURE; j++)
	{
		i = sprintf(buf,",%7.3f",value[j]);
		fwrite(buf,i,1,file);
	}
	__write_eol(file);
	fclose(file);
}

void __write_frz(/*FILE *file,*/ SYS_TIME64 *tm64, float value[])
{
	char buf[128];
	int i,j;
	FILE *file = f_test_open(exeFullPath,"\\raw\\FRZ.csv");

	__write_time(file,tm64);
	for(j = 0; j < NUM_TEST_FROZEN; j++)
	{
		i = sprintf(buf,",%7.3f",value[j]);
		fwrite(buf,i,1,file);
	}
	__write_eol(file);
	fclose(file);
}

void __write_ulog(/*FILE *file,*/ SYS_TIME64 *tm64, ULOGEVENT *event)
{
	char buf[128];
	int i;
	FILE *file = f_test_open(exeFullPath,"\\raw\\ULOG.csv");
	
	__write_time(file,tm64);

	i = sprintf(buf,",20%02d-%02d-%02d %02d:%02d:%02d.%03d",
		event->time.year,event->time.mon,event->time.day,
		event->time.hour,event->time.min,event->time.sec,
		event->time.msec);
	fwrite(buf,i,1,file);

	i = sprintf(buf,",%d,%d,%s",event->type,event->sts,event->buf);
	fwrite(buf,i,1,file);

	__write_eol(file);
	fclose(file);
}

void __write_prtlog(/*FILE *file,*/ SYS_TIME64 *tm64, PRTLOGEVENT *event)
{
	char buf[128];
	int i;
	FILE *file = f_test_open(exeFullPath,"\\raw\\PRTLOG.csv");

	__write_time(file,tm64);

	i = sprintf(buf,",20%02d-%02d-%02d %02d:%02d:%02d.%03d",
		event->time.year,event->time.mon,event->time.day,
		event->time.hour,event->time.min,event->time.sec,
		event->time.msec);
	fwrite(buf,i,1,file);

	i = sprintf(buf,",%s",event->buf);
	fwrite(buf,i,1,file);

	__write_eol(file);
	fclose(file);
}

void __write_soe(/*FILE *file,*/ SYS_TIME64 *tm64, SOEEVENT *event)
{
	char buf[128];
	int i;
	FILE *file = f_test_open(exeFullPath,"\\raw\\SOE.csv");

	__write_time(file,tm64);

	i = sprintf(buf,",20%02d-%02d-%02d %02d:%02d:%02d.%03d",
		event->time.year,event->time.mon,event->time.day,
		event->time.hour,event->time.min,event->time.sec,
		event->time.msec);
	fwrite(buf,i,1,file);

	i = sprintf(buf,",%d,%d,%d",event->pnt,event->val,event->ainum);
	fwrite(buf,i,1,file);

	__write_eol(file);
	fclose(file);
}

void __write_trd(/*FILE *file,*/ SYS_TIME64 *tm64, TRDEVENT *event)
{
	char buf[128];
	int i;
	FILE *file = f_test_open(exeFullPath,"\\raw\\TRD.csv");

	__write_time(file,tm64);

	i = sprintf(buf,",%d,%d",event->pnt,event->val);
	fwrite(buf,i,1,file);

	__write_eol(file);
	fclose(file);
}

DWORD WINAPI signal_generator(LPVOID lpParameter)
{
	int i;
	DWORD sl;
	int tickSoe,tickTrd,tickUlog,tickPrtlog;
	SYS_TIME64 tm64;
	char sbuf[MAX_PATH];

	tickSoe = i_gen_rand(59) + 1;
	tickTrd = i_gen_rand(59) + 1;
	tickUlog = i_gen_rand(59) + 1;
	tickPrtlog = i_gen_rand(59) + 1;

	while(1)
	{
		glb_GetDateTime(&tm64);

		WaitForSingleObject(test_lock,INFINITE);
		if(tm64.sec < 2)
		{
			tickSoe = i_gen_rand(29) + 1;
			tickTrd = i_gen_rand(29) + 1;
			tickUlog = i_gen_rand(29) + 1;
			tickPrtlog = i_gen_rand(29) + 1;
		}
		else if(tm64.sec >= 30 && tm64.sec < 32)
		{
			tickSoe = i_gen_rand(29) + 31;
			tickTrd = i_gen_rand(29) + 31;
			tickUlog = i_gen_rand(29) + 31;
			tickPrtlog = i_gen_rand(29) + 31;
		}

#if (defined(ENABLE_MODULE_EXV) || defined(ENABLE_MODULE_FIXPT) || defined(ENABLE_MODULE_ALL))
		if(hDtuPipe != INVALID_HANDLE_VALUE)
			WriteFile(hDtuPipe,"MEASURE:\n",9,&sl,NULL);
		for( i = 0; i < NUM_TEST_MEASURE; i++ )
		{
			test_measure[i] = f_gen_rand(32.768f);
			test_measure[i] = min(test_measure[i],9999.0);
			test_measure[i] = max(test_measure[i],0.001);
			sl = sprintf(sbuf," %7.3f%c",test_measure[i],((i+1)%5==0)?'\n':',');
			if(hDtuPipe != INVALID_HANDLE_VALUE)
				WriteFile(hDtuPipe,sbuf,sl,&sl,NULL);
		}
		__write_fixpt(&tm64,test_measure);
#endif

#if (defined(ENABLE_MODULE_FROZEN) || defined(ENABLE_MODULE_ALL))
		if(hDtuPipe != INVALID_HANDLE_VALUE)
			WriteFile(hDtuPipe,"FROZEN:\n",8,&sl,NULL);
		for( i = 0; i < NUM_TEST_FROZEN; i++ )
		{
			test_frozen[i] = f_gen_rand(32.768f);
			test_frozen[i] = min(test_frozen[i],9999.0);
			test_frozen[i] = max(test_frozen[i],0.001);
			sl = sprintf(sbuf," %7.3f%c",test_frozen[i],(i==NUM_TEST_FROZEN-1)?'\n':',');
			if(hDtuPipe != INVALID_HANDLE_VALUE)
				WriteFile(hDtuPipe,sbuf,sl,&sl,NULL);
		}
		__write_frz(&tm64,test_frozen);
#endif

#if (defined(ENABLE_MODULE_LOG) || defined(ENABLE_MODULE_ALL))
		if(tm64.sec == tickUlog && !bUlogUpdate)
		{
			memcpy(&test_ulog.time,&tm64,sizeof(tm64));
			test_ulog.type = i_gen_rand(11) + 1;
			test_ulog.sts = i_gen_rand(2);
			sprintf(test_ulog.buf,"ULOG trigged %d=%d at %02d:%02d:%02d.%03d",test_ulog.type,test_ulog.sts,tm64.hour,tm64.min,tm64.sec,tm64.msec);
			__write_ulog(&tm64,&test_ulog);
			bUlogUpdate = true;
			sl = sprintf(sbuf,"ULOG %d, %d, \"%s\"\n",test_ulog.type,test_ulog.sts,test_ulog.buf);
			if(hDtuPipe != INVALID_HANDLE_VALUE)
				WriteFile(hDtuPipe,sbuf,sl,&sl,NULL);
		}
		if(tm64.sec == tickPrtlog && !bPrtlogUpdate)
		{
			memcpy(&test_prtlog.time,&tm64,sizeof(tm64));
			sprintf(test_prtlog.buf,"PRTLOG trigged at %02d:%02d:%02d.%03d",tm64.hour,tm64.min,tm64.sec,tm64.msec);
			__write_prtlog(&tm64,&test_prtlog);
			bPrtlogUpdate = true;
			sl = sprintf(sbuf,"PRTLOG \"%s\"\n",test_prtlog.buf);
			if(hDtuPipe != INVALID_HANDLE_VALUE)
				WriteFile(hDtuPipe,sbuf,sl,&sl,NULL);
		}
#endif

#if (defined(ENABLE_MODULE_SOE) || defined(ENABLE_MODULE_ALL))
		if(tm64.sec == tickSoe && !bSoeUpdate)
		{
			memcpy(&test_soe.time,&tm64,sizeof(tm64));
			test_soe.pnt = i_gen_rand(NUM_TEST_FROZEN + NUM_TEST_MEASURE) + START_SYSPNT;
			test_soe.val = i_gen_rand(2);
			__write_soe(&tm64,&test_soe);
			bSoeUpdate = true;
			sl = sprintf(sbuf,"SOE[%02d:%02d:%02d.%03d] %d, %d\n",tm64.hour,tm64.min,tm64.sec,tm64.msec,test_soe.pnt,test_soe.val);
			if(hDtuPipe != INVALID_HANDLE_VALUE)
				WriteFile(hDtuPipe,sbuf,sl,&sl,NULL);
		}
#endif

#if (defined(ENABLE_MODULE_CO) || defined(ENABLE_MODULE_ALL))
		if(tm64.sec == tickTrd && !bTrdUpdate)
		{
			//memcpy(&test_trd.time,&tm64,sizeof(tm64));
			test_trd.pnt = i_gen_rand(NUM_TEST_FROZEN + NUM_TEST_MEASURE) + START_SYSPNT;
			test_trd.val = i_gen_rand(2);
			__write_trd(&tm64,&test_trd);
			bTrdUpdate = true;
			sl = sprintf(sbuf,"CO[%02d:%02d:%02d.%03d] %d, %d\n",tm64.hour,tm64.min,tm64.sec,tm64.msec,test_trd.pnt,test_trd.val);
			if(hDtuPipe != INVALID_HANDLE_VALUE)
				WriteFile(hDtuPipe,sbuf,sl,&sl,NULL);
		}
#endif
		ReleaseMutex(test_lock);

		two_sec_delay(&tm64);
	}

	return 0;
}

void save_log_file(FSLOG *pLog)
{
	char fname[MAX_PATH];
	int i,j;
	FILE *file;
	unsigned char *buf;
	
	i = sprintf(fname,"%s\\log\\%s",exeFullPath,pLog->name);
	fname[i] = 0;

	remove(fname);
	__create_folder(fname);
	file = fopen(fname,"wb+");
	if(!file)
	{
		printf("Fail to create file. err: %d.\n",GetLastError());
		return;
	}
	FSLOG_Lock(pLog);
//	buf = new unsigned char[pLog->pInformation->unitSize];
	j = FSLOG_ReadFmt(pLog,-1UL,fname);
	fwrite(fname,j,1,file);
	for(i = 0; i < FSLOG_GetUnitCount(pLog); i++ )
	{
		j = FSLOG_ReadFmt(pLog,i,fname);
		fwrite(fname,j,1,file);
	}
	FSLOG_Unlock(pLog);

//	delete [] buf;
	fclose(file);
}

int write_flash(unsigned int address, const void* data, unsigned int length);
int read_flash(unsigned int address, void* data, unsigned int length);
int erase_flash(unsigned int address, unsigned int length);
extern void init_dpa_dca_frame();

bool init_dtu_enviroment(char *pPath)
{
	fpos_t pos;
	int offset;
	uint32 inf = START_INF;
	int16 syspnt = START_SYSPNT;
	TCHAR thePath[MAX_PATH];

	memset(thePath,0,sizeof(thePath));
	sprintf(thePath,"%s\\%s",pPath,FLASH_FILE_NAME);
	printf("Try open flash file: %s\n",thePath);
	sim_flash_file = fopen(thePath,"rb+");
	if(sim_flash_file == NULL)
	{
		sim_flash_file = fopen(thePath,"wb+");
		if(sim_flash_file == NULL)
		{
			printf("Fail to create file \"%s\".\n",thePath);
			return false;
		}
	}
	offset = fseek(sim_flash_file,0,SEEK_END);
	fgetpos(sim_flash_file,&pos);
	if(pos == 0)
	{
		printf("Create new file. erase all.\n");
		erase_flash(0,SIM_FLASH_SIZE);
		printf("Init file done.\n\n");
	}
	fseek(sim_flash_file,0,SEEK_SET);

	init_dpa_dca_frame();

	test_lock = CreateMutex(NULL,FALSE,"test_mutex");
	return true;
}

void get_filted_string( char *cmd, bool bUpcase)
{
	int i;
	for(i = 0; i < MAX_PATH-1;i ++)
	{
		cmd[i] = _getch();
		_putch(cmd[i]);
		if(cmd[i] == 0xD || cmd[i] == 0x1B)
		{
			printf("\r\n");
			cmd[i] = 0;
			break;
		}
		else if(bUpcase && cmd[i] >= 'a' && cmd[i] <='z')
			cmd[i] = cmd[i] - 'a' + 'A';
	}
}

DWORD WINAPI threadDebugCmdLine(LPVOID lpParameter)
{ 
	int code;
	char cmd[MAX_PATH];
	unsigned int i,nItem = 0;
	FSLOG *pLog;
	while(1)
	{
		printf("input command code:");
		code = _getch();
		printf("\n");
		if(code == 0x1B)//ESC
			break;
		switch(code)
		{
		case 'l':
		case 'L':
			ZeroMemory(cmd,MAX_PATH);
			printf("Please input filter string:");
			get_filted_string(cmd,true);
			nItem = FSLOG_Filter(cmd,NULL);
			printf("\n%d files selected.\n",nItem);
			break;
		case 'd':
		case 'D':
			printf("%d item will be listed.\n",nItem);
			for(i = 0; i < nItem; i++)
			{
				printLog(FSLOG_GetFiltedItem(i));
				// 				if(i != nItem - 1) 
				// 					_getch();
			}
			printf("All item listed.\n");
			break;
		case 's':
		case 'S':
			for(i = 0; i < nItem; i++)
			{
				pLog = FSLOG_GetFiltedItem(i);
				if(!pLog)
					printf("\n!Invalid selection.\n");
				else
				{
					save_log_file(pLog);
					printf("\n \"%s\" will be saved.\n",pLog->name);
				}
			}
			break;
		case 'r':
		case 'R':
			FSLOG_ReleaseFilter();
			nItem = 0;
			printf("Filer released.\n");
			break;
		}
	}
	exit(1);
	return 0;
}

DWORD WINAPI threadConsole(LPVOID lpParameter)
{
	extern DWORD WINAPI FSMID_Task(void*);
	extern DWORD WINAPI threadProtocol(void*);
	char strPipeName[] = "\\\\.\\pipe\\dtuPipe";
	const char pipConnecting[] = "Pipe connecting...\n";
	DWORD wLen;

	init_dtu_enviroment((char*)lpParameter);
	srand((unsigned int)time(NULL));

// 	sprintf(cmd,"%s\\fsmiddle_console.exe",(char*)lpParameter);
// 	WinExec(cmd,SW_SHOW);
// 	Sleep(100);
	printf("Waif for connecting Pipe...\n"); 
	if(WaitNamedPipe(strPipeName,NMPWAIT_WAIT_FOREVER))
	{
		hDtuPipe = CreateFile(strPipeName,GENERIC_READ|GENERIC_WRITE,0,NULL,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,NULL);
		if(INVALID_HANDLE_VALUE == hDtuPipe)
		{
			printf("Fail to Create pipe. Err:%d.\n",GetLastError());
			return 0;
		}
		WriteFile(hDtuPipe,pipConnecting,strlen(pipConnecting),&wLen,NULL);
	}
	else
		printf("No pipe.\n");

#ifndef FILE_NO_UPDATE
	HANDLE t1 = CreateThread(NULL, 0, signal_generator, lpParameter, 0, NULL);  
#endif
	HANDLE t2 = CreateThread(NULL, 0, FSMID_Task, lpParameter, 0, NULL);  
 	HANDLE t3 = CreateThread(NULL, 0, threadDebugCmdLine, lpParameter, 0, NULL); 
	while(1)
		Sleep(1000);
}