#ifndef __SYSTIMER_H_
#define __SYSTIMER_H_

//#include "stdint.h"

typedef struct
{
	unsigned char year;
	unsigned char mon;
	unsigned char day;
	unsigned char hour;
	unsigned char min;
	unsigned char sec;
	unsigned short msec;
}SYS_TIME64;

/****ϵͳ TICK �� RTC************************************/
extern unsigned int glb_sysTick;//FREERUNNING TICK, ����ֱ���ñ���������ͨ��������ȡ�������������0��ʼ��
extern unsigned int glb_sysSecond;//RTC.TSRֵ
extern unsigned short glb_RtcMsec;

//bool glb_sysTick_Init(void);//��RTOS XTick�� vApplicationTickHook()��ɣ���user.c��
bool glb_sysRtc_Init(void);
void glb_GetDateTime(SYS_TIME64 *datetime);
void glb_SetDateTime(SYS_TIME64 *datetime);

#endif