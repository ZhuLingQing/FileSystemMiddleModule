#ifndef _FSMID_DEF_H_
#define _FSMID_DEF_H_

#include "sysTimerV1.h"


#if (defined(WIN32) && !defined(__cplusplus))
extern "C" {
#endif

#pragma pack(push,1)
/**************************************************************************************************/

#ifndef NULL
#define NULL	0
#endif

#ifndef min
#define min(a,b)		(((a)<(b))?(a):(b))
#endif

#ifndef xor
#define xor(a,b)		((!(a)&&(b))||((a)&&!(b)))
#endif


//#define __DEF_CP56TIME2A
#ifndef __DEF_CP56TIME2A
typedef struct __cp56time2a {
	unsigned short milliSecond;

	unsigned char minute:6;
	unsigned char res1 :1;
	unsigned char invalid :1;

	unsigned char hour :5;
	unsigned char res2 :2;
	unsigned char summerTime :1;

	unsigned char monthDay :5;
	unsigned char weekDay :3;

	unsigned char month :4;
	unsigned char res3 :4;

	unsigned char year :7;
	unsigned char res4 :1;
}CP56TIME2A;
#endif

enum __fsmid_result
{
	FSMIDR_OK = 0,
	FSMIDR_GENERAL,
	FSMIDR_LEAK_MEMORY,
	FSMIDR_BAD_ARGUMENT,
	FSMIDR_LENGTH_LARGE,
	FSMIDR_ACCESS,
	FSMIDR_CONFLICT,
	FSMIDR_NOT_EXIST,
	FSMIDR_POINT_NOT_NULL,
};

/*-----------------------------------------------------------------------------------------------*/
typedef struct __fslog_interface
{
	int (*write)(unsigned int address, const void* data, unsigned int length);
	int (*read)(unsigned int address, void* data, unsigned int length);
	int (*erase)(unsigned int address, unsigned int length);
}FSLOG_INTERFACE;

#pragma pack(pop)

#if (defined(WIN32) && !defined(__cplusplus))
};
#endif

#endif