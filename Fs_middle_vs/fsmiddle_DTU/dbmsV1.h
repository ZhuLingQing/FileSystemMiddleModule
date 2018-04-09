
//////////////////////////////////////////////
#ifndef __DBME__
#define __DBME__

#ifndef VS_SIMULATE
#include "fsl_common.h"
#include "board.h"
#endif

#include "stdio.h"
#include "stdlib.h"
#include "commonDefEx.h"
#include "sysTimerV1.h"


////////////////////////////////////////////////


//database types
enum 
{
	DBDI = 0,
	DBAI = 1,
	DBACC = 2,
	DBDO = 3,
	DBAO = 4,
	DBJAI = 5,
};

/* flag , Point quality */
enum{
	IQ_IV = 0X80,	  // invalid
	IQ_SB = 0X20,	//Forced
};

/* queue buffer size */
#define	MAXDPAH		32
#define	MAXDCAH		32
#define MAXMSGH		32 //��Ҫ��ȡmessage��Ӧ����������һ��ID 

#define MAXSOE		100
#define MAXTRD		5
#define MAXAGC		1
#define MAXMSG			0	//��Ϣ����
#define MAXINITLOG			50	//������־����
#define MAXULOG		5	//ң������
#define MAXPRTLOG		100	//��ӡ����

#define MAXMONICOMM		4096//ͨѶ���, ����ŵ�ͨѶ���ֽ���

//////////////////////////////////////////////
// common used data structure

// ���ݿ�����С
typedef struct 
{
	int16 di;		//ң�ŵ���
	int16 ai;		//ң�����
	int16 pa;		//�����ۼ�������
	int16 doo;		//ң�ص�����ָ������
	int16 ao;		//������
	int16 jai;		//˲ʱң�����
	int16 rev1;		
	int16 rev2;
	int16 rev3;
	int16 rev4;

}struDbSize;

//DCA HEAD
typedef struct
{
	INT16 distart;
	UINT16 dinum;
	INT16 aistart;
	UINT16 ainum;
	INT16 pastart;
	UINT16 panum;
	INT16 dostart;
	UINT16 donum;
	INT16 aostart;
	UINT16 aonum;
	INT16 jaistart;
	UINT16 jainum;
	INT16 rev0start;
	UINT16 rev0num;
	INT16 rev1Start;
	UINT16 rev1Num;
	INT16 rev2Start;
	UINT16 rev2Num;
	INT16 rev3Start;
	UINT16 rev3Num;

}struDcaHead;

//DEV SYS����
typedef struct 
{
	struDbSize dbsize;
	char rev[32];

}struDevSysCfg;

/*************************************************************************/
/*************************************************************************/



extern struDbSize db_TotSize;


extern uint8 db_GetDpaHand(void);
extern uint8 db_GetDcaHand(void);
extern uint8 db_GetMsgHand(void);





/***************************************/
//���ݿ�������ݵ�structure, ��д����
/***************************************/


typedef struct {
	uint8	val;// bit0:val bit1:sb_val bit2~7:IQ
} DI_PNT;
extern void db_PutDi(int16 pnt, uint8 val);
extern void db_ForceDi(int16 pnt, uint8 val);
extern uint8 db_GetDi(int16 pnt);//!���ذ���IQ��val
extern void db_ClrDiFlag(int16 pnt, uint8 flag);
extern void db_SetDiFlag(int16 pnt, uint8 flag);
extern uint8 db_GetDiFlag(int16 pnt);
/***************************************/

#define COMMON_ID	0xFF  //db_GetAi(uint8 dpaH, int16 pnt)��dpaHΪCOMMON_IDʱ�����ظõ���ֵ. ��������Ӧ�ö�AI�Ķ�ȡ
typedef struct {
	float val;
	//float realval;
	//float deadband;
	uint32 chg;
	uint8 flag;
} AI_PNT;
extern void db_PutAi(int16 pnt, float val);
//void db_PutAiDeadband(int16 pnt, float deadband);
extern void db_ForceAi(int16 pnt, float val);
extern bool db_GetAiChg(uint8 dpaH, int16 pnt);
extern void db_ResetAiChg(uint8 dpaH);
extern float db_GetAi(uint8 dpaH, int16 pnt);
extern void db_ClrAiFlag(int16 pnt, uint8 flag);
extern void db_SetAiFlag(int16 pnt, uint8 flag);
extern uint8 db_GetAiFlag(int16 pnt);
/***************************************/
//���ǵ�DCA���ܲ������ڲ���ŵ��ܵı�����ÿ�δ����ݿ��ȡ���ۼ���������д�����ݿ⣬
//��ֵ��force����ֵ�Ͳ����ٶ��ˣ�����runningval���ʵ��DCA PUT������ֵ��
//DCA��Ҫ����ʱ����db_GetRunningPa()

typedef struct {			
	float val;		//���Ա�FORCE
	float runningval;	//��ʵ��DCA PUT������ֵ����unforce��copy��val
	uint8 flag;
} PA_PNT;
extern void db_PutPa(int16 pnt, float val);
extern void db_ForcePa(int16 pnt, float val);//hgy
extern float db_GetPa(int16 pnt);
extern float db_GetRunningPa(int16 pnt);
extern void db_ClrPaFlag(int16 pnt, uint8 flag);
extern void db_SetPaFlag(int16 pnt, uint8 flag);
extern uint8 db_GetPaFlag(int16 pnt);

/***************************************/

typedef struct {
	float	val;
} AO_PNT;
extern void db_PutAo(int16, float);
extern float db_GetAo(int16 pnt);
/***************************************/

typedef struct {
	float	val;
} JAI_PNT;
extern void db_PutJAi(int16 pnt, float);
extern float db_GetJAi(int16 pnt);
/***************************************/




/***************************************/

#define DB_SOEVALNUM  8
#define DB_SOEFVALNUM  8

typedef struct {
	SYS_TIME64	time;//ʱ�䣬������sysTimer.h��
	int16	pnt;//ϵͳ���
	uint8	val;//��ֵ 1�� 0��
	UINT8 ainum;//������ң�����
	INT16 aipnt[DB_SOEFVALNUM];//����ң���ĵ��
	float aival[DB_SOEFVALNUM];//����ң����ֵ
} SOEEVENT;

typedef struct {
	int16		cnt[MAXDPAH];
	int16		rpnt[MAXDPAH];
	int16		wpnt;
	SOEEVENT	soeevent[MAXSOE];
} SOE_QUEUE;

extern void db_PutSoe(int16 pnt, uint8 val, SYS_TIME64 *time);
extern void db_PutVirSoe(int16 pnt, uint8 val);
extern void db_ForceVirSoe(int pnt, uint8 val);
extern SOEEVENT * db_GetSoe(uint8 dpaH);
extern int16	db_GetSoeCount(uint8 dpaH);
extern void db_ResetSoe(uint8 dpaH);
extern void db_PutEvSoe(SOEEVENT * evsoe);//���뱣���¼�
/***************************************/


typedef struct{
	int16 pnt;//ϵͳ���
	uint8 val;//ֵ 1�� 0��
} TRDEVENT;
typedef struct {
	int16		cnt[MAXDCAH];
	int16		rpnt[MAXDCAH];
	int16		wpnt;
	TRDEVENT	trdevent[MAXTRD];
} TRD_QUEUE;
extern void db_PutTrd(int16 pnt, uint8 val);
extern TRDEVENT * db_GetTrd(uint8 dcaH);
extern int16 db_GetTrdCount(uint8 dcaH);
extern void db_ResetTrd(uint8 dcaH);
/***************************************/

typedef struct{
	int16  	pnt;
	float	val;
} AGCEVENT;
typedef struct{
	int16		cnt[MAXDCAH];
	int16		rpnt[MAXDCAH];
	int16		wpnt;
	AGCEVENT agcevent[MAXAGC];
} AGC_QUEUE;
extern void db_PutAgc(int16 pnt, float val);
extern AGCEVENT * db_GetAgc(uint8 dcaH);
extern int16 db_GetAgcCount(uint8 dcaH);
extern void db_ResetAgc(uint8 dcaH);
/***************************************/


//��Ϣ���У�Ӧ�ü䴫����Ϣ
typedef struct{
	uint32 msgid;//��Ϣ��ţ���ʾʲô��Ϣ
	uint32 data;//������Ϣ
	uint32 *retsignal;//����Ϣ���շ������Ӧ
}MSGEVENT;
typedef struct{
	int16 cnt[MAXMSGH];
	int16 rpnt[MAXMSGH];
	int16 wpnt;
	MSGEVENT msgevent[MAXMSG];
}  MSG_QUEUE;
extern void db_PutMsg(uint32 msgid, uint32 data, uint32* retsignal);
extern MSGEVENT * db_GetMsg(uint8 msgH);
extern int16 db_GetMsgCount(uint8 msgH);
extern void db_ResetMsg(uint8 msgH);

/***************************************/



//Ӧ����Ϣ����������ЩӦ�ã���汾
#define LOGINITSTRLEN 64
typedef struct{
	char buf[64];
}INITLOGEVENT;
typedef struct{		
	int16 cnt[2];		//�̶�Ϊ��cnt[0]dpaZzmap,cnt[1]FileMid
	int16 rpnt[2];
	int16 wpnt;
	INITLOGEVENT logevent[MAXINITLOG];
}  INITLOG_QUEUE;
extern void db_ResetInitLog(uint8 who);
extern void db_PutInitLog(char *buf);
extern INITLOGEVENT* db_GetInitLog(uint8 who);
extern int16 db_GetInitLogCount(uint8 who);

/******************************************************/
//�¼���־��ָ�������á��������쳣����Ϣ
#define ULOGSTRLEN 64
typedef struct{
	SYS_TIME64 time;
	uint8 type;//��Ϣ���ͱ��
	uint8 sts;//��Ϣֵ
	char buf[64];
}ULOGEVENT;
typedef struct{		
	int16 cnt[2];		//�̶�Ϊ��cnt[0]dpaZzmap,cnt[1]FileMid
	int16 rpnt[2];
	int16 wpnt;
	ULOGEVENT logevent[MAXULOG];
}  ULOG_QUEUE;
extern void db_ResetULog(uint8 who);
extern void db_PutULog(uint8 type, uint8 sts, char *buf);
extern ULOGEVENT * db_GetULog(uint8 who);
extern int16 db_GetULogCount(uint8 who);
/******************************************************/
//��ӡ��Ϣ����ҪΪ����ĵ��������ʾ��Ϣ
#define LOGPRINTSTRLEN 72
typedef struct{
	SYS_TIME64 time;
	char buf[72];
}PRTLOGEVENT;
typedef struct{		
	int16 cnt[2];		//�̶�Ϊ��cnt[0]dpaZzmap,cnt[1]FileMid
	int16 rpnt[2];
	int16 wpnt;
	PRTLOGEVENT logevent[MAXPRTLOG];
}  PRTLOG_QUEUE;
extern void db_ResetPrtLog(uint8 who);
extern void db_PutPrtLog(char *buf);
extern PRTLOGEVENT * db_GetPrtLog(uint8 who);
extern int16 db_GetPrtLogCount(uint8 who);
/******************************************************/



/*****************************************************
Ӧ����ά���ڷ���ͨѶ���ĵȣ���Щ��������DBMS��ʹά����Ӧ�ÿ��Բ�link��������
*****************************/

#define MONICOMM_DIR_TX	0X40
#define MONICOMM_DIR_RX  0X41
#define MONICOMM_DIR_NONE 0X42

typedef struct{
	uint8 MonCom;//���ӵĴ��ڣ�ָportnr, 0Ϊ��Ч��
	uint32 RemoteIP;//���ӵĶԷ�IP,����������ͨѶʱ��Ч
	uint32 LocalIP;//���ӵı���IP,����������ͨѶʱ��Ч
	int16 rpnt;
	int16 wpnt;
	char buf[MAXMONICOMM];
}  MONCOMM_QUEUE;
extern void glb_ResetMoniComm(void);
extern void glb_PutComLog(uint8 portnr, char *buf, uint8 dir);//���79���ַ�
extern void glb_PutComCode(uint8 portnr, uint8 *buf, uint16 len, uint8 dir);
extern void glb_PutNetLog(uint32 LocalIP, uint32 remotIP, char *buf, uint8 dir);//���79���ַ�
extern void glb_PutNetCode(uint32 LocalIP, uint32 remotIP, uint8 *buf, uint16 len, uint8 dir);
extern bool glb_GetMoniCommCode(uint8 *code);
extern int16 db_GetMoniCommCount(void);
/******************************************************/


/*******************************************************/
extern void db_unForce(void);
extern bool db_Init(void);
/*******************************************************/




/*******************************************************/

extern uint8 glb_f_ApplsRunEn;//����APP���б�־����û�����á��������ã����س���ʱglb_ApplsEn��0
extern uint8* glb_pSfgFile;   //ָ�������ļ����׵�ַ��ͬʱ��Ϊ������ȷ���õı�ʶ��NULL��ʾ��


#define MEMCTRLCBK_IDT	0X123456
typedef struct
{
	uint32 identify;
	uint32 size;
	uint32 systick;//ʱ����Ϊ���������CHKSUM
	uint16 dummy1;
	uint16 chksum;//��PRG/CFG����CRC
} struPrgCfgCbk;//������������״̬���ƿ�

typedef struct
{
	uint32 identify;
	uint8 isMacSet;
	uint8 isIpSet;
	uint8 isSnSet;
	uint8 isSzParaSet;
	uint8 isDzParaSet;
	uint8 isTtParaSet;
	uint8 isFixParaSet;
	uint8 dummy1;
	uint16 dummy2;
	uint16 chksum;
} struParaCbk;//��������״̬���ƿ�


typedef struct
{
	uint32 IpAddr;
	uint32 Mask;
	uint32 Gateway;
} struIp;


extern int8 glb_cfgCurr;
extern struParaCbk glb_ParaCbk;

extern struIp glb_DefaultLocalIp[];


extern bool glb_RebootFlag;
extern uint32 glb_RebootTick;

/**************************************/
extern void glb_Init(void);
extern uint8 * glb_FindAppCfg(uint32 appidver);//ver:A.B.C  appidver: bit76:A, bit54:B, bit3210:appid
extern struIp* glb_getLocalIp(uint8 n);


extern float glb_GetDz(int16 pnt);//��ֵ
extern float glb_GetSz(int16 pnt);//���в���
extern bool glb_GetTt(int16 pnt);//Ͷ��״̬
extern uint8 glb_GetLed(uint8 pnt);//LED��״̬��bit0:1��0�� bit67:0����1����2����3����
extern void glb_PutLed(uint8 pnt, uint8 val);



/******************************************************/
#endif
