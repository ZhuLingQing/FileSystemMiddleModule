#ifndef _FSMID_POINT_H_
#define _FSMID_POINT_H_


#include "sysTimerV1.h"
#include "dbmsV1.h"

#if (defined(WIN32) && !defined(__cplusplus))
extern "C" {
#endif

#pragma pack(push,1)

/**************************************************************************************************/
typedef SOEEVENT LOG_RAWSOE;

typedef struct __log_raw_trd{
	SYS_TIME64 time;
	TRDEVENT   trd;
}LOG_RAWTRD;

typedef ULOGEVENT LOG_ULOG;

typedef struct __log_soe_co{
	SYS_TIME64 time;
	unsigned int information;
	unsigned char value;
    unsigned char reserved[3];
}LOG_SOE,LOG_CO;

#define EXTREME_MAX_MARK		0xFFFF
#define EXTREME_MIN_MARK		0xFFFE
#define EXTREME_EOF_MARK		0xFFFD

typedef struct __log_extreme{
	SYS_TIME64 time;
	unsigned short pointIndex;
	unsigned short type;//0:minimum point,1:maximum point,0xFFFF:maximum mark,0xFFFE:minimum mark,0xFFFD:eof
	float value;
}LOG_EXTREME;

typedef struct __log_fix_frozen{
	SYS_TIME64 time;
	unsigned int numUnit;
	float value[0];
}LOG_FIXPT,LOG_FROZRN;

typedef struct __log_cfg{
// 	SYS_TIME64 timeStart;
// 	SYS_TIME64 timeTrigger;
// 	unsigned int channelOffset;
// 	float dcOffset;
// 	float acGain;
// 	float frequency;
	char strBuf[80];
}LOG_CFG;

typedef struct __log_dat{
	unsigned int pointIndex;
	unsigned int pointTime;
	unsigned short channelValue[4][8];
}LOG_DAT;

/*-----------------------------------------------------------------------------------------------*/
typedef struct __struct_fsmid_point{
	unsigned int information;
	unsigned short point;
	unsigned short reserved;
}FSMID_POINT;

#pragma pack(pop)

int FSMID_InitConfig();

FSMID_POINT * const GetMeasureTable();
unsigned int GetMeasureCount();
LOG_EXTREME * const GetMaximumTable();
LOG_EXTREME * const GetMinimumTable();

void ResetExtremeTable();
void UpdateExtremeValue(const SYS_TIME64 *tm64, unsigned int index, float fValue);

FSMID_POINT * const GetFrozenTable();
unsigned int GetFrozenCount();

#if (defined(WIN32) && !defined(__cplusplus))
};
#endif

#endif
