// fsmiddle_DTU.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <windows.h>
#include <conio.h>
#include <ctype.h>

extern void test_log(TCHAR *path);
extern bool init_dtu_enviroment(TCHAR *path);
extern void FSMID_Task(void*);
char exeFullPath[MAX_PATH];

extern DWORD WINAPI threadConsole(LPVOID lpParameter);
extern DWORD WINAPI threadProtocol(LPVOID lpParameter);

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
	getCurrentFolder(exeFullPath);
#if 0
	test_log(exeFullPath);
#elif 0
	HANDLE t1 = CreateThread(NULL, 0, threadConsole, exeFullPath, 0, NULL); 
	WaitForSingleObject(t1,INFINITE);
#else
	HANDLE t1 = CreateThread(NULL, 0, threadProtocol, exeFullPath, 0, NULL); 
	WaitForSingleObject(t1,INFINITE);
#endif
	_getch();
	return 0;
}

