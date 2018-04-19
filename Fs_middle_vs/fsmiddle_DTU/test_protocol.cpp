#include "fs_middle.h"
#include <windows.h>
#include <time.h>
#include <conio.h>
#include <ctype.h>
#include <stdio.h>
#include <direct.h>

uint8 FileMid_101Requir(uint8 *rexbuf, uint16 rexlen, uint16 rcot);
uint8 FileMid_101Continue(uint8 *texbuf, uint16 *texlen, uint16 *tcot);

void __folder_call(const char *path, uint32 id, uint16 rcot);
void __file_read_call(const char *path, uint16 rcot);
void __file_write_call(const char *path, uint32 id, uint16 rcot);

DWORD WINAPI threadProtocol(void *lpParameter)
{
	extern void get_filted_string( char *cmd, bool bUpcase);
	extern bool init_dtu_enviroment(char*);
	extern DWORD WINAPI FSMID_Task(void*);
	int code;
	uint16 cot;
	uint32 id;
	char pathname[MAX_PATH];

	init_dtu_enviroment((char*)lpParameter);
	srand((unsigned int)time(NULL));

	HANDLE t2 = CreateThread(NULL, 0, FSMID_Task, NULL, 0, NULL);  
	while(1)
	{
		printf("input command code:");
		code = _getch();
		printf("\n");
		if(code == 0x1B)//ESC
			break;
		switch(code)
		{
		case 'r':
		case 'R':
			cot = rand();
// 			id = rand() << 16;
// 			id += rand();
			printf("input name:");
			get_filted_string(pathname,false);
			//strcpy(pathname,"frz__203000.msg");
			printf("File read call NAME:\"%s\". rcot:%X.\n",pathname,cot);
			__file_read_call(pathname,cot);
			break;
		case 'w':
		case 'W':
			cot = rand();
			id = rand() << 16;
			id += rand();
			printf("input name:");
			get_filted_string(pathname,false);
			printf("File write call NAME:\"%s\". ID:%08X, rcot:%X.\n",pathname,id,cot);
			__file_write_call(pathname,id,cot);
			break;
		case 'f':
		case 'F':
			cot = rand();
			id = rand() << 16;
			id += rand();
			printf("input name:");
			get_filted_string(pathname,true);
			printf("Folder call PATH:\"%s\". ID:%08X, rcot:%X.\n",pathname,id,cot);
			__folder_call(pathname,id,cot);
			break;
		}
	}
	exit(1);
	return 0;
}

void __folder_call(const char *path, uint32 id, uint16 rcot)
{
	uint32 flen;
	uint8 _class;
	uint8 rexbuf[MAX_PATH],texbuf[MAX_PATH],*pBuf;
	uint16 rexlen,texlen;
	uint8 i,numFile;

	rexbuf[0] = 1;
	memcpy(&rexbuf[1],&id,4);
	rexbuf[5] = strlen(path);
	memcpy(rexbuf + 6,path,rexbuf[5]);
	rexbuf[6 + rexbuf[5]] = 0;//all files
	rexlen = 7 + rexbuf[5];
	printf("\nRequire... ");
	_class = FileMid_101Requir(rexbuf,rexlen,rcot);;
	fsmid_assert(_class==2,__FUNCTION__,__LINE__);
	printf("Result is class %d.\n",_class);

	do{
		printf("Continue... \n");
		pBuf = texbuf;
		_class = FileMid_101Continue(texbuf,&texlen,&rcot);
		printf("Result is class %d",_class);
		fsmid_assert(pBuf[0] == 2,__FUNCTION__,__LINE__);
		if(pBuf[1])
			printf("Operate fail %d.\n",pBuf[1]);
		else
			printf("Operate success.\n");
		if(memcmp(&id,pBuf+2,4))
			printf("Invalid id.",*(uint32*)(pBuf+2));
		if(!pBuf[6])
			printf("!No continues.!\n");
		numFile = pBuf[7];
		printf("%d files int this frame.\n",numFile);
		pBuf += 8;
		if(numFile)
		{
			fsmid_assert(texlen > 8,__FUNCTION__,__LINE__);
			texlen -= 8;
			for(i = 0; i < numFile; i++)
			{
				flen = pBuf[0];
				fsmid_assert(texlen >= 1 + flen + 12,__FUNCTION__,__LINE__);
				texlen -= 1 + flen + 12;
				memcpy(rexbuf,pBuf + 1, flen);
				rexbuf[flen] = 0;
				pBuf += flen + 1;
				memcpy(&flen,pBuf + 1,4);
				printf("%d) %s , %6d, 20%02d-%02d-%02d.\n",i,rexbuf,flen,pBuf[5],pBuf[6],pBuf[7]);
				pBuf += 12;
			}
			fsmid_assert(texlen == 0,__FUNCTION__,__LINE__);
		}
	}while(_class);
}

void __file_read_call(const char *path, uint16 rcot)
{
	extern char exeFullPath[MAX_PATH];
	uint32 flen;
	uint8 _class;
	uint8 rexbuf[MAX_PATH],texbuf[MAX_PATH],*pBuf;
	uint16 rexlen,texlen;
	uint8 i,checksum = 0;
	FILE *freaded;

	sprintf((char*)rexbuf, "%s\\read.txt",exeFullPath);
	freaded = fopen((char*)rexbuf,"wb+");
	rexbuf[0] = 3;
	rexbuf[1] = strlen(path);
	memcpy(rexbuf + 2,path,rexbuf[1]);
	rexlen = rexbuf[1] + 2;
	printf("\nRequire...\n");
	_class = FileMid_101Requir(rexbuf,rexlen,rcot);
	fsmid_assert(_class==2,__FUNCTION__,__LINE__);
	printf("Continue... \n");
	pBuf = texbuf;
	_class = FileMid_101Continue(texbuf,&texlen,&rcot);
	printf("Result is class %d\n",_class);
	fsmid_assert(pBuf[0] == 4,__FUNCTION__,__LINE__);
	if(pBuf[1])
		printf("Operate fail %d.\n",pBuf[1]);
	else
		printf("Operate success.\n");
	flen = pBuf[2];
	memcpy(rexbuf,pBuf + 3,flen);
	rexbuf[flen] = 0;
	pBuf += flen + 3;
	fsmid_assert(texlen == flen + 11,__FUNCTION__,__LINE__);
	memcpy(&i,pBuf,4);
	memcpy(&flen,pBuf + 4,4);
	printf("FILE:%s, ID:%08X, size:%d\n",rexbuf,i,flen);

	while(_class){
		printf("Continue... \n");
		_class = FileMid_101Continue(texbuf,&texlen,&rcot);
		printf("Result is class %d\n",_class);
		fsmid_assert(texbuf[0] == 5,__FUNCTION__,__LINE__);
		fsmid_assert((_class == 2 && texbuf[9] == 1)||(_class == 0 && texbuf[9] == 0),__FUNCTION__,__LINE__);
		fwrite(texbuf + 10,texlen-11,1,freaded);
		fsmid_assert(texbuf[texlen-1] == byteChecksum(0,texbuf + 10,texlen-11),__FUNCTION__,__LINE__);
	}while(_class);

	rexbuf[0] = 6;
	rexbuf[9] = 0;
	_class = FileMid_101Requir(rexbuf,10,rcot);
	fsmid_assert(_class==0,__FUNCTION__,__LINE__);
	fclose(freaded);
}

void __file_write_call(const char *path, uint32 id, uint16 rcot)
{
	extern char exeFullPath[MAX_PATH];
	const char cstrFileName[] = "Romeo and Juliet.txt";
	fpos_t pos;
	uint32 packlen,i,flen;
	uint8 _class;
	uint8 rexbuf[MAX_PATH],texbuf[MAX_PATH],*pBuf;
	uint16 rexlen,texlen;
	uint8 checksum = 0;
	FILE *fwritten;

	sprintf((char*)rexbuf, "%s\\%s",exeFullPath,cstrFileName);
	fwritten = fopen((char*)rexbuf,"rb+");
	fseek(fwritten,0,SEEK_END);
	fgetpos(fwritten,&pos);
	fseek(fwritten,0,SEEK_SET);

	rexbuf[0] = 7;
	rexbuf[1] = strlen(cstrFileName);
	memcpy(rexbuf + 2,path,rexbuf[1]);
	memcpy(rexbuf + 2+rexbuf[1],&id,4);
	memcpy(rexbuf + 6+rexbuf[1],&pos,4);
	rexlen = rexbuf[1] + 10;
	printf("\nRequire... ");
	_class = FileMid_101Requir(rexbuf,rexlen,rcot);
	fsmid_assert(_class==2,__FUNCTION__,__LINE__);
	printf("Continue... \n");

	pBuf = texbuf;
	_class = FileMid_101Continue(texbuf,&texlen,&rcot);
	printf("Result is class %d",_class);
	fsmid_assert(pBuf[0] == 8,__FUNCTION__,__LINE__);
	fsmid_assert(_class==0,__FUNCTION__,__LINE__);
	if(pBuf[1])
		printf("Operate fail %d.\n",pBuf[1]);
	else
		printf("Operate success.\n");
	flen = pBuf[2];
	memcpy(rexbuf,pBuf + 3,flen);
	rexbuf[flen] = 0;
	pBuf += flen + 3;
	fsmid_assert(texlen == flen + 11,__FUNCTION__,__LINE__);
	memcpy(&i,pBuf,4);
	memcpy(&flen,pBuf + 4,4);
	printf("FILE:%s, ID:%08X, size:%d\n",rexbuf,i,flen);

#define LENGTH_PER_PACKET		200
	flen = pos;
	for(i = 0; i < flen; i+=packlen)
	{
		packlen = min((flen - i),LENGTH_PER_PACKET);
		rexbuf[0] = 9;
		memcpy(rexbuf+1,&id,4);
		memcpy(rexbuf+5,&i,4);
		rexbuf[9] = ((flen - i)>packlen)?1:0;
		fread(rexbuf+10,1,packlen,fwritten);
		checksum = byteChecksum(0,rexbuf + 10,packlen);
		rexbuf[10 + packlen] = checksum;
		rexlen = 11 + packlen;
		_class = FileMid_101Requir(rexbuf,rexlen,rcot);
		fsmid_assert(_class==2,__FUNCTION__,__LINE__);
		printf("Write from:%7d, %d Bytes of %d Bytes.\n",i,packlen,flen);
	}

	printf("Continue... \n");
	_class = FileMid_101Continue(texbuf,&texlen,&rcot);
	printf("Result is class %d",_class);
	fsmid_assert(_class == 0,__FUNCTION__,__LINE__);
	if(texbuf[9] == 0)
		printf("Success.\n");
	else
		printf("Fail %d.\n",texbuf[9]);

	fclose(fwritten);
}