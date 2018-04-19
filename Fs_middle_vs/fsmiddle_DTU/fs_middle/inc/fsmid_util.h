#ifndef _FSMID_UTIL_H_
#define _FSMID_UTIL_H_

#include "fsmid_def.h"

#ifndef __cplusplus
extern "C" {
#endif

extern unsigned int bitmap2number(unsigned char* bitmap, unsigned int length);
extern void number2bitmap(unsigned int number, unsigned char* bitmap, unsigned int length);

bool systimeSameDay(const SYS_TIME64 *tm1, const SYS_TIME64 *tm2);
bool unixSameDay(unsigned int tm1, unsigned int tm2);
extern unsigned int time_sys2unix(const SYS_TIME64* systime);
extern void time_unix2sys(unsigned int unix, SYS_TIME64 *systime);

unsigned char byteChecksum(unsigned char seed, unsigned char *buf, unsigned int length);

#ifndef __cplusplus
};
#endif

#endif
