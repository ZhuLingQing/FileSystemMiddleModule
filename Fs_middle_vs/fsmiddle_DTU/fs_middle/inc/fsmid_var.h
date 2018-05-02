#ifndef _FSMID_VARIABLE_H_
#define _FSMID_VARIABLE_H_

#include "fsmid_log.h"

#if (defined(WIN32) && !defined(__cplusplus))
extern "C" {
#endif

	extern FSLOG_INTERFACE intrFslog;

	extern const FSLOG_FUNCTION funcFwUpdate;

	extern const FSLOG_FUNCTION funcLogUlog;

	extern const FSLOG_FUNCTION funcLogSoe;

	extern const FSLOG_FUNCTION funcLogCo;

	extern const FSLOG_FUNCTION funcLogCfg;
	extern const FSLOG_FUNCTION funcLogDat;

	extern const FSLOG_FUNCTION funcLogExtreme;//for logMaximum and logMinimum

	extern const FSLOG_FUNCTION funcLogFixpt;

	extern const FSLOG_FUNCTION funcLogFrozen;
	

	unsigned int FSLOG_CalcBlockNumber(unsigned int unitSize, unsigned int blockSize, unsigned int unitCount,bool bOtp);


	extern const FSLOG_INFORMATION infoFwUpdate;
	extern const FSLOG_INFORMATION infoRawSoe;
	extern const FSLOG_INFORMATION infoRawTrd;
	extern const FSLOG_INFORMATION infoPrintLog;
	extern const FSLOG_INFORMATION infoLogUlog;
	extern const FSLOG_INFORMATION infoLogSoe;
	extern const FSLOG_INFORMATION infoLogCo;
	extern const FSLOG_INFORMATION infoLogCfg[NUMBER_OF_CFG];
	extern const FSLOG_INFORMATION infoLogDat[NUMBER_OF_DAT];
	extern const FSLOG_INFORMATION infoLogExtreme;
	extern const FSLOG_INFORMATION infoLogFixpt;
	extern const FSLOG_INFORMATION infoLogFrozen;

#if (defined(WIN32) && !defined(__cplusplus))
};
#endif

#endif
