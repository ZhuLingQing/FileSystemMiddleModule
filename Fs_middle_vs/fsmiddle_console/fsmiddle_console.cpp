// fsmiddle_console.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <windows.h>
#include <time.h>
#include <conio.h>
#include <ctype.h>
#include <stdio.h>
#include <direct.h>

char exeFullPath[MAX_PATH];

void getCurrentFolder(char path[])
{
	char *p;
	GetModuleFileName(NULL,path,MAX_PATH);
	p = path + strlen(path) - 1;
	while(*p != '\\' && p != path)
		p--;
	*p = '\0';
}


int _tmain(int argc, _TCHAR* argv[])
{
	DWORD i = 0;
	FILE *flog;
	SYSTEMTIME sys; 
	char buf[MAX_PATH] = "\\\\.\\pipe\\dtuPipe";
	char timemark[MAX_PATH];
	HANDLE hDtuPipe = CreateNamedPipe(buf,
		PIPE_ACCESS_DUPLEX | FILE_FLAG_WRITE_THROUGH,
		PIPE_TYPE_BYTE | PIPE_READMODE_BYTE | PIPE_WAIT, 
		2,
		1024,
		1024,
		NMPWAIT_WAIT_FOREVER,
		NULL);
	getCurrentFolder(exeFullPath);
	printf("Create pipe:\"%s\"\n",buf);
	if(INVALID_HANDLE_VALUE == hDtuPipe)
		printf("Fail to Create pipe. Err:%d\n",GetLastError());
	else
	{
		printf("Connecting pipe...\n");
		while(1)//for(i = 0; i < 60*10; i++)
		{
			if(ConnectNamedPipe(hDtuPipe,NULL))
				break;
			Sleep(100);
		}
		if(i >= 60*10)
			printf("Fail to connect pipe.\n");
		else
		{
			sprintf(buf,"%s\\log.log",exeFullPath);
			flog = fopen(buf,"wb+");
			fseek(flog,0,SEEK_END);
			GetLocalTime( &sys );

			i = sprintf(buf,"\n===================== LOG START FROM %02d:%02d:%02d =====================\n",sys.wHour,sys.wMinute,sys.wSecond);
			fwrite(buf,i,1,flog);
			printf("%s",buf);

			while(ReadFile(hDtuPipe,buf,sizeof(buf),&i,NULL))
			{
				if(i)
				{
					GetLocalTime( &sys );
					sprintf(timemark,"%02d:%02d:%02d \t",sys.wHour,sys.wMinute,sys.wSecond);
					fwrite(timemark,strlen(timemark),1,flog);
					printf("%s",timemark);

					buf[i] = 0;
					fwrite(buf,i,1,flog);
					printf("%s",buf);
				}
			}
		}
	}
	fclose(flog);
	//printf("Any key to exit().");
	//_getch();
	return 0;
}

