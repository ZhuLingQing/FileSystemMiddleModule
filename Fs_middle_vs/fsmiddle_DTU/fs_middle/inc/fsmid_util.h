#ifndef _FSMID_UTIL_H_
#define _FSMID_UTIL_H_

#include "fsmid_def.h"

#if (defined(WIN32) && !defined(__cplusplus))
extern "C" {
#endif

extern unsigned int bitmap2number(unsigned char* bitmap, unsigned int length);
extern void number2bitmap(unsigned int number, unsigned char* bitmap, unsigned int length);

bool systimeSameDay(const SYS_TIME64 *tm1, const SYS_TIME64 *tm2);
//signed int systimeCmp(const SYS_TIME64 *tm1, const SYS_TIME64 *tm2);

#define systimeCmp(tm1,tm2)		memcmp((tm1),(tm2),sizeof(SYS_TIME64)-2)

void systimeToCp56(const SYS_TIME64 *tm64,CP56TIME2A * cp56);
void cp56ToSystime(const CP56TIME2A *cp56, SYS_TIME64 *tm64);

unsigned char byteChecksum(unsigned char seed, unsigned char *buf, unsigned int length);

#if (defined(WIN32) && !defined(__cplusplus))
};
#endif
#endif
