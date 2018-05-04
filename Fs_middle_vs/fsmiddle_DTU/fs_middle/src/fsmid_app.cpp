

#ifdef CPU_MK64FN1M0VMD12
#include "board.h"
#include "fsl_common.h"
#include "board.h"
#include "SpiNorFlash.h"
#include "fsl_debug_console.h"
#endif

#include "dbmsV1.h"
#include "dpa10x.h"

#include "fs_middle.h"

#undef  _FSLOG_INFO_MSG_
#define _FSLOG_INFO_MSG_
#if defined(_FSLOG_INFO_MSG_)
#define FSLOG_INFO_MSG(fmt,...)       fsmid_info(fmt, ##__VA_ARGS__)
#else
#define FSLOG_INFO_MSG(fmt,...)
#endif  //#if defined(_FSLOG_INFO_MSG_)

static uint8 handleDpa;
static uint8 handleDca;
static uint8 handleWho;

FSLOG *logFirmware;

//*no for 101
FSLOG *logRawSoe;
FSLOG *logRawTrd;
FSLOG *logPrintLog;

//*1
FSLOG *logUlog;
FSLOG *logSoe;
FSLOG *logCo;

#define TEMP_CFG_NAME		"TEMP/BAYxx_xxxx_xxxxxxxx_xxxxxx_xxx.cfg"
#define TEMP_DAT_NAME		"TEMP/BAYxx_xxxx_xxxxxxxx_xxxxxx_xxx.dat"
#define TEMP_EXV_NAME		"TEMP/EXVxxxxxxxx.msg"
#define TEMP_FIXPT_NAME		"TEMP/FIXPTxxxxxxxx.msg"
#define TEMP_FRZ_NAME		"TEMP/FRZxxxxxxxx.msg"

FSLOG *logCfgTable[NUMBER_OF_CFG];
unsigned int nCfg = 0;
FSLOG **logCfg = NULL;

FSLOG *logDatTable[NUMBER_OF_DAT];
unsigned int nDat = 0;
FSLOG **logDat = NULL;

FSLOG *logExtremeTable[NUMBER_OF_EXV];
unsigned int nExtreme = 0;
FSLOG **logExtreme = NULL;

FSLOG *logFixptTable[NUMBER_OF_FIXPT];
unsigned int nFixpt = 0;
FSLOG **logFixpt = NULL;

FSLOG *logFrozenTable[NUMBER_OF_FRZ];
unsigned int nFrozen = 0;
FSLOG **logFrozen = NULL;

#ifdef CPU_MK64FN1M0VMD12

int write_flash(unsigned int address, const void* data, unsigned int length)
{
    if(SPINOR_Write(data_flash,address,data,length) != kStatus_Success) return -1;
	return 0;
}
int read_flash(unsigned int address, void* data, unsigned int length)
{
    if(SPINOR_Read(data_flash,address,data,length) != kStatus_Success) return -1;
	return 0;
}
int erase_flash(unsigned int address, unsigned int length)
{
    if(SPINOR_Erase(data_flash,address,length) != kStatus_Success) return -1;
	return 0;
}

FSLOG_INTERFACE intrFslog = 
{
	write_flash,
	read_flash,
	erase_flash,
};
#endif



void FSMID_FormatLogName(FSLOG *pLog, const char* nameLowCase, const SYS_TIME64 *tm64)
{
	int i = 0;
	char nameUpCase[16];
	while(nameLowCase[i])
	{
		if(nameLowCase[i]>='a'&&nameLowCase[i]<='z')
			nameUpCase[i] = nameLowCase[i] - 'a' + 'A';
		i++;
	}
	nameUpCase[i] = 0;
	FORMAT_LOG_NAME(pLog,nameUpCase,nameLowCase,tm64);
	FSLOG_INFO_MSG("[FSRENAME] to \"%s\".\r\n",pLog->name);
}

void FSMID_FormatWaveName(FSLOG *pLog, const char* nameExt, const SYS_TIME64 *tm64)
{
	FSLOG_INFO_MSG("[FSRENAME] from:\"%s\" to ",pLog->name);
	FORMAT_WAVE_NAME(pLog,nameExt,0,0,tm64);//??
	FSLOG_INFO_MSG("%s\".\r\n",pLog->name);
}

void FSMID_CreateLogs(const SYS_TIME64 *tm64)
{
	unsigned int i, address = DYNAMIC_START_BLOCK*FLASH_BLOCK_SIZE;
	FSLOG_INFORMATION *pInfo;
	FSLOG **ppLog;

	logFirmware = FSLOG_Open("SYSTEM/FIRMWARE.BIN", NULL,			&infoFwUpdate, FSLOG_ATTR_OTP|FSLOG_ATTR_DATA_ONLY);

#if (defined(ENABLE_MODULE_SOE) || defined(ENABLE_MODULE_ALL))
	logRawSoe   = FSLOG_Open("SYSTEM/RAW_SOE",		NULL,			&infoRawSoe,	FSLOG_ATTR_OPEN_EXIST);
	fsmid_assert(logRawSoe,__FILE__,__LINE__);
#endif
#if (defined(ENABLE_MODULE_CO) || defined(ENABLE_MODULE_ALL))
	logRawTrd   = FSLOG_Open("SYSTEM/RAW_TRD",		NULL,			&infoRawTrd,	FSLOG_ATTR_OPEN_EXIST);
	fsmid_assert(logRawTrd,__FILE__,__LINE__);
#endif
#if (defined(ENABLE_MODULE_LOG) || defined(ENABLE_MODULE_ALL))
	logPrintLog = FSLOG_Open("SYSTEM/PRINTLOG",	NULL,			&infoPrintLog,	FSLOG_ATTR_OPEN_EXIST);
	fsmid_assert(logPrintLog,__FILE__,__LINE__);
#endif

#if (defined(ENABLE_MODULE_LOG) || defined(ENABLE_MODULE_ALL))
	logUlog		= FSLOG_Open("HISTORY/ULOG/ulog.msg",		&funcLogUlog,	&infoLogUlog,	FSLOG_ATTR_OPEN_EXIST);
	fsmid_assert(logUlog,__FILE__,__LINE__);
#endif

#if (defined(ENABLE_MODULE_SOE) || defined(ENABLE_MODULE_ALL))
	logSoe		= FSLOG_Open("HISTORY/SOE/soe.msg",		&funcLogSoe,	&infoLogSoe,	FSLOG_ATTR_OPEN_EXIST);
	fsmid_assert(logSoe,__FILE__,__LINE__);
#endif
#if (defined(ENABLE_MODULE_CO) || defined(ENABLE_MODULE_ALL))
	logCo		= FSLOG_Open("HISTORY/CO/co.msg",			&funcLogCo,		&infoLogCo,		FSLOG_ATTR_OPEN_EXIST);
	fsmid_assert(logCo,__FILE__,__LINE__);
#endif

#if (defined(ENABLE_MODULE_CFG_DAT) || defined(ENABLE_MODULE_ALL))
	for(i = 0, nCfg = 0, ppLog = logCfgTable; i < NUMBER_OF_CFG; i++, ppLog++)
	{
		*ppLog = FSLOG_Open(TEMP_CFG_NAME,&funcLogCfg,&infoLogCfg[i],FSLOG_ATTR_OPEN_EXIST|FSLOG_ATTR_OTP);
		fsmid_assert(*ppLog,__FILE__,__LINE__);
		if((*ppLog)->timeCreate.year != 0)
		{
			FSMID_FormatWaveName(*ppLog,"cfg",&(*ppLog)->timeCreate);
			nCfg++;
		}
		else if(!logCfg)
			logCfg = ppLog;
	}
	if(!logCfg)
	{
		logCfg = logCfgTable;
		for(i = 1, ppLog = logCfgTable + 1; i < NUMBER_OF_CFG; i++,ppLog++)
		{
			if(systimeCmp(&(*logCfg)->timeCreate,&(*ppLog)->timeCreate) > 0)
				logCfg = ppLog;
		}
	}

	for(i = 0, nDat = 0, ppLog = logDatTable; i < NUMBER_OF_DAT; i++, ppLog++)
	{
		*ppLog = FSLOG_Open(TEMP_DAT_NAME,&funcLogDat,&infoLogDat[i],FSLOG_ATTR_OPEN_EXIST|FSLOG_ATTR_OTP);
		fsmid_assert(*ppLog,__FILE__,__LINE__);
		if((*ppLog)->timeCreate.year != 0)
		{
			FSMID_FormatWaveName(*ppLog,"dat",&(*ppLog)->timeCreate);
			nDat++;
		}
		else if(!logDat)
			logDat = ppLog;
	}
	if(!logDat)
	{
		logDat = logDatTable;
		for(i = 1, ppLog = logDatTable + 1; i < NUMBER_OF_DAT; i++,ppLog++)
		{
			if(systimeCmp(&(*logDat)->timeCreate,&(*ppLog)->timeCreate) > 0)
				logDat = ppLog;
		}
	}
#endif

#if (defined(ENABLE_MODULE_EXV) || defined(ENABLE_MODULE_ALL))
	if(GetMeasureCount())
	{
		for(i = 0, nExtreme = 0, ppLog = logExtremeTable; i < NUMBER_OF_EXV; i++,ppLog++)
		{
			pInfo = fsmid_malloc(FSLOG_INFORMATION,1);
			memcpy(pInfo,&infoLogExtreme,sizeof(FSLOG_INFORMATION));
			pInfo->baseAddress = address;
			pInfo->unitCount = GetMeasureCount()*2+3;
			pInfo->blockNumber = FSLOG_CalcBlockNumber(pInfo->unitSize,pInfo->blockSize,pInfo->unitCount,true);
			fsmid_assert(address + pInfo->blockNumber * pInfo->blockSize < FLASH_MEMORY_SIZE,__FILE__,__LINE__);
			*ppLog = FSLOG_Open(TEMP_EXV_NAME,&funcLogExtreme,pInfo,FSLOG_ATTR_OPEN_EXIST|FSLOG_ATTR_OTP);
			fsmid_assert(*ppLog,__FILE__,__LINE__);
			address += pInfo->blockNumber * pInfo->blockSize;
			if((*ppLog)->timeCreate.year != 0)
			{
				FSMID_FormatLogName(*ppLog,"exv",&(*ppLog)->timeCreate);
				nExtreme++;
				if(systimeSameDay(&(*ppLog)->timeCreate,tm64))
				{
					fsmid_assert(!logExtreme,__FILE__,__LINE__);
					logExtreme = ppLog;
				}
			}
			else if(!logExtreme)
				logExtreme = ppLog;
		}
		if(!logExtreme)
		{
			logExtreme = logExtremeTable;
			for(i = 1, ppLog = logExtremeTable + 1; i < NUMBER_OF_EXV; i++,ppLog++)
			{
				if(systimeCmp(&(*logExtreme)->timeCreate,&(*ppLog)->timeCreate) > 0)
					logExtreme = ppLog;
			}
		}
	}
#else
	address += infoLogExtreme.blockNumber * infoLogExtreme.blockSize*NUMBER_OF_EXV;
#endif

#if (defined(ENABLE_MODULE_FIXPT) || defined(ENABLE_MODULE_ALL))
	if(GetMeasureCount())
	{
		for(i = 0, nFixpt = 0, ppLog = logFixptTable; i < NUMBER_OF_FIXPT; i++,ppLog++)
		{
			pInfo = fsmid_malloc(FSLOG_INFORMATION,1);
			memcpy(pInfo,&infoLogFixpt,sizeof(FSLOG_INFORMATION));
			pInfo->baseAddress = address;
			pInfo->blockNumber = FSLOG_CalcBlockNumber(pInfo->unitSize,pInfo->blockSize,pInfo->unitCount,true);
			pInfo->unitSize = sizeof(LOG_FIXPT) + sizeof(float)*GetMeasureCount();
			//pInfo->unitCount = 96;
			fsmid_assert(address + pInfo->blockNumber * pInfo->blockSize < FLASH_MEMORY_SIZE,__FILE__,__LINE__);
			*ppLog = FSLOG_Open(TEMP_FIXPT_NAME,&funcLogFixpt,pInfo,FSLOG_ATTR_OPEN_EXIST|FSLOG_ATTR_OTP);
			fsmid_assert(ppLog,__FILE__,__LINE__);
			address += pInfo->blockNumber * pInfo->blockSize;
			if((*ppLog)->timeCreate.year != 0)
			{
				FSMID_FormatLogName(*ppLog,"fixpt",&(*ppLog)->timeCreate);
				nFixpt++;
				//select current day file
				if(systimeSameDay(&(*ppLog)->timeCreate,tm64))
				{
					fsmid_assert(!logFixpt,__FILE__,__LINE__);
					logFixpt = ppLog;
				}
			}
			else if(!logFixpt)
				logFixpt = ppLog;
		}
		if(logFixpt)
		{
			if(strcmp((*logFixpt)->name,TEMP_FIXPT_NAME)==0)
			{
				FSMID_FormatLogName(*logFixpt,"fixpt",tm64);
				memcpy(&(*logFixpt)->timeCreate,tm64,sizeof(SYS_TIME64));
				nFixpt++;
			}
		}
		if(!logFixpt)
		{
			logFixpt = logExtremeTable;
			for(i = 1, ppLog = logExtremeTable + 1; i < NUMBER_OF_FIXPT; i++,ppLog++)
			{
				if(systimeCmp(&(*logFixpt)->timeCreate,&(*ppLog)->timeCreate) > 0)
					logFixpt = ppLog;
			}
		}
	}
#else
	address += infoLogFixpt.blockNumber * infoLogFixpt.blockSize*NUMBER_OF_FIXPT;
#endif

#if (defined(ENABLE_MODULE_RROZEN) || defined(ENABLE_MODULE_ALL))
	if(GetFrozenCount())
	{
		for(i = 0, nFrozen = 0, ppLog = logFrozenTable; i < NUMBER_OF_FRZ; i++,ppLog++)
		{
			pInfo = fsmid_malloc(FSLOG_INFORMATION,1);
			memcpy(pInfo,&infoLogFrozen,sizeof(FSLOG_INFORMATION));
			pInfo->baseAddress = address;
			pInfo->blockNumber = FSLOG_CalcBlockNumber(pInfo->unitSize,pInfo->blockSize,pInfo->unitCount,true);
			pInfo->unitSize = sizeof(LOG_FROZRN) + sizeof(float)*GetFrozenCount();
			//pInfo->unitCount = 97;
			fsmid_assert(address + pInfo->blockNumber * pInfo->blockSize < FLASH_MEMORY_SIZE,__FILE__,__LINE__);
			*ppLog = FSLOG_Open(TEMP_FRZ_NAME,&funcLogFrozen,pInfo,FSLOG_ATTR_OPEN_EXIST|FSLOG_ATTR_OTP);
			fsmid_assert(ppLog,__FILE__,__LINE__);
			address += pInfo->blockNumber * pInfo->blockSize;
			if((*ppLog)->timeCreate.year != 0)
			{
				FSMID_FormatLogName(*ppLog,"frz",&(*ppLog)->timeCreate);
				nFrozen++;
				//select current day file
				if(systimeSameDay(&(*ppLog)->timeCreate,tm64))
				{
					fsmid_assert(!logFrozen,__FILE__,__LINE__);
					logFrozen = ppLog;
				}
			}
			else if(!logFrozen)
				logFrozen = ppLog;
		}
		if(!logFrozen)
		{
			logFrozen = logFrozenTable;
			for(i = 1, ppLog = logFrozenTable + 1; i < NUMBER_OF_FRZ; i++,ppLog++)
			{
				if(systimeCmp(&(*logFrozen)->timeCreate,&(*ppLog)->timeCreate) > 0)
					logFrozen = ppLog;
			}
		}
	}
#else
	address += infoLogFrozen.blockNumber * infoLogFrozen.blockSize*NUMBER_OF_FRZ;
#endif
}

// static void write_soe(SYS_TIME64 *pTime, unsigned int inf, unsigned char value)
// {
// 	LOG_SOE soe;
// 	memcpy(&soe.time,pTime,sizeof(soe.time));
// 	soe.information = inf;
// 	soe.value = value;
// 	FSLOG_LockWrite(logSoe,&soe);
// }

static void FSMID_SoeApp(const SYS_TIME64 *tm64)
{
#if (defined(ENABLE_MODULE_SOE) || defined(ENABLE_MODULE_ALL))
//	int i, j;
	struDpa10xFrm *pfrm;
	void *ppntcfg = NULL;
// 	struDpa10xIt_Cfg *pItCfg;
// 	struDpa10xMe_Cfg *pMeCfg;
	struDpa10xDp_Cfg *pDpCfg;
	struDpa10xSp_Cfg *pSpCfg;

	SOEEVENT *pEvent;

	uint32 inf;
	int8 frm;
	int16 pnt,otherpnt;

	/*static*/ LOG_SOE soe = {0};
	/*static*/ int16 s_otherpnt = 0;
	/*static*/ bool flag=0;//表示有临时soe未保存

	pfrm = dpa101appl.pport->pfrm;//指向第1帧
	while (pEvent = db_GetSoe(handleDpa))
	{
		//1.save soeevent, 单纯把event记录下来，给维护口读取，维护口将按记录读取，与文件无关
		//包括soe trd prtlog
		FSLOG_LockWrite(logRawSoe,pEvent);

		//2.save soe for 101
		//包括soe trd ulog, 仅soe有双点处理, ulog不需要search到inf,直接保存
		//这里仅以soe为例，以soe1为临时变量(struSoeLog soe1)
		ppntcfg = dpa10x_SearchSyspntInFrms(dpa101appl.pport, pEvent->pnt, TypeidDi, &frm, &pnt, &otherpnt, &inf);//查找系统点对应的点配置等，并得到inf

#ifdef VS_SIMULATE
		memcpy(&soe.time,&pEvent->time,sizeof(soe.time));
		soe.information = inf;
		soe.value = inf^0xFF;//把单点SIQ做成双点DIQ
		FSLOG_LockWrite(logSoe,&soe);
#else
		if (ppntcfg == NULL)//没找到，说明点不在101配置中
		{
			if(flag)
			{
				flag = 0;
				FSLOG_LockWrite(logSoe,&soe);
			}
			continue;
		}


		if (pfrm[frm].pcfg->frmtype == M_DP_TA_1 || pfrm[frm].pcfg->frmtype == M_DP_TB_1)	//找到在双点帧里
		{	
			pDpCfg = (struDpa10xDp_Cfg *)ppntcfg;//指向点配置

			if(flag == 1)//有临时变量中未存SOE
			{
				if(pEvent->pnt == s_otherpnt)//找到第2条soe，丢弃上次soe，保存本次soe
				{
					flag = 0;
					memcpy(&soe.time,&pEvent->time,sizeof(soe.time));
					soe.information = inf;
					soe.value = ((db_GetDi(pDpCfg->syspnton)&1)<<1) | (db_GetDi(pDpCfg->syspntoff)&1);
					FSLOG_LockWrite(logSoe,&soe);
				}
				else //不是同一个双点双点遥信点，则保存临时变量soe，然后把本soe推入临时变量
				{
					FSLOG_LockWrite(logSoe,&soe);

					flag = 1;
					s_otherpnt = otherpnt;
					memcpy(&soe.time,&pEvent->time,sizeof(soe.time));
					soe.information = inf;
					soe.value = ((db_GetDi(pDpCfg->syspnton)&1)<<1) | (db_GetDi(pDpCfg->syspntoff)&1);
				}
			}
			else //没有未保存临时变量，把本soe推入临时变量soe1中
			{		
				flag = 1;
				s_otherpnt = otherpnt;
				memcpy(&soe.time,&pEvent->time,sizeof(soe.time));
				soe.information = inf;
				soe.value = ((db_GetDi(pDpCfg->syspnton)&1)<<1) | (db_GetDi(pDpCfg->syspntoff)&1);
			}
		}
		else //单点帧的点，直接保存log
		{
			if(flag)
				FSLOG_LockWrite(logSoe,&soe);

			pSpCfg = (struDpa10xSp_Cfg *)ppntcfg;
			flag = 0;
			memcpy(&soe.time,&pEvent->time,sizeof(soe.time));
			soe.information = inf;
			soe.value = (db_GetDi(pSpCfg->syspnt)&1)<<1;//把单点SIQ做成双点DIQ
			FSLOG_LockWrite(logSoe,&soe);
		}
#endif
	}

	if(flag)
		FSLOG_LockWrite(logSoe,&soe);
#endif
}

static void FSMID_CoApp(const SYS_TIME64 *tm64)
{
#if (defined(ENABLE_MODULE_CO) || defined(ENABLE_MODULE_ALL))
	struDpa10xFrm *pfrm;
	void *ppntcfg = NULL;

	TRDEVENT *pEvent;

	uint32 inf;
	int8 frm;
	int16 pnt,otherpnt;

	LOG_CO co = {0};
	LOG_RAWTRD trd;

	pfrm = dpa101appl.pport->pfrm;//指向第1帧
	while (pEvent = db_GetTrd(handleDca))
	{
		memcpy(&trd.time,tm64,sizeof(trd.time));
		memcpy(&trd.trd,pEvent,sizeof(trd.trd));
		FSLOG_LockWrite(logRawTrd,&trd);

		ppntcfg = dpa10x_SearchSyspntInFrms(dpa101appl.pport, pEvent->pnt, TypeidDo, &frm, &pnt, &otherpnt, &inf);//查找系统点对应的点配置等，并得到inf

		memcpy(&co.time,tm64,sizeof(co.time));
		co.information = inf;
		co.value = pEvent->val;
		FSLOG_LockWrite(logCo,&co);
	}
#endif
}

static void FSMID_LogApp(const SYS_TIME64 *tm64)
{
#if (defined(ENABLE_MODULE_LOG) || defined(ENABLE_MODULE_ALL))
	PRTLOGEVENT *prtEvent;
	ULOGEVENT *ulogEvent;

	while(ulogEvent = db_GetULog(handleWho))
		FSLOG_LockWrite(logUlog,ulogEvent);

	while(prtEvent = db_GetPrtLog(handleWho))
		FSLOG_LockWrite(logPrintLog,prtEvent);
#endif
}

static void FSMID_ExtremeApp(const SYS_TIME64 *tm64)
{
#if (defined(ENABLE_MODULE_EXV) || defined(ENABLE_MODULE_ALL))
	unsigned int i;
	FSMID_POINT *point;

	for( i = 0, point = GetMeasureTable(); i < GetMeasureCount(); i++,point++ )
	{
		UpdateExtremeValue(tm64, i, db_GetAi(handleDpa,point->point));
	}
#endif
}

static void FSMID_FixptApp(const SYS_TIME64 *tm64)
{
#if (defined(ENABLE_MODULE_FIXPT) || defined(ENABLE_MODULE_ALL))
	unsigned int i;
	FSMID_POINT *point;
	LOG_FIXPT *pFixpt = (LOG_FIXPT*)fsmid_malloc(unsigned char,sizeof(LOG_FIXPT) + GetMeasureCount()*sizeof(float));

	memcpy(&pFixpt->time,tm64,sizeof(pFixpt->time));
	pFixpt->numUnit = GetMeasureCount();
	for( i = 0, point = GetMeasureTable(); i < GetMeasureCount(); i++,point++ )
	{
		pFixpt->value[i] = db_GetAi(handleDpa,point->point);
	}
	if(pFixpt->numUnit)
		FSLOG_LockWrite(*logFixpt,pFixpt);
	fsmid_free(pFixpt);
#endif
}

static void FSMID_FrozenApp(const SYS_TIME64 *tm64)
{
#if (defined(ENABLE_MODULE_FROZEN) || defined(ENABLE_MODULE_ALL))
	unsigned int i;
	FSMID_POINT *point;
	LOG_FIXPT *pFrozen = (LOG_FIXPT*)fsmid_malloc(unsigned char,sizeof(LOG_FIXPT) + GetFrozenCount()*sizeof(float));

	memcpy(&pFrozen->time,tm64,sizeof(pFrozen->time));
	pFrozen->numUnit = GetFrozenCount();
	for( i = 0, point = GetFrozenTable(); i < GetFrozenCount(); i++,point++ )
	{
		pFrozen->value[i] = db_GetPa(point->point);
	}
	if(pFrozen->numUnit)
		FSLOG_LockWrite(*logFrozen,pFrozen);
	fsmid_free(pFrozen);
#endif
}

// 每次调用就生产一个新的CFG文件
// 该任务有Dtu3016进行调用
// 参数，当前时间，通道起始（0或者8），采集频率
void FSMID_CfgApp(const SYS_TIME64 *tm64,unsigned int chnoffset,float freq)
{
#if (defined(ENABLE_MODULE_CFG_DAT) || defined(ENABLE_MODULE_ALL))
	LOG_CFG *pCfg = (LOG_CFG*)fsmid_malloc(unsigned char,sizeof(LOG_CFG));;
	SYS_TIME64 tmpTime;
	unsigned short mSec;

	if(!logCfg) return;

	// 计算前导时间,当前触发时间-3个周波的时间
	mSec = (unsigned short)(1000.0 / freq * 3);
	memcpy(&tmpTime,tm64,sizeof(SYS_TIME64));
	if(tmpTime.msec >= mSec) 
		tmpTime.msec -= mSec;
	else
	{
		mSec -= tmpTime.msec;
		tmpTime.msec = 1000 - mSec;
		if(tmpTime.sec > 0) 
			tmpTime.sec--;
		else
		{
			tmpTime.sec = 59;
			if(tmpTime.min > 0)
				tmpTime.min--;
			else
			{
				tmpTime.min = 59;
				if(tmpTime.hour > 0) tmpTime.hour--;
				else tmpTime.hour = 23;
			}
		}
	}

	// 直流偏移在记录的时候,减去,这里就保留为0
	// 直接输入9个条目信息
	memset(pCfg->strBuf,0,80);
	sprintf(pCfg->strBuf,"%d,IA,A,CT,A,0.015019053,0.000000,0.000000,-32767,372727,1.000000,1.000000,S\r\n",chnoffset);
	FSLOG_LockWrite(*logCfg,pCfg);
	memset(pCfg->strBuf,0,80);
	sprintf(pCfg->strBuf,"%d,IB,B,CT,A,0.015019053,0.000000,0.000000,-32767,372727,1.000000,1.000000,S\r\n",chnoffset+1);
	FSLOG_LockWrite(*logCfg,pCfg);
	memset(pCfg->strBuf,0,80);
	sprintf(pCfg->strBuf,"%d,IC,0,CT,A,0.015019053,0.000000,0.000000,-32767,372727,1.000000,1.000000,S\r\n",chnoffset+2);
	FSLOG_LockWrite(*logCfg,pCfg);
	memset(pCfg->strBuf,0,80);
	sprintf(pCfg->strBuf,"%d,I0,0,CT,A,0.015019053,0.000000,0.000000,-32767,372727,1.000000,1.000000,S\r\n",chnoffset+3);
	FSLOG_LockWrite(*logCfg,pCfg);
	memset(pCfg->strBuf,0,80);
	sprintf(pCfg->strBuf,"%d,UA,A,PT,V,0.015019053,0.000000,0.000000,-32767,372727,1.000000,1.000000,S\r\n",chnoffset+4);
	FSLOG_LockWrite(*logCfg,pCfg);
	memset(pCfg->strBuf,0,80);
	sprintf(pCfg->strBuf,"%d,UB,B,PT,V,0.015019053,0.000000,0.000000,-32767,372727,1.000000,1.000000,S\r\n",chnoffset+5);
	FSLOG_LockWrite(*logCfg,pCfg);
	memset(pCfg->strBuf,0,80);
	sprintf(pCfg->strBuf,"%d,UC,0,PT,V,0.015019053,0.000000,0.000000,-32767,372727,1.000000,1.000000,S\r\n",chnoffset+6);
	FSLOG_LockWrite(*logCfg,pCfg);
	memset(pCfg->strBuf,0,80);
	sprintf(pCfg->strBuf,"%d,U0,0,PT,V,0.015019053,0.000000,0.000000,-32767,372727,1.000000,1.000000,S\r\n",chnoffset+7);
	FSLOG_LockWrite(*logCfg,pCfg);
	memset(pCfg->strBuf,0,80);
	sprintf(pCfg->strBuf,"%.6f\r\n1\n\r,%.6f,768\r\n%02d/%02d%04d,%02d:%02d:%02d.%06d\r\n%02d/%02d%04d,%02d:%02d:%02d.%06d\r\nBINARY\r\n\1.000000",
		freq,freq*96,
		tmpTime.mon,tmpTime.day,tmpTime.year,tmpTime.min,tmpTime.sec,tmpTime.msec*1000,
		tm64->mon,tm64->day,tm64->year,tm64->hour,tm64->min,tm64->sec,tm64->msec*1000);
	FSLOG_LockWrite(*logCfg,pCfg);
	fsmid_free(pCfg);

	// 保存为文件,并移动指针
	if(nCfg < NUMBER_OF_CFG) nCfg++;
	/* 确认一下 移动指针是否正确 */
		logCfg++;
	if(logCfg > &logCfgTable[NUMBER_OF_CFG-1]) logCfg = &logCfgTable[0];

	if((*logCfg)->unitNumber) FSLOG_Clear(*logCfg);                /* 不理解 确认一下问题,有没有问题*/
	memcpy(&(*logCfg)->timeCreate,tm64,sizeof(SYS_TIME64));
	FSMID_FormatWaveName(*logFixpt,"cfg",tm64);
#endif
}
void FSMID_SaveDat(const SYS_TIME64 *tm64)
{
#if (defined(ENABLE_MODULE_CFG_DAT) || defined(ENABLE_MODULE_ALL))

	if(!logDat) return;

	if(nFrozen < NUMBER_OF_FRZ) nFrozen++;
	/* 同 logCfg一样，需确认 */
	logDat ++;
	if(logDat > &logDatTable[4]+ NUMBER_OF_DAT) logDat = &logDatTable[0];

	if((*logDat)->unitNumber) FSLOG_Clear(*logDat);  /* 不理解 确认一下问题*/
	memcpy(&(*logDat)->timeCreate,tm64,sizeof(SYS_TIME64));
	FSMID_FormatLogName(*logDat,"dat",tm64);
#endif
}

static void FSMID_SaveExtremeLog(const SYS_TIME64 *tm64)
{
#if (defined(ENABLE_MODULE_EXV) || defined(ENABLE_MODULE_ALL))
	int i;
	LOG_EXTREME exv = {0};
	LOG_EXTREME *pExtreme = GetMaximumTable();

	if(!pExtreme)
		return;
	if((*logExtreme)->unitNumber)
	{
		FSLOG_Clear(*logExtreme);
	}
	memcpy(&(*logExtreme)->timeCreate,&pExtreme->time,sizeof(SYS_TIME64));
	FSMID_FormatLogName(*logExtreme,"exv",&pExtreme->time);
	
	FSLOG_Lock(*logExtreme);
// 	exv.time.year = pExtreme->time.year;
// 	exv.time.mon = pExtreme->time.mon;
// 	exv.time.day = pExtreme->time.day;
// 	exv.time.hour = pExtreme->time.hour;
// 	exv.time.min = pExtreme->time.min;
// 	exv.time.sec = pExtreme->time.sec;
	memcpy(&exv.time,&pExtreme->time,sizeof(exv.time));
	exv.type = EXTREME_MAX_MARK;
	FSLOG_Write(*logExtreme,&exv);

	for( i = 0, pExtreme = GetMaximumTable(); i < GetMeasureCount(); i++, pExtreme++ )
	{
		FSLOG_Write(*logExtreme,pExtreme);
	}

	exv.type = EXTREME_MIN_MARK;
	FSLOG_Write(*logExtreme,&exv);

	for( i = 0, pExtreme = GetMinimumTable(); i < GetMeasureCount(); i++, pExtreme++ )
	{
		FSLOG_Write(*logExtreme,pExtreme);
	}

	exv.type = EXTREME_EOF_MARK;
	FSLOG_Write(*logExtreme,&exv);

	FSLOG_Unlock(*logExtreme);
	fsmid_assert((*logExtreme)->unitNumber == 3+GetMeasureCount()*2,__FILE__,__LINE__);

	ResetExtremeTable();
	logExtreme ++;
	if(nExtreme < NUMBER_OF_EXV)
		nExtreme++;
	if(logExtreme >= logExtremeTable + NUMBER_OF_EXV)
		logExtreme = logExtremeTable;
#endif
}

static void FSMID_SaveFixptLog(const SYS_TIME64 *tm64)
{
#if (defined(ENABLE_MODULE_FIXPT) || defined(ENABLE_MODULE_ALL))
	if(!logFixpt)
		return;

	logFixpt ++;
	if(nFixpt < NUMBER_OF_FIXPT)
		nFixpt++;
	if(logFixpt >= logFixptTable + NUMBER_OF_FIXPT)
		logFixpt = logFixptTable;

// 	if((*logFixpt)->unitNumber != 96)
// 		fsmid_warning("!FIXPT NUMBER");

	if((*logFixpt)->unitNumber)
		FSLOG_Clear(*logFixpt);
	memcpy(&(*logFixpt)->timeCreate,tm64,sizeof(SYS_TIME64));
	FSMID_FormatLogName(*logFixpt,"fixpt",tm64);
#endif
}

static void FSMID_SaveFrozenLog(const SYS_TIME64 *tm64)
{
#if (defined(ENABLE_MODULE_FROZEN) || defined(ENABLE_MODULE_ALL))

	if(!logFrozen)
		return;

	FSMID_FrozenApp(tm64);//FROZEN

	logFrozen ++;
	if(nFrozen < NUMBER_OF_FRZ)
		nFrozen++;
	if(logFrozen >= logFrozenTable + NUMBER_OF_FRZ)
		logFrozen = logFrozenTable;

	if((*logFrozen)->unitNumber)
		FSLOG_Clear(*logFrozen);
	memcpy(&(*logFrozen)->timeCreate,tm64,sizeof(SYS_TIME64));
	FSMID_FormatLogName(*logFrozen,"frz",tm64);
#endif
}

static void one_sec_delay(SYS_TIME64 *tm64)
{
	SYS_TIME64 _tm64;
	do{
		fsmid_delayMs(300);
		glb_GetDateTime(&_tm64);
	}while(_tm64.sec == tm64->sec);
}

#ifdef WIN32
DWORD WINAPI FSMID_Task(void*)
#else
void FSMID_Task(void *pvParameters)
#endif
{
	extern FSLOG_INTERFACE intrFslog;
	SYS_TIME64 tm64;

	glb_GetDateTime(&tm64);
	handleDpa = db_GetDpaHand();
	handleDca = db_GetDcaHand();
	handleWho = 1;

	FSLOG_Init(&intrFslog);
	FSMID_InitConfig();
	FSMID_CreateLogs(&tm64);
	ResetExtremeTable();

	FSLOG_INFO_MSG("============================== APP START==============================\r\n");
	while(1)
	{
		one_sec_delay(&tm64);
		glb_GetDateTime(&tm64);

#ifndef FILE_NO_UPDATE
	
		if(FIFTEEN_MINUTE_CONDITION(tm64))//15分钟处理一次数据
		{
			//FSLOG_INFO_MSG("[TIME] Tick:20%02d-%02d-%02d %02d:%02d:%02d %03d\r\n",tm64.year,tm64.mon,tm64.day,tm64.hour,tm64.min,tm64.sec,tm64.msec);
			if(DAILY_CONDITION(tm64)) //  0点生成新的文件
			{
				FSMID_SaveExtremeLog(&tm64);
				FSMID_SaveFixptLog(&tm64);
				FSMID_SaveFrozenLog(&tm64);
			}
			FSMID_FixptApp(&tm64);//FIXPT
			FSMID_FrozenApp(&tm64);//FROZEN
		}
		FSMID_SoeApp(&tm64);//SOE and RawSoe
		FSMID_CoApp(&tm64);//CO
		FSMID_LogApp(&tm64);//ULOG and PrintLog
		FSMID_ExtremeApp(&tm64);//EXV
#endif

	}
	#ifdef WIN32
	return 0;
	#endif
}
