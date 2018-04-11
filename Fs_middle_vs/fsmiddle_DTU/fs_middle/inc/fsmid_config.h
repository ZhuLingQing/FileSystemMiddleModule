#ifndef _FSMID_CONFIG_H_
#define _FSMID_CONFIG_H_

#define FSMID_MODULE_VERSION		0.90

#define LOG_FILE_VERSION		"1.0"

#ifdef FAST_MODE

#define NUMBER_OF_EXV			5
#define NUMBER_OF_FIXPT			5
#define NUMBER_OF_FRZ			5

#define FIXPT_POINT_PER_LOG		24
#define FROZEN_POINT_PER_LOG	25

#define FIFTEEN_MINUTE_CONDITION(tm64)		(!(tm64.sec%5))
#define DAILY_CONDITION(tm64)				(!((tm64.hour*60+tm64.min)%2) && !tm64.sec)

#define FORMAT_NAME(pLog,uc,lc,tm64)		sprintf((pLog)->name,"HISTORY\\%s\\%s%02d%02d00.msg",uc,lc,(tm64)->hour,(tm64)->min&0xFE)

#define SYSTM64_SAMEDAY(tm1,tm2)			((tm1->day == tm2->day) && (tm1->hour == tm2->hour) && ((tm1->min&0xFE) == (tm2->min&0xFE)))

#else

#define NUMBER_OF_EXV			30
#define NUMBER_OF_FIXPT			31
#define NUMBER_OF_FRZ			31

#define FIXPT_POINT_PER_LOG		96
#define FROZEN_POINT_PER_LOG	97

#define FIFTEEN_MINUTE_CONDITION(tm64)		(!(tm64.min%15) && !tm64.sec)
#define DAILY_CONDITION(tm64)				(!tm64.hour && !tm64.min)

#define FORMAT_NAME(pLog,uc,lc,tm64)		sprintf((pLog)->name,"HISTORY\\%s\\%s20%02d%02d%02d.msg",uc,lc,(tm64)->year,(tm64)->mon,(tm64)->day)

#define SYSTM64_SAMEDAY(tm1,tm2)			((tm1->year == tm2->year) && (tm1->mon == tm2->mon) && (tm1->day == tm2->day))

#endif

#define FLASH_BLOCK_SIZE			4096
#define FLASH_MEMORY_SIZE			(16<<20)

#define FSMID_CONFIG_ADDRESS		0
#define FSMID_DATA_ADDRESS			(64<<10)

#define MAXIMUM_MEASURE_POINT		(16*4)
#define MAXIMUM_POWER_POINT			(4*4)

#define START_BLOCK_RAWSOE			16
#define START_BLOCK_RAWTRD			34
#define START_BLOCK_PRINTLOG		36

#define START_BLOCK_ULOG			64
#define START_BLOCK_LOG_SOE			72
#define START_BLOCK_LOG_CO			80
#define DYNAMIC_START_BLOCK			88

#define ENABLE_MODULE_ALL
// #define ENABLE_MODULE_LOG
// #define ENABLE_MODULE_SOE
// #define ENABLE_MODULE_CO
// #define ENABLE_MODULE_EXV
// #define ENABLE_MODULE_FIXPT
// #define ENABLE_MODULE_FROZEN

#endif

