#ifndef _FSMID_CONFIG_H_
#define _FSMID_CONFIG_H_

#define FSMID_MODULE_VERSION		0.90

#define LOG_FILE_VERSION		"v1.0"
#define LOG_FILE_HEADER         "文件头："

/**************************************************************************************************/

#ifdef FAST_MODE
    
    #define NUMBER_OF_EXV                   5
    #define NUMBER_OF_FIXPT                 5
    #define NUMBER_OF_FRZ                   5
    #define NUMBER_OF_CFG                   5                                           // 最多5个CFG文件
    #define NUMBER_OF_DAT                   5                                           // 最多5个DAT文件
    
    #define FIXPT_POINT_PER_LOG             24
    #define FROZEN_POINT_PER_LOG            25
    #define CFG_POINT_PER_LOG               1                                           // CFG文件只需要一个记录实际即可
    #define DAT_POINT_PER_LOG               (96*8)                                      // DAT文件记录8个周波,每个周波96个点
    
    #define FIFTEEN_MINUTE_CONDITION(tm64)  (!(tm64.sec%5))
#define DAILY_CONDITION(tm64)				(!((tm64.hour*60+tm64.min)%2) && !tm64.sec)

#define FORMAT_LOG_NAME(pLog,uc,lc,tm64)			sprintf((pLog)->name,"HISTORY/%s/%s__%02d%02d00.msg",uc,lc,(tm64)->hour,(tm64)->min&0xFE)
#define FORMAT_WAVE_NAME(pLog,ext,duty,index,tm64)	sprintf((pLog)->name,"COMTRADE/BAY%02d_%04d_20%02d%02d%02d__%04d%02d%02d_%03d.%s",duty,index,(tm64)->year,(tm64)->mon,(tm64)->day,(tm64)->hour,(tm64)->min,(tm64)->sec,(tm64)->msec,ext)

#define SYSTM64_SAMEDAY(tm1,tm2)			((tm1->day == tm2->day) && (tm1->hour == tm2->hour) && ((tm1->min&0xFE) == (tm2->min&0xFE)))

#else

    #define NUMBER_OF_EXV                   30
    #define NUMBER_OF_FIXPT                 31
    #define NUMBER_OF_FRZ                   31
    #define NUMBER_OF_CFG                   5                                           // 最多5个CFG文件
    #define NUMBER_OF_DAT                   5                                           // 最多5个DAT文件
    
    #define FIXPT_POINT_PER_LOG             96
    #define FROZEN_POINT_PER_LOG            97
    #define CFG_POINT_PER_LOG               1                                           // CFG文件只需要一个记录实际即可
    #define DAT_POINT_PER_LOG               (96*8)                                      // DAT文件记录8个周波,每个周波96个点
    
#define FIFTEEN_MINUTE_CONDITION(tm64)		(!(tm64.min%15) && !tm64.sec)
#define DAILY_CONDITION(tm64)				(!tm64.hour && !tm64.min)

#define FORMAT_LOG_NAME(pLog,uc,lc,tm64)		sprintf((pLog)->name,"HISTORY/%s/%s20%02d%02d%02d.msg",uc,lc,(tm64)->year,(tm64)->mon,(tm64)->day)
#define FORMAT_WAVE_NAME(pLog,ext,duty,index,tm64)	sprintf((pLog)->name,"COMTRADE/BAY%02d_%04d_20%02d%02d%02d__%04d%02d%02d_%03d.%s",duty,index,(tm64)->year,(tm64)->mon,(tm64)->day,(tm64)->hour,(tm64)->min,(tm64)->sec,(tm64)->msec,ext)

#define SYSTM64_SAMEDAY(tm1,tm2)			((tm1->year == tm2->year) && (tm1->mon == tm2->mon) && (tm1->day == tm2->day))

#endif
/*-----------------------------------------------------------------------------------------------*/

#define FLASH_BLOCK_SIZE			4096
#define FLASH_MEMORY_SIZE			(8<<20)//(16<<20)

#define START_BLOCK_FIRMWARE		0
#define NUM_BLOCK_FIRMWARE			((512*1024)/FLASH_BLOCK_SIZE)

#define START_BLOCK_CONFIG			(NUM_BLOCK_FIRMWARE)
#define NUM_BLOCK_CONFIG			((64<<10)/FLASH_BLOCK_SIZE)

#define MAXIMUM_MEASURE_POINT		(16*4)
#define MAXIMUM_POWER_POINT			(4*4)

#define START_BLOCK_RAWSOE			(START_BLOCK_CONFIG + NUM_BLOCK_CONFIG)
#define NUM_BLOCK_RAWSOE			18
#define NUM_POINT_RAWSOE			1024

#define START_BLOCK_RAWTRD			(START_BLOCK_RAWSOE + NUM_BLOCK_RAWSOE)
#define NUM_BLOCK_TRD				2
#define NUM_POINT_TRD				336

#define START_BLOCK_PRINTLOG		(START_BLOCK_RAWTRD + NUM_BLOCK_TRD)
#define NUM_BLOCK_PRTLOG			22
#define NUM_POINT_PRTLOG			1024

#define START_BLOCK_ULOG			(NUM_BLOCK_FIRMWARE + 64)
#define NUM_BLOCK_ULOG				20
#define NUM_POINT_ULOG				1024

#define START_BLOCK_LOG_SOE			(START_BLOCK_ULOG + NUM_BLOCK_ULOG)
#define NUM_BLOCK_LOG_SOE			6
#define NUM_POINT_LOG_SOE			1024

#define START_BLOCK_LOG_CO			(START_BLOCK_LOG_SOE + NUM_BLOCK_LOG_SOE)
#define NUM_BLOCK_LOG_CO			2
#define NUM_POINT_LOG_CO			30

#define NUM_LOG_LOG_CFG				5
#define START_BLOCK_LOG_CFG			(START_BLOCK_LOG_CO + NUM_BLOCK_LOG_CO)
#define NUM_BLOCK_LOG_CFG			1
#define NUM_POINT_LOG_CFG			1

#define NUM_LOG_LOG_DAT				5
#define START_BLOCK_LOG_DAT			(START_BLOCK_LOG_CFG + (NUM_LOG_LOG_CFG*NUM_BLOCK_LOG_CFG))
#define NUM_BLOCK_LOG_DAT			5
#define NUM_POINT_LOG_DAT			(96*8)

#define FIX_END_BLOCK				(START_BLOCK_LOG_DAT + (NUM_LOG_LOG_DAT*NUM_BLOCK_LOG_DAT))

#define DYNAMIC_START_BLOCK			(NUM_BLOCK_FIRMWARE + 128)

#if (DYNAMIC_START_BLOCK < FIX_END_BLOCK)
#error "INVALID DYNAMIC_START_BLOCK!"
#endif

#define ENABLE_MODULE_ALL
// #define ENABLE_MODULE_LOG
// #define ENABLE_MODULE_SOE
// #define ENABLE_MODULE_CO
// #define ENABLE_MODULE_CFG_DAT
// #define ENABLE_MODULE_EXV
// #define ENABLE_MODULE_FIXPT
// #define ENABLE_MODULE_FROZEN
/**************************************************************************************************/

#endif

