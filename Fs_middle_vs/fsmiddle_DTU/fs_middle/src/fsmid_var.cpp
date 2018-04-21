
#ifndef CPU_MK64FN1M0VMD12
#include "dbmsV1.h"
#endif
#include "fs_middle.h"

static int format_info_addr_len(char *buf,unsigned int infoAddr)
{
	char fmt_format[] = "%02X";
	fmt_format[2] = db_GetInfoAddressLength() + '0';
	int len = sprintf(buf,fmt_format,infoAddr);
	return len;
}

static int format_header_soe(char *buf, FSLOG* pLog)
{
	int len;
	if(buf)
		len = sprintf(buf,"%s,%s\r\n%-24s,%4d,%2d\r\n",FSLOG_GetName(pLog),LOG_FILE_VERSION,db_GetTerminalID(),FSLOG_GetUnitCount(pLog),db_GetInfoAddressLength());
	else
		len = strlen(FSLOG_GetName(pLog)) + 1 + strlen(LOG_FILE_VERSION) + 2 + 24 + 1 + 4 + 1 + 2 + 2;
	return len;
}

static int format_header_co(char *buf, FSLOG* pLog)
{
	int len;
	if(buf)
		len = sprintf(buf,"%s,%s\r\n%-24s,%4d,%2d\r\n",FSLOG_GetName(pLog),LOG_FILE_VERSION,db_GetTerminalID(),FSLOG_GetUnitCount(pLog)*2,db_GetInfoAddressLength());
	else
		len = strlen(FSLOG_GetName(pLog)) + 1 + strlen(LOG_FILE_VERSION) + 2 + 24 + 1 + 4 + 1 + 2 + 2;
	return len;
}

static int format_header_exv(char *buf, FSLOG* pLog)
{
	int len;
	if(buf)
	{
		len = sprintf(buf,"%s,%s\r\n%-24s,20%02d%02d%02d,%2d\r\n",FSLOG_GetName(pLog),LOG_FILE_VERSION,db_GetTerminalID(),
		pLog->timeCreate.year,pLog->timeCreate.mon,pLog->timeCreate.day,
		db_GetInfoAddressLength());
	}
	else
		len = 15 + 1 + strlen(LOG_FILE_VERSION) + 2 + 24 + 1 + 8 + 1 + 2 + 2;
	return len;
}

static int format_header_fixpt(char *buf, FSLOG* pLog)
{
	int len;
	if(buf)
	{
		len = sprintf(buf,"%s,%s\r\n%-24s,20%02d%02d%02d,%2d,%2d\r\n",FSLOG_GetName(pLog),LOG_FILE_VERSION,db_GetTerminalID(),
			pLog->timeCreate.year,pLog->timeCreate.mon,pLog->timeCreate.day,
			FSLOG_GetUnitCount(pLog),db_GetInfoAddressLength());
	}
	else
		len = 17 + 1 + strlen(LOG_FILE_VERSION) + 2 + 24 + 1 + 8 + 1 + 2 + 1 + 2 + 2;
	return len;
}

static int format_header_frz(char *buf, FSLOG* pLog)
{
	int len;
	if(buf)
	{
		len = sprintf(buf,"%s,%s\r\n%-24s,20%02d%02d%02d,%2d,%2d\r\n",FSLOG_GetName(pLog),LOG_FILE_VERSION,db_GetTerminalID(),
			pLog->timeCreate.year,pLog->timeCreate.mon,pLog->timeCreate.day,
			FSLOG_GetUnitCount(pLog),db_GetInfoAddressLength());
	}
	else
		len = 15 + 1 + strlen(LOG_FILE_VERSION) + 2 + 24 + 1 + 8 + 1 + 2 + 1 + 2 + 2;
	return len;
}

static int format_header_ulog(char *buf, FSLOG *pLog)
{
	int len;
	if(buf)
		len = sprintf(buf,"%-24s,%4d\r\n",db_GetTerminalID(),FSLOG_GetUnitCount(pLog));
	else
		len = 24 + 1 + 4 + 2;
	return len;
}

static int format_ulog(char *buf, const void* data)
{
	int len;
	const LOG_ULOG *log = (const LOG_ULOG *)data;

	if(buf)
	{
		len = sprintf(buf,"%2d,20%02d-%02d-%02d %02d:%02d:%02d.%03d,%-128s,%d\r\n",
			log->type,
			log->time.year,log->time.mon,log->time.day,
			log->time.hour,log->time.min,log->time.sec,
			log->time.msec,
			log->buf,
			log->sts?1:0);
	}
	else
		len = 2 + 1 + 23 + 1 + 128 + 1 + 1 + 2;
	return len;
}



static int format_soe(char *buf, const void* data)
{
	int len;
	char strInfoAddr[4];
	const LOG_SOE *log = (const LOG_SOE *)data;

	if(buf)
	{
		format_info_addr_len(strInfoAddr,log->information);
		len = sprintf(buf,"%s,%d,20%02d-%02d-%02d %02d:%02d:%02d.%03d\r\n",
			strInfoAddr,log->value%10,
			log->time.year,log->time.mon,log->time.day,
			log->time.hour,log->time.min,log->time.sec,
			log->time.msec);
	}
	else
		len = db_GetInfoAddressLength() + 1 + 23 + 2;
	//fsmid_assert(len <= maxlen,__FILE__,__LINE__);
	return len;
}

static int format_co(char *buf, const void* data)
{
	const char *cstrTrdOperate[] = {"分","合"};
	int len;
	char strInfoAddr[4];
	const LOG_CO *log = (const LOG_CO *)data;

	if(buf)
	{
		format_info_addr_len(strInfoAddr,log->information);
		len = sprintf(buf,"%s,选择,%s,20%02d-%02d-%02d %02d:%02d:%02d.%03d\r\n%s,执行,%s,20%02d-%02d-%02d %02d:%02d:%02d.%03d\r\n",
			strInfoAddr,cstrTrdOperate[log->value?1:0],
			log->time.year,log->time.mon,log->time.day,
			log->time.hour,log->time.min,log->time.sec,
			log->time.msec,
			strInfoAddr,cstrTrdOperate[log->value?1:0],
			log->time.year,log->time.mon,log->time.day,
			log->time.hour,log->time.min,log->time.sec,
			log->time.msec);
	}
	else
		len = (db_GetInfoAddressLength() + 1 + 4 + 2 + 23 + 2)*2;
	//fsmid_assert(len <= maxlen,__FILE__,__LINE__);
	return len;
}

static int format_extreme(char *buf, const void* data)
{
	int len;
	char strInfoAddr[4];
	FSMID_POINT * const measure = GetMeasureTable();
	const LOG_EXTREME *log = (const LOG_EXTREME *)data;

	if(log->type == 0xFFFF)//maximum
	{
		if(buf)
			len = sprintf(buf,"%3d",GetMeasureCount());
		else
			len = 3;
	}
	else if(log->type == 0xFFFE)//minimum
	{
		if(buf)
			len = sprintf(buf,"\r\n%3d",GetMeasureCount());
		else
			len = 2 + 3;
	}
	else if(log->type == 0xFFFD)//eof
	{
		if(buf)
			len = sprintf(buf,"\r\n");
		else
			len = 2;
	}
	else
	{
		if(buf)
		{
			format_info_addr_len(strInfoAddr,measure[log->pointIndex].information);
			len = sprintf(buf,",%s,%7.3f,20%02d-%02d-%02d %02d:%02d:%02d.%03d",
				strInfoAddr,log->value,
				log->time.year,log->time.mon,log->time.day,
				log->time.hour,log->time.min,log->time.sec,
				log->time.msec);
		}
		else
			len = 1 + db_GetInfoAddressLength() + 1 + 7 + 1 +23;
	}
	//fsmid_assert(len <= maxlen,__FILE__,__LINE__);
	return len;
}

static int format_fix(char *buf, const void* data)
{
	unsigned int i,len;
	char strInfoAddr[4];
	FSMID_POINT * const measure = GetMeasureTable();
	const LOG_FIXPT *log = (const LOG_FIXPT *)data;
	
	if(buf)
	{
		len = sprintf(buf,"%2d,20%02d-%02d-%02d %02d:%02d:%02d.%03d",
			GetMeasureCount(),
			log->time.year,log->time.mon,log->time.day,
			log->time.hour,log->time.min,log->time.sec,
			log->time.msec);

		for( i = 0; i < GetMeasureCount(); i++ )
		{
			format_info_addr_len(strInfoAddr,measure[i].information);
			len += sprintf(buf + len,",%s,%7.3f",strInfoAddr, log->value[i] );
		}
		len += sprintf(buf + len,"\r\n");
	}
	else
		len = 2 + 1 + 23 + (1 + db_GetInfoAddressLength() + 1 + 7)*GetMeasureCount() + 2;
	//fsmid_assert(len <= maxlen,__FILE__,__LINE__);
	return len;
}

static int format_frozen(char *buf, const void* data)
{
	unsigned int i,len;
	char strInfoAddr[4];
	FSMID_POINT * const frozen = GetFrozenTable();
	const LOG_FIXPT *log = (const LOG_FIXPT *)data;

	if(buf)
	{
		len = sprintf(buf,"%2d,20%02d-%02d-%02d %02d:%02d:%02d.%03d",
			GetFrozenCount(),
			log->time.year,log->time.mon,log->time.day,
			log->time.hour,log->time.min,log->time.sec,
			log->time.msec);

		for( i = 0; i < GetFrozenCount(); i++ )
		{
			format_info_addr_len(strInfoAddr,frozen[i].information);
			len += sprintf(buf + len,",%s,%7.3f",strInfoAddr, log->value[i] );
		}
		len += sprintf(buf + len,"\r\n");
	}
	else
		len = 2 + 1 + 23 + (1 + db_GetInfoAddressLength() + 1 + 7)*GetFrozenCount() + 2;
	//fsmid_assert(len <= maxlen,__FILE__,__LINE__);
	return len;
}

static const SYS_TIME64 *get_log_time(const void* data)
{
	return ((const SYS_TIME64 *)data);
}

const FSLOG_FUNCTION funcLogUlog = {
// 	write_flash,
// 	read_flash,
// 	erase_flash,
	format_header_ulog,
	format_ulog,
	get_log_time,
};

const FSLOG_FUNCTION funcLogSoe = {
// 	write_flash,
// 	read_flash,
// 	erase_flash,
	format_header_soe,
	format_soe,
	get_log_time,
};

const FSLOG_FUNCTION funcLogCo = {
// 	write_flash,
// 	read_flash,
	// 	erase_flash,
	format_header_co,
	format_co,
	get_log_time,
};

const FSLOG_FUNCTION funcLogExtreme = {
// 	write_flash,
// 	read_flash,
	// 	erase_flash,
	format_header_exv,
	format_extreme,
	get_log_time,
};

const FSLOG_FUNCTION funcLogFixpt = {
// 	write_flash,
// 	read_flash,
	// 	erase_flash,
	format_header_fixpt,
	format_fix,
	get_log_time,
};

const FSLOG_FUNCTION funcLogFrozen = {
// 	write_flash,
// 	read_flash,
	// 	erase_flash,
	format_header_frz,
	format_frozen,
	get_log_time,
};

unsigned int FSLOG_CalcBlockNumber(unsigned int unitSize, unsigned int blockSize, unsigned int unitCount, bool bOtp)
{
	unsigned int res;

	res = blockSize - 64;
	res = res/unitSize;
	if(unitCount % res)
		res = unitCount/res + 1;
	else
		res = unitCount/res;
	if(!bOtp)
		res ++;

	return res;
}

const FSLOG_INFORMATION infoFwUpdate = {
	FLASH_BLOCK_SIZE * START_BLOCK_FIRMWARE,
	NUM_BLOCK_FIRMWARE,
	FLASH_BLOCK_SIZE,
	1,
	NUM_BLOCK_FIRMWARE * FLASH_BLOCK_SIZE,
};

const FSLOG_INFORMATION infoRawSoe = {
	FLASH_BLOCK_SIZE * START_BLOCK_RAWSOE,
	NUM_BLOCK_RAWSOE,
	FLASH_BLOCK_SIZE,
	sizeof(LOG_RAWSOE),
	NUM_POINT_RAWSOE,
};

const FSLOG_INFORMATION infoRawTrd = {
	FLASH_BLOCK_SIZE * START_BLOCK_RAWTRD,
	NUM_BLOCK_TRD,
	FLASH_BLOCK_SIZE,
	sizeof(LOG_RAWTRD),
	NUM_POINT_TRD,
};

const FSLOG_INFORMATION infoPrintLog = {
	FLASH_BLOCK_SIZE * START_BLOCK_PRINTLOG,
	NUM_BLOCK_PRTLOG,
	FLASH_BLOCK_SIZE,
	sizeof(PRTLOGEVENT),
	NUM_POINT_PRTLOG,
};

const FSLOG_INFORMATION infoLogUlog = {
	FLASH_BLOCK_SIZE * START_BLOCK_ULOG,
	NUM_BLOCK_ULOG,
	FLASH_BLOCK_SIZE,
	sizeof(LOG_ULOG),
	NUM_POINT_ULOG,
};

const FSLOG_INFORMATION infoLogSoe = {
	FLASH_BLOCK_SIZE * START_BLOCK_LOG_SOE,
	NUM_BLOCK_LOG_SOE,
	FLASH_BLOCK_SIZE,
	sizeof(LOG_SOE),
	NUM_POINT_LOG_SOE,
};

const FSLOG_INFORMATION infoLogCo= {
	FLASH_BLOCK_SIZE * START_BLOCK_LOG_CO,
	NUM_BLOCK_LOG_CO,
	FLASH_BLOCK_SIZE,
	sizeof(LOG_CO),
	NUM_POINT_LOG_CO,
};


const FSLOG_INFORMATION infoLogExtreme = {
	0,//FLASH_BLOCK_SIZE * START_BLOCK_LOG_EXTREME,
	0,
	FLASH_BLOCK_SIZE,
	sizeof(LOG_EXTREME),
	0,
};

//dynamic!!!
const FSLOG_INFORMATION infoLogFixpt = {
	0,//FLASH_BLOCK_SIZE * START_BLOCK_LOG_FIX,
	0,
	FLASH_BLOCK_SIZE,
	sizeof(LOG_FIXPT),
	FIXPT_POINT_PER_LOG,
};

//dynamic!!!
const FSLOG_INFORMATION infoLogFrozen = {
	0,//FLASH_BLOCK_SIZE * START_BLOCK_LOG_FROZEN,
	0,
	FLASH_BLOCK_SIZE,
	sizeof(LOG_FROZRN),
	FROZEN_POINT_PER_LOG,
};

