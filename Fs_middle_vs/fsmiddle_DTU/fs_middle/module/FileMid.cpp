#include "dbmsV1.h"
#include "fs_middle.h"
#include <stdio.h>
#include <string.h>


#ifdef CPU_MK64FN1M0VMD12
#include "flashshell.h"
static bool f_ProgramUpgrade = false;
#endif

struct __filemid_operate{
	unsigned char code;
	uint8 (*f_require)(uint8 *rxbuf, uint16 len);
	uint8 (*f_continue)(uint8 *txbuf, uint16 *len);
};

struct __filemid_response{
	unsigned char code;
};

uint8 __folder_call(uint8 *rxbuf, uint16 len);
uint8 __file_read_activate(uint8 *rxbuf, uint16 len);
uint8 __file_read_confirm_rx(uint8 *rxbuf, uint16 len);
uint8 __file_write_activate(uint8 *rxbuf, uint16 len);
uint8 __file_write_transfer(uint8 *rxbuf, uint16 len);

uint8 __folder_call_confirm(uint8 *txbuf, uint16 *len);
uint8 __file_read_confirm_tx(uint8 *txbuf, uint16 *len);
uint8 __file_read_transfer_confirm(uint8 *txbuf, uint16 *len);
uint8 __file_write_confirm(uint8 *txbuf, uint16 *len);
uint8 __file_write_transfer_confirm(uint8 *txbuf, uint16 *len);

static const struct __filemid_operate __the_filemid_op[] = {
	{1,__folder_call,__folder_call_confirm},
	{3,__file_read_activate,__file_read_confirm_tx},
	{6,__file_read_confirm_rx,__file_read_transfer_confirm},
	{7,__file_write_activate,__file_write_confirm},
	{9,__file_write_transfer,__file_write_transfer_confirm},
	{0,NULL,NULL}
};

static const struct __filemid_operate *pOperate = NULL;

static uint16 s_rcot = 0;
static FSLOG *s_theFile = NULL;
static uint32 s_selectID;
static uint32 filtedItemCount;
static uint32 s_writeLength;
static char *s_filename = NULL;


static uint32 s_offset;

#ifdef CPU_MK64FN1M0VMD12
void FileMid_ProgramUpgrade(bool yes)
{
	f_ProgramUpgrade = yes;
	if(yes == true)
	{
		flashshell_Erase(MEMADDR_FLASH_PRG1, MEMSIZE_FLASH_PRG);//擦除PRG1和CBK1
	}	
}
#endif

//rexbuf[0] is "Operate Mark"
uint8 FileMid_101Requir(uint8 *rexbuf, uint16 rexlen, uint16 rcot)
{
	uint8 op = rexbuf[0];
	pOperate = __the_filemid_op;

	s_rcot = rcot;
	while(pOperate->f_require)
	{
		if(pOperate->code == op)
		{
			return pOperate->f_require(rexbuf, rexlen);
		}
		pOperate++;
	}
	fsmid_warning("![WARNING] invalid opCode()\r\n");
	return 0;
}

uint8 FileMid_101Continue(uint8 *texbuf, uint16 *texlen, uint16 *tcot)
{
	if(!pOperate || !pOperate->f_continue)
	{
		fsmid_warning("INVALID continue.\r\n");
		return 0;
	}
	*tcot = s_rcot+1;
	return pOperate->f_continue(texbuf,texlen);
}

static uint8 __folder_call(uint8 *rxbuf, uint16 len)
{
	char *pFilter;
	uint8 length = rxbuf[5];
	SYS_TIME64 tm64Pair[2];

	memcpy(&s_selectID,rxbuf + 1,4);
	pFilter = fsmid_malloc(char,length + 1);
	fsmid_assert(pFilter,__FUNCTION__,__LINE__);
    if(length==0)                        //hgy----,目录名长度为0，读取默认目录HISTORY/SOE
	{
		memcpy(pFilter,"HISTORY/SOE",11);// 11，默认目录名长度
		pFilter[11] = '\0';
	}	   
	else
	{
		memcpy(pFilter,rxbuf + 6,length);
		pFilter[length] = '\0';
	}
	rxbuf += (6 + length);
	len -= (6 + length);

	if(rxbuf[0] == 0)
		filtedItemCount = FSLOG_Filter(pFilter,NULL);
	else
	{
		rxbuf++;
		cp56ToSystime((const CP56TIME2A*)rxbuf,tm64Pair);  
		cp56ToSystime((const CP56TIME2A*)(rxbuf + sizeof(CP56TIME2A)),tm64Pair + 1);
		filtedItemCount = FSLOG_Filter(pFilter,tm64Pair);
	}
	
	s_offset = 0;
	fsmid_free(pFilter);
	return 2;
}

static uint8 __file_read_activate(uint8 *rxbuf, uint16 len)
{
	char *pName;
	uint8 length = rxbuf[1];

	pName = fsmid_malloc(char,length + 1);
	fsmid_assert(pName,__FUNCTION__,__LINE__);
	memcpy(pName,rxbuf + 2,length);
	pName[length] = '\0';

	s_theFile = FSLOG_Search(pName);
	s_offset = 0;
	if(s_theFile)
	{
		filtedItemCount = FSLOG_GetUnitCount(s_theFile);
// 		if(filtedItemCount > s_theFile->pInformation->unitCount)
// 		{
// 			s_offset += (filtedItemCount - s_theFile->pInformation->unitCount);
// 			filtedItemCount = s_theFile->pInformation->unitCount;
// 		}
	}
	else
		filtedItemCount = 0;

	fsmid_free(pName);
	return 2;
}

static uint8 __file_read_confirm_rx(uint8 *rxbuf, uint16 len)
{
	if(rxbuf[9] == 0)
	{
		s_theFile = NULL;
		return 0;
	}
	else
		return 2;
}

static uint8 __file_write_activate(uint8 *rxbuf, uint16 len)
{
	extern FSLOG *logFirmware;
	uint8 length;

	s_theFile = logFirmware;

	length = rxbuf[1];
	memcpy(s_theFile->name,rxbuf + 2,length);
	s_theFile->name[length] = '\0';
	memcpy(&s_selectID,rxbuf + 2 + length,4);
	//file size
	memcpy(&s_writeLength,rxbuf + 2 + length + 4,4);
	
	FSLOG_Clear(s_theFile);

	return 2;
}

static uint8 __file_write_transfer(uint8 *rxbuf, uint16 len)
{
	//memcpy(&s_theFile->indexLast,rxbuf + 5,4);
	//segment
	memcpy(&s_offset, rxbuf + 5, 4);

	//write file transfer here
	if(FSLOG_WriteBinary(s_theFile,rxbuf + 10,len - 11))
		return 0;

	return 2;//return (rxbuf[9]?2:0);
}



uint8 __folder_call_confirm(uint8 *txbuf, uint16 *len)
{
#define NUM_FILE_INFO_PER_PACKET		2
	FSLOG *pLog;
	uint32 i,length;

	*len = 0;

	txbuf[0] = 2;
	txbuf[1] = (filtedItemCount)?0:1;
	memcpy(txbuf + 2,&s_selectID,4);
	txbuf[6] = (s_offset +NUM_FILE_INFO_PER_PACKET < filtedItemCount)?1:0;
	txbuf[7] = min(filtedItemCount-s_offset,NUM_FILE_INFO_PER_PACKET);
	*len = 8;
	if(txbuf[7] == 0)
		return 0;
	txbuf += 8;

	for(i = 0; (i < NUM_FILE_INFO_PER_PACKET)&&(s_offset<filtedItemCount);i++)
	{
		pLog = FSLOG_GetFiltedItem(s_offset);
		fsmid_assert(pLog,__FUNCTION__,__LINE__);
		length = strlen(FSLOG_GetName(pLog));
		*txbuf = length;
		strcpy((char*)(txbuf + 1),FSLOG_GetName(pLog));
		txbuf += 1 + length;
		*txbuf++ = 0;//attribute
		memcpy(txbuf,&pLog->formatedSize,4);
		txbuf += 4;
              
        systimeToCp56(&pLog->timeCreate,(CP56TIME2A*)txbuf);                
		*len += 1 + length + 1 + 4 + 7;
		txbuf += 7;
		s_offset++;
	}

	return (filtedItemCount == s_offset)?0:2;
}

uint8 __file_read_confirm_tx(uint8 *txbuf, uint16 *len)
{
	uint32 length = 0;

	*len = 0;

	txbuf[0] = 4;
	txbuf[1] = (s_theFile)?0:1;
	if(s_theFile)
		length = strlen(s_theFile->name);//length = strlen(FSLOG_GetName(s_theFile));hgy----
	txbuf[2] = length;
	txbuf += 3;
	*len += 3;
	if(s_theFile)
	{
		memcpy(txbuf,s_theFile->name,length);//memcpy(txbuf,FSLOG_GetName(s_theFile),length);hgy---
		txbuf += length;
		*len += length;
		memcpy(txbuf,&s_selectID,4);
		memcpy(txbuf + 4,&s_theFile->formatedSize,4);
	}	
	else
	{
		memcpy(txbuf,&s_selectID,4);
		*(uint32*)&txbuf[4]=0x00;
	}
	txbuf += 8;
	*len += 8;

	if(s_theFile)
	{
		pOperate++;
		return 2;
	}
	return 0;
}

uint8 __file_read_transfer_confirm(uint8 *txbuf, uint16 *len)
{
#define NUM_LOG_STR_PER_PACKET		2  // 
	uint8 checksum = 0;
	uint32 i,length = 0;
	uint16 start=0;

	*len = 0;
	txbuf[0] = 5;
	memcpy(txbuf + 1,&s_selectID,4);
	memcpy(txbuf + 5,&s_offset,4);
	txbuf[9] = (s_offset +NUM_LOG_STR_PER_PACKET < filtedItemCount)?1:0;
	txbuf += 10;
	*len += 10;

	if(s_offset == 0)
	{

		length = FSLOG_LockReadFmt(s_theFile,-1UL,(char*)txbuf);
		checksum = byteChecksum(0,txbuf,length);
		txbuf += length;
		*len += length;
	}
	for(i = start; (i < NUM_LOG_STR_PER_PACKET)&&(s_offset<filtedItemCount);i++) 
	{
		length = FSLOG_LockReadFmt(s_theFile,s_offset,(char*)txbuf);
		checksum = byteChecksum(checksum,txbuf,length);
		txbuf += length;
		*len += length;
		s_offset++;
	}
	txbuf[0] = checksum;
	(*len)++;

	return (filtedItemCount == s_offset)?0:2;

}

uint8 __file_write_confirm(uint8 *txbuf, uint16 *len)
{
	uint8 length;

	*len = 0;
	txbuf[0] = 8;
	if(s_theFile && (s_theFile->attribute & FSLOG_ATTR_DATA_ONLY) && (s_writeLength <= s_theFile->maxUnitCount))
		txbuf[1] = 0;
	else
	{
		txbuf[1] = 1;
		txbuf[2] = 0;
		memcpy(txbuf + 3,&s_selectID,4);
		memset(txbuf + 7,0,4);
		*len = 11;
		return 0;
	}
	length = strlen(s_theFile->name);
	txbuf[2] = length;
	memcpy(txbuf + 3,s_theFile->name,length);
	txbuf += 3 + length;

	memcpy(txbuf,&s_selectID,4);
	memcpy(txbuf + 4,&s_writeLength,4);

	*len = 11 + length;

	return 0;
}

uint8 __file_write_transfer_confirm(uint8 *txbuf, uint16 *len)
{
	txbuf[0] = 10;
	memcpy(txbuf + 1,&s_selectID,4);
	//segment
	memcpy(txbuf + 5,&s_offset,4);
	txbuf[9] = 0;
	*len = 10;

	return 0;
}
