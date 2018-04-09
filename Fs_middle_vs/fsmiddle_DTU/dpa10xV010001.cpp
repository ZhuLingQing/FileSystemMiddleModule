
//#pragma once
//#include "stdafx.h"
//#include "ZZ.h"


#ifdef VS_SIMULATE
//#include "vsCommunications.h"
#else 
#include "fsl_uart.h"
#include "flashshell.h"
#include "w5100.h"
#include "board.h"
#endif

#include "dbmsV1.h"
//#include "sc1161.h"
#include "dpa10x.h"


 
#ifdef DPA10_SUPPORT_LOG
extern uint8 FileMid_101Requir(uint8 *rexbuf, uint16 rexlen, uint16 rcot);
extern uint8 FileMid_101Continue(uint8 *texbuf, uint16 *texlen, uint16 *tcot);
#endif


#define APPID_DPA101   0x300C
#define APPVER_DPA101  0x010001
#define APPID_DPA104	0X300D
#define APPVER_DPA104	0X010001


/*  IEC101 protocol definition */
/************************************************************************/
#define START1		0x10
#define START2		0x68
#define STOP		0x16
/***********************************************************************/
#define SEND_RESET_LINK 	0
#define SEND_RESET_PROCESS	1
#define SEND_TEST_LINK		2
#define SEND_REPLY_DATA		3
#define SEND_NOREPLY_DATA	4
#define REQUEST_ACCESS_BIT	8
#define REQUEST_LINK_STATUS	9
#define REQUEST_CLASS1_DATA	10
#define REQUEST_CLASS2_DATA	11

#define CONFIRM_SEND		0
#define CONFIRM_LINK_BUSY	1
#define RESPOND_DATA		8
#define RESPOND_NODATA		9
#define RESPOND_LINK_STATUS	11
/***************************************************************************/

/*  IEC104 protocol definition */
/************************************************************************/
#define STARTDT_ACT 0X04
#define STARTDT_CON 0X08
#define STOPDT_ACT  0X10
#define STOPDT_CON  0X20
#define TESTFR_ACT  0X40
#define TESTFR_CON  0X80

#define DPA104_SEND_INTERVAL	500
#define FORMAT_I	0X0
#define FORMAT_S	0X1
#define FORMAT_U	0X3
#define FRAME_LEN 240

#define TCP104_TCPPORT	2404
/************************************************************************/



// TYPE IDENTIFICATION		:= UI8(1..8)<1..255>
// Process information in monitor direction
#define M_SP_NA_1	1	// single-point information
#define M_SP_TA_1	2	// single-point information
#define M_DP_NA_1	3	// dobule-point information
#define M_DP_TA_1	4	// dobule-point information
#define M_ST_NA_1	5	// step position information
#define M_ST_TA_1	6	// step position information
#define M_BO_NA_1	7	// bitstring of 32 bit
#define M_BO_TA_1	8	// bitstring of 32 bit
#define M_ME_NA_1	9	// measured value, normalized value
#define M_ME_TA_1	10	// measured value, normalized value
#define M_ME_NB_1	11	// measured value, scaled value
#define M_ME_TB_1	12	// measured value, scaled value
#define M_ME_NC_1	13	// measured value, short floating point number
#define M_ME_TC_1	14	// measured value, short floating point number
#define M_IT_NA_1	15	// integrated totals
#define M_IT_TA_1	16	// integrated totals
#define M_EP_TA_1	17	// event of protection equipment with time tag
#define M_EP_TB_1	18	// packed start events of protection with time tag
#define M_EP_TC_1	19	// packed output circuit information of protection equipment with time tag
#define M_PS_NA_1	20	// packed single-point information with status change detection
#define M_ME_ND_1	21	// measured value, normalized value without quality descriptor
// Process information in monitor direction with time tag CP56Time2a
#define M_SP_TB_1	30	// single-point information
#define M_DP_TB_1	31	// double-point information
#define M_ST_TB_1	32	// step position information
#define M_BO_TB_1	33	// bitstring of 32 bit
#define M_ME_TD_1	34	// measured value, normalized value
#define M_ME_TE_1	35	// measured value, scaled value
#define M_ME_TF_1	36	// measured value, short floating point number
#define M_IT_TB_1	37	// integrated totals
#define M_EP_TD_1	38	// event of protection equipment
#define M_EP_TE_1	39	// packed start events of protection equipment
#define M_EP_TF_1	40	// packed output circuit information of protection equipment
// Process information in control direction
#define C_SC_NA_1	45	// single command
#define C_DC_NA_1	46	// double command
#define C_RC_NA_1	47	// regulating step command
#define C_SE_NA_1	48	// set point command, normalized value
#define C_SE_NB_1	49	// set point command, scaled value
#define C_SE_NC_1	50	// set point command, short floating point number
#define C_BO_NA_1	51	// bitstring of 32 bits
// Process information in control direction with time tag CP56Time2a
#define C_SC_TA_1	58	// single command
#define C_DC_TA_1	59	// double command
#define C_RC_TA_1	60	// regulating step command
#define C_SE_TA_1	61	// set point command, normalized value
#define C_SE_TB_1	62	// set point command, scaled value
#define C_SE_TC_1	63	// set point command, short floating point number
#define C_BO_TA_1	64	// bitstring of 32 bits
// System information in monitor direction
#define M_EI_NA_1	70	// end of initialization
// System information in control direction
#define C_IC_NA_1	100	// interrogation command
#define C_CI_NA_1	101	// counter interrogation command
#define C_RD_NA_1	102	// read command
#define C_CS_NA_1	103	// clock synchronization command
#define C_TS_NA_1	104	// test command
#define C_RP_NA_1	105	// reset process command
#define C_CD_NA_1	106	// delay acquisition command
#define C_TS_TA_1	107	// test command with CP56Time2a

// Parameter in control direction
//#define P_ME_NA_1	110	// parameter of measured value, normalized value
//#define P_ME_NB_1	111	// parameter of measured value, scaled value
//#define P_ME_NC_1	112	// parameter of measured value, short floating-point number
//#define P_AC_NA_1	113	// parameter activation

//	File transfer
//#define F_FR_NA_1	120	// file ready
//#define F_SR_NA_1	121	// section ready
//#define F_SC_NA_1	122	// call directory, select file, call section
//#define F_LS_NA_1	123	// last section, last segment
//#define F_AF_NA_1	124	// ack file, ack section
//#define F_SG_NA_1	125	// segment
//#define F_DR_TA_1	126	// directory

// ���Ժ��չ����
#define M_FT_NA_1	42	// �����¼���Ϣ
#define M_IT_NB_1	206	// �����ۼ���
#define M_IT_TC_1	207	// �����ۼ��� with timestamp
#define C_SR_NA_1	200	// �л���ֵ��
#define C_RR_NA_1	201	// ����ֵ����
#define C_RS_NA_1	202	// �������Ͷ�ֵ
#define C_WS_NA_1	203	// д�����Ͷ�ֵ
#define F_FR_NA_1	210	// �ļ�����
#define F_SR_NA_1	211	// �������



/***************************************************************************/
// VARIABLE STRUCTURE QUALIFIER=CP8{SQ,Number}
// Number=N		:= UI7(1..7)<0..127>
// <0>			ASDU contains no INFORMATION OBJECT
// <1..127>		number of INFORMATION OBJECTs or ELEMENTs
// SQ=Single/sequence	:= BS1(8)<0..1>
// <0>	addressing of an individual element or combination of elements in
//	a number of INFORMATION OBJECTs of the same type
// <1>	addressing of a SEQUENCE INFORMATION ELEMENTs in one object
// SQ<0> and N<0-127>	number of INFORMATION OBJECTs
// SQ<1> and N<0-127>	number of INFORMATION OBJECTs of single object per
//			ACDU
/***********************************************************************/
// CAUSE OF TRANSMISSION=CP16{Cause,P/N,T,Originator Address(opt)}
// CAUSE=UI6(1..6)<0..63>	0:not difined, 1-63:number of cause
// P/N=BS1[7]<0..1>		0:positive confirm, 1:negative confirm
// T=test=BS1[8]<0..1>		0:no test, 1:test
#define PER_CYC 	1	// periodic, cyclic
#define BACK		2	// background scan
#define SPONT		3	// spontaneous
#define INIT		4	// initilize
#define REQ		5	// request or requested
#define ACT		6	// activation
#define ACTCON		7	// activation confirmation
#define DEACT		8	// deactivation
#define DEACTCON	9	// deactivation confirmation
#define ACTTERM 	10	// activation termination
#define RETREM		11	// return information caused by a remote command
#define RETLOC		12	// return information caused by a local command
#define FILE_TRANS	13	// file transfer
#define INTROGEN	20	// interrogated by general interrogation
#define CNINTROGEN      1   //   INterrogate for general counter
#define INTRO1		21	// interrogated by group1 interrogation
#define INTRO2		22	// interrogated by group2 interrogation
#define INTRO3		23	// interrogated by group3 interrogation
#define INTRO4		24	// interrogated by group4 interrogation
#define INTRO5		25	// interrogated by group5 interrogation
#define INTRO6		26	// interrogated by group6 interrogation
#define INTRO7		27	// interrogated by group7 interrogation
#define INTRO8		28	// interrogated by group8 interrogation
#define INTRO9		29	// interrogated by group9 interrogation
#define INTRO10 	30	// interrogated by group10 interrogation
#define INTRO11 	31	// interrogated by group11 interrogation
#define INTRO12 	32	// interrogated by group12 interrogation
#define INTRO13 	33	// interrogated by group13 interrogation
#define INTRO14 	34	// interrogated by group14 interrogation
#define INTRO15 	35	// interrogated by group15 interrogation
#define INTRO16 	36	// interrogated by group16 interrogation
#define REQCOGEN	37	// requested by general counter request
#define REQCO1		38	// requested by group1 counter request
#define REQCO2		39	// requested by group2 counter request
#define REQCO3		40	// requested by group3 counter request
#define REQCO4		41	// requested by group4 counter request

/***********************************************************************/
// 101 controlword bits
#define	DIR  0x80
#define PRM  0x40
#define FCB  0x20
#define FCV  0x10
#define	ACD  0x20
#define DFC  0x10

/*******************************/
#define QULI_SINGLE	0x0
#define QULI_SEQUENCE	0x80

#define DP_ON	0X2
#define DP_OFF	0X1



/***********************************************************************/
//sc1161

#define	LINK_MASTER    0x00<<6
#define LINK_TOOL      0x01<<6
#define LINK_GATEWAY   0x10<<6

#define ENCRYPT         0x00<<3
#define UNENCRYPT       0x01<<3

#define KEYID_MASTER    0x00
#define KEYID_TOOL      0x01
#define DEV_SIGN_KEY    0x01  //�ն�ǩ����Կ��ʶ   ������01����06?????????

#define CONFIRM_MASTER    0x01;
#define CONFIRM_TOOL      0x02;
#define CONFIRM_GATEWAY   0x04;

#define MIN_SN  0   //�ն�֧�ֵ���С��ֵ����
#define MAX_SN  3   //�ն�֧�ֵ����ֵ����
#define TOOL_TIMEOUT  60000*60  //�ݶ�1Сʱ   �涨ʱ�޸������޽���


/****************************/
// app type define

#define APP0			0x00
#define APP1			0x01
#define APP2			0x02
#define APP3			0x03
#define APP4			0x04
#define APP5			0x05
#define APP6			0x06
#define APP7                    0x07
#define APP8                    0x08
#define ERROR                   0x1F

#define GATEWAY_AUTH_REQUST          0x20
#define GDEV_AUTH_ACK                0x21
#define GATEWAY_AUTH_RESPONSE        0x22
#define GDEV_AUTH_RESULT             0x23

#define TOOL_AUTH_REQUST             0x30
#define TDEV_AUTH_ACK                0x31
#define TOOL_AUTH_RESPONSE           0x32
#define TDEV_AUTH_RESULT             0x33

#define TOOL_KEY_VERSION             0x34
#define TDEV_KEY_VERSIONACK          0x35
#define TOOL_DEV_VERSION             0x36
#define TDEV_DEV_VERSIONACK          0x37
#define TOOL_SN_GET                  0x38
#define TDEV_SN_RETURN               0x39
#define TOOL_PUBLICKEY_GET           0x3A
#define TDEV_PUBLICKEY_RETURN        0x3B

#define TOOL_SIGN_REQUEST            0x3C
#define TDEV_SIGN_RETURN             0x3D
#define TOOL_CER_IMPORT              0x3E
#define TDEV_CER_IMPORTNACK          0x3F
#define TOOL_CER_REWRITE             0x40
#define TDEV_CER_REWRITEACK          0x41
#define TOOL_DEVCER_GET              0x42
#define TDEV_DEVCER_RETURN           0x43
#define TOOL_DEVCER_RESULT           0x44
#define TDEV_FRAME_ACK               0x45
#define TOOL_KEY_RECOVERY            0x46    //����ִ����Կ�ָ�
#define TDEV_KEY_RECOVERYACK         0x47
#define TOOL_DATA_GET                0x48
#define TDEV_DATA_RETURN             0x49

#define MASTER_AUTH_REQUST          0x50
#define MDEV_AUTH_ACK               0x51
#define MASTER_AUTH_RESPONSE        0x52
#define MDEV_AUTH_RESULT            0x53
#define MASTER_SN_GET               0x54
#define MDEV_SN_RETURN              0x55


#define MASTER_KEY_VERSION          0x60    //��վ��ȡ��Կ�汾
#define MDEV_KEY_VERSIONACK         0x61    //�豸������Կ�汾
#define MASTER_KEY_UPDATE           0x62    //��վִ����Կ����
#define MDEV_KEY_UPDATEACK          0x63    //�豸������Կ���½��
#define MASTER_KEY_RECOVERY         0x64    //��վִ����Կ�ָ�
#define MDEV_KEY_RECOVERYACK        0x65    //�豸������Կ�ָ����


#define MASTER_CER_UPDATE           0x70    //��վ����CA/��վ/����֤��Զ�̸���
#define MDEV_CER_UPDATEACK          0x71    //�豸���ظ��½��
#define MASTER_CER_DOWNLOAD         0x72    //��վ����Զ�������ն�֤��
#define MDEV_CER_DOWNLOADACK        0x73    //�豸�������ؽ��
#define MASTER_CER_GET              0x74    //��վ������ȡ֤��
#define MDEV_CER_RETURN             0x75    //�豸����֤��
#define MASTER_CER_GETACK           0x76    //��վ����֤����ȡ���

#define ERRO_BUSS_TYPE               0x9101
#define ERRO_BUSS_SIGN               0x9102
#define ERRO_BUSS_DECRYP             0x9103
#define ERRO_BUSS_RAND               0x9104
#define ERRO_BUSS_TIME               0x9105
#define ERRO_BUSS_NONSTANDARD        0x9106
#define ERRO_BUSS_SAFEPROCESS        0x9107
#define ERRO_BUSS_LIMIT              0x9108
#define ERRO_BUSS_UNKNOWN            0x9109
#define ERRO_BUSS_ANALYSIS           0x9110

#define SAFE_SUCCESS                 0x9000
#define ERRO_SAFE_AUTH               0x9090
#define ERRO_SAFE_KEYUPDATE          0x9091
#define ERRO_SAFE_KEYRECOVER         0x9092
#define ERRO_SAFE_CERINPUT           0x9093
#define ERRO_SAFE_CEROUTPUT          0x9094
#define ERRO_SAFE_CERGET             0x9095
#define ERRO_SAFE_CERRECEIVE         0x9096
#define ERRO_SAFE_CERUPDATE          0x9097

/*****************************************************************/
/*
typedef enum
{
	TypeidDi,
	TypeidAi,
	TypeidDo,
	TypeidPa,
	TypeidPara,
}enumTYPID_GRP;
*/
/**********************/
/*
#define RXSIZE	263
#define TXSIZE  272
#define CLASS1BUFSIZE	1024
#define CLASS2BUFSIZE	128
*/
//#define REPLY	1
//#define NOREPLY 0

#define BROARDCAST 255

#define COSONLY	2
#define SOEONLY 1

#define DPA10x_SCAN_INTERVAL	150

#define PORTSTS_INIT		0
#define PORTSTS_RUN		1
#define PORTSTS_ERR		2



//only101, f_sendframe
enum
{
	F_CONFIRM_SEND = 1,
	F_RESPOND_LINK_STATUS,
	F_RESPOND_CLASS1,
	F_RESPOND_CLASS2,
	F_RESPOND_NODATA,
};

//only104
#define TCP_INIT		0
#define TCP_LISTEN              1
#define TCP_CONN                2
#define TCP_REC                 3
#define TCP_WAIT                4
#define TCP_CLOSE               5
#define TCP_TIMEOUT             6
//#define TCP_ERR			7

#define TEST_T1  30000   //��ԼҪ��t0��15s������ʵ�������Ϊ30s

#define MAXNUM 256
#define DPA104_UNACK_K	12
/***************************************************************/
/***************************************************************/
/*
//����structures, ��cpu flash��

typedef struct  //����ң��SPTB����ʱ�꣬SPTA����ʱ��
{
	int16 syspnt;			//ϵͳ���
	uint16 option;			//ѡ��
	int8 rev[4];			//����
}struDpa10xSp_Cfg;

typedef struct  //˫��ң��DPTB����ʱ�꣬DPTA��ʱ��
{
	int16 syspnton;			//��λϵͳ���
	int16 syspntoff;		//��λϵͳ���
	uint16 option;			//ѡ��
	int8 rev[2];			//����
}struDpa10xDp_Cfg;

typedef struct  //ң��MENA MENB MENC   Na��һ�� Nb��Ȼ� Nc����
{
	int16 syspnt;			//ϵͳ���
	uint16 option;			//ѡ��
	float multiply;			//ϵ��  ������վ��ֵ=���ݿ��ֵ*ϵ��
	int8 rev[4];			//����
}struDpa10xMe_Cfg;


typedef struct  //������ITNA
{
	int16 syspnt;			//ϵͳ���
	uint16 option;			//ѡ��
	float multiply;			//ϵ��	������վ��ֵ=���ݿ��ֵ*ϵ��
	int8 rev[4];			//����
}struDpa10xIt_Cfg;

typedef struct  //����SCNA��˫��DCNAң��
{
	int16 syspnton;			//�غ�ϵͳ���
	int16 syspntoff;		//�ط�ϵͳ���
	uint16 option;			//ѡ��
	int8 rev[2];			//����
}struDpa10xDc_Cfg;

typedef struct  //���SENA SENB SENC  Na��һ�� Nb��Ȼ� Nc���� ң��
{
	int16 syspnt;			//ϵͳ���
	uint16 option;			//ѡ��
	float multiply;			//ϵ��  �������ݿ��ֵ=��վ�·�ֵ*ϵ��
	int8 rev[4];			//����
}struDpa10xSe_Cfg;

typedef struct //��ֵ������
{
	INT16 syspnt;			//ϵͳ���
	INT8  datatype;			//0Ͷ�˿����� 1��ֵ 2���в��� 
	INT8 Tag;				//104�е�����TAG
	INT8 Len;				//104�еĲ�������
	char Rev[3];
	float multiply;			//ϵ��  �������ݿ��ֵ=��վ�·�ֵ*ϵ��
}struDpa10xPara_Cfg;


typedef struct
{
	int16 grpnr;			//��� 1��16
	uint16 frmtype;		//֡���ͣ�SPTB DPTB MENA MENB MENC ITNA SCNA DCNA SENA SENB SENC
	int16 startpnt;			//��������ص�����ʼ�����
	int16 endpnt;			//��������ص��Ľ��������
	uint8	rev[4];
}struDpa10xGrp_Cfg;

//----
typedef struct
{
	uint16 frmtype;		//֡���� 
	uint16 pntnum1frm;		//ÿһ֡�ĵ�����0��ʾ������
	UINT32 frminf;		//��ʼ��Ϣ��
	UINT8  rev[6];			//Ԥ��

	uint16 pntnum;			//������֡�ܵ���
	int16 pntcfg;		//pntcfg struct����frmtype��
}struDpa10xFrm_Cfg;

//----
typedef struct
{
	uint32 portsize;		//ͨ�������ó��ȣ��ֽ�����

	union{
		int32 portnr1;			//װ�ö˿�
		uint32 remoteip3;       //Զ����IP
	};
	union{
		int32 portnr2;			//װ�ö˿�
		uint32 remoteip4;       //Զ����IP
	};
	union{
		uint8 baud1;		    //װ�ò�����
		int8 localip1;			//������IP
	};
	union{
		uint8 baud2;		    //װ�ò�����
		int8 localip2;			//���ر�IP
	};
	union{
		int8 parity;            //װ��У��λ
		int8 rev2;
	};
	uint8 commkey;   

	uint8 commaddrlen;
	int8 linkaddrlen;		//��·��ַ�ֽ��� 1��2
	int8 inflen;			//��Ϣ���ַ�ֽ��� 2��3
	int8 causelen;			//����ԭ���ֽ��� 1��2

	int16	linkaddr;		//��ͨ����·��ַ
	int16 commaddr;		//��ͨ��������ַ

	int8 timesynen;		//�Ƿ��ɱ�ͨ����վ��ʱ
	int8 soecos;			//��λ���ͷ�ʽ 0���ͱ�λ 1����SOE 2����COS 3SOE+COS
	uint16 giinterval;	//���ڷ��͵ļ��ʱ��ms  0��֧�����ڷ���

	uint16 ciinterval;	//���ڷ��͵ļ��ʱ��ms  0��֧�����ڷ���
	int16 remotectrlen;		//ң����ѹ���Ӧ��ң��ϵͳ���

	int8 rev1[8];

	uint32 frmnum;
	struDpa10xFrm_Cfg frmcfg;
}struDpa10xPort_Cfg;

//----

typedef struct
{
	uint16 appdelay;		//Ӧ����ʱ�������ִ��
	uint16 portnum;			//ͨѶͨ����
	struDpa10xPort_Cfg  portcfg;
}struDpa10xApp_Cfg;

///////////////////////////////////////////
//����ʱstructures, ��ram��
#define DPA10x_DOSTS_SELECTED	1
#define DPA10x_DOTIMEOUT		60000
typedef struct
{
	uint32 inf;//��Ϣ��
	uint8  val;//0�ֻ�1��
	uint8  sts;//״̬��ʶ
	uint32 timetick;//ң�ؿ�ʼʱ��
}struDpa10xDoevent;

typedef struct
{
	SOEEVENT soeevent;//SOE��Ϣ
	int8 frm;//��PORT�е�֡ƫ��
	int16 pnt;//��FRM�еĵ�ƫ��
	int16 otherpnt;//���Ϊ��˫�㣬��ű���λ���Ӧ����һ����
}struDpa10xSoe;

typedef struct
{
	int16 pntnum;//Ԥ�õĵ���
	uint8 pack[256];//Ԥ�õ�ASDU���ݰ�
	uint8 f_select;//��ѡ���־
	uint32 selecttime;
}struDpa10xSzDzEvent;




////////////////////////////////////////////////////////////////
typedef struct
{
	struDpa10xFrm_Cfg		*pcfg;//֡����
	int16		pntnum;//��֡����
	void		*ppntcfg;//������
}struDpa10xFrm;



typedef struct
{
	struDpa10xPort_Cfg	*pcfg;//port����
	int16				frmnum;//��port֡��
	struDpa10xFrm		*pfrm;
	int32				ginum;//�����ٻ�����
	struDpa10xGrp_Cfg	*pgicfg;//�����ٻ�����
	int32				cinum;//�ۻ��������ٻ�����
	struDpa10xGrp_Cfg	*pcicfg;//�ۻ��������ٻ�����

	uint16	acd_count;	//δ���͵�1�����ݰ���
	uint16 noacknum;//������δ��ȷ�ϵ�CLASS1���ݰ���
	uint16	class2_count;	//δ���͵�2�����ݰ���
	uint8  class1_buf[CLASS1BUFSIZE];//һ������BUFFER
	uint8  *class1_buf_in, *class1_buf_out, *class1_buf_tmpout;//���1�����ݵ�BUF class1_buf_in:Wrָ�룬class1_buf_out:Reָ�룻buf_tmpout�����͵�δ��Ӧbufָ��
	uint8  class2_buf[CLASS2BUFSIZE];
	uint8  *class2_buf_in, *class2_buf_out;

	uint8	dpaH;//DPA��
	uint8	rbuf[RXSIZE], tbuf[TXSIZE];
	int16	rlen, tlen;

	uint8 gi_grp;//����ֵ��ʾ�������٣��˴�������ٱ��ĵ�QOI 20:�� 21:��1 36:��16
	int8 gi_currfrm;//��ǰɨ���֡
	int16 gi_currpnt, gi_endpnt;//��ǰɨ��ĵ㣬 ��֡Ӧ���͵����һ����

	uint8 ci_grp;//QCC 1:��1 2:��2... 5:��
	int8 ci_currfrm;
	int16 ci_currpnt, ci_endpnt;

	int8 ai_currfrm;//�仯ң��ɨ��ĵ�ǰ֡
	int16 ai_currpnt;//��ǰ��

	uint32 scan_timetick;//ÿ150msִ��һ��scan(), ���soeɨ���
	uint8	portsts1;//��ͨѶ��״̬ 0δ��ʼ����ERR����RUN������
	uint8	portsts2;
	uint8	activeport;//��ָ���ձ��������ĸ����յ��ġ���101��˵�ĸ��ڽ��ĸ��ڻأ�
						//��104��˵U֡Ҳ���ĸ��ڽ��ĸ��ڻأ�����֡�ĸ���STARTDT�ͷ��ĸ��������������޹ء�
						
	uint32	porttick1;//����ͨѶ��״̬(����ͨ��),��101ͨѶ�ڷ���֡ʱ��TICK�����յ��Ŀ������ʱ��˵����������ж�ͨѶ��״̬�� ��104ΪͨѶ�ڽ��յ����ĵ�TICK��104��һֱ����������Ŷ

	struDpa10xDoevent doevent;//���ң��ѡ������
	uint8 f_sendframe;//Ӧ��֡����
	uint8 f_resend;//resend����

	struDpa10xSzDzEvent SzDzEvent;//����Ԥ�õ���������
        uint16 para_sn;


	uint8 last_remote_fcb;//��101

	uint16 remote_receive_sn, remote_send_sn;//��104��������ŵ�
	uint16 local_receive_sn, local_send_sn;
	uint8 startdt1;//START DT��ʶ
	uint8 startdt2;
	int	sockid1;
	int	sockid2;
	uint32 LocalIp1Addr;
	uint32 LocalIp2Addr;
	uint8 sockinf1;//���ӽ���ʱ�����Ӧ��SockInf[]�±꣬������closeʱ�����ر�SockInf.used
	uint8 sockinf2;

	int  test_t1;   //���ͻ����APDU�ĳ�ʱ��ʱ��
	uint8 k_num;  //ĳһʱ����δ����վȷ�ϵ�������ŵ�I֡�������Ŀ
	uint32 send_timetick;//���ͼ��

        
  uint16 Mess_type;
	uint8 App_type;
	uint8 dat_rbuf[256],dat_tbuf[256]; //���ͣ����յķ�װ������buf�����������ݣ���
	uint8 Master_R1[8],Send_Rand[8];

	uint8 F_SendCER;//�Ƿ���֤�����Ҫ����
	uint16 dat_tlen,dat_rlen;//����,���յķ�װ�����򳤶�
	uint8 F_NeedACK;
	uint8 F_CONFIRM;  //�Ƿ���֤��ʶ
	uint32 sendcer_tick;
	uint32 Tool_Rectick;
        
        
        

#ifdef DPA10x_SUPPORT_LOG
	uint8 f_FileContinue;//bit0�к���CLASS1 bit1�к���CLASS2
#endif
	
	uint8 DTStart;

}struDpa10xPort;


typedef struct
{
	struDpa10xApp_Cfg *pcfg;
	int16 portnum;
	struDpa10xPort *pport;
}struDpa10xApp;
*/
struDpa10xApp dpa101appl;
static int8 f_Dpa101Init = FALSE;

static struDpa10xApp dpa104appl;
static int8 f_Dpa104Init = FALSE;

static uint8 Memtmp[4096];

static uint8 sc_rbuf[900];
static uint8 temp_buf[900];


 static uint8 Tool_ID[8];   
 static uint8 Key_Version; 
 static uint8 Tool_R1[8];   
 static uint8 Dev_Cer[800];  //�ն�֤��
 static uint16 DevCer_len;   //�ն�֤�鳤��
 static uint8 SverData[65]; //���������֤�����е���֤���+ǩ����Կ��ʶ

//uint8*sc_rbuf      (uint8*)SRAM_BASE_ADDR;
//uint8*temp_rbuf    (uint8*)(SRAM_BASE_ADDR+1000);
//uint8*DEV_CER      (uint8*)SRAM_BASE_ADDR+2000);
//char*MAST_CER      (char*)SRAM_BASE_ADDR+3000);
//char *temp_rbuf      (char*)SRAM_BASE_ADDR;



/***********************************************************************/
extern unsigned int dpaZzmaint_Crc16(void* pvBuff, int lens);
/***********************************************************************/
static uint8 dpa10x_Crc(uint8 *src, int16 count)//
{
	uint8	arith = 0;
	while (count--) arith += *src++;
	return(arith);
}


/***********************************/
static void dpa10x_AppMirrorReply(struDpa10xPort *pport, uint8 *rabuf, int alen, uint16 cause)//���ݴ����alen:ASDU�ĳ���,cause:����ԭ��
{
	uint8 *ptmp;
	int i;

	ptmp = pport->class1_buf_in;//app buf in
	*ptmp++ = alen;//
	for (i = 0; i<alen; i++)	*ptmp++ = rabuf[i];
	pport->class1_buf_in[3] = (uint8)cause;//
	if (pport->pcfg->causelen>1)pport->class1_buf_in[4] = 0;
	pport->class1_buf_in = ptmp;//app1_buf_inҲ�������Ƶģ���Ϊ*ptmp++
	pport->acd_count++;//δ���͵�һ�����ݰ�
}

/***********************************************************************/

static void dpa10x_ResetGi(struDpa10xPort *pport)
{
	pport->gi_grp = 0;
	pport->gi_currfrm = 0;
	pport->gi_currpnt = 0;
	pport->gi_endpnt = 0;
}
static void dpa10x_ResetCi(struDpa10xPort *pport)
{
	pport->ci_grp = 0;
	pport->ci_currfrm = 0;
	pport->ci_currpnt = 0;
	pport->ci_endpnt = 0;
}

/***************************************/
static bool dpa10x_FindNextGiFrm(struDpa10xPort *pport)//
{
	int j;
	uint16 typid;//֡����
	int i;
	uint8 *ptmp;

	if (pport->gi_grp == 20)
	{
		while (pport->gi_currfrm<pport->frmnum)//Ѱ��ң��ң��֡
		{
			typid = pport->pfrm[pport->gi_currfrm].pcfg->frmtype;//֡������
			if (typid == M_SP_TA_1 || typid == M_SP_TB_1 || typid == M_DP_TA_1 || typid == M_DP_TB_1
				|| typid == M_ME_NA_1 || typid == M_ME_NB_1 || typid == M_ME_NC_1)
			{
				pport->gi_endpnt = pport->pfrm[pport->gi_currfrm].pntnum - 1;//��¼��֡���һ�����͵ĵ� 
				return TRUE;
			}
			pport->gi_currfrm++;
			pport->gi_currpnt = 0;
		}
		if (pport->gi_currfrm >= pport->frmnum)//���ٽ���֡
		{
			i = 0;
			ptmp = pport->class1_buf_in;
			i++;//len
			ptmp[i++] = C_IC_NA_1;//���ٽ�����������class1_buf��
			ptmp[i++] = 1;
			ptmp[i++] = ACTTERM;
			if (pport->pcfg->causelen > 1)ptmp[i++] = 0;
			ptmp[i++] = (uint8)pport->pcfg->commaddr;
			if (pport->pcfg->commaddrlen> 1)ptmp[i++] = pport->pcfg->commaddr >> 8;
			ptmp[i++] = 0;//inf
			ptmp[i++] = 0;
			if (pport->pcfg->inflen > 2)ptmp[i++] = 0;
			ptmp[i++] = pport->gi_grp;//QOI
			ptmp[0] = i - 1;
			pport->class1_buf_in = &ptmp[i]; //
			pport->acd_count++;

			dpa10x_ResetGi(pport);
			pport->DTStart = 1;//���ٺ���SOE
		}
	}
	else if (pport->gi_grp>20)
	{
		while (pport->gi_currfrm<pport->frmnum)
		{
			typid = pport->pfrm[pport->gi_currfrm].pcfg->frmtype;//֡����
			for (j = 0; j<pport->ginum; j++)//�����
			{
				if (pport->pgicfg[j].grpnr == pport->gi_grp - 20 && pport->pgicfg[j].frmtype == typid 
					&& pport->pgicfg[j].startpnt < pport->pfrm[pport->gi_currfrm].pcfg->pntnum && pport->pgicfg[j].endpnt < pport->pfrm[pport->gi_currfrm].pcfg->pntnum)//У�����õĺ�����
				{
					if(pport->gi_currpnt==0)pport->gi_currpnt = pport->pgicfg[j].startpnt;
					pport->gi_endpnt = (pport->pgicfg[j].endpnt > pport->pfrm[pport->gi_currfrm].pcfg->pntnum - 1) ? 
						               (pport->pfrm[pport->gi_currfrm].pcfg->pntnum - 1) : pport->pgicfg[j].endpnt;
					return TRUE;
				}
			}
			pport->gi_currfrm++;
			pport->gi_currpnt = 0;
		}
		if (pport->gi_currfrm >= pport->frmnum)
			dpa10x_ResetGi(pport);
	}
	return FALSE;
}

static bool dpa10x_FindNextCiFrm(struDpa10xPort *pport)
{
	int j;
	uint16 typid;

	if (pport->ci_grp == 5)
	{
		while (pport->ci_currfrm<pport->frmnum)
		{
			typid = (uint8)pport->pfrm[pport->ci_currfrm].pcfg->frmtype;
			if (typid == M_IT_NA_1 || typid == M_IT_NB_1)
			{
				pport->ci_endpnt = pport->pfrm[pport->ci_currfrm].pntnum - 1;
				return TRUE;
			}
			pport->ci_currfrm++;
			pport->ci_currpnt = 0;
		}
		if (pport->ci_currfrm >= pport->frmnum)
			dpa10x_ResetCi(pport);
	}
	else if (pport->ci_grp>0 && pport->ci_grp<5)
	{
		while (pport->ci_currfrm<pport->frmnum)
		{
			typid = (uint8)pport->pfrm[pport->ci_currfrm].pcfg->frmtype;
			for (j = 0; j<pport->cinum; j++)
			{
				if (pport->pcicfg[j].grpnr == pport->ci_grp && pport->pcicfg[j].frmtype == typid
					&& pport->pcicfg[j].startpnt < pport->pfrm[pport->ci_currfrm].pcfg->pntnum && pport->pcicfg[j].endpnt < pport->pfrm[pport->ci_currfrm].pcfg->pntnum)//У�����õĺ�����
				{
					if (pport->ci_currpnt == 0)pport->ci_currpnt = pport->pcicfg[j].startpnt;
					pport->ci_endpnt = (pport->pcicfg[j].endpnt > pport->pfrm[pport->ci_currfrm].pcfg->pntnum - 1) ?
						(pport->pfrm[pport->ci_currfrm].pcfg->pntnum - 1) : pport->pcicfg[j].endpnt;
					return TRUE;
				}
			}
			pport->ci_currfrm++;
			pport->ci_currpnt = 0;
		}
		if (pport->ci_currfrm >= pport->frmnum)
			dpa10x_ResetCi(pport);
	}
	return FALSE;
}


void* dpa10x_SearchSyspntInFrms(struDpa10xPort *pport, int16 syspnt, enumTYPID_GRP typgrp, int8 *frm, int16 *pnt, int16 *otherpnt, uint32 *inf)
{
	int i, j;
	struDpa10xFrm *pfrm;
	void *ppntcfg = NULL;
	uint16 typid;
	void *p;

	pfrm = pport->pfrm;
	for (i = 0; i < pport->frmnum; i++, pfrm++)
	{
		typid = pfrm->pcfg->frmtype;
		if (typgrp == TypeidDi)
		{
			if (typid == M_SP_TA_1 || typid == M_SP_TB_1 || typid == M_FT_NA_1)
			{
				for (j = 0; j < pfrm->pntnum; j++)
				{
					p = (struDpa10xSp_Cfg *)(pfrm->ppntcfg) + j;
					if (((struDpa10xSp_Cfg *)p)->syspnt == syspnt)
					{
						if (frm) *frm = i;
						if (pnt) *pnt = j;
						if (otherpnt) *otherpnt = -1;
						if (inf) *inf = pfrm->pcfg->frminf + j;
						ppntcfg = p;
						return ppntcfg;
					}
				}
			}
			else if (pfrm->pcfg->frmtype == M_DP_TA_1 || pfrm->pcfg->frmtype == M_DP_TB_1)
			{
				for (j = 0; j < pfrm->pntnum; j++)
				{
					p = (struDpa10xDp_Cfg *)pfrm->ppntcfg + j;
					if (((struDpa10xDp_Cfg *)p)->syspnton == syspnt || ((struDpa10xDp_Cfg *)p)->syspntoff == syspnt)
					{
						if (frm) *frm = i;
						if (pnt) *pnt = j;
						if (otherpnt) *otherpnt = (((struDpa10xDp_Cfg *)p)->syspnton == syspnt) ? ((struDpa10xDp_Cfg *)p)->syspntoff : ((struDpa10xDp_Cfg *)p)->syspnton;
						if (inf) *inf = pfrm->pcfg->frminf + j;
						ppntcfg = p;
						return ppntcfg;
					}
				}
			}
		}
		else if (typgrp == TypeidAi)
		{
			if (pfrm->pcfg->frmtype == M_ME_NA_1 || pfrm->pcfg->frmtype == M_ME_NB_1 || pfrm->pcfg->frmtype == M_ME_NC_1)
			{
				for (j = 0; j < pfrm->pntnum; j++)
				{
					p = (struDpa10xMe_Cfg *)pfrm->ppntcfg;
					if (((struDpa10xMe_Cfg *)p)->syspnt == syspnt)
					{
						if (frm) *frm = i;
						if (pnt) *pnt = j;
						if (inf) *inf = pfrm->pcfg->frminf + j;
						ppntcfg = p;
						return ppntcfg;
					}
				}
			}
		}
		else if (typgrp == TypeidPa)
		{
			if (pfrm->pcfg->frmtype == M_IT_NA_1 || pfrm->pcfg->frmtype == M_IT_NB_1)
			{
				for (j = 0; j < pfrm->pntnum; j++)
				{
					p = (struDpa10xIt_Cfg *)pfrm->ppntcfg;
					if (((struDpa10xIt_Cfg *)p)->syspnt == syspnt)
					{
						if (frm) *frm = i;
						if (pnt) *pnt = j;
						if (inf) *inf = pfrm->pcfg->frminf + j;
						ppntcfg = p;
						return ppntcfg;
					}
				}
			}
		}
		else if (typgrp == TypeidDo)
		{
			if (pfrm->pcfg->frmtype == C_SC_NA_1 || pfrm->pcfg->frmtype == C_DC_NA_1)
			{
				for (j = 0; j < pfrm->pntnum; j++)
				{
					p = (struDpa10xDc_Cfg *)pfrm->ppntcfg;
					if (((struDpa10xDc_Cfg *)p)->syspnton == syspnt || ((struDpa10xDc_Cfg *)p)->syspntoff == syspnt)
					{
						if (frm) *frm = i;
						if (pnt) *pnt = j;
						if (inf) *inf = pfrm->pcfg->frminf + j;
						ppntcfg = p;
						return ppntcfg;
					}
				}
			}
		}
	}
	return NULL;
}

/***********************************/


static void* dpa10x_searchInfInFrms(struDpa10xPort *pport, uint32 inf, enumTYPID_GRP typgrp, int* frm, int* pnt)
{
	int i, j;
	struDpa10xFrm *pfrm;
	uint8 *ppntcfg = NULL;
	uint16 typid;

	pfrm = pport->pfrm;
	for (i = 0; i < pport->frmnum; i++, pfrm++)
	{
		typid = pfrm->pcfg->frmtype;
		if (typgrp == TypeidDi)
		{
			if (typid != M_SP_TA_1 && typid != M_DP_TA_1
				&& typid != M_SP_TB_1 && typid != M_DP_TB_1
				&& typid != M_FT_NA_1)
				continue;
		}
		else if (typgrp == TypeidAi)
		{
			if (typid != M_ME_NA_1 && typid != M_ME_NB_1
				&& typid != M_ME_NC_1)
				continue;
		}
		else if (typgrp == TypeidPa)
		{
			if (typid != M_IT_NA_1 && typid != M_IT_NB_1)
				continue;
		}
		else if (typgrp == TypeidDo)
		{
			if (typid != C_SC_NA_1 && typid != C_DC_NA_1)
				continue;
		}
		else if (typgrp == TypeidPara)
		{
			if ((typid != C_RS_NA_1) )//&& typid != (C_RS_NA_1 + 0X100)
				continue;
		}

		if (inf >= pfrm->pcfg->frminf && inf < pfrm->pcfg->frminf + pfrm->pntnum) 
		{
			if (frm) *frm = i;
			j = inf - pfrm->pcfg->frminf;
			if (pnt) *pnt = j;

			ppntcfg = (uint8 *)pfrm->ppntcfg;
			if (typid == M_SP_TA_1 || typid == M_SP_TB_1 || typid == M_FT_NA_1)
				ppntcfg += sizeof(struDpa10xSp_Cfg)*j;
			else if (typid == M_DP_TA_1 || typid == M_DP_TB_1)
				ppntcfg += sizeof(struDpa10xDp_Cfg)*j;
			else if (typid == M_ME_NA_1 || typid == M_ME_NB_1 || typid == M_ME_NC_1)
				ppntcfg += sizeof(struDpa10xMe_Cfg)*j;
			else if (typid == M_IT_TA_1 || typid == M_IT_TB_1)
				ppntcfg += sizeof(struDpa10xIt_Cfg)*j;
			else if (typid == C_SC_NA_1 || typid == C_DC_NA_1)
				ppntcfg += sizeof(struDpa10xDc_Cfg)*j;
			else if (typid == C_RS_NA_1 || typid == (C_RS_NA_1 | 0X100))
				ppntcfg += sizeof(struDpa10xPara_Cfg)*j;
			else ppntcfg = NULL;

			return ppntcfg;
		}
	}
	return NULL;
}



/***************************************/
//���class1_buf free�ռ��Ƿ����needlen����������buf
static void dpa10x_ChkAppbuf(struDpa10xPort *pport, int needlen)
{
	if (pport->class1_buf_in + needlen - pport->class1_buf >= CLASS1BUFSIZE )//�������buf�Ŀռ�
	{
		pport->class1_buf_in = pport->class1_buf_out = pport->class1_buf;
		pport->class1_buf_tmpout = pport->class1_buf_out;//class1_buf_tmpout�����͸���վ��������վû��Ӧ��ı���
		pport->noacknum = 0;
		pport->acd_count = 0;
	}
}
/***************************************/
static void dpa10x_ERROR(struDpa10xPort *pport,uint8 app_type,uint16 mess_type)
{
      int i;
      i=0;
      uint8 *dat_tbuf;
      dat_tbuf=pport->dat_tbuf;
      dat_tbuf[i++]=app_type;
      dat_tbuf[i++]=0x00;
      dat_tbuf[i++]=0x02;
      dat_tbuf[i++]=mess_type >>8;     // �쳣����:û��ǩ��,����ʱ���101���� 9101
      dat_tbuf[i++]=mess_type ;
      pport->dat_tlen=i;
      return; //hgy----------
}


static void dpa10x_AppLayer(struDpa10xPort *pport, uint8* rabuf, int alen, bool reply)//  ȷ�ϻ�Ӧ  rabuf��ָ��ASDU��buf��alen:ASDU���ȣ�reply���Ƿ��лش�
{
	uint16 typid;//���ͱ�ʶ
	uint32	inf=0;//��Ϣ���ַ�����
	uint8 vsq;
	uint8 cot;
	uint16 sn;
	uint8 u8val;
	int16 syspnt;
	int32 val;
	float fval;
	uint8 is_select;
	int i,j,k, l,n,m;
	char out[16];
	SYS_TIME64  tm,rec_tm;
	struDpa10xFrm *pfrm;
	struDpa10xPara_Cfg *pparacfg;
	struDpa10xDc_Cfg *pdc;
	struDpa10xSe_Cfg *pse;
	uint8 newpack;
	int num;
	uint8 *ptmp;

	        uint8*dat_rbuf;
        uint8 Rec_Rand[8];
        uint16 dat_rlen;

	//uint8_t *class1_buf_in;
#ifdef DPA10x_SUPPORT_LOG	
	//int   tn;
	//int res;
#endif
	
    dat_rbuf=pport->dat_rbuf;
	dat_rlen=pport->dat_rlen;
	
	dpa10x_ChkAppbuf(pport, 512);//���class1_buf free�ռ��Ƿ����needlen����������buf  

	typid = rabuf[0];//���ͱ�ʶ
	cot = rabuf[2];
	i = 2 + pport->pcfg->causelen + pport->pcfg->commaddrlen;
	if (pport->pcfg->inflen == 3)//��Ϣ���ַ�ֽ���=3
	{
		inf = ((uint32)rabuf[i] & 0xffL) | (((uint32)rabuf[i + 1] << 8) & 0xff00L) | (((uint32)rabuf[i + 2] << 16) & 0xff0000L);
		i += 3;
	}
	else//��Ϣ���ַ�ֽ���=2
	{
		inf = *(uint16*)&rabuf[i]; inf &= 0xffffL;
		i += 2;
	}

	switch (typid)//�ж����ͱ�ʶ
	{
	case C_CS_NA_1:	//time sync 103  ʱ��ͬ��
		if (pport->pcfg->timesynen)
		{
			tm.msec = *(uint16 *)&rabuf[i] % 1000;//Ŀǰ��rabuf[i]Ϊ��ϢԪ�ؼ�
			tm.sec = *(uint16 *)&rabuf[i] / 1000;//
			i += 2;
			tm.min = rabuf[i++] & 0x3f;
			tm.hour = rabuf[i++] & 0x1f;
			tm.day = rabuf[i++] & 0x1f;
			tm.mon = rabuf[i++] & 0xf; 
			tm.year = rabuf[i++];
			glb_SetDateTime(&tm);//��
		}
		if (reply) dpa10x_AppMirrorReply(pport, rabuf, alen, ACTCON);//reply���յ��ı����Ƿ���ҪӦ��  ����ȷ��
		break;

	case C_DC_NA_1: //double pnt command  ˫��ң��46
	case C_SC_NA_1: //single pnt command  ����ң��45
		//glb_PutComLog(pport->activeport?pport->pcfg->portnr2:pport->pcfg->portnr1, "receive DO command", MONICOMM_DIR_NONE);
		if (pport->pcfg->remotectrlen >= 0 && !(db_GetDi(pport->pcfg->remotectrlen) & 1))//ң����ѹ���Ӧ��ң��ϵͳ��Ŷ�Ӧ��ֵΪ0
		{
			  //��Ӧ��//dpa10x_AppMirrorReply(pport, rabuf, alen, 47);//ʧ�� δ֪����Ϣ�����ַ
			break;
		}
		for (k = 0, pfrm = pport->pfrm; k<pport->frmnum; k++, pfrm++)//�ҵ���Ӧ��֡
		{
			if (typid == C_DC_NA_1 && pfrm->pcfg->frmtype != C_DC_NA_1)continue;
			if (typid == C_SC_NA_1 && pfrm->pcfg->frmtype != C_SC_NA_1)continue;

			if (inf >= pfrm->pcfg->frminf  && inf - pfrm->pcfg->frminf<(uint32)pfrm->pntnum)//�ж���Ϣ���ַ�Ƿ���װ�õķ�Χ��
			{
				if (typid == C_DC_NA_1)	val = ((rabuf[i] & 0x3) == DP_ON) ? 1 : 0;
				else val = rabuf[i] & 0x1;
				is_select = rabuf[i] >> 7;//is_select 1��ʾѡ��  0��ʾִ�У�

				//sprintf(out, "DO inf=%xH val=%d isselect=%d", inf, val, is_select);
				//glb_PutComLog(pport->activeport ? pport->pcfg->portnr2 : pport->pcfg->portnr1, out,MONICOMM_DIR_RX);

				if (rabuf[2] == DEACT&&!is_select)//cancel ����ԭ��          ң�س���/ң����ֹ
				{
                                     if(pport->pcfg->commkey)
                                     {
                                          if(pport->App_type!=0x05)
                                           {
                                                 dpa10x_ERROR(pport,ERROR,ERRO_BUSS_TYPE);
                                                 return; //hgy----------
                                           }
                                           else
                                           {
                                                 glb_GetDateTime(&tm);
                                                 rec_tm=*(SYS_TIME64*)&dat_rbuf[dat_rlen-71];
                                                 if(((rec_tm.hour*3600+rec_tm.min*60+rec_tm.sec)-(tm.hour*3600+tm.min*60+tm.sec)>60)
                                                        ||((tm.hour*3600+tm.min*60+tm.sec)-(rec_tm.hour*3600+rec_tm.min*60+rec_tm.sec)>60))
                                                 {
                                                          dpa10x_ERROR(pport,ERROR,ERRO_BUSS_TIME);
                                                          return; //hgy----------
                                                 }
                                                 if (SC1161_Verify_DevSign(data_sc1161, dat_rlen, dat_rbuf, sc_rbuf) == FALSE)
                                                 {  
                                                          dpa10x_ERROR(pport,ERROR,ERRO_BUSS_SIGN);
                                                          return;  
                                                  } 
                                           }
                                     }  
                                     memset(&pport->doevent, 0, sizeof(struDpa10xDoevent));
                                     dpa10x_AppMirrorReply(pport, rabuf, alen, DEACTCON);//DEACTCON ֹͣ����ȷ��
				}
				else if (is_select)//select����
				{
                                     if(pport->pcfg->commkey)
                                     {
                                          if(pport->App_type!=0x05)
                                           {
                                                 dpa10x_ERROR(pport,ERROR,ERRO_BUSS_TYPE);
                                                 return; //hgy----------
                                           }
                                           else
                                           {
                                                 glb_GetDateTime(&tm);
                                                 rec_tm=*(SYS_TIME64*)&dat_rbuf[dat_rlen-71];
                                                 //memcpy(rec_tm,()dat_rbuf[dat_rlen-71],6);
                                                 if(((rec_tm.hour*3600+rec_tm.min*60+rec_tm.sec)-(tm.hour*3600+tm.min*60+tm.sec)>60)
                                                        ||((tm.hour*3600+tm.min*60+tm.sec)-(rec_tm.hour*3600+rec_tm.min*60+rec_tm.sec)>60))
                                                 {
                                                          dpa10x_ERROR(pport,ERROR,ERRO_BUSS_TIME);
                                                          return; //hgy----------
                                                 }
                                                 
                                                 if (SC1161_Verify_DevSign(data_sc1161, dat_rlen, dat_rbuf, sc_rbuf) == FALSE)
                                                 {  
                                                          dpa10x_ERROR(pport,ERROR,ERRO_BUSS_SIGN);
                                                          return;  
                                                  } 
                                            }
                                      }                                
                                      pport->doevent.inf = inf;
                                      pport->doevent.val = val;
                                      pport->doevent.sts = DPA10x_DOSTS_SELECTED;
                                      pport->doevent.timetick = glb_sysTick;
                                      dpa10x_AppMirrorReply(pport, rabuf, alen, ACTCON); 
				}
				else //execute
				{ 
                                      if(pport->pcfg->commkey)
                                        {
                                            if(pport->App_type!=0x07)
                                            {
                                                dpa10x_ERROR(pport,ERROR,ERRO_BUSS_TYPE);
                                                return; 
                                            }
                                            else
                                            {
                                                 glb_GetDateTime(&tm);
                                                 rec_tm=*(SYS_TIME64*)&dat_rbuf[dat_rlen-79];
                                                 if(((rec_tm.hour*3600+rec_tm.min*60+rec_tm.sec)-(tm.hour*3600+tm.min*60+tm.sec)>60)
                                                        ||((tm.hour*3600+tm.min*60+tm.sec)-(rec_tm.hour*3600+rec_tm.min*60+rec_tm.sec)>60))
                                                 {
                                                          dpa10x_ERROR(pport,ERROR,ERRO_BUSS_TIME);
                                                          return;
                                                 }
                                                 memcpy(Rec_Rand,&dat_rbuf[dat_rlen-73],8);
                                                 if( memcmp(Rec_Rand,pport->Send_Rand,8)!=0)
                                                 {
                                                          dpa10x_ERROR(pport,ERROR,ERRO_BUSS_RAND);
                                                          return;
                                                 }
                                                 if (SC1161_Verify_DevSign(data_sc1161, dat_rlen, dat_rbuf, sc_rbuf) == FALSE)
                                                 {  
                                                          dpa10x_ERROR(pport,ERROR,ERRO_BUSS_SIGN);
                                                          return;
                                                  } 
                                             }
                                        }
					if (pport->doevent.inf == inf && pport->doevent.val == val && pport->doevent.sts == DPA10x_DOSTS_SELECTED)
					{
							pdc = (struDpa10xDc_Cfg*)pfrm->ppntcfg;
							syspnt = (val & 1) ? pdc[inf - pfrm->pcfg->frminf].syspnton :pdc[inf - pfrm->pcfg->frminf].syspntoff;
							db_PutTrd(syspnt, val);
							dpa10x_AppMirrorReply(pport, rabuf, alen, ACTCON);
							dpa10x_AppMirrorReply(pport, rabuf, alen, ACTTERM);
							memset(&pport->doevent, 0, sizeof(struDpa10xDoevent));

					}
					else
					{
						memset(&pport->doevent, 0, sizeof(struDpa10xDoevent));
						dpa10x_AppMirrorReply(pport, rabuf, alen, 47);//ʧ��ACTCON | 0X40
					}
				}
				break; // skip remain frames
			}
		}
		if (k == pport->frmnum)//�Ҳ�����Ӧ��֡�͵�
		{
			memset(&pport->doevent, 0, sizeof(struDpa10xDoevent));
			dpa10x_AppMirrorReply(pport, rabuf, alen, 47);//ʧ��
		}
		break;

	case C_SE_NA_1: // 48 set point
	case C_SE_NB_1://49
	case C_SE_NC_1://  50
		//glb_PutComLog(pport->activeport ? pport->pcfg->portnr2 : pport->pcfg->portnr1, "receive AO command",MONICOMM_DIR_RX);
		for (k = 0, pfrm = pport->pfrm; k<pport->frmnum; k++, pfrm++)
		{
			if (typid == C_SE_NA_1 && pfrm->pcfg->frmtype != C_SE_NA_1)continue;
			if (typid == C_SE_NB_1 && pfrm->pcfg->frmtype != C_SE_NB_1)continue;
			if (typid == C_SE_NC_1 && pfrm->pcfg->frmtype != C_SE_NC_1)continue;

			if (inf >= pfrm->pcfg->frminf && inf - pfrm->pcfg->frminf<(uint32)pfrm->pntnum)
			{
				
				if (typid == C_SE_NC_1) is_select = rabuf[i + 4] >> 7;
				else is_select = rabuf[i + 2] >> 7;

				float ftmp;
				memcpy(&ftmp, &rabuf[i], sizeof(float));
				//if (typid == C_SE_NC_1)	sprintf(out, "AO inf=%xH val=%f isselect=%d", inf, ftmp, is_select);
				//else	sprintf(out, "AO inf=%xH val=%d isselect=%d", inf, *(int16*)&rabuf[i], is_select);
				//glb_PutComLog(pport->activeport ? pport->pcfg->portnr2 : pport->pcfg->portnr1, out,MONICOMM_DIR_RX);

				if (!is_select)//����ִ��ʱ�������ݿ�
				{
					pse = (struDpa10xSe_Cfg *)pfrm->ppntcfg;
					syspnt = pse[inf - pfrm->pcfg->frminf].syspnt;
					if (typid == C_SE_NC_1)
					{
						memcpy(&fval, &rabuf[i], sizeof(float)); 
						fval = (fval*pse[inf - pfrm->pcfg->frminf].multiply);
					}
					else
					{
						val = *(int16*)&rabuf[i];
						fval = ((float)val*pse[inf - pfrm->pcfg->frminf].multiply);
					}
					db_PutAgc(syspnt, fval);//������
				}
				dpa10x_AppMirrorReply(pport, rabuf, alen, ACTCON);//selectҲ��Ҫ�ظ�
				break;//skip remain frames
			}
		}
		if (k == pport->frmnum)//�Ҳ�����Ӧ��֡�͵�
			dpa10x_AppMirrorReply(pport, rabuf, alen, 47);//ʧ��ACTCON | 0X40
		break;
		
	case C_IC_NA_1: // general integration �ٻ�ȫ����
		dpa10x_ResetGi(pport);//���������Ƿ��������У����¿�ʼ   ��λ����
		if (rabuf[i] >= 20 && rabuf[i] <= 36)	pport->gi_grp = rabuf[i];//���ٱ��ĵ�QOI 
		else pport->gi_grp = 20;
		//pport->cyclic_gi_time = glb_sysTick;//����tick
		dpa10x_AppMirrorReply(pport, rabuf, alen, ACTCON);
		dpa10x_FindNextGiFrm(pport);//�ҵ�����֡��û��ʱ��gi_grp��ACTTERM������mirrorreply����

		//sprintf(out, "general integration group%d", pport->gi_grp);
		//glb_PutComLog(pport->activeport ? pport->pcfg->portnr2 : pport->pcfg->portnr1, out,MONICOMM_DIR_RX);
		break;
		
	case C_CI_NA_1: // counter intergration���ܼ�����
		dpa10x_ResetCi(pport);
		if ((rabuf[i]&0x3f) >=1 && (rabuf[i]&0x3f)<=5)	pport->ci_grp = rabuf[i]&0x3f;//QOI 
		else pport->ci_grp = 5;
		//pport->cyclic_ci_time = glb_sysTick;
		dpa10x_AppMirrorReply(pport, rabuf, alen, ACTCON);
		dpa10x_FindNextCiFrm(pport);

		//sprintf(out, "counter integration group%d", pport->gi_grp);
		//glb_PutComLog(pport->activeport ? pport->pcfg->portnr2 : pport->pcfg->portnr1, out,MONICOMM_DIR_RX);
		break;

#ifdef DPA10x_SUPPORT_LOG
	case F_FR_NA_1: //�ļ����� Ϊ���Ժ��չ����
		if (rabuf[i++] != 2) break;//�������ݰ����� 2�ļ�����
                if(pport->pcfg->commkey&&rabuf[i]==7) //д�ļ�����
		{
			 if(pport->App_type!=0x01)
			 {
				  dpa10x_ERROR(pport,ERROR,ERRO_BUSS_TYPE);
				  return;
			 }  
			else if (SC1161_Verify_DevSign(data_sc1161, dat_rlen, dat_rbuf, sc_rbuf) == FALSE)
			 {  
				  dpa10x_ERROR(pport,ERROR,ERRO_BUSS_SIGN);
				  return; 
			  } 		
		}
		//�����Ӹ�FileMidȥ�����������ģ�Ȼ����class1 class2��ú������ݣ��Ǳ߹�����Ҳ����õĸ������ݰ�����
		pport->f_FileContinue = FileMid_101Requir(&rabuf[i], alen-i, cot);
		break;

	case F_SR_NA_1: //�������, 
		if(pport->pcfg->commkey&&rabuf[alen-1]&0x80)//��������
		{
                     if(pport->App_type!=0x01)
                     {
                                      dpa10x_ERROR(pport,ERROR,ERRO_BUSS_TYPE);
                                      return;
                     }  
                     else if (SC1161_Verify_DevSign(data_sc1161, dat_rlen, dat_rbuf, sc_rbuf) == FALSE)
                     {  
                                      dpa10x_ERROR(pport,ERROR,ERRO_BUSS_SIGN);
                                      return;  
                      } 
		}
		ptmp = pport->class2_buf_in;//FileMid������F_FR_NA_1�ļ���д���������class1/2����һ��ΪF_FR_NA_1������������SR��ȷ��֡
		*ptmp++ = alen;
		for (k = 0; k < alen; k++)	*ptmp++ = rabuf[k];
		if (cot == ACT)
			pport->class2_buf_in[3] = ACTCON;
		else pport->class2_buf_in[3] = DEACTCON;
		pport->class2_buf_in = ptmp;//app1_buf_inҲ�������Ƶģ���Ϊ*ptmp++
		pport->class2_count++;

		if (cot == ACT && rabuf[i] == 0x80)
			FileMid_ProgramUpgrade(true);//֪ͨFileMid�����д�ļ�Ϊ�������
		else if(cot == ACT && rabuf[i] == 0)
		{
			FileMid_ProgramUpgrade(false);
			glb_RebootTick = glb_sysTick;
			glb_RebootFlag = true; //��reboot�ܱ�־���ӳ�ʱ�䣬��commtaskִ������
		}
		break;
#endif	


#ifndef VS_SIMULATE
	case C_SR_NA_1://�л���ֵ����
		if(pport->pcfg->commkey)                  
		{
                     if(pport->App_type!=0x01)
                     {
                          dpa10x_ERROR(pport,ERROR,ERRO_BUSS_TYPE);
                          return;
                     }  
                     else if (SC1161_Verify_DevSign(data_sc1161, dat_rlen, dat_rbuf, sc_rbuf) == FALSE)
                     {  
                          dpa10x_ERROR(pport,ERROR,ERRO_BUSS_SIGN);
                          return;  
                      } 
		}
                      pport->para_sn=*(uint16*)&rabuf[i];
		dpa10x_AppMirrorReply(pport, rabuf, alen, ACTCON);
                break;
    case C_RR_NA_1: //����ֵ����   
                j=0;
		ptmp = pport->class1_buf_in;
		l = 2 + pport->pcfg->causelen + pport->pcfg->commaddrlen+pport->pcfg->inflen+6; //typeid vsq cot add        hgy----------
		ptmp[j++]= l;
		for (i = 0; i < l-6; i++)	ptmp[j++]= rabuf[i];
		ptmp[3] = (cot==ACT)? ACTCON: DEACTCON;//COT                //����ȷ��
		if (pport->pcfg->causelen > 1)ptmp[4] = 0;
                *(uint16*)&ptmp[j]=pport->para_sn;
		j=j+2;
                *(uint16*)&ptmp[j]=MIN_SN;  //////�ն�֧�ֵ���С��ֵ����
		j=j+2;
		*(uint16*)&ptmp[j]=MAX_SN;   //////�ն�֧�ֵ����ֵ����
		j=j+2;
		pport->class1_buf_in =&ptmp[j];
		pport->acd_count++;//δ���͵�2�����ݰ�����    

		j=0;
		ptmp = pport->class1_buf_in;
		l = 2 + pport->pcfg->causelen + pport->pcfg->commaddrlen+pport->pcfg->inflen+6; //typeid vsq cot add        hgy----------
		ptmp[j++]= l;
		for (i = 0; i < l-6; i++)	ptmp[j++]= rabuf[i];
		ptmp[3] = ACTTERM;//COT            ������ֹ
		if (pport->pcfg->causelen > 1)ptmp[4] = 0;
               *(uint16*)&ptmp[j]=pport->para_sn;
		j=j+2;
                *(uint16*)&ptmp[j]=MIN_SN;//////�ն�֧�ֵ���С��ֵ����
		j=j+2;
		*(uint16*)&ptmp[j]=MAX_SN;//////�ն�֧�ֵ����ֵ����
		j=j+2;
		pport->class1_buf_in = &ptmp[j];
		pport->acd_count++;//δ���͵�2�����ݰ�����
                break;
	case C_RS_NA_1://�������Ͷ�ֵ
		i = 0;//ע�Ȿ���б��ĵ�VSQ��Ҫ���ͣ���infǰ����SN,��������˻����½���

		i++; //TYPEID
		vsq = rabuf[i++];//VSQ

		if (pport->pcfg->causelen == 2){ cot = *(uint16*)&rabuf[i]; i += 2; }//COT����ԭ��
		else { cot = rabuf[i]; i += 1; }

		if (pport->pcfg->commaddrlen == 2)	i += 2;//COMMON ADDR, skip
		else i += 1;

               sn=*(uint16*)&rabuf[i];
               i+=2;       //SN����ֵ���ţ���ʱ��֧��,skip

		//----��֯������class2_buf----
		dpa10x_ChkAppbuf(pport, 512);
		if (vsq == 0)  //0��ȫ������
		{
			//���в�����9��
			{
				ptmp = pport->class1_buf_in + 1;
				*ptmp++ = C_RS_NA_1;
				*ptmp++ = 9;//vsq
				*ptmp++ = ACTCON;
				if (pport->pcfg->causelen > 1)*ptmp++ = 0;
				*ptmp++ = (uint8)pport->pcfg->commaddr;
				if (pport->pcfg->commaddrlen > 1)*ptmp++ = pport->pcfg->commaddr >> 8;
				*ptmp++ = sn;//SN ��ֵ���ŵ�
				*ptmp++=sn>>8;   //SN ��ֵ���Ÿ�     hgy----------
				*ptmp++ = 1;//PI ����������ʶ 1�к�����0�޺����� �������Զ�ÿһ����֡�������25������

				*(uint16*)ptmp = 0x8001;//INF
				ptmp += 2;
				if (pport->pcfg->inflen > 2)*ptmp++ = 0;
				*ptmp++ = 4;//tag
				*ptmp++ = strlen(BOARD_STR_DEVTYP) + 1;//len
				strcpy(ptmp, BOARD_STR_DEVTYP);
				ptmp += strlen(BOARD_STR_DEVTYP) + 1;

				*(uint16*)ptmp = 0x8002;//INF
				ptmp += 2;
				if (pport->pcfg->inflen > 2)*ptmp++ = 0;
				*ptmp++ = 4;//tag
				*ptmp++ = strlen(BOARD_STR_OSTYP) + 1;//len
				strcpy(ptmp, BOARD_STR_OSTYP);
				ptmp += strlen(BOARD_STR_OSTYP) + 1;

				*(uint16*)ptmp = 0x8003;//INF
				ptmp += 2;
				if (pport->pcfg->inflen > 2)*ptmp++ = 0;
				*ptmp++ = 4;//tag
				*ptmp++ = strlen(BOARD_STR_MANUFACTER) + 1;//len
				strcpy(ptmp, BOARD_STR_MANUFACTER);
				ptmp += strlen(BOARD_STR_MANUFACTER) + 1;

				*(uint16*)ptmp = 0x8004;//INF
				ptmp += 2;
				if (pport->pcfg->inflen > 2)*ptmp++ = 0;
				*ptmp++ = 4;//tag
				*ptmp++ = strlen(BOARD_STR_HARDVER) + 1;//len
				strcpy(ptmp, BOARD_STR_HARDVER);
				ptmp += strlen(BOARD_STR_HARDVER) + 1;

				*(uint16*)ptmp = 0x8005;//INF
				ptmp += 2;
				if (pport->pcfg->inflen > 2)*ptmp++ = 0;
				*ptmp++ = 4;//tag
				*ptmp++ = strlen(BOARD_STR_SOFTVER) + 1;//len
				strcpy(ptmp, BOARD_STR_SOFTVER);
				ptmp += strlen(BOARD_STR_SOFTVER) + 1;

				*(uint16*)ptmp = 0x8006;//INF ���У����
				ptmp += 2;
				if (pport->pcfg->inflen > 2)*ptmp++ = 0;
				*ptmp++ = 4;//tag
					struPrgCfgCbk cbk;
					flashshell_Read(MEMADDR_FLASH_PRGCBK0, &cbk, sizeof(struPrgCfgCbk));
					sprintf(out, "%04x", cbk.chksum);
				*ptmp++ = strlen(out) + 1;//len 
				strcpy(ptmp, out);
				ptmp += strlen(out) + 1;

				*(uint16*)ptmp = 0x8007;//INF
				ptmp += 2;
				if (pport->pcfg->inflen > 2)*ptmp++ = 0;
				*ptmp++ = 4;//tag
				*ptmp++ = strlen(BOARD_STR_PROTOCOL) + 1;//len
				strcpy(ptmp, BOARD_STR_PROTOCOL);
				ptmp += strlen(BOARD_STR_PROTOCOL) + 1; 

				*(uint16*)ptmp = 0x8008;//INF
				ptmp += 2;
				if (pport->pcfg->inflen > 2)*ptmp++ = 0;
				*ptmp++ = 4;//tag
				*ptmp++ = strlen(BOARD_STR_PN) + 1;//len
				strcpy(ptmp, BOARD_STR_PN);
				ptmp += strlen(BOARD_STR_PN) + 1;

				*(uint16*)ptmp = 0x8009;//INF SN //�ն����к�
				ptmp += 2;
				if (pport->pcfg->inflen > 2)*ptmp++ = 0;
				*ptmp++ = 4;//tag
				if (glb_ParaCbk.isSnSet)
				{
					flashshell_Read(MEMADDR_FLASH_FIXPARA + FIXPARA_SN_IDX, ptmp + 1, 32);
					k = strlen(ptmp + 1) + 1;//len    
					*ptmp++ = k;
					ptmp += k;
				} 
				else
				{
					*ptmp++ = strlen("NONE") + 1;//len
					strcpy(ptmp, "NONE");
					ptmp += strlen("NONE") + 1;
				}

				pport->class1_buf_in[0] = ptmp - pport->class1_buf_in - 1;
				pport->class1_buf_in = ptmp;
				pport->acd_count++;
			}
			
			num = 0;//�����ܵ���
			for (k = 0, pfrm = pport->pfrm; k < pport->frmnum; k++, pfrm++)
			{
				if (pfrm->pcfg->frmtype == C_RS_NA_1)// || pfrm->pcfg->frmtype == (C_RS_NA_1 | 0X100)
					num += pfrm->pntnum;
			}
			l = 0;//�Ѵ���������������num����
			for (k = 0, pfrm = pport->pfrm; k < pport->frmnum; k++, pfrm++)
			{
				if (l == num) break;
				if (pfrm->pcfg->frmtype != C_RS_NA_1 ) continue;//&& pfrm->pcfg->frmtype != (C_RS_NA_1 | 0X100)

				m = 0;//��pfrm�е������������дinf
				newpack = 1;
				while (m < pfrm->pntnum)
				{
					if (newpack)
					{
						ptmp = pport->class1_buf_in + 1;
						*ptmp++ = C_RS_NA_1;
						ptmp++;//vsq, fill later
						*ptmp++ = ACTCON;
						if (pport->pcfg->causelen > 1)*ptmp++ = 0;
						*ptmp++ = (uint8)pport->pcfg->commaddr;
						if (pport->pcfg->commaddrlen > 1)*ptmp++ = pport->pcfg->commaddr >> 8;
						*ptmp++ = sn;//SN ��ֵ���ŵ�
                                                *ptmp++ = sn>>8;//SN ��ֵ���Ÿ�//hgy------------
						*ptmp++ = 0;//��ʱ��Ϊ0�� PI ����������ʶ 1�к�����0�޺����� �������Զ�ÿһ����֡�������25������

						newpack = 0;
						n = 0;//������֡�����ݰ��������
					}
					pparacfg = (struDpa10xPara_Cfg*)pfrm->ppntcfg;
					pparacfg += m;
					inf = pfrm->pcfg->frminf + m;

					*ptmp++ = inf; *ptmp++ = inf >> 8;
					if (pport->pcfg->inflen > 2)*ptmp++ = inf >> 16;
                                        if(sn==0)
                                        {
                                             if(pparacfg->datatype==0)
                                             {
                                                flashshell_Read(MEMADDR_FLASH_TTPARA+ pparacfg->syspnt*sizeof(int8), &u8val, sizeof(int8));
                                                fval=(float)u8val;
                                             }
                                             else if(pparacfg->datatype==1)
                                                flashshell_Read(MEMADDR_FLASH_DZPARA+ pparacfg->syspnt*sizeof(float), &fval, sizeof(float));
                                             else
                                                flashshell_Read(MEMADDR_FLASH_SZPARA + SZPARA_OTHER_IDX + pparacfg->syspnt*sizeof(float), &fval, sizeof(float));
                                        }
                                        else  fval=0;
                                        fval *= pparacfg->multiply;
                                        *ptmp++ = 38;//pparacfg->Tag;
                                        *ptmp++ = 4;//pparacfg->Len;
                                        memcpy(ptmp, &fval, sizeof(float));//��ʱȫ��float��
                                        ptmp += sizeof(float);

                                        n++; m++; l++;//�ֱ�Ϊn:pack�м��� m:frm�м��� l:�ܼ���
                                        if (n == 25 || m == pfrm->pntnum || l == num)
                                        {
                                                pport->class1_buf_in[2] = n;//VSQ
                                                pport->class1_buf_in[0] = ptmp - pport->class1_buf_in - 1;
                                                if (l < num)
                                                        pport->class1_buf_in[5 + pport->pcfg->causelen + pport->pcfg->commaddrlen] |= 0x1;//PI bit0:1�к���

                                                pport->class1_buf_in = ptmp;
                                                pport->acd_count++;
                                                newpack = 1;
                                        }
				}
			}
		}

		else // VSQ>0 �ٻ�������
		{
			num = vsq & 0x7f;
			l = 0;//�Ѵ���������������num����
			newpack = 1;
			while (l < num)
			{
				if (newpack)
				{
					ptmp = pport->class1_buf_in + 1;
					*ptmp++ = C_RS_NA_1;
					ptmp++;//vsq, fill later
					*ptmp++ = ACTCON;
					if (pport->pcfg->causelen > 1)*ptmp++ = 0;
					*ptmp++ = (uint8)pport->pcfg->commaddr;
					if (pport->pcfg->commaddrlen > 1)*ptmp++ = pport->pcfg->commaddr >> 8;
					*ptmp++ =sn;//SN ��ֵ���ŵ�
          *ptmp++ =sn>>8;//SN ��ֵ���Ÿ�     hgy-------
					*ptmp++ = 0;//��ʱ��Ϊ0�� PI ����������ʶ 1�к�����0�޺����� �������Զ�ÿһ����֡�������25������

					newpack = 0;
					n = 0;//������֡�����ݰ��������
				}

				if (pport->pcfg->inflen == 2)
				{
					inf = rabuf[i] + ((uint32)rabuf[i + 1] << 8);
					i += 2;
				}
				else
				{
					inf = rabuf[i] + ((uint32)rabuf[i + 1] << 8) + ((uint32)rabuf[i + 2] << 16);
					i += 3;
				}

				l++;//��ʹû���ҵ�INFҲ��Ҫl++,���봦����ĵ���
				if (pparacfg = (struDpa10xPara_Cfg*)dpa10x_searchInfInFrms(pport, inf, TypeidPara, NULL, NULL))
				{
					*ptmp++ = inf; *ptmp++ = inf >> 8;
					if (pport->pcfg->inflen > 2)*ptmp++ = inf >> 16;
          if(sn==0)
          {
               if(pparacfg->datatype==0)//Ͷ��
               {   
                    flashshell_Read(MEMADDR_FLASH_TTPARA+ pparacfg->syspnt*sizeof(int8), &u8val, sizeof(int8));
                    fval=(float)u8val;
               }
               else if(pparacfg->datatype==1)//��ֵ
                   flashshell_Read(MEMADDR_FLASH_DZPARA+ pparacfg->syspnt*sizeof(float), &fval, sizeof(float));
               else//���в���
                  flashshell_Read(MEMADDR_FLASH_SZPARA + SZPARA_OTHER_IDX + pparacfg->syspnt*sizeof(float), &fval, sizeof(float));
          }
					else fval=0;    //��ʱ֧��һ����ֵ����������ֵ����0ֵ
          fval *= pparacfg->multiply;
					*ptmp++ = 38;//pparacfg->Tag;
					*ptmp++ = 4;// pparacfg->Len;
					memcpy(ptmp, &fval, sizeof(float));//��ʱȫ��float��
					ptmp += sizeof(float);
					n++;
				}
				
				else if(inf >= 0x8001 && inf <= 0x8009) //������в���
				{
					if (inf == 0x8001)
					{
						*(uint16*)ptmp = 0x8001;//INF
						ptmp += 2;
						if (pport->pcfg->inflen > 2)*ptmp++ = 0;
						*ptmp++ = 4;//tag
						*ptmp++ = strlen(BOARD_STR_DEVTYP) + 1;//len
						strcpy(ptmp, BOARD_STR_DEVTYP);
						ptmp += strlen(BOARD_STR_DEVTYP) + 1;
					}
					else if (inf == 0x8002)
					{
						*(uint16*)ptmp = 0x8002;//INF
						ptmp += 2;
						if (pport->pcfg->inflen > 2)*ptmp++ = 0;
						*ptmp++ = 4;//tag
						*ptmp++ = strlen(BOARD_STR_OSTYP) + 1;//len
						strcpy(ptmp, BOARD_STR_OSTYP);
						ptmp += strlen(BOARD_STR_OSTYP) + 1;
					}
					else if (inf == 0x8003)
					{
						*(uint16*)ptmp = 0x8003;//INF
						ptmp += 2;
						if (pport->pcfg->inflen > 2)*ptmp++ = 0;
						*ptmp++ = 4;//tag
						*ptmp++ = strlen(BOARD_STR_MANUFACTER) + 1;//len
						strcpy(ptmp, BOARD_STR_MANUFACTER);
						ptmp += strlen(BOARD_STR_MANUFACTER) + 1;
					}

					else if (inf == 0x8004)
					{
						*(uint16*)ptmp = 0x8004;//INF
						ptmp += 2;
						if (pport->pcfg->inflen > 2)*ptmp++ = 0;
						*ptmp++ = 4;//tag
						*ptmp++ = strlen(BOARD_STR_HARDVER) + 1;//len
						strcpy(ptmp, BOARD_STR_HARDVER);
						ptmp += strlen(BOARD_STR_HARDVER) + 1;
					}
					else if (inf == 0x8005)
					{
						*(uint16*)ptmp = 0x8005;//INF
						ptmp += 2;
						if (pport->pcfg->inflen > 2)*ptmp++ = 0;
						*ptmp++ = 4;//tag
						*ptmp++ = strlen(BOARD_STR_SOFTVER) + 1;//len
						strcpy(ptmp, BOARD_STR_SOFTVER);
						ptmp += strlen(BOARD_STR_SOFTVER) + 1;
					}
					else if (inf == 0x8006)
					{
						*(uint16*)ptmp = 0x8006;//INF ���У���룬��NONE
						ptmp += 2;
						if (pport->pcfg->inflen > 2)*ptmp++ = 0;
						*ptmp++ = 4;//tag
						*ptmp++ = strlen("NONE") + 1;//len 
						strcpy(ptmp, "NONE");
						ptmp += strlen("NONE") + 1;
					}
					else if (inf == 0x8007)
					{
						*(uint16*)ptmp = 0x8007;//INF
						ptmp += 2;
						if (pport->pcfg->inflen > 2)*ptmp++ = 0;
						*ptmp++ = 4;//tag
						*ptmp++ = strlen(BOARD_STR_PROTOCOL) + 1;//len
						strcpy(ptmp, BOARD_STR_PROTOCOL);
						ptmp += strlen(BOARD_STR_PROTOCOL) + 1;
					}
					else if (inf == 0x8008)
					{
						*(uint16*)ptmp = 0x8008;//INF
						ptmp += 2;
						if (pport->pcfg->inflen > 2)*ptmp++ = 0;
						*ptmp++ = 4;//tag
						*ptmp++ = strlen(BOARD_STR_PN) + 1;//len
						strcpy(ptmp, BOARD_STR_PN);
						ptmp += strlen(BOARD_STR_PN) + 1;
					}
					else if (inf == 0x8009)
					{
						*(uint16*)ptmp = 0x8009;//INF SN
						ptmp += 2;
						if (pport->pcfg->inflen > 2)*ptmp++ = 0;
						*ptmp++ = 4;//tag
						if (glb_ParaCbk.isSnSet)
						{
							flashshell_Read(MEMADDR_FLASH_FIXPARA + FIXPARA_SN_IDX, ptmp + 1, 32);
							k = strlen(ptmp + 1) + 1;//len
							*ptmp++ = k;
							ptmp += k;
						}
						else
						{
							*ptmp++ = strlen("NONE") + 1;//len
							strcpy(ptmp, "NONE");
							ptmp += strlen("NONE") + 1;
						}
					}
					n++;
				}
				
				if (ptmp - pport->class1_buf_in < 32 || l == num)//n:pack�ڼ��� l:�ܼ���, ��Ϊ������в�����n���������Ը�Ϊptmp-class1_buf_in < 32
				{
					pport->class1_buf_in[2] = n;//VSQ
					pport->class1_buf_in[0] = ptmp - pport->class1_buf_in - 1;
					if (l < num)
						pport->class1_buf_in[5 + pport->pcfg->causelen + pport->pcfg->commaddrlen] |= 0x1;//PI bit0:1�к���

					pport->class1_buf_in = ptmp;
					pport->acd_count++;
					newpack = 1;
				}
			}
		}
		break;
	
	case C_WS_NA_1://д�����Ͷ�ֵ
		i = 0;//ע�Ȿ���б��ĵ�VSQ��Ҫ���ͣ���infǰ����SN,��������˻����½���

		i++; //TYPEID
		vsq = rabuf[i++];//VSQ

		if (pport->pcfg->causelen == 2){ cot = *(uint16*)&rabuf[i]; i += 2; }//COT����ԭ��
		else { cot = rabuf[i]; i += 1; }

		if (pport->pcfg->commaddrlen == 2)	i += 2;//COMMON ADDR, skip
		else i += 1;
                sn=*(uint16*)&rabuf[i];//hgy----      //i++;//SN����ֵ���ţ���ʱ��֧��,skip
                i=i+2;
                
		is_select = rabuf[i++];	//PI, bit0:1�к������޺���; bit6:1ȡ��Ԥ��; bit7:0�̻� 1Ԥ��
		if (cot == DEACT || is_select & 0x40)	//������ֹ
		{
                    if(pport->pcfg->commkey)                  
                    {
                       if(pport->App_type!=0x01)
                       {
                                dpa10x_ERROR(pport,ERROR,ERRO_BUSS_TYPE);
                                return;
                       }  
                      else if (SC1161_Verify_DevSign(data_sc1161, dat_rlen, dat_rbuf, sc_rbuf) == FALSE)
                       {  
                                dpa10x_ERROR(pport,ERROR,ERRO_BUSS_SIGN);
                                return;  
                        } //hgy----------
                    }
                    memset(&pport->SzDzEvent, 0, sizeof(pport->SzDzEvent));
		}
		else if (is_select & 0x80)//Ԥ��
		{
                    if(pport->pcfg->commkey)
                    {
                         if(pport->App_type!=0x01)
                         {
                                  dpa10x_ERROR(pport,ERROR,ERRO_BUSS_TYPE);
                                  return;
                         }  
                        else if (SC1161_Verify_DevSign(data_sc1161, dat_rlen, dat_rbuf, sc_rbuf) == FALSE)
                         {  
                                  dpa10x_ERROR(pport,ERROR,ERRO_BUSS_SIGN);
                                  return;  
                          } //hgy----------   
                    }
                    if (pport->SzDzEvent.f_select || (vsq & 0x7f) == 0)//�ظ�select��vsqΪ0, ���Ԥ��
                            memset(&pport->SzDzEvent, 0, sizeof(pport->SzDzEvent));
                    else
                    {
                            pport->SzDzEvent.pntnum = vsq & 0x7f;
                            memcpy(pport->SzDzEvent.pack, &rabuf[i], 256);//������ʵ�ʵĳ��ȣ�����COPY����
                            pport->SzDzEvent.f_select = 1;
                            pport->SzDzEvent.selecttime = glb_sysTick;
                    }
		}
		else if (pport->SzDzEvent.f_select)//�̻�
		{
                        if(pport->pcfg->commkey)
                      {
                            if(pport->App_type!=0x03)
                            {
                                    dpa10x_ERROR(pport,ERROR,ERRO_BUSS_TYPE);
                                    return; 
                            }
                            else
                            {
                                   memcpy(Rec_Rand,&dat_rbuf[dat_rlen-73],8);
                                   if( memcmp(Rec_Rand,pport->Send_Rand,8)!=0)
                                   {
                                                dpa10x_ERROR(pport,ERROR,ERRO_BUSS_RAND);
                                                return;
                                   }
                                   if (SC1161_Verify_DevSign(data_sc1161, dat_rlen, dat_rbuf, sc_rbuf) == FALSE)
                                   {  
                                                dpa10x_ERROR(pport,ERROR,ERRO_BUSS_SIGN);
                                                return;
                                    } 
                             }
                        } //hgy----------
			if(sn==0&&cot==ACT)   //����
			{
					    //flashshell_Read(MEMADDR_FLASH_SZPARA, Memtmp, MEMSIZE_FLASH_PARA);
					ptmp = pport->SzDzEvent.pack;

					for (l = 0; l < pport->SzDzEvent.pntnum; l++)
					{
							if (pport->pcfg->inflen == 2) { inf = ptmp[0] + ((uint32)ptmp[1] << 8); ptmp += 2; }
							else { inf = ptmp[0] + ((uint32)ptmp[1] << 8) + ((uint32)ptmp[1] << 16); ptmp += 3; }
							ptmp++;//TAG
							ptmp++;//len;
	                                          
							if (pparacfg = (struDpa10xPara_Cfg*)dpa10x_searchInfInFrms(pport, inf, TypeidPara, NULL, NULL))
							{
		                 if(pparacfg->datatype==0)//Ͷ��
		                 {
		                      flashshell_Read(MEMADDR_FLASH_TTPARA+ pparacfg->syspnt*sizeof(int8), &u8val, sizeof(int8));
		                      fval=(float)u8val; 
		                      memcpy(&fval, ptmp, sizeof(float));//��Ϊ���в���Ϊfloat
		                      ptmp += 4;
		                      fval /= pparacfg->multiply;
		                      u8val=(uint8)fval;
		                      memcpy(&Memtmp[pparacfg->syspnt * sizeof(int8)], &u8val, sizeof(int8));
		                 }
		                 else if(pparacfg->datatype==1)//��ֵ
		                 {
		                      flashshell_Read(MEMADDR_FLASH_DZPARA+ pparacfg->syspnt*sizeof(float), &fval, sizeof(float));
		                      memcpy(&fval, ptmp, sizeof(float));//��Ϊ���в���Ϊfloat
		                      ptmp += 4;
		                      fval /= pparacfg->multiply;
		                      memcpy(&Memtmp[pparacfg->syspnt * sizeof(float)], &fval, sizeof(float));
		                 }
		                 else//���в���
		                 {
		                      flashshell_Read(MEMADDR_FLASH_SZPARA + SZPARA_OTHER_IDX + pparacfg->syspnt*sizeof(float), &fval, sizeof(float));
		                      memcpy(&fval, ptmp, sizeof(float));//��Ϊ���в���Ϊfloat
		                      ptmp += 4;
		                      fval /= pparacfg->multiply;
		                      memcpy(&Memtmp[SZPARA_OTHER_IDX + pparacfg->syspnt * sizeof(float)], &fval, sizeof(float));             
		                 }
			        }
			          
		          if(pparacfg->datatype==0)//Ͷ��
		          {
		              flashshell_Erase(MEMADDR_FLASH_TTPARA, MEMSIZE_FLASH_PARA);
		              flashshell_Write(MEMADDR_FLASH_TTPARA, Memtmp, MEMSIZE_FLASH_PARA);
		          }
		          else if(pparacfg->datatype==1)//��ֵ
		          {
		               flashshell_Erase(MEMADDR_FLASH_DZPARA, MEMSIZE_FLASH_PARA);
		               flashshell_Write(MEMADDR_FLASH_DZPARA, Memtmp, MEMSIZE_FLASH_PARA); 
		          }
		          else
		          {
		                flashshell_Erase(MEMADDR_FLASH_SZPARA, MEMSIZE_FLASH_PARA);
		                flashshell_Write(MEMADDR_FLASH_SZPARA, Memtmp, MEMSIZE_FLASH_PARA);
		          }

							glb_ParaCbk.isSzParaSet = 1;
							glb_ParaCbk.chksum = dpaZzmaint_Crc16((uint8*)&glb_ParaCbk, sizeof(struParaCbk) - sizeof(uint16));
							flashshell_Erase(MEMADDR_FLASH_PARACBK, sizeof(struParaCbk));
							flashshell_Write(MEMADDR_FLASH_PARACBK, &glb_ParaCbk, sizeof(struParaCbk));
					}                             
					memset(&pport->SzDzEvent, 0, sizeof(pport->SzDzEvent));
				}
		}

		//Ӧ�ò�ȷ�ϼ����
		dpa10x_ChkAppbuf(pport, 262);

        //  dpa10x_AppMirrorReply(pport, rabuf, alen, ACTCON);
		ptmp = pport->class1_buf_in;
		l = 5 + pport->pcfg->causelen + pport->pcfg->commaddr;//typeid vsq cot add sn pi//l = 4 + pport->pcfg->causelen + pport->pcfg->commaddrl;//typeid vsq cot add sn pi
		*ptmp++ = l;
		for (i = 0; i < l; i++)	*ptmp++ = rabuf[i];
		pport->class1_buf_in[2] = 0;//VSQ
		pport->class1_buf_in[3] = (cot==ACT)? ACTCON: DEACTCON;//COT
		if (pport->pcfg->causelen > 1)pport->class1_buf_in[4] = 0;
		pport->class1_buf_in = ptmp;
		pport->acd_count++;//δ���͵�1�����ݰ�����

		if ((is_select & (0x40 + 0x80)) == 0)//��ȡ����Ԥ��->�̻�
		{
				ptmp = pport->class1_buf_in;
				l = 5 + pport->pcfg->causelen + pport->pcfg->commaddrlen;
				*ptmp++ = l;
				for (i = 0; i < l; i++)	*ptmp++ = rabuf[i];
				pport->class1_buf_in[2] = 0;//VSQ
				pport->class1_buf_in[3] = ACTTERM;//COT
				if (pport->pcfg->causelen > 1)pport->class1_buf_in[4] = 0;
				pport->class1_buf_in = ptmp;
				pport->acd_count++;//δ���͵�1�����ݰ�����
		}
		break;
#endif
	case C_TS_NA_1://��վ������·��������֡
	case C_RP_NA_1: // reset process��վ���͸�λ����֡
	default:
		dpa10x_AppMirrorReply(pport, rabuf, alen, ACTCON);
		break;
		
	}
}

/***************************************/
//104����k��δȷ�ϣ�һ��kΪ12; GetClass1Data���ܷ���class1֡���꣬�����ʱδ��ȷ�ϣ�����Scan()�ָ�class1buf
//101ֻҪѯ�ʾͰѵ�ǰ��δȷ�ϵĵ�һ��CLASS1������

static int dpa10x_GetClass1Data(struDpa10xPort *pport, uint8 *tabuf)//tabuf��ASDU��buf
{
	int i = 0;
	int n = 0;
	uint8 *ptmp;
	struDpa10xFrm *pfrm;
	uint32 inf;
	int32 val;
	uint32 uval;
	float fval;
	uint16 cause;
	struDpa10xSp_Cfg *psp;
	struDpa10xDp_Cfg *pdp;
	struDpa10xMe_Cfg *pme;
	struDpa10xIt_Cfg *pit;
	int vallen;

	if (pport->acd_count - pport->noacknum)
	{
		ptmp = pport->class1_buf_tmpout;

		for (i = 0; i < ptmp[0]; i++)
			tabuf[i] = ptmp[1 + i];
		pport->class1_buf_tmpout += i + 1;

		pport->noacknum++;
		return i;
	}
	
#ifdef DPA10x_SUPPORT_LOG
	if (pport->f_FileContinue & 1)
	{
		i = 0;
		tabuf[i++] = F_FR_NA_1;
		tabuf[i++] = 0;//VSQ, ��Ч
		i++;//cot fill later
		if (pport->pcfg->causelen > 1)tabuf[i++] = 0;
		tabuf[i++] = (uint8)pport->pcfg->commaddr;//COMMADDR
		if (pport->pcfg->commaddrlen > 1)tabuf[i++] = (uint8)(pport->pcfg->commaddr >> 8);
		tabuf[i++] = 0;//INF
		tabuf[i++] = 0;
		if (pport->pcfg->inflen > 2)tabuf[i++] = 0;
		tabuf[i++] = 2;//�������ݰ����ͣ�2�ļ�����
		pport->f_FileContinue = FileMid_101Continue(&tabuf[i], &n, &cause);
		i += n;
		tabuf[2] = cause;//cot
		return i;
	}
#endif

	//--------����Ҫȷ�ϵı��ģ��������ٺ��ۼ���
	if (!pport->gi_grp&&!pport->ci_grp)return 0;
	//��������
	if (pport->gi_grp) pfrm = &pport->pfrm[pport->gi_currfrm];
	else pfrm = &pport->pfrm[pport->ci_currfrm];

	i = 0;
	if (pfrm->pcfg->frmtype == M_SP_TA_1 || pfrm->pcfg->frmtype == M_SP_TB_1)//����ң��
		tabuf[i++] = M_SP_NA_1;//����ʱ��ĵ�����Ϣ
	else if (pfrm->pcfg->frmtype == M_DP_TA_1 || pfrm->pcfg->frmtype == M_DP_TB_1)//˫��ң��
		tabuf[i++] = M_DP_NA_1;//����ʱ���˫����Ϣ
	else tabuf[i++] = (uint8)pfrm->pcfg->frmtype;//ң����ۼ���

	i++;//��Ϣ���������
	
	if (pport->gi_grp)	cause = pport->gi_grp;
	else if(pport->ci_grp==5)	cause=37;//hgy-------------
        else if(pport->ci_grp!=5)  cause = pport->ci_grp + 36;
	tabuf[i++] = (uint8)cause;
	if (pport->pcfg->causelen>1)tabuf[i++] = 0;

	tabuf[i++] = (uint8)pport->pcfg->commaddr;
	if (pport->pcfg->commaddrlen>1)tabuf[i++] = pport->pcfg->commaddr >> 8;

	if (pport->gi_grp)	inf = pfrm->pcfg->frminf + pport->gi_currpnt;
	else inf = pfrm->pcfg->frminf + pport->ci_currpnt;
	if (pport->pcfg->inflen == 3)
	{
		tabuf[i++] = inf; tabuf[i++] = inf >> 8; tabuf[i++] = inf >> 16;
	}
	else
	{
		tabuf[i++] = inf; tabuf[i++] = inf >> 8;
	}

	n = 0;//��Ϣ��ĸ���
	while (i<256)
	{
		if (pfrm->pcfg->frmtype == M_SP_TA_1 || pfrm->pcfg->frmtype == M_SP_TB_1)
		{
			psp = (struDpa10xSp_Cfg *)pfrm->ppntcfg;
			tabuf[i++] = (db_GetDi(psp[pport->gi_currpnt].syspnt)&1)^(psp[pport->gi_currpnt].option&1);
		}
		else if (pfrm->pcfg->frmtype == M_DP_TA_1 || pfrm->pcfg->frmtype == M_DP_TB_1)
		{
			pdp = (struDpa10xDp_Cfg *)pfrm->ppntcfg;
			if (pdp[pport->gi_currpnt].syspnton >= 0 && pdp[pport->gi_currpnt].syspntoff >= 0)//��˫��
			{
				val = db_GetDi(pdp[pport->gi_currpnt].syspntoff)&1;
				val += (db_GetDi(pdp[pport->gi_currpnt].syspnton)&1) << 1;
			}
			else if (pdp[pport->gi_currpnt].syspnton >= 0 && pdp[pport->gi_currpnt].syspntoff < 0)//���кϵ�
			{
				if ((db_GetDi(pdp[pport->gi_currpnt].syspnton)&1) == 1)
					val = DP_ON;
				else val = DP_OFF;
			}
			else if (pdp[pport->gi_currpnt].syspnton < 0 && pdp[pport->gi_currpnt].syspntoff >= 0)//���зֵ�
			{
				if ((db_GetDi(pdp[pport->gi_currpnt].syspntoff)&1) == 1)
					val = DP_OFF;
				else val = DP_ON;
			}
			else val = 0;
			tabuf[i++] = val^(pdp[pport->gi_currpnt].option&0x3);
		}
		else if (pfrm->pcfg->frmtype == M_ME_NA_1 || pfrm->pcfg->frmtype == M_ME_NB_1)
		{
			pme = (struDpa10xMe_Cfg *)pfrm->ppntcfg;
			fval = db_GetAi(pport->dpaH,pme[pport->gi_currpnt].syspnt);
			val = (int32)(fval*pme[pport->gi_currpnt].multiply);
			*(int16*)&tabuf[i] = (int16)val;//
			i += 2;
			tabuf[i++] = 0;//Qulity
		}
		else if (pfrm->pcfg->frmtype == M_ME_NC_1)
		{
			pme = (struDpa10xMe_Cfg *)pfrm->ppntcfg;
			fval = db_GetAi(pport->dpaH, pme[pport->gi_currpnt].syspnt);
			fval = fval * pme[pport->gi_currpnt].multiply;
			memcpy(&tabuf[i], &fval, sizeof(float));
			i += 4;
			tabuf[i++] = 0;//Qulity
		}
		else if (pfrm->pcfg->frmtype == M_IT_NA_1)//15 �ۼ���
		{
			pit = (struDpa10xIt_Cfg *)pfrm->ppntcfg;
			fval = db_GetPa(pit[pport->ci_currpnt].syspnt);
			uval = (uint32)(fval * pit[pport->ci_currpnt].multiply);
                        tabuf[i++]=uval;
                        tabuf[i++]=uval>>8;
                        tabuf[i++]=uval>>16;
                        tabuf[i++]=uval>>24;
			/* *(uint32*)&tabuf[i] = uval; //�����Ῠ��������������������������
			i += 4;*/
			tabuf[i++] = 0;//Qulity
		}
		else if (pfrm->pcfg->frmtype == M_IT_NB_1)//206 �����ۼ���
		{
			pit = (struDpa10xIt_Cfg *)pfrm->ppntcfg;
			fval = db_GetPa(pit[pport->ci_currpnt].syspnt);
			fval = fval * pit[pport->ci_currpnt].multiply;
			memcpy(&tabuf[i], &fval, sizeof(float));
			i += 4;
			tabuf[i++] = 0;//Qulity
		}		
		
		//--------
		n++;
		if (pfrm->pcfg->frmtype == M_IT_NA_1 || pfrm->pcfg->frmtype == M_IT_NB_1)
		{
			pport->ci_currpnt++;
			if (pport->ci_currpnt>pport->ci_endpnt)//��֧��������ͬ��grpnrָ��ͬ����֡
			{
				pport->ci_currpnt = 0;
				pport->ci_currfrm++;
				break;
			}
		}
		else
		{
			pport->gi_currpnt++;
			if (pport->gi_currpnt>pport->gi_endpnt)//��֧��������ͬ��grpnrָ��ͬ����֡ ͬһ��������ֻ��һ��֡
			{
				pport->gi_currpnt = 0;
				pport->gi_currfrm++;
				break;
			}
		}

		if (pfrm->pcfg->pntnum1frm)//����е���Ҫ��
		{
			if (n >= pfrm->pcfg->pntnum1frm || n >= 128)break;//�Ϻ���������ʱҪ��ң����128��,��˲���127�ж�
		}
		else
		{
			if (n >= 127)break;

			if (pfrm->pcfg->frmtype == M_SP_TA_1 || pfrm->pcfg->frmtype == M_SP_TB_1
				|| pfrm->pcfg->frmtype == M_DP_TA_1 || pfrm->pcfg->frmtype == M_DP_TB_1)vallen = 1;
			else if (pfrm->pcfg->frmtype == M_ME_NA_1 || pfrm->pcfg->frmtype == M_ME_NB_1)vallen = 3;
			else if (pfrm->pcfg->frmtype == M_ME_NC_1)vallen = 5;
			else if (pfrm->pcfg->frmtype == M_IT_NA_1 || pfrm->pcfg->frmtype == M_IT_NB_1)vallen = 5;
			if (i + vallen > 249) break;//104asdulen<=253-4, 101:if (i + vallen + 1 + pport->pcfg->commaddrlen > 255) 
		}
	}

	//����Ƿ��к���֡��û��ʱgi_grp��Ӧ�����ʹACDλ����������ڷ���ǰFINDFRM
	if (pport->gi_grp)	 dpa10x_FindNextGiFrm(pport);//
	else if (pport->ci_grp)	dpa10x_FindNextCiFrm(pport);

	tabuf[1] = n | QULI_SEQUENCE;//��Ϣ��
	return i;
}

/************************************/
static int dpa10x_GetClass2Data(struDpa10xPort *pport, uint8 *tabuf)
{
	int i = 0,n;
	struDpa10xFrm *pfrm;
	uint32 inf;
	uint16 typid;
	uint16 cause;
	int32 val;
	float fval;
	struDpa10xMe_Cfg *pme;
	int vallen;
	uint8* ptmp;
#ifdef DPA10x_SUPPORT_LOG	
	//int l;
	//void* isample;
#endif
	
	if (pport->class2_count)//
	{
		ptmp = pport->class2_buf_out;

		for (i = 0; i < ptmp[0]; i++)
			tabuf[i] = ptmp[1 + i];
		pport->class2_buf_out += i + 1;

		pport->class2_count--;
		if (pport->class2_count == 0)
		{
			pport->class2_buf_out = pport->class2_buf_in = pport->class2_buf;
		}
		return i;
	}

#ifdef DPA10x_SUPPORT_LOG
	if (pport->f_FileContinue & 2)
	{
		i = 0;
		tabuf[i++] = F_FR_NA_1;
		tabuf[i++] = 0;//VSQ, ��Ч
		i++;//COT fill later
		if (pport->pcfg->causelen > 1)tabuf[i++] = 0;
		tabuf[i++] = (uint8)pport->pcfg->commaddr;//COMMADDR
		if (pport->pcfg->commaddrlen > 1)tabuf[i++] = (uint8)(pport->pcfg->commaddr >> 8);
		tabuf[i++] = 0;//INF
		tabuf[i++] = 0;
		if (pport->pcfg->inflen > 2)tabuf[i++] = 0;
                tabuf[i++]=0x02;
		pport->f_FileContinue = FileMid_101Continue(&tabuf[i], &n, &cause);
		i += n;
		tabuf[2] = cause; //cot
                //tabuf[2] = ACTCON; //cot
		return i;
	}
#endif

//SEARCHFRAME:
	n = 0;
	while (n++<pport->frmnum)//���תһȦ
	{
		if (pport->ai_currfrm >= pport->frmnum)pport->ai_currfrm = 0;

		typid = (uint8)pport->pfrm[pport->ai_currfrm].pcfg->frmtype;
		if (typid == M_ME_NA_1 || typid == M_ME_NB_1 || typid == M_ME_NC_1)
		{
			cause = SPONT;
			goto MAKEFRAME;
		}
		pport->ai_currfrm++;
		pport->ai_currpnt = 0;
	}
	//����֡ɨ�겻�ټ���
	return 0;

MAKEFRAME:
	pfrm = &pport->pfrm[pport->ai_currfrm];

	i = 0;
	tabuf[i++] = (uint8)pfrm->pcfg->frmtype;
	i++;//��Ϣ���������
	tabuf[i++] = (uint8)cause;
	if (pport->pcfg->causelen>1)tabuf[i++] = 0;
	tabuf[i++] = (uint8)pport->pcfg->commaddr;
	if (pport->pcfg->commaddrlen>1)tabuf[i++] = (uint8)(pport->pcfg->commaddr >> 8);

	n = 0;
	while (i<256)
	{
		pme = (struDpa10xMe_Cfg*)pport->pfrm[pport->ai_currfrm].ppntcfg;
		if (db_GetAiChg(pport->dpaH, pme[pport->ai_currpnt].syspnt))
		{
			inf = pfrm->pcfg->frminf + pport->ai_currpnt;
			if (pport->pcfg->inflen == 3)
			{
				tabuf[i++] = inf; tabuf[i++] = inf >> 8; tabuf[i++] = inf >> 16;
			}
			else
			{
				tabuf[i++] = inf; tabuf[i++] = inf >> 8;
			}

			if (pfrm->pcfg->frmtype == M_ME_NA_1 || pfrm->pcfg->frmtype == M_ME_NB_1)
			{
				fval = db_GetAi(pport->dpaH, pme[pport->ai_currpnt].syspnt);
				val = (int32)(fval*pme[pport->ai_currpnt].multiply);
				*(int16*)&tabuf[i] = (int16)val;//??????
				i += 2;
				tabuf[i++] = 0;//qulity
			}
			else //M_ME_NC_1
			{
				fval = db_GetAi(pport->dpaH, pme[pport->ai_currpnt].syspnt);
				fval = fval*pme[pport->ai_currpnt].multiply;
				memcpy(&tabuf[i], &fval, sizeof(float));
				i += 4;
				tabuf[i++] = 0;//qulity
			}
			n++;
		}

		pport->ai_currpnt++;
		if (pport->ai_currpnt >= pfrm->pntnum)
		{
			pport->ai_currpnt = 0;
			pport->ai_currfrm++;
			break;//����if(i<240)goto SEARCHFRAME; һ֡���Ժ�ͻ�TYPEID,���뻻֡�´η���
		}

		if (n >= 127)break;
		if (pfrm->pcfg->frmtype == M_ME_NA_1 || pfrm->pcfg->frmtype == M_ME_NB_1)vallen = 3 + pport->pcfg->inflen;
		else if (pfrm->pcfg->frmtype == M_ME_NC_1)vallen = 5 + pport->pcfg->inflen;
		if (i + vallen > 249)break; //104asdulen<=253-4, 101:if (i + vallen + 1 + pport->pcfg->commaddrlen > 255) 
	}
	//֡���������ټ���
	if (n)
	{
		tabuf[1] = n;
		return i;
	}
	else return 0;
}


/******************************/
static void dpa10x_Soe2Class1Data(struDpa10xPort* pport, struDpa10xSoe* soe, int8 soenum)//����dpa10x_Soe()����
{
	uint16 typid = 0;
	uint8 *plastfrm = 0;
	struDpa10xFrm *pfrm;
	int8 frm;
	int16 pnt;
	uint32 inf;
	int i,j,k,n;
	uint8 *ptmp;
	SOEEVENT *psoeevent;
	struDpa10xDp_Cfg *pdp;
	struDpa10xSp_Cfg *psp;
	struDpa10xMe_Cfg* pme;
	int ms;
	float fval;
	


	//------���鱣���¼�--------------
	dpa10x_ChkAppbuf(pport, 128);//�����¼�����ֻ����һ���¼�������һ�������¼���Ҫ100�ֽ�

	typid = 0;
	plastfrm = 0;
	for (j = 0; j<soenum; j++)
	{
		frm = soe[j].frm;
		pnt = soe[j].pnt;//���
		pfrm = &pport->pfrm[frm];
		psoeevent = &soe[j].soeevent;

		if (pfrm->pcfg->frmtype != M_FT_NA_1) continue;
		
		pport->acd_count++;
		typid = pfrm->pcfg->frmtype;
		ptmp = pport->class1_buf_in;

		i = 0;
		i++;//len
		ptmp[i++] = typid;
		ptmp[i++] = 1;//inf num
		ptmp[i++] = SPONT;
		if (pport->pcfg->causelen > 1)ptmp[i++] = 0;
		ptmp[i++] = (uint8)pport->pcfg->commaddr;
		if (pport->pcfg->commaddrlen > 1)ptmp[i++] = (uint8)(pport->pcfg->commaddr >> 8);
		
		
		ptmp[i++] = 1;//ң�Ÿ�����������̶�Ϊ1
		ptmp[i++] = M_SP_TB_1;//ң������

		inf = pfrm->pcfg->frminf + pnt;//����ң�ŵ��
		if (pport->pcfg->inflen == 3)
		{
			ptmp[i++] = inf; ptmp[i++] = inf >> 8; ptmp[i++] = inf >> 16;
		}
		else { ptmp[i++] = inf; ptmp[i++] = inf >> 8; }

		ptmp[i++] = psoeevent->val;//�����¼��͵���ң��ֵ

		ms = psoeevent->time.msec + psoeevent->time.sec * 1000;
		ptmp[i++] = ms;
		ptmp[i++] = ms >> 8;
		ptmp[i++] = psoeevent->time.min;
		ptmp[i++] = psoeevent->time.hour;
		ptmp[i++] = psoeevent->time.day;
		ptmp[i++] = psoeevent->time.mon;
		ptmp[i++] = psoeevent->time.year;

		//--����ң��------
		n=i;//ң�������fill later
		ptmp[i++] = 0;//ң�����
		for (k = 0; k < psoeevent->ainum; k++)
		{
			if (dpa10x_SearchSyspntInFrms(pport, psoeevent->aipnt[k], TypeidAi, &frm, &pnt, NULL, NULL))
			{
				ptmp[n]++;//ң�����++
				ptmp[i++] = pport->pfrm[frm].pcfg->frmtype;//ң������
				inf = pport->pfrm[frm].pcfg->frminf + pnt;//ң��inf
				if (pport->pcfg->inflen == 3)
				{
					ptmp[i++] = inf; ptmp[i++] = inf >> 8; ptmp[i++] = inf >> 16;
				}
				else { ptmp[i++] = inf; ptmp[i++] = inf >> 8; }

				if (pport->pfrm[frm].pcfg->frmtype == M_ME_NA_1 || pport->pfrm[frm].pcfg->frmtype == M_ME_NB_1)
				{
					fval = psoeevent->aival[k];
					pme = (struDpa10xMe_Cfg*)(pport->pfrm[frm].ppntcfg);
					fval *= pme[pnt].multiply;
					*(int16*)&ptmp[i] = (int16)fval;
					i += sizeof(int16);
				}
				else
				{
					fval = psoeevent->aival[k];
					pme = (struDpa10xMe_Cfg*)(pport->pfrm[frm].ppntcfg);
					fval *= pme[pnt].multiply;
					memcpy(ptmp, &fval, sizeof(float));
					i += sizeof(float);
				}
				ptmp[i++] = 0;//IQ
			}
		}

		//-------------
		ptmp[0] = i - 1;
		pport->class1_buf_in = &ptmp[i];
	}

	//--����COS----------------------
	if ((pport->pcfg->soecos & COSONLY) == 0)goto SOE;
	dpa10x_ChkAppbuf(pport, 8 * 16);

	typid = 0;
	plastfrm = 0;
	for (j = 0; j<soenum; j++)
	{
		frm = soe[j].frm;
		pnt = soe[j].pnt;
		pfrm = &pport->pfrm[frm];
		psoeevent = &soe[j].soeevent;

		if (typid != pfrm->pcfg->frmtype)//��һ��SOE
		{
			pport->acd_count++;
			typid = pfrm->pcfg->frmtype;
			ptmp = pport->class1_buf_in;
			plastfrm = pport->class1_buf_in;

			i = 0;
			i++;//len
			if (typid == M_SP_TA_1 || typid == M_SP_TB_1)
				ptmp[i++] = M_SP_NA_1;		//ע���TYPEIDΪNA
			else ptmp[i++] = M_DP_NA_1;
			ptmp[i++] = 1;//inf num
			ptmp[i++] = SPONT;
			if (pport->pcfg->causelen>1)ptmp[i++] = 0;
			ptmp[i++] = (uint8)pport->pcfg->commaddr;
			if (pport->pcfg->commaddrlen>1)ptmp[i++] = (uint8)(pport->pcfg->commaddr >> 8);
		}
		else             //����soe
		{
			ptmp = plastfrm;
			ptmp[2]++;//inf num
			i = ptmp[0] + 1;
		}

		inf = pfrm->pcfg->frminf + pnt;
		if (pport->pcfg->inflen == 3)
		{
			ptmp[i++] = inf; ptmp[i++] = inf >> 8; ptmp[i++] = inf >> 16;
		}
		else { ptmp[i++] = inf; ptmp[i++] = inf >> 8; }

		if (typid == M_SP_TA_1 || typid == M_SP_TB_1)
		{	
			psp = (struDpa10xSp_Cfg*)(pport->pfrm[frm].ppntcfg);
			ptmp[i++] = psoeevent->val^(psp[pnt].option&1);
		}
		else
		{
			pdp = (struDpa10xDp_Cfg*)pfrm->ppntcfg;
			if (pdp[pnt].syspnton >= 0 && pdp[pnt].syspntoff >= 0)
				ptmp[i] = ((db_GetDi(pdp[pnt].syspnton)&1) << 1) + (db_GetDi(pdp[pnt].syspntoff) & 1);
			else if (pdp[pnt].syspnton >= 0 && pdp[pnt].syspntoff < 0)
				ptmp[i] = (db_GetDi(pdp[pnt].syspnton) & 1) ? DP_ON : DP_OFF;
			else if (pdp[pnt].syspnton < 0 && pdp[pnt].syspntoff >= 0)
				ptmp[i] = (db_GetDi(pdp[pnt].syspntoff) & 1) ? DP_OFF : DP_ON;
			else ptmp[i] = 0;//������SOE����˲��ᷢ�����˾����
			ptmp[i]^=(pdp[pnt].option&0x3);
			i++;
		}

		ptmp[0] = i - 1;
		pport->class1_buf_in = &ptmp[i];//ȡ����һ����ַ
	}
	
	//-----����SOE---------------
SOE:	
	if ((pport->pcfg->soecos & SOEONLY) == 0) return;
	dpa10x_ChkAppbuf(pport, 12 * 16);

	typid = 0;
	plastfrm = 0;
	for (j = 0; j<soenum; j++)
	{
		frm = soe[j].frm;
		pnt = soe[j].pnt;//���
		pfrm = &pport->pfrm[frm];
		psoeevent = &soe[j].soeevent;

		if (typid != pfrm->pcfg->frmtype) //!=0��һ��soe
		{
			pport->acd_count++;
			typid = pfrm->pcfg->frmtype;
			ptmp = pport->class1_buf_in;
			plastfrm = pport->class1_buf_in;

			i = 0;
			i++;//len
			ptmp[i++] = typid;
			ptmp[i++] = 1;//inf num
			ptmp[i++] = SPONT;
			if (pport->pcfg->causelen>1)ptmp[i++] = 0;
			ptmp[i++] = (uint8)pport->pcfg->commaddr;
			if (pport->pcfg->commaddrlen>1)ptmp[i++] = (uint8)(pport->pcfg->commaddr >> 8);
		}
		else
		{
			ptmp = plastfrm;
			ptmp[2]++;//inf num
			i = ptmp[0] + 1;
		}

		inf = pfrm->pcfg->frminf + pnt;
		if (pport->pcfg->inflen == 3)
		{
			ptmp[i++] = inf; ptmp[i++] = inf >> 8; ptmp[i++] = inf >> 16;
		}
		else { ptmp[i++] = inf; ptmp[i++] = inf >> 8; }

		if (typid == M_SP_TA_1 || typid == M_SP_TB_1)//����ң��
		{	
			psp = (struDpa10xSp_Cfg*)pfrm->ppntcfg;
			ptmp[i++] = psoeevent->val^(psp[pnt].option&1);
		}
		else//˫��ң��
		{
			pdp = (struDpa10xDp_Cfg*)pfrm->ppntcfg;
			if (pdp[pnt].syspnton >= 0 && pdp[pnt].syspntoff >= 0)//��˫��
				ptmp[i] = ((db_GetDi(pdp[pnt].syspnton)&1) << 1) + (db_GetDi(pdp[pnt].syspntoff) & 1);
			else if (pdp[pnt].syspnton >= 0 && pdp[pnt].syspntoff < 0)//��˫��
				ptmp[i] = (db_GetDi(pdp[pnt].syspnton) & 1) ? DP_ON : DP_OFF;
			else if (pdp[pnt].syspnton < 0 && pdp[pnt].syspntoff >= 0)
				ptmp[i] = (db_GetDi(pdp[pnt].syspntoff) & 1) ? DP_OFF : DP_ON;
			else ptmp[i] = 0;//������SOE����˲��ᷢ�����˾����
			ptmp[i]^=(pdp[pnt].option&0x3);
			i++;
		}

		ms = psoeevent->time.msec + psoeevent->time.sec * 1000;
		ptmp[i++] = ms;
		ptmp[i++] = ms >> 8;
		ptmp[i++] = psoeevent->time.min;
		ptmp[i++] = psoeevent->time.hour;
		if (pfrm->pcfg->frmtype == M_SP_TB_1 || pfrm->pcfg->frmtype == M_DP_TB_1)
		{
			ptmp[i++] = psoeevent->time.day;
			ptmp[i++] = psoeevent->time.mon;
			ptmp[i++] = psoeevent->time.year;
		}

		ptmp[0] = i - 1;
		pport->class1_buf_in = &ptmp[i];
	}
}

/***********************************/

static void	dpa10x_Soe(struDpa10xPort *pport)
{
	static bool needwait = 1;
	//static uint8 last_typeid = 0;
	int event_count;
	SOEEVENT *soeevent;
	int i,j;
	int8 frm;
	int16 pnt;
	int16 otherpnt;
	struDpa10xSoe soetmpbuf[16];//��ʱ���SOE
	uint8 soenum=0;

	event_count = db_GetSoeCount(pport->dpaH);
	if (!event_count) { needwait = 1; return; }
	else if (needwait){ needwait = 0; return; }//�˳�����̬

	if (event_count > 16)event_count = 16;

	for (j = 0; j < event_count; j++)
	{
		soeevent = db_GetSoe(pport->dpaH);
		for (i = 0; i < soenum; i++)//����ԭSOEEVENT�в���˫�㣬�ҵ�������soenum��˫���¼���ʱ�䰴��һ����λ
		{
			if (soetmpbuf[i].otherpnt == soeevent->pnt)
				goto NEXTEVENT;
		}
			
		if (dpa10x_SearchSyspntInFrms(pport, soeevent->pnt, TypeidDi, &frm, &pnt,  &otherpnt, NULL))
		{
			soetmpbuf[soenum].soeevent = *soeevent;
			soetmpbuf[soenum].frm = frm;
			soetmpbuf[soenum].pnt = pnt;
			soetmpbuf[soenum].otherpnt = otherpnt;
			soenum++;
		}
		NEXTEVENT:	continue;
	}

	//��tmpbuf����class1_buf_in
	if (soenum)
		dpa10x_Soe2Class1Data(pport, soetmpbuf, soenum);
}


static void dpa10x_ResetCounters(struDpa10xPort *pport)
{
	pport->class1_buf_in = pport->class1_buf_out = pport->class1_buf;
	pport->class1_buf_tmpout = pport->class1_buf_out;//appl_buf_tmpout�����͸���վ��������վû��Ӧ��ı���
	pport->noacknum = 0;
	pport->acd_count = 0;
	pport->class2_buf_in = pport->class2_buf_out = pport->class2_buf;
	pport->class2_count = 0;

	pport->remote_receive_sn = pport->remote_send_sn = 0;
	pport->local_receive_sn = pport->local_send_sn = 0;
	pport->k_num = 0;
}


/*********SC1161*********SC1161***********************************************/
/*****************************************************************************/

void dpa10x_packetlayer_Nodata(void* dev,struDpa10xPort *pport,uint8 *rsbuf) // rsbuf:��װ������
{
        uint8 *dat_tbuf;
	int i;
        uint16 le,sw;
        uint8 cerID;
        uint8 Kcommand;
        uint16 N;
        static int n=0;
	i = 0;
        le=0;
        uint8 Gateway_R1[8];
        dat_tbuf=pport->dat_tbuf; //û��Ӧ���������ķ�װ������
	switch (rsbuf[0])
        {       
		case GATEWAY_AUTH_REQUST://0x20
                case MASTER_AUTH_REQUST://0x50
                     if(rsbuf[0]==GATEWAY_AUTH_REQUST)
                     {
                        memcpy(Gateway_R1,&rsbuf[3],8);
                        SC1161_Get_Sign(dev,Gateway_R1,sc_rbuf);
                        dat_tbuf[i++] = GDEV_AUTH_ACK;      // 0x21
                     }
                     else
                     {
                          memcpy(pport->Master_R1,&rsbuf[3],8);  //pport
                          SC1161_Get_Sign(dev,pport->Master_R1,sc_rbuf);
                          dat_tbuf[i++] = MDEV_AUTH_ACK;    // 0x51
                     }
                     dat_tbuf[i++] = 0x00;
                     dat_tbuf[i++] = 0x49;
                     memcpy(&dat_tbuf[i], &sc_rbuf[5], 72);
                     i= i + 72;
                     dat_tbuf[i++] =DEV_SIGN_KEY;    //   �ն�ǩ����Կ��ʶ  0x06
                     pport->dat_tlen=i;
                     break;                                   
		case GATEWAY_AUTH_RESPONSE:   //0x22 
                     le=((uint16)rsbuf[1]<<8)+rsbuf[2]; 
                     if(le<65)  
                     {    dpa10x_ERROR(pport,GDEV_AUTH_RESULT,ERRO_SAFE_AUTH);//9090
                          break;
                     }
                     if( SC1161_Verify_MasterSign(dev,&rsbuf[3],sc_rbuf)==FALSE)
                         dpa10x_ERROR(pport,GDEV_AUTH_RESULT,ERRO_SAFE_AUTH); //9090
                     else
                     {
                         pport->F_CONFIRM|=0x04;
                         dpa10x_ERROR(pport,GDEV_AUTH_RESULT,SAFE_SUCCESS);  //0x23
                     }
		     break;                                                               
                case TOOL_AUTH_REQUST://0x30
                      N=((uint16)rsbuf[1]<<8)+rsbuf[2];           
                      memcpy(&temp_buf[n],&rsbuf[6],N-11);
                      n=n+N-11;
                      if(rsbuf[5]<rsbuf[4])     
                      {
                            dpa10x_ERROR(pport,TDEV_FRAME_ACK ,SAFE_SUCCESS);                            
                            return;   
                      }
                      memcpy(Tool_ID,&rsbuf[N-5],8);
                      if( SC1161_Verify_ToolCer( dev,temp_buf,n,sc_rbuf)==FALSE)
                      {
                            dpa10x_ERROR(pport,TDEV_AUTH_ACK,ERRO_SAFE_AUTH);//9090
                            n=0;
                            return;
                      }
                      n=0;
                      SC1161_Get_Rand(dev,sc_rbuf);
                      memcpy(Tool_R1,&sc_rbuf[5],8);
                      dat_tbuf[i++] = TDEV_AUTH_ACK;  //Ӧ������
                      dat_tbuf[i++] = 0x00;
                      dat_tbuf[i++] = 0x08;
                      memcpy(&dat_tbuf[i], &sc_rbuf[5], 8);
                      i= i + 8;
                      pport->dat_tlen=i; 
                      break;
                case TOOL_AUTH_RESPONSE://0x32
                     if(SC1161_Verify_ToolSign(dev,&rsbuf[3],sc_rbuf)==TRUE)
                     {
                            dpa10x_ERROR(pport,TDEV_AUTH_RESULT,SAFE_SUCCESS);
                            pport->F_CONFIRM|=0x02;
                     }
                     else
                            dpa10x_ERROR(pport,TDEV_AUTH_RESULT,ERRO_SAFE_AUTH);//9090
                     break;   
                case TOOL_DEV_VERSION://0x36
                case TOOL_DEVCER_RESULT://0x44   �յ���վ���͵��ն�֤�鵼����� �����������ն����к�
                     if(rsbuf[0]==TOOL_DEVCER_RESULT&&pport->rlen<14)break;
                     flashshell_Read(MEMADDR_FLASH_FIXPARA + FIXPARA_SN_IDX, temp_buf, 32);//���ն����к�                         

                     dat_tbuf[i++] = TDEV_DEV_VERSIONACK;//0x37
                     dat_tbuf[i++]=0x00;
                     dat_tbuf[i++]=0x18;
                     memcpy(&dat_tbuf[i],temp_buf, 24);
                     i = i + 24;
                     pport->dat_tlen=i;
                     break; 
                case TOOL_PUBLICKEY_GET://0x3A 
                     SC1161_PubKEY_GET(dev,sc_rbuf);
                     le=((uint16)sc_rbuf[3]<<8)+sc_rbuf[4];
                     temp_buf[i++] = TDEV_PUBLICKEY_RETURN;// 0x3B
                     temp_buf[i++]=le>>8;
                     temp_buf[i++]=le;
                     memcpy(&temp_buf[i],&sc_rbuf[5],le);
                     i=i+le;
                     SC1161_Encrypt_Tool(dev,Tool_ID,i,temp_buf,Tool_R1,sc_rbuf);
                     le=((uint16)sc_rbuf[3]<<8)+sc_rbuf[4];                     
                     memcpy(dat_tbuf,&sc_rbuf[5], le);	
                     pport->dat_tlen=le;
                     break;    
               case TOOL_CER_IMPORT://0x3E        //֤�鵼��   
		     N=((uint16)rsbuf[1]<<8)+rsbuf[2];
                     memcpy(&temp_buf[n],&rsbuf[6],N-3);
                     n=n+N-3;
                     if(rsbuf[5]<rsbuf[4])     
                     {
                           dpa10x_ERROR(pport,TDEV_FRAME_ACK ,SAFE_SUCCESS);    //0x45                       
                           return;    
                     }
                     cerID=rsbuf[3];
                     if(SC1161_Updata_Cer(dev,cerID,n,temp_buf,sc_rbuf)==TRUE)
                          dpa10x_ERROR(pport,TDEV_CER_IMPORTNACK,SAFE_SUCCESS);   //0x3D
                     else
                            dpa10x_ERROR(pport,TDEV_CER_IMPORTNACK,ERRO_SAFE_CERINPUT);//9093
                      n=0;
                      break;
                case TOOL_CER_REWRITE: //0x40
                     if(SC1161_Rewrite_DEVCer(dev,sc_rbuf)==TRUE)                 
                        dpa10x_ERROR(pport,TDEV_CER_REWRITEACK,SAFE_SUCCESS); //0x41
                      break;   
                case TDEV_FRAME_ACK ://0x45
                     sw=((uint16)rsbuf[3]<<8)+rsbuf[4];
                     if(sw==0x9000)
                        pport->F_SendCER=1;
                      break;                 
                case TOOL_DATA_GET://0x48
                      temp_buf[i++] = TDEV_DATA_RETURN;//Ӧ������
		      temp_buf[i++]=pport->dat_rlen>>8;
                      temp_buf[i++]=pport->dat_rlen;
                      memcpy(&temp_buf[i],&rsbuf[3],pport->dat_rlen);
                      i=i+le;
                      SC1161_Encrypt_Tool(dev,Tool_ID,pport->dat_rlen,&rsbuf[3],Tool_R1,sc_rbuf);
                      le=((uint16)sc_rbuf[3]<<8)+sc_rbuf[4];                     
		      memcpy(dat_tbuf,&sc_rbuf[5], le);	
		      pport->dat_tlen=le;  
                       break;
               case TOOL_SIGN_REQUEST://0x3c
                      N=((uint16)rsbuf[1]<<8)+rsbuf[2]-2;
                      memcpy(&temp_buf[n],&rsbuf[5],N);
                      n+=N;
                      if(rsbuf[3]>rsbuf[4])
                      {
                          dpa10x_ERROR(pport,TDEV_FRAME_ACK ,SAFE_SUCCESS);  
                          return;
                      }
                      SC1161_Verify_FileSign(dev,n,temp_buf,sc_rbuf);
                       n=0;
                      le=((uint16)sc_rbuf[3]<<8)+sc_rbuf[4];  
                      dat_tbuf[i++]=TDEV_SIGN_RETURN;
                      dat_tbuf[i++]=le>>8;
                      dat_tbuf[i++]=le;
		      memcpy(&dat_tbuf[i],&sc_rbuf[5], le);	
                      i=i+le;
		      pport->dat_tlen=i;  
                      break;
		case MASTER_AUTH_RESPONSE://0x52
                      le=((uint16)rsbuf[1]<<8)+rsbuf[2]; 
                      if(le<65)  
                      {    dpa10x_ERROR(pport,MDEV_AUTH_RESULT,ERRO_SAFE_AUTH);//9090
                           break;
                      }
                      if(SC1161_Verify_MasterSign(dev,&rsbuf[3],sc_rbuf)==TRUE)
                      {
                              dpa10x_ERROR(pport,MDEV_AUTH_RESULT,SAFE_SUCCESS);
                              pport->F_CONFIRM|=0x01;
                      }
                      else
                              dpa10x_ERROR(pport,MDEV_AUTH_RESULT,ERRO_SAFE_AUTH);//9090
                      break;
                case TOOL_SN_GET://0x38
		case MASTER_SN_GET://54
                      SC1161_Get_SN(dev,sc_rbuf);//
                      if(rsbuf[0]==TOOL_SN_GET)
                              dat_tbuf[i++] = TDEV_SN_RETURN;//Ӧ������
                      else
                              dat_tbuf[i++] = MDEV_SN_RETURN;//Ӧ������
                      dat_tbuf[i++]=0x00;
                      dat_tbuf[i++]=0x08;
                      memcpy(&dat_tbuf[i], &sc_rbuf[5], 8);
                      i = i + 8;
                      pport->dat_tlen=i;
                      break;
                case TOOL_KEY_VERSION://0x34
                case MASTER_KEY_VERSION://60
                      SC1161_Get_Version(dev,sc_rbuf);
                      Key_Version=sc_rbuf[5];
                       SC1161_Get_Rand(dev,sc_rbuf);
                      if(rsbuf[0]==TOOL_KEY_VERSION)
                              dat_tbuf[i++] = TDEV_KEY_VERSIONACK;//Ӧ������
                      else
                              dat_tbuf[i++] = MDEV_KEY_VERSIONACK;//Ӧ������
                      dat_tbuf[i++]=0x00;
                      dat_tbuf[i++]=0x09;
                      dat_tbuf[i++] = Key_Version;  // 
                      memcpy(&dat_tbuf[i],&sc_rbuf[5], 8);
                      i = i + 8;
                      pport->dat_tlen=i;
                      break;
                case  TOOL_KEY_RECOVERY://0x46  ��Կ�ָ�
                      Kcommand=0x02;
                      le=((uint16)rsbuf[1]<<8)+rsbuf[2];                      
                      if(SC1161_Updata_Key(dev,Kcommand,le,&rsbuf[3],sc_rbuf)==TRUE)
                      {
                           Key_Version=0;//
                           dpa10x_ERROR(pport,TDEV_KEY_RECOVERYACK,SAFE_SUCCESS); 
                           SC1161_Rewrite_DEVCer(dev,sc_rbuf);
                      }
                      else
                           dpa10x_ERROR(pport,TDEV_KEY_RECOVERYACK,ERRO_SAFE_KEYUPDATE);
                      break;
               case  MASTER_KEY_UPDATE://0x62  ��Կ����
                       Kcommand=0x00;
                      le=((uint16)rsbuf[1]<<8)+rsbuf[2]; 
                      if(le<246)//0xF6  
                      {    dpa10x_ERROR(pport,MDEV_KEY_UPDATEACK,ERRO_SAFE_KEYUPDATE);//9090
                           break;
                      }  
                      if(SC1161_Updata_Key(dev,Kcommand,le,&rsbuf[3],sc_rbuf)==TRUE)
                      {
                            Key_Version=rsbuf[3];
                           dpa10x_ERROR(pport,MDEV_KEY_UPDATEACK,SAFE_SUCCESS); 
                      }
                      else
                           dpa10x_ERROR(pport,MDEV_KEY_UPDATEACK,ERRO_SAFE_KEYUPDATE);
                      break;
               case  MASTER_KEY_RECOVERY://0x64  ��Կ�ָ�
                      Kcommand=0x01;
                      le=((uint16)rsbuf[1]<<8)+rsbuf[2]; 
                      if(le<246)//0xF6  
                      {    dpa10x_ERROR(pport,MDEV_KEY_UPDATEACK,ERRO_SAFE_KEYUPDATE);//9090     //����ǩ���ı���
                           break;
                      } 
                      if(SC1161_Updata_Key(dev,Kcommand,le,&rsbuf[3],sc_rbuf)==TRUE)
                      {
                           Key_Version=rsbuf[3];
                           dpa10x_ERROR(pport,MDEV_KEY_RECOVERYACK,SAFE_SUCCESS); 
                           SC1161_Rewrite_DEVCer(dev,sc_rbuf);
                      }
                      else
                           dpa10x_ERROR(pport,MDEV_KEY_RECOVERYACK,ERRO_SAFE_KEYUPDATE);
                      break;
                case MASTER_CER_UPDATE://70
                      N=((uint16)rsbuf[1]<<8)+rsbuf[2];
                      memcpy(&temp_buf[n],&rsbuf[6],N-3);
                      n=n+N-3;
                      if(rsbuf[5]<rsbuf[4])     
                      {
                            pport->F_NeedACK=0;  //ֱ���յ����еı��ĲŻظ����½��
                            return;   
                      }
                     if( SC1161_Decrypt(dev,n,temp_buf,pport->Master_R1,sc_rbuf)==FALSE)
                     {
                            dpa10x_ERROR(pport,MDEV_CER_UPDATEACK,ERRO_SAFE_CERUPDATE); 
                            n=0;
                             return;
                     }
                      n=0;
                      cerID=sc_rbuf[5];
                      le=((uint16)sc_rbuf[3]<<8)+sc_rbuf[4];
                      memcpy(temp_buf,&sc_rbuf[5],le);
                      if(SC1161_Verify_CerSign(dev,le,temp_buf,sc_rbuf)==TRUE)
                      {
                          le=le-72;

                          if(SC1161_Updata_Cer(dev,cerID,le,&temp_buf[1],sc_rbuf)==TRUE)
                                  dpa10x_ERROR(pport,MDEV_CER_UPDATEACK,SAFE_SUCCESS); 
                          else
                                   dpa10x_ERROR(pport,MDEV_CER_UPDATEACK,ERRO_SAFE_CERUPDATE); 
                      }
                      else
                          dpa10x_ERROR(pport,MDEV_CER_UPDATEACK,ERRO_SAFE_CERUPDATE);     
                      break;
                case MASTER_CER_DOWNLOAD://72
                     cerID=rsbuf[3];        
                     cerID=0x06;              
                     if(rsbuf[5]<=rsbuf[4])
                     {
                          N=((uint16)rsbuf[1]<<8)+rsbuf[2];
                          memcpy(&temp_buf[n],&rsbuf[6],N-3);
                          n=n+N-3;
                         if(rsbuf[5]<rsbuf[4])
                         {
                               pport->F_NeedACK=0;
                                return;
                         }
                     }  
                    if(SC1161_Updata_Cer(dev,cerID,n,temp_buf,sc_rbuf)==TRUE)
                             dpa10x_ERROR(pport,MDEV_CER_DOWNLOADACK,SAFE_SUCCESS);
                    else
                            dpa10x_ERROR(pport,MDEV_CER_DOWNLOADACK,ERRO_SAFE_CERUPDATE);//��װʧ��
                    n=0;             
                    break;                      
	   case MASTER_CER_GET://74
           case TOOL_DEVCER_GET://0x42
		  if(SC1161_Get_Cer(dev,sc_rbuf)==TRUE)
                  {
                      le=((uint16)sc_rbuf[3]<<8)+sc_rbuf[4];
                      memcpy(Dev_Cer,&sc_rbuf[5],le);
                      DevCer_len=le;
                      pport->F_SendCER=1;
                  }
		  break;        
	   case MASTER_CER_GETACK://76
		  // sw=((uint16)rsbuf[3]<<8)+rsbuf[4];
		   //if(sw==0x9000)pport->F_NeedACK=0; 
		   //if(sw!=0x9000)          //��ô����
		  break;
          default:break;
                    
        }     
}






/********************************************************************/
// ���ϳ���Ϊ���ֱ��ġ����ֹ��ܵ��߼���Ϊ101 104���ò��֣���������Ҫ�޸ģ����Ƿ���BUG
// ���³���Ϊ��Լ��·��ͨѶ���ܣ�����ֻ�Ķ�ͨѶDRIVER�ӿں�Recv()��Send()���û��ƣ�
// ���Ķ���Э�鴦���йصĲ��֡�
/********************************************************************/


/*********101**********************101*****************************************************************/
/******************************************************************************************************/


static bool dpa101_CheckRxFrm(struDpa10xPort *pport)
{
	uint8 *rbuf;
	uint16 rlen, len;
	uint8 tmpb;
	uint16 tmpi16;
	uint8 rn;

	rn = 0;
	rbuf = pport->dat_rbuf;
	if (pport->pcfg->commkey)
	{
          	len = rbuf[1];
		rn = rn + 2;
	} 

	if (rbuf[rn] != START1 && rbuf[rn] != START2)return FALSE;

	rlen = (rbuf[rn] == START1) ? (4 + pport->pcfg->linkaddrlen) : (rbuf[rn + 1] + 6);//�յ���ԭʼ���ĵĳ���

	if (pport->pcfg->commkey&&rlen != len)return FALSE; //�жϼ��ܹ�����ԭʼ���ĳ���
	if (rbuf[rn + rlen - 1] != STOP) return FALSE;//�ж�ֹͣλ

	tmpb = (rbuf[rn] == START1) ? dpa10x_Crc(&rbuf[rn + 1], rlen - 3) : dpa10x_Crc(&rbuf[rn+4], rlen - 6);//MOD256
	if (tmpb != rbuf[rn + rlen - 2]) return FALSE;//�ж�У��λ

	if (pport->pcfg->linkaddrlen == 1)//�ж���·��ַ�ֽ���
		tmpi16 = (rbuf[rn] == START1) ? rbuf[rn + 2] : rbuf[rn + 5];//tmpi:��·��ַ
	else tmpi16 = (rbuf[rn] == START1) ? *(int16*)&rbuf[rn + 2] : *(int16*)&rbuf[rn + 5];//��·��ַ��ռ���ֽ���ֻ��1��2��
	if (pport->pcfg->linkaddr != tmpi16 && pport->pcfg->linkaddr != BROARDCAST)return FALSE;//�ж���·��ַ��������ҵ���·��ַ��Ҳ���ǹ㲥��ַ

	return TRUE;
}

static void dpa101_PortOpen(struDpa10xPort *pport)
{
 	if (pport->pcfg->portnr1 == 0)pport->portsts1 = PORTSTS_ERR;
	else if  (pport->portsts1 == 0)
	{
        if (uart_Init(pport->pcfg->portnr1, pport->pcfg->baud1, pport->pcfg->parity, 1, RXSIZE, NULL))
			pport->portsts1 = PORTSTS_RUN;
		else pport->portsts1 = PORTSTS_ERR;
	}

	if (pport->pcfg->portnr2 == 0)pport->portsts2 = PORTSTS_ERR;
	else if (pport->portsts2 == 0)
	{
		if (uart_Init(pport->pcfg->portnr2, pport->pcfg->baud2, pport->pcfg->parity, 1, RXSIZE, NULL))
			pport->portsts2 = PORTSTS_RUN;
		else pport->portsts2 = PORTSTS_ERR;
	}
}

/********************************************************************/
//����ִ��
static void dpa101_Scan(struDpa10xPort *pport)
{
	uint32 tick;
 
	if (pport->portsts1 != PORTSTS_RUN && pport->portsts2 != PORTSTS_RUN)return;

	tick = glb_sysTick;
	if (tick - pport->scan_timetick < DPA10x_SCAN_INTERVAL)return;//150ms 
	pport->scan_timetick = tick;

	if(pport->DTStart) dpa10x_Soe(pport);//����������ٽ�����ɨ��SOE

	//����δ���ң��
	if (pport->doevent.sts && tick - pport->doevent.timetick>DPA10x_DOTIMEOUT)
		memset(&pport->doevent, 0, sizeof(struDpa10xDoevent));

	//����δ��ɲ�������
	if (pport->SzDzEvent.f_select && tick - pport->SzDzEvent.selecttime > DPA10x_DOTIMEOUT)
		memset(&pport->SzDzEvent, 0, sizeof(struDpa10xSzDzEvent));
	
	//����֤���������֤���
        if(tick-pport->Tool_Rectick>TOOL_TIMEOUT) 
  	{
              pport->F_CONFIRM&=~0x02;
              memset(Tool_ID,0,8);
              memset(Tool_R1,0,8);
        }
	
	//ͨѶ��ͨѶ״̬
	if (pport->portsts1 == PORTSTS_RUN && tick - pport->porttick1 > 10000)
	{
		//PutLed(0);
		pport->porttick1 = tick;
	}
}

/********************************************************************/

static void dpa101_Send(struDpa10xPort *pport)
{
	uint8 *tbuf;
        uint8 *dat_tbuf;
	uint8 local_ctrl;
	int16 asdu_len=0;
	int16 i,j,tn,len;
        uint8 crc;
        uint8 typid,TotalNum,N;
        i=0;
        tn=0;
        uint32 tick;
        static int k=0,num=0;
         
       N=200; //���°�֡�Ĵ�С        
       tbuf = pport->tbuf;
       dat_tbuf=pport->dat_tbuf;
       if (pport->f_resend)	goto COMMSEND;
       
        if (pport->pcfg->commkey&&pport->F_NeedACK==1)
        {   
               if(pport->F_SendCER)        //�ն�֤������
              {         
                    tick=glb_sysTick;
                   if((tick-pport->sendcer_tick)<1000)return;
                   pport->sendcer_tick=tick;
                   TotalNum=DevCer_len/N+1;
                   k++;
                   if(k==TotalNum)
                   {  
                      pport->F_NeedACK=0; 
                      pport->F_SendCER=0;
                      len=DevCer_len-num;
                   }
                   else
                      len=N;
                   tbuf[i++] = 0xEB;
                    i=i+2;
                   tbuf[i++] = 0xEB;
                   tbuf[i++] = pport->Mess_type >> 8;
                   tbuf[i++] = pport->Mess_type&0xF0;
                   if(pport->Mess_type&0xC0)//TOOL
                   {
                        tbuf[i++] = TDEV_DEVCER_RETURN;//Ӧ������  43
                         pport->F_SendCER=0;
                   }
                   else
                        tbuf[i++] = MDEV_CER_RETURN;//Ӧ������  75
                   tbuf[i++] =(3+len)>>8;
                   tbuf[i++] =(3+len);
                   tbuf[i++]=0x06;                   //�ն�֤���ʶ0x06
                   tbuf[i++]=TotalNum;
                   tbuf[i++]=k;
                   memcpy(&tbuf[i],&Dev_Cer[num],len);
                   num+=len;
                   i+=len;
                  if(k==TotalNum)
                  {     
                    k=0;
                    num=0;
                  }
                   
                   crc=dpa10x_Crc(&tbuf[4], i-4);
                   tbuf[i++]=crc;
                   tbuf[i++]=0xD7; 
                   tbuf[1]=(i-6)>>8;
                   tbuf[2]=i-6;
                   pport->tlen=i;
                   goto COMMSEND;
              }         
              else  if (pport->App_type >= 0x20&&pport->dat_tlen)
                {
                     pport->F_NeedACK=0;  
                    tbuf[i++] = 0xEB;
                    tbuf[i++] = (pport->dat_tlen + 2) >> 8;
                    tbuf[i++] = pport->dat_tlen + 2;
                    tbuf[i++] = 0xEB;
                    tbuf[i++] = pport->Mess_type >> 8;
                    if(pport->App_type==0x3A||pport->App_type==0x49)
                    {
                        pport->Mess_type&=0xF0;
                        tbuf[i++] = pport->Mess_type|0x08;
                    }
                    else
                        tbuf[i++] = pport->Mess_type&0xF0;
                    memcpy(&tbuf[i], dat_tbuf, pport->dat_tlen);//dat_tbuf��������������
                    i = i + pport->dat_tlen;
                     pport->App_type =0;
                     crc=dpa10x_Crc(&tbuf[4], i-4);
                     tbuf[i++]=crc;
                     tbuf[i++]=0xD7; 
                     pport->tlen=i;
                    goto COMMSEND;
                }
              else
              {
                    pport->F_NeedACK=0; 
                    tbuf[i++] = 0xEB;
                    i = i + 2;//����
                    tbuf[i++] = 0xEB;
                    tn=2;
              }
        }
        if (pport->f_sendframe == 0)return;

	switch (pport->f_sendframe)
	{
	case F_CONFIRM_SEND:
		local_ctrl = CONFIRM_SEND;
		break;
	case F_RESPOND_LINK_STATUS:                        
		local_ctrl = RESPOND_LINK_STATUS;
		break;
	case F_RESPOND_CLASS1:   // 
		asdu_len = dpa10x_GetClass1Data(pport, &dat_tbuf[tn+5 + pport->pcfg->linkaddrlen]);//Ҫ���͵�ASDU����
		if (!asdu_len)
			local_ctrl = RESPOND_NODATA;
		else local_ctrl = RESPOND_DATA;
		break;
	case F_RESPOND_CLASS2:   // 
		asdu_len = dpa10x_GetClass2Data(pport, &dat_tbuf[tn+5 + pport->pcfg->linkaddrlen]);
		if (!asdu_len)
			local_ctrl = RESPOND_NODATA;
		else local_ctrl = RESPOND_DATA;
		break;
	default:
		local_ctrl = RESPOND_NODATA;
                
		break;
	}
	if (!asdu_len)//10��ͷ�̶�֡���Ļ�Ӧ
	{     
                j=tn;
		dat_tbuf[j++] = START1;
		dat_tbuf[j] = local_ctrl;
		if (pport->acd_count - pport->noacknum)dat_tbuf[j] |= ACD;//
		if (pport->gi_grp || pport->ci_grp)dat_tbuf[j] |= ACD;
		j++;
		dat_tbuf[j++] = (uint8)pport->pcfg->linkaddr;
		if (pport->pcfg->linkaddrlen>1)dat_tbuf[j++] = (uint8)(pport->pcfg->linkaddr >> 8);
		crc = dpa10x_Crc(&dat_tbuf[tn+1], j - tn-1);
                dat_tbuf[j++] = crc;
		dat_tbuf[j++] = STOP;
		if (!pport->pcfg->commkey)
		{
			memcpy(tbuf, dat_tbuf, j);
                         pport->tlen = j;
			goto COMMSEND;
		}                                 
                dat_tbuf[0]=APP0;
                dat_tbuf[1]=j-2;   
                dat_tbuf[j++]=0x00; //��Ϣ��չ��
                dat_tbuf[j++]=0x00;
                
                tbuf[i++] = pport->Mess_type >> 8;
                tbuf[i++] = pport->Mess_type&0xF0;
                memcpy(&tbuf[i],dat_tbuf,j);
                i=i+j;          
	}
	else 	
	{
                j=tn;
		dat_tbuf[j++] = START2;
		dat_tbuf[j++] = asdu_len + 1 + pport->pcfg->linkaddrlen;
		dat_tbuf[j++] = asdu_len + 1 + pport->pcfg->linkaddrlen;
		dat_tbuf[j++] = START2;
		dat_tbuf[j] = local_ctrl;
		if (pport->acd_count - pport->noacknum)dat_tbuf[j] |= ACD;
		if (pport->gi_grp || pport->ci_grp)dat_tbuf[j] |= ACD;
		j++;
		dat_tbuf[j++] = (uint8)pport->pcfg->linkaddr;
		if (pport->pcfg->linkaddrlen > 1)dat_tbuf[j++] = (uint8)(pport->pcfg->linkaddr >> 8);
		j += asdu_len;
		crc = dpa10x_Crc(&dat_tbuf[tn+4], j-tn-4);
                dat_tbuf[j++] = crc;
		dat_tbuf[j++] = STOP;
		if (!pport->pcfg->commkey)
		{
			memcpy(tbuf, dat_tbuf, j);
                        pport->tlen = j;
			goto COMMSEND;
		}
                tbuf[i++] = pport->Mess_type >> 8;
                tbuf[i++] = pport->Mess_type|0x08;
                dat_tbuf[1]=j-2;                
                uint8 le;
                typid=dat_tbuf[2+5+pport->pcfg->linkaddrlen];
                if(((typid==C_SC_NA_1||typid==C_DC_NA_1)&&dat_tbuf[j-3]&0x80)//ң��ѡ��ȷ��
                   ||((typid==C_WS_NA_1)&&(dat_tbuf[j-3]&0x80))||(typid==F_SR_NA_1&&dat_tbuf[j-3]&0x80))//����Ԥ��ȷ�ϣ���������ȷ��
                {  
                                 dat_tbuf[0]=APP2;
                                 dat_tbuf[j++]=0x00; //��Ϣ��չ������
                                 dat_tbuf[j++]=0x08;  
                                 
                                 SC1161_Get_Rand(data_sc1161,sc_rbuf);
                                 memcpy( pport->Send_Rand,&sc_rbuf[5],8);
                                 memcpy(&dat_tbuf[j], pport->Send_Rand,8);
                                 j=j+8;                      
                 }
                else
                {
                         dat_tbuf[0]=APP0;
                         dat_tbuf[j++]=0x00; //��Ϣ��չ������
                         dat_tbuf[j++]=0x00;
                }                  
                SC1161_Encrypt(data_sc1161,j,dat_tbuf,pport->Master_R1,sc_rbuf); 
                le=((uint16)sc_rbuf[3]<<8)+sc_rbuf[4];
                memcpy(&tbuf[i],&sc_rbuf[5],le);
                  i=i+le;            
       }   
       if(i>=5)
       {
           crc=dpa10x_Crc(&tbuf[4], i-4);
           tbuf[i++]=crc;
           tbuf[i++]=0xD7; 
           tbuf[1]=(i-6)>>8;
           tbuf[2]=i-6;
           pport->tlen = i;
       }

COMMSEND:

	if (pport->activeport == 0)
	{
		uart_Send(pport->pcfg->portnr1, pport->tbuf, pport->tlen);
		glb_PutComCode(pport->pcfg->portnr1, pport->tbuf, pport->tlen, MONICOMM_DIR_TX);
		//PutLed(1);//�˿�ͨѶ״̬����ͨѶ
		pport->porttick1 = glb_sysTick;
	}
	else
	{
		uart_Send(pport->pcfg->portnr2, pport->tbuf, pport->tlen);
	}

	//�巢�ͱ�־
	pport->f_sendframe = 0;
	        pport->dat_tlen=0;
}


static void dpa101_Recv(struDpa10xPort *pport)
{
	int i;
	uint8 *rbuf,*dat_rbuf;
	uint8 remote_ctrl;
	uint8 *ptmp;
        uint16 rn;
        uint16 dat_rlen,le;
        uint8 tmpb1 ;
        uint32 tick;
        SYS_TIME64  tm,rec_tm;
        uint8 Rec_Rand[8];
        
        rn=0;   
	rbuf = pport->rbuf;
        dat_rbuf=pport->dat_rbuf;

 	if (pport->portsts1 == PORTSTS_RUN)
	{
		pport->rlen = uart_RecvFrame(pport->pcfg->portnr1, rbuf);
		if (pport->rlen)
		{
			glb_PutComCode(pport->pcfg->portnr1, rbuf, pport->rlen, MONICOMM_DIR_RX);
			pport->activeport = 0;
			goto CheckRxFrm;
		}
	}
	if (pport->portsts2 == PORTSTS_RUN)
	{
		pport->rlen = uart_RecvFrame(pport->pcfg->portnr2, rbuf);
		if (pport->rlen)
		{
			//glb_PutComCode(pport->pcfg->portnr2, rbuf, pport->rlen, MONICOMM_DIR_RX);
			pport->activeport = 1;
			goto CheckRxFrm;
		}
	}
	return;

CheckRxFrm:
	if (pport->pcfg->commkey)//commkeyΪ1ʱ�����м���ͨѶ
	{ 
                tick = glb_sysTick;
                dat_rlen = ((uint16)rbuf[1] << 8) + rbuf[2]-2; //��װ�����򳤶�
		if (rbuf[0] != 0xEB || rbuf[3] != 0xEB || rbuf[dat_rlen+7] != 0xD7) return ;//��ⱨ����ʼ�ͽ�����
		tmpb1 = dpa10x_Crc(&rbuf[4], dat_rlen+2);
		if (tmpb1 != pport->rbuf[dat_rlen+6]) return ;          //У�鲻��ȷ������
                
                pport->F_NeedACK=1;
		pport->Mess_type = ((uint16)rbuf[4] << 8) + rbuf[5];
		if ((pport->Mess_type & 0x0F)==0x09)//���� ���н���
		{
			if(SC1161_Decrypt(data_sc1161, dat_rlen, &rbuf[6], pport->Master_R1, sc_rbuf)==FALSE)
			{
				 dpa10x_ERROR(pport,ERROR,ERRO_BUSS_DECRYP);  // �쳣����:MAC���� (����ʧ��)   ��101����
					return;
			}
			le = ((uint16)sc_rbuf[3] << 8) + sc_rbuf[4];
			memcpy(dat_rbuf, &sc_rbuf[5], le);
			pport->App_type = dat_rbuf[0];
		}
                else if ((pport->Mess_type & 0x0F)==0x0A)//���� ���н���
		{
                       if( SC1161_Decrypt_Tool(data_sc1161,Tool_ID,dat_rlen,&rbuf[6],Tool_R1,sc_rbuf)==FALSE)   //if(SC1161_Decrypt(data_sc1161, dat_rlen, &rbuf[6],Tool_R1, sc_rbuf)==FALSE)
			{
				 dpa10x_ERROR(pport,ERROR,ERRO_BUSS_DECRYP);  // �쳣����:MAC���� (����ʧ��)   �ı���
				 return;
			}
			le = ((uint16)sc_rbuf[3] << 8) + sc_rbuf[4];
			memcpy(dat_rbuf,  &sc_rbuf[5], le);
			pport->App_type = dat_rbuf[0];
		}
		else
		{
			memcpy(dat_rbuf, &rbuf[6], dat_rlen);//����           //dat_rbuf�ǽ��ܺ��Ӧ������+Ӧ��������+��Ϣ��ȫ��չ��
			pport->App_type = dat_rbuf[0];
		}
                
                if(pport->Mess_type&0xC0==LINK_MASTER)
                {
                      if(!(pport->F_CONFIRM&0x01)&&(pport->App_type==0x62||pport->App_type==0x64||pport->App_type==0x70))//��Կ���£��ָ���֤�����
                      {
                               dpa10x_ERROR(pport,ERROR,ERRO_BUSS_SAFEPROCESS);  // �쳣����:δͨ����ȫ��֤ ����վ101����  9107
                               return; 
                      } 
                }
                else if(pport->Mess_type&0xC0==LINK_TOOL)
               {
                      pport->Tool_Rectick=tick;
                      if(!(pport->F_CONFIRM&0x02)&& (pport->App_type==0x34||pport->App_type==0x42||pport->App_type==0x46))// ��ȡ��Կ�汾����Կ�ָ���
                      {
                                dpa10x_ERROR(pport,ERROR,ERRO_BUSS_SAFEPROCESS); // �쳣����:δͨ����ȫ��֤ ��ά������101����  9107
                                return;  
                      }
                }
		pport->dat_rlen=le;
		if(pport->App_type==0x08) //��������֤
                {
                     glb_GetDateTime(&tm);
                     rec_tm=*(SYS_TIME64*)&dat_rbuf[dat_rlen-79];
                     if(((rec_tm.hour*3600+rec_tm.min*60+rec_tm.sec)-(tm.hour*3600+tm.min*60+tm.sec)>60)
                            ||((tm.hour*3600+tm.min*60+tm.sec)-(rec_tm.hour*3600+rec_tm.min*60+rec_tm.sec)>60))
                     {
                              dpa10x_ERROR(pport,ERROR,ERRO_BUSS_TIME);
                              return;
                     }
                     memcpy(Rec_Rand,&dat_rbuf[dat_rlen-73],8);
                     if( memcmp(Rec_Rand,pport->Send_Rand,8)!=0)
                     {
                              dpa10x_ERROR(pport,ERROR,ERRO_BUSS_RAND);
                              return;
                     }
                     if (SC1161_Verify_DevSign(data_sc1161, dat_rlen, dat_rbuf, sc_rbuf) == FALSE)
                     {  
                              dpa10x_ERROR(pport,ERROR,ERRO_BUSS_SIGN);
                              return;
                      } 
                      pport->F_NeedACK=0;
                      memcpy(SverData,&sc_rbuf[19],le-14);//SverData:����������֤�����е�ǩ�����+ǩ����Կ 64+1
                      return;
                }
		else if(pport->App_type >= 0x20)
		{
			dpa10x_packetlayer_Nodata(data_sc1161, pport, dat_rbuf);
			return;
		}
		rn += 2;
	}
	else
            memcpy(dat_rbuf,pport->rbuf,pport->rlen);
        
        if(pport->pcfg->commkey&&(pport->Mess_type&0xC0)==LINK_MASTER&&!(pport->F_CONFIRM&0x01))
        {
             dpa10x_ERROR(pport,ERROR,ERRO_BUSS_SAFEPROCESS);  // �쳣����:δͨ����ȫ��֤ ����վ101����  9107
             return; 
        }
        
        if(dpa101_CheckRxFrm(pport)==FALSE)return; 
        

	remote_ctrl = (dat_rbuf[rn] == START1) ? dat_rbuf[rn+1] : dat_rbuf[rn+4];//��·������
        

	
	//Ϊ���Ժ�������Ӵ���RESEND
	//if (pport->last_remote_fcb & FCV && remote_ctrl & FCV &&
	//	(pport->last_remote_fcb&FCB) == (remote_ctrl&FCB))
	//{
	//	pport->f_resend++;
	//	if (pport->f_resend < 3) return;//<3ȥRESEND,����f_resend��0
	//}

	pport->f_resend = 0;

	//����������FCV��Ч����ѯ�ʣ���FCBλ��ת������һ�η�����CLASS1���ݣ���pport->class1_buf_out = pport->class1_buf_tmpout
	if ( /*pport->last_remote_fcb & FCV && remote_ctrl & FCV &&
		(pport->last_remote_fcb&FCB) != (remote_ctrl&FCB) &&*/ pport->class1_buf_tmpout > pport->class1_buf_out) //
	{
		if (pport->noacknum)
		{
			pport->class1_buf_out = pport->class1_buf_tmpout;
			pport->acd_count -= pport->noacknum;
			pport->noacknum = 0;
		}
		if (pport->acd_count == 0)
		{
			pport->class1_buf_out = pport->class1_buf_in = pport->class1_buf;
			pport->class1_buf_tmpout = pport->class1_buf_out;
		}
	}
	

	pport->last_remote_fcb = remote_ctrl&(FCB + FCV);//��¼���һ�ε�FCB��FCV��״̬

	if (dat_rbuf[rn] == START2)//��������appl��asdu
	{
		if(pport->pcfg->commkey&&!(pport->Mess_type&0x08))
		{       
			  dpa10x_ERROR(pport,ERROR,ERRO_BUSS_NONSTANDARD);
			  return;
		}
		dpa10x_AppLayer(pport, &dat_rbuf[rn+5 + pport->pcfg->linkaddrlen], dat_rbuf[rn+1] - 1 - pport->pcfg->linkaddrlen,
			               ((remote_ctrl & 0xf) == SEND_NOREPLY_DATA) ? 0 : 1);
	}  
        remote_ctrl&=0x0f;
	switch (remote_ctrl)//�ж�Ӧ��֡������
	{
	case SEND_RESET_LINK:// 0 ��λԶ����·

		pport->f_sendframe = F_CONFIRM_SEND;//1  ȷ��֡�Ĺ�����Ϊ0
		dpa10x_ResetCounters(pport);
		{
			i = 0;
			ptmp = pport->class1_buf_in;
			i++;//len
			ptmp[i++] = M_EI_NA_1;//��ʼ������
			ptmp[i++] = 1;
			ptmp[i++] = INIT;
			if (pport->pcfg->causelen > 1)ptmp[i++] = 0;
			ptmp[i++] = (uint8)pport->pcfg->commaddr;
			if (pport->pcfg->commaddrlen > 1)ptmp[i++] = pport->pcfg->commaddr >> 8;
			ptmp[i++] = 0;//inf
			ptmp[i++] = 0;
			if (pport->pcfg->inflen > 2)ptmp[i++] = 0;
			ptmp[i++] = 0x02;//Զ����λ COI
			ptmp[0] = i - 1;
			pport->class1_buf_in = &ptmp[i];
			pport->acd_count++;
		}
		break;
	case SEND_RESET_PROCESS://1 ��λ����֡
		pport->f_sendframe = F_CONFIRM_SEND;//1  ȷ��֡�Ĺ�����Ϊ0
		dpa10x_ResetCounters(pport);

		break;
	case SEND_TEST_LINK://2
		pport->f_sendframe = F_RESPOND_LINK_STATUS;// ��Ӧ������Ϊ ��·״̬
		break;
	case SEND_REPLY_DATA: //3
		pport->f_sendframe = F_CONFIRM_SEND;//
		break;
	case SEND_NOREPLY_DATA://4
		break;
	case REQUEST_LINK_STATUS:   // 0x09 ; �ٻ���·״̬
		pport->f_sendframe = F_RESPOND_LINK_STATUS;
		break;
	case REQUEST_CLASS1_DATA:   // 0x0A ; ����һ�౨��
		pport->f_sendframe = F_RESPOND_CLASS1; //��Ӧ����
		break;
	case REQUEST_CLASS2_DATA:		//0x0B  �����������
		pport->f_sendframe = F_RESPOND_CLASS2; //��Ӧ����
		break;
	default:
		pport->f_sendframe = F_RESPOND_NODATA;//4
		break;
	}
}

/****************************************/

void dpa101V1_Init(void)
{
	int		 i,j;
	struDpa10xPort     *pport;
	struDpa10xFrm      *pfrm;
	struDpa10xPort_Cfg	*pportcfg;
	struDpa10xFrm_Cfg	*pfrmcfg;
	uint8 *ptmp;
	//uint32 tick;
	struDpa10xApp *pappl;
       char out[80];

   	sprintf(out, "dpa101 version %06x", APPVER_DPA101);
	db_PutInitLog(out);
	if(!glb_f_ApplsRunEn)return;


	//tick = glb_sysTick;
	pappl = &dpa101appl; 
	memset(pappl, 0, sizeof(struDpa10xApp));

	pappl->pcfg = (struDpa10xApp_Cfg*)glb_FindAppCfg(APPID_DPA101 + ((APPVER_DPA101 & 0XFFFF00) << 8));
	if (pappl->pcfg == NULL)
	{
		db_PutInitLog("dpa101: no configuration file");
		return ;
	}

	pappl->portnum = pappl->pcfg->portnum;						//g_numport
	if (pappl->portnum == NULL)
	{
		db_PutPrtLog("dpa101: no port configured");
		return;
	}

	pappl->pport = (struDpa10xPort*)malloc(sizeof(struDpa10xPort)*pappl->portnum);	//dpa101_pport
	if (pappl->pport == NULL)
	{
		db_PutPrtLog("dpa101: memory alloc err or portnum=0");
		return;
	}

	memset(pappl->pport, 0, sizeof(struDpa10xPort)*pappl->portnum);//��ʼ��
	pport = pappl->pport;
	ptmp = (uint8*)&pappl->pcfg->portcfg;
	for (i = 0; i<pappl->portnum; i++, pport++)
	{
		pportcfg = (struDpa10xPort_Cfg*)ptmp;	//pportcfg = dpa101_FindPortCfg(pappl->pcfg, i);
		pport->pcfg = pportcfg;					//pport->pcfg

		pport->frmnum = (int16)pportcfg->frmnum;		//pport->frmnum
		pport->pfrm = (struDpa10xFrm *)malloc(sizeof(struDpa10xFrm)*pport->frmnum);//pport->pfrm
		if (pport->pfrm == NULL)
		{
			db_PutPrtLog("dpa101: memory alloc err or frmnum=0");
			return;
		}

		memset(pport->pfrm, 0, sizeof(struDpa10xFrm)*pport->frmnum);
		pfrm = pport->pfrm;
		ptmp = (uint8*)&pportcfg->frmcfg;
		for (j = 0; j<pport->frmnum; j++, pfrm++)
		{
			pfrmcfg = (struDpa10xFrm_Cfg *)ptmp;//dpa101_FindFrmCfg(pportcfg, j);
			pfrm->pcfg = pfrmcfg;				//pfrm->pcfg

			pfrm->pntnum = pfrmcfg->pntnum;			//pfrm->pntnum
			pfrm->ppntcfg = &pfrmcfg->pntcfg;			//pfrm->ppntcfg

			ptmp = (uint8*)pfrm->ppntcfg; 
			if (pfrmcfg->frmtype == M_SP_TA_1 || pfrmcfg->frmtype == M_SP_TB_1 || pfrmcfg->frmtype == M_FT_NA_1)		
				ptmp += pfrmcfg->pntnum*sizeof(struDpa10xSp_Cfg);
			else if (pfrmcfg->frmtype == M_DP_TA_1 || pfrmcfg->frmtype == M_DP_TB_1)
				ptmp += pfrmcfg->pntnum*sizeof(struDpa10xDp_Cfg);
			else if (pfrmcfg->frmtype == M_ME_NA_1 || pfrmcfg->frmtype == M_ME_NB_1 || pfrmcfg->frmtype == M_ME_NC_1)
				ptmp += pfrmcfg->pntnum*sizeof(struDpa10xMe_Cfg);
			else if (pfrmcfg->frmtype == M_IT_NA_1 || pfrmcfg->frmtype == M_IT_NB_1)
				ptmp += pfrmcfg->pntnum*sizeof(struDpa10xIt_Cfg);
			else if (pfrmcfg->frmtype == C_SC_NA_1 || pfrmcfg->frmtype == C_DC_NA_1)
				ptmp += pfrmcfg->pntnum*sizeof(struDpa10xDc_Cfg);
			else if (pfrmcfg->frmtype == C_SE_NA_1 || pfrmcfg->frmtype == C_SE_NB_1 || pfrmcfg->frmtype == C_SE_NC_1)
				ptmp += pfrmcfg->pntnum*sizeof(struDpa10xSe_Cfg);
			else if (pfrmcfg->frmtype == C_RS_NA_1 )//|| pfrmcfg->frmtype == (C_RS_NA_1 |0X100)
				ptmp += pfrmcfg->pntnum*sizeof(struDpa10xPara_Cfg);
		}

		pport->ginum = *(int32*)ptmp;		//ginum
		ptmp += sizeof(int32);
		pport->pgicfg = (struDpa10xGrp_Cfg*)ptmp;
		ptmp += sizeof(struDpa10xGrp_Cfg)*pport->ginum;

		pport->cinum = *(int32*)ptmp;		//cinum
		ptmp += sizeof(int32);
		pport->pcicfg = (struDpa10xGrp_Cfg*)ptmp;
		ptmp += sizeof(struDpa10xGrp_Cfg)*pport->cinum;

		dpa10x_ResetCounters(pport);
		pport->dpaH = db_GetDpaHand();

	}

//	struDpa10xPort *pport;
	for (pport = dpa101appl.pport, i = 0; i<dpa101appl.portnum; i++, pport++)
        {
		dpa101_PortOpen(pport);	//����Э�飬ͨѶ��ֻ��ʼ��һ�Σ�ERR��ÿڲ��ٿ���
        }
	
               sprintf(out, "dpa101: %d port configured, init ok", dpa101appl.portnum);
               db_PutInitLog(out);
 
	f_Dpa101Init = TRUE;

      
}

/***********************************************************************/
// struPrgCfgCbk cbk1;
void dpa101V1(void)
{
	static bool f_appdelay = 1;
	struDpa10xPort *pport;
	int i;
	uint32 tick;
        ////////////////////           ����
        ////////////                   ����
	if (f_Dpa101Init == FALSE)return;

	tick = glb_sysTick;	//Ӧ����ʱappdelay���ʼִ��
	if (f_appdelay && tick < (uint32)dpa101appl.pcfg->appdelay * 1000)return;
	f_appdelay = 0;

	//--------

	for (pport = dpa101appl.pport, i = 0; i<dpa101appl.portnum; i++, pport++)
	{
		if (pport->frmnum == 0)continue;
		if (pport->portsts1 != PORTSTS_RUN && pport->portsts2 != PORTSTS_RUN)continue;//�����ڶ������� 

		dpa101_Scan(pport);//SOEɨ�衢�����Զ����͡�ͨѶ״̬�жϵȷ��շ����֡�
		dpa101_Recv(pport);
		dpa101_Send(pport);
	}
}



/********104*****************104********************************************/
/***************************************************************************/
#define DPA104_MAXSOCK	4
typedef struct
{
	int sockid;
	struIp localip;
	uint8 p;//�����ӽ���ʱͨ��findpport����
	uint8 s;
	uint8 sts;
	bool used;
}struDpa104SockInf;
static struDpa104SockInf SockInf[DPA104_MAXSOCK];

void TcpsRecvFunc(uint32 usr)
{SockInf[usr].sts = TCP_REC;}
void TcpsConnFunc(uint32 usr)
{SockInf[usr].sts = TCP_CONN;}
void TcpsCloseFunc(uint32 usr)
{SockInf[usr].sts = TCP_CLOSE;}
void TcpsTimeoutFunc(uint32 usr)
{SockInf[usr].sts = TCP_TIMEOUT;}


static int dpa104_findUnusedSock(void)
{
	for (int i = 0; i < DPA104_MAXSOCK; i++)
	{
		if (SockInf[i].used == false)
			return i;
	}
	return -1;
}

static bool dpa104_CreateSock(struIp *ip)
{
	int i = dpa104_findUnusedSock();
	if (i == -1) return false;

	int sockid = socket_create(SOCK_STREAM, ip, 2404);
	if (sockid >= 0)
	{
		socket_SetCallback(sockid, TcpsConnFunc, TcpsCloseFunc, TcpsRecvFunc, TcpsTimeoutFunc, i);
		socket_listen(sockid);

		SockInf[i].sockid = sockid;
		SockInf[i].localip = *ip;//��connect�����Ŀͻ�����Ԥ�ڵĿͻ�ʱ��close sockȻ�����½�һ������ʱ��Ҫ��ʱ��sockʱ��ip
		SockInf[i].sts = TCP_LISTEN;
		SockInf[i].used = true;
		return true;
	}
	return false;
}

static bool dpa104_findpport(uint32 lip, uint32 rip, uint8* p, uint8* s)
{
	struDpa10xPort *pport;
	bool find = false;

	pport = dpa104appl.pport;
	for (int i = 0; i < dpa104appl.portnum; i++, pport++)
	{
		if (pport->LocalIp1Addr == lip && pport->pcfg->remoteip3 == rip)
		{
			*s = 0; *p = i;
			find = true;
		}
		else if (pport->LocalIp2Addr == lip && pport->pcfg->remoteip4 == rip)
		{
			*s = 1; *p = i;
			find = true;
		}
	}
	return find;
}

static void dpa104_Recv(struDpa10xPort *pport);
static void dpa104_SocketOpen(void)
{
	struDpa10xPort *pport = dpa104appl.pport;
	struIp *ip, desnetaddr;
	uint16 port ;

	uint16 len;
	uint8 *rbuf;

	
	//ͨ��SockInf����sts
	struDpa104SockInf *psockinf = SockInf;
	uint8 p, s;
	for (int i = 0; i < DPA104_MAXSOCK; i++, psockinf++)
	{
		if (!psockinf->used)continue;

		switch (psockinf->sts)
		{
		//case TCP_LISTEN:
		case TCP_CONN:
			//if (socket_accept(psockinf->sockid) < 0) break;
			psockinf->sts = TCP_WAIT;
	
			socket_getPeerIp(psockinf->sockid, &desnetaddr, &port);
			if (dpa104_findpport(psockinf->localip.IpAddr, desnetaddr.IpAddr, &p, &s))
			{
				psockinf->p = p;
				psockinf->s = s;
				if (s == 0)
				{
					dpa104appl.pport[p].portsts1 = TCP_REC;//������������һ������
					dpa104appl.pport[p].sockid1 = psockinf->sockid;//����ʱ��
					dpa104appl.pport[p].sockinf1 = i;//��������closeʱ�ر�sockinf.used
				}
				else
				{
					dpa104appl.pport[p].portsts2 = TCP_REC;
					dpa104appl.pport[p].sockid2 = psockinf->sockid;
					dpa104appl.pport[p].sockinf2 = i;
				}
			}
			else//δ�ҵ���Ӧpport
			{
				socket_close(psockinf->sockid);//�������õĿͻ�
				psockinf->used = false;
				
				//��connect�����Ŀͻ�����Ԥ�ڵĿͻ�ʱ��close sockȻ�����½�һ��. �㲻������ĳpport������sock close������Ϊ�����Ǹ������ӵ�socket
				dpa104_CreateSock(&psockinf->localip);
			}
			break;
		case TCP_REC:
			psockinf->sts = TCP_WAIT;

			if (psockinf->s == 0)	dpa104appl.pport[psockinf->p].portsts1 = TCP_REC;
			else dpa104appl.pport[psockinf->p].portsts2 = TCP_REC;
			break;
		case TCP_CLOSE:
		case TCP_TIMEOUT:
			socket_close(psockinf->sockid);
			psockinf->used = false;
			psockinf->sts = TCP_INIT;
			
			if (psockinf->s == 0)
			{
				dpa104appl.pport[psockinf->p].portsts1 = TCP_INIT;
				pport->startdt1 = FALSE;
			}
			else
			{
				dpa104appl.pport[psockinf->p].portsts2 = TCP_INIT;
				pport->startdt2 = FALSE;
			}
			break;
		}
	}
	
	//����pportͨѶ
	pport = dpa104appl.pport;
	for ( int i = 0; i < dpa104appl.portnum; i++, pport++)
	{
		rbuf = pport->rbuf;
		switch (pport->portsts1)
		{
		case TCP_INIT:
			if (pport->pcfg->localip1 && pport->pcfg->remoteip3)
			{
				ip = glb_getLocalIp(pport->pcfg->localip1 - 0x40);//0x40 ��ʾ�׸����ڣ�0x41��ʾ��2����  
				if (ip)
				{
					pport->LocalIp1Addr = ip->IpAddr;
					if (dpa104_CreateSock(ip))
						pport->portsts1 = TCP_LISTEN;
				}
			}
			break;
		case TCP_REC:
			if ((len = socket_recv(pport->sockid1, rbuf, RXSIZE)) > 0)
			{
				glb_PutNetCode(pport->LocalIp1Addr, pport->pcfg->remoteip3, rbuf, len, MONICOMM_DIR_RX);

				if ((rbuf[0] == 0x68 && !pport->pcfg->commkey)
					|| (rbuf[0] == 0xEB && rbuf[3] == 0xEB && pport->pcfg->commkey))
				{
					pport->activeport = 0;
					pport->rlen = len;
					dpa104_Recv(pport);//socket_send(pport->sockid1, rbuf, len);//
				}
			}
			pport->portsts1 = TCP_WAIT;
			break;
		}
		
		switch (pport->portsts2)
		{
		case TCP_INIT:
			if (pport->pcfg->localip2 && pport->pcfg->remoteip4)
			{
				ip = glb_getLocalIp(pport->pcfg->localip2 - 0x40);//0X40 ��ʾ�׸����ڣ�0X41 ��ʾ��2����  
				if (ip)
				{
					pport->LocalIp2Addr = ip->IpAddr;
					if (dpa104_CreateSock(ip))
						pport->portsts2 = TCP_LISTEN;
				}
			}
			break;
		case TCP_REC:
			if ((len = socket_recv(pport->sockid2, rbuf, RXSIZE)) > 0)
			{
				if ((rbuf[0] == 0x68 && !pport->pcfg->commkey)
					|| (rbuf[0] == 0xEB && rbuf[3] == 0xEB && pport->pcfg->commkey))
				{
					pport->activeport = 1;
					pport->rlen = len;
					dpa104_Recv(pport);//socket_send(pport->sockid2, rbuf, len);//
				}
			}
			pport->portsts2 = TCP_WAIT;
			break;
		}
	}
}

//����ִ��
static void dpa104_Scan(struDpa10xPort *pport)
{
	uint32 tick;

	tick = glb_sysTick;
	if (tick - pport->scan_timetick < DPA10x_SCAN_INTERVAL)return;//150ms 
	pport->scan_timetick = tick;

	if (pport->startdt1 || pport->startdt2)
		dpa10x_Soe(pport);


	//����δ���ң��
	if (pport->doevent.sts && tick - pport->doevent.timetick>DPA10x_DOTIMEOUT)
		memset(&pport->doevent, 0, sizeof(struDpa10xDoevent));

	//����δ��ɲ�������
	if (pport->SzDzEvent.f_select && tick - pport->SzDzEvent.selecttime > DPA10x_DOTIMEOUT)
		memset(&pport->SzDzEvent, 0, sizeof(struDpa10xSzDzEvent));

         	//����֤���������֤���
        if(tick-pport->Tool_Rectick>TOOL_TIMEOUT) 
  	{
              pport->F_CONFIRM&=~0x02;
              memset(Tool_ID,0,8);
              memset(Tool_R1,0,8);
        }
        
	/* ���PMA������ȷ��֡����ע���
	//ͨѶ�쳣�����
	if (pport->k_num >=12 &&(tick - pport->test_t1 > TEST_T1))//�رյ�����
	{
		pport->k_num = 0;
		pport->test_t1 = tick;

		if (pport->portsts1 != TCP_INIT)
		{
			pport->portsts1= TCP_INIT;
			socket_close(pport->sockid1);
			SockInf[pport->sockinf1].used = false;
			pport->startdt1=FALSE;
		}
		if (pport->portsts2 != TCP_INIT)
		{
			pport->portsts2= TCP_INIT;
			socket_close(pport->sockid2);
			SockInf[pport->sockinf2].used = false;
			pport->startdt2=FALSE;
	
		}
	}
	//ͨѶ�쳣ʱ�ͷ�SOCKET,����ͨѶ������ĳӦ���ö˿�״̬�����û��PutSCommSts()
	*/


	//DEBUG----------
	//���PMA������ȷ��֡���ڴ�ֱ����Ϊ�ѽ���
	if (pport->noacknum)
	{
		pport->class1_buf_out = pport->class1_buf_tmpout;
		pport->acd_count -= pport->noacknum;
		pport->noacknum = 0;
	}
	if (pport->acd_count == 0)
	{
		pport->class1_buf_out = pport->class1_buf_in = pport->class1_buf;
		pport->class1_buf_tmpout = pport->class1_buf_out;

	}
	//-----------DEBUG

}


static void dpa104_Send(struDpa10xPort *pport)
{
	uint8 *tbuf;
	int16 asdu_len = 0;
	int16 i = 0, j = 0, tn = 0,n;
	uint32 tick;
	uint8 *ptmp;
	uint8 *dat_tbuf;
	uint8 crc;
	uint8 *sc_rbuf;
	uint8 typid;
        uint16 TotalNum;
        static int k1=0,num=0;
         uint16 N=200; //���°�֡�Ĵ�С
         uint16 len;
         
	tbuf = pport->tbuf;
	dat_tbuf = pport->dat_tbuf;

	tick = glb_sysTick;//500msһ���Զ�ɨ��

	if (pport->f_sendframe)goto SEND;//����Ӧ��

	if (tick - pport->send_timetick < DPA104_SEND_INTERVAL)return;//500ms 
	pport->send_timetick = tick;

SEND:
	if (pport->pcfg->commkey&&pport->F_NeedACK==1)
        {   
               if(pport->F_SendCER)       //�ն�֤������
              {         
                   if((tick-pport->sendcer_tick)<1000)return; //�������͵ļ��1s
                   pport->sendcer_tick=tick;
                   TotalNum=DevCer_len/N+1;
                   k1++;
                   if(k1==TotalNum)
                   {  
                      pport->F_NeedACK=0; 
                      pport->F_SendCER=0;
                      len=DevCer_len-num;
                   }
                   else
                      len=N;
                   tbuf[i++] = 0xEB;
                    i=i+2;
                   tbuf[i++] = 0xEB;
                   tbuf[i++] = pport->Mess_type >> 8;
                   tbuf[i++] = pport->Mess_type&0xF0;
                   if(pport->Mess_type&0xC0)//TOOL
                   {
                        tbuf[i++] = TDEV_DEVCER_RETURN;//Ӧ������  43
                         pport->F_SendCER=0;
                   }
                   else
                        tbuf[i++] = MDEV_CER_RETURN;//Ӧ������  75
                   tbuf[i++] =(3+len)>>8;
                   tbuf[i++] =(3+len);
                   tbuf[i++]=0x06;                   //�ն�֤���ʶ0x06
                   tbuf[i++]=TotalNum;
                   tbuf[i++]=k1;
                   memcpy(&tbuf[i],&Dev_Cer[num],len);
                   num+=len;
                   i+=len;
                  if(k1==TotalNum)
                  {     
                    k1=0;
                    num=0;
                  }
                   
                   crc=dpa10x_Crc(&tbuf[4], i-4);
                   tbuf[i++]=crc;
                   tbuf[i++]=0xD7; 
                   tbuf[1]=(i-6)>>8;
                   tbuf[2]=i-6;
                   goto COMMSEND_104;
              }         
               else  if (pport->App_type >= 0x20&&pport->dat_tlen)
              {
                     pport->F_NeedACK=0;  
                    tbuf[i++] = 0xEB;
                    tbuf[i++] = (pport->dat_tlen + 2) >> 8;
                    tbuf[i++] = pport->dat_tlen + 2;
                    tbuf[i++] = 0xEB;
                    tbuf[i++] = pport->Mess_type >> 8;
                    if(pport->App_type==0x3A||pport->App_type==0x49)
                    {
                        pport->Mess_type&=0xF0;
                        tbuf[i++] = pport->Mess_type|0x08;
                    }
                    else
                        tbuf[i++] = pport->Mess_type&0xF0;
                    memcpy(&tbuf[i], dat_tbuf, pport->dat_tlen);//dat_tbuf��������������
                    i = i + pport->dat_tlen;
                     pport->App_type =0;
                     crc=dpa10x_Crc(&tbuf[4], i-4);
                     tbuf[i++]=crc;
                     tbuf[i++]=0xD7; 
                    goto COMMSEND_104;
                }
		else
		{
                         pport->F_NeedACK=0; 
			tbuf[i++] = 0xEB;
			i = i + 2;//����
			tbuf[i++] = 0xEB;
			tn = 2;
		 }
	}
	if ((pport->f_sendframe & 0x3) == FORMAT_U)//FORMAT_U               
	{
		j= tn;
		dat_tbuf[j++] = START2;
		dat_tbuf[j++] = 4;
		dat_tbuf[j++] = pport->f_sendframe;
		dat_tbuf[j++] = 0;
		dat_tbuf[j++] = 0;
		dat_tbuf[j++] = 0;

		if (pport->f_sendframe & 0x08)
		{       
                        n=0;
			ptmp = pport->class1_buf_in;
			n++;//len
			ptmp[n++] = M_EI_NA_1;//��ʼ������
			ptmp[n++] = 1;
			ptmp[n++] = INIT;
			if (pport->pcfg->causelen > 1)ptmp[n++] = 0;
			ptmp[n++] = (uint8)pport->pcfg->commaddr;
			if (pport->pcfg->commaddrlen > 1)ptmp[n++] = pport->pcfg->commaddr >> 8;
			ptmp[n++] = 0;//inf
			ptmp[n++] = 0;
			if (pport->pcfg->inflen > 2)ptmp[n++] = 0;
			ptmp[n++] = 0x02;//Զ����λ COI
			ptmp[0] = n - 1;
			pport->class1_buf_in = &ptmp[n];
			pport->acd_count++;
		}

		if (!pport->pcfg->commkey)
		{
			memcpy(tbuf, dat_tbuf, j);
			i = j - tn;
                        //pport->tlen = j;
			goto COMMSEND_104;
		}
		dat_tbuf[0] = APP0;
		dat_tbuf[1] = j - 2;
		dat_tbuf[j++] = 0x00; //��Ϣ��չ��
		dat_tbuf[j++] = 0x00;

		tbuf[i++] = pport->Mess_type >> 8;
		tbuf[i++] = pport->Mess_type & 0xF0;
		memcpy(&tbuf[i], dat_tbuf, j);
		i = i + j;
	}
	else
	{
		if (pport->startdt1 || pport->startdt2)
		{
			asdu_len = dpa10x_GetClass1Data(pport, &dat_tbuf[tn + 6]);
			if (!asdu_len)asdu_len = dpa10x_GetClass2Data(pport, &dat_tbuf[tn + 6]);
			if (asdu_len)//FORMAT_I
			{
				j = tn;
				dat_tbuf[j++] = START2;
				dat_tbuf[j++] = asdu_len + 4;
				*(uint16*)&dat_tbuf[j] = (pport->local_send_sn++) << 1; j += 2;
				*(uint16*)&dat_tbuf[j] = (pport->local_receive_sn) << 1; j += 2;
				j += asdu_len;
				if (!pport->pcfg->commkey)
				{
					memcpy(tbuf, dat_tbuf, j); //memcpy(tbuf, &dat_buf[tn], k-tn);
                                        i = j - tn;
                                        //pport->tlen = j;
					goto COMMSEND_104;
				}
				tbuf[i++] = pport->Mess_type >> 8;
				tbuf[i++] = pport->Mess_type | 0x08;
				dat_tbuf[1] = j - 2;
				uint8 le;
				typid = dat_tbuf[2 + 5 + pport->pcfg->linkaddrlen];

                                if(((typid==C_SC_NA_1||typid==C_DC_NA_1)&&dat_tbuf[j-3]&0x80)//ң��ѡ��ȷ��
                                   ||((typid==C_WS_NA_1)&&(dat_tbuf[j-3]&0x80))||(typid==F_SR_NA_1&&dat_tbuf[j-3]&0x80))//����Ԥ��ȷ�ϣ���������ȷ��
                                {  
                                                 dat_tbuf[0]=APP2;
                                                 dat_tbuf[j++]=0x00; //��Ϣ��չ������
                                                 dat_tbuf[j++]=0x08;  
                                                 
                                                 SC1161_Get_Rand(data_sc1161,sc_rbuf);
                                                 memcpy( pport->Send_Rand,&sc_rbuf[5],8);
                                                 memcpy(&dat_tbuf[j], pport->Send_Rand,8);
                                                 j=j+8;                      
                                 }
                                else
                                {
                                         dat_tbuf[0]=APP0;
                                         dat_tbuf[j++]=0x00; //��Ϣ��չ������
                                         dat_tbuf[j++]=0x00;
                                }                  
                                SC1161_Encrypt(data_sc1161,j,dat_tbuf,pport->Master_R1,sc_rbuf); 
                                le=((uint16)sc_rbuf[3]<<8)+sc_rbuf[4];
                                memcpy(&tbuf[i],&sc_rbuf[5],le);
                                  i=i+le;            
                       
                              pport->k_num++;
                              if (pport->k_num == 1)pport->test_t1 = tick;

			}
			else if ((pport->f_sendframe & 0x3) == FORMAT_S)//�յ�S֡������Ӧ��
			{
				j = tn;
				dat_tbuf[j++] = START2;
				dat_tbuf[j++] = 4;
				dat_tbuf[j++] = FORMAT_S;
				dat_tbuf[j++] = 0;
				*(uint16 *)&dat_tbuf[j++] = (pport->local_receive_sn)<< 1; j += 2;
				if (!pport->pcfg->commkey)
				{
					memcpy(tbuf, dat_tbuf, j);//memcpy(tbuf, &dat_buf[tn], k-tn);
					i = j - tn;
                                        //pport->tlen = i;
					goto COMMSEND_104;
				}

				dat_tbuf[0] = APP0;
				dat_tbuf[1] = j - 2;
				dat_tbuf[j++] = 0x00; //��Ϣ��չ��
				dat_tbuf[j++] = 0x00;

				tbuf[i++] = pport->Mess_type >> 8;
				tbuf[i++] = pport->Mess_type & 0xF0;
				memcpy(&tbuf[i], dat_tbuf, j);
				i = i + j;
			}
		}
	}
	if (i>7)
	{
		crc = dpa10x_Crc(&tbuf[4], i - 4);
		tbuf[i++] = crc;
		tbuf[i++] = 0xD7;
		tbuf[1] = (i-6) >> 8;
		tbuf[2] = (i-6);
	}
COMMSEND_104:
	if (i)//��104��˵U֡Ҳ���ĸ��ڽ��ĸ��ڻأ�����֡��������ֻҪRUN&STARTDT�ͷ��������������޹ء�
	{
		pport->tlen = i;

		if ((pport->f_sendframe & 0x3) == FORMAT_U)
		{

			if (pport->activeport == 0)
			{
				socket_send(pport->sockid1, tbuf, i);
				glb_PutNetCode(pport->LocalIp1Addr, pport->pcfg->remoteip3, tbuf, i, MONICOMM_DIR_TX);
			}
			else if (pport->activeport == 1)
			{
				socket_send(pport->sockid2, tbuf, i);
			}

		}
		else
		{
			if (pport->portsts1 == TCP_WAIT && pport->startdt1 == TRUE)
			{
				socket_send(pport->sockid1, tbuf, i);
				glb_PutNetCode(pport->LocalIp1Addr, pport->pcfg->remoteip3, tbuf, i, MONICOMM_DIR_TX);
			}
			if (pport->portsts2 == TCP_WAIT && pport->startdt2 == TRUE)
			{
				socket_send(pport->sockid2, tbuf, i);
			}
		}

		pport->f_sendframe = 0;
	}
}

static void dpa104_Recv(struDpa10xPort *pport)
{
	uint8 *rbuf;
	uint16  le;
	int rn;
	uint8 *dat_rbuf;
        uint16 dat_rlen;
        uint8 tmpb1;
        uint32 tick;
        SYS_TIME64  tm,rec_tm;
		uint8 Rec_Rand[8];

	rn = 0;
        rbuf = pport->rbuf;
	dat_rbuf = pport->dat_rbuf;
        if (pport->rlen == 0)return;
	if (pport->pcfg->commkey)//commkeyΪ1ʱ�����м���ͨѶ
	{
                tick = glb_sysTick;
                dat_rlen = ((uint16)rbuf[1] << 8) + rbuf[2]-2; //��װ�����򳤶�
		if (rbuf[0] != 0xEB || rbuf[3] != 0xEB || rbuf[dat_rlen+7] != 0xD7) return ;//��ⱨ����ʼ�ͽ�����
		tmpb1 = dpa10x_Crc(&rbuf[4], dat_rlen+2);
		if (tmpb1 != pport->rbuf[dat_rlen+6]) return ;          //У�鲻��ȷ������
                
                pport->F_NeedACK=1;
		pport->Mess_type = ((uint16)rbuf[4] << 8) + rbuf[5];
		if ((pport->Mess_type & 0x0F)==0x09)//���� ���н���
		{
			if(SC1161_Decrypt(data_sc1161, dat_rlen, &rbuf[6], pport->Master_R1, sc_rbuf)==FALSE)
			{
				 dpa10x_ERROR(pport,ERROR,ERRO_BUSS_DECRYP);  // �쳣����:MAC���� (����ʧ��)   ��10x����
					return;
			}
			le = ((uint16)sc_rbuf[3] << 8) + sc_rbuf[4];
			memcpy(dat_rbuf, &sc_rbuf[5], le);
			pport->App_type = dat_rbuf[0];
		}
                else if ((pport->Mess_type & 0x0F)==0x0A)//���� ���н���
		{
                       if( SC1161_Decrypt_Tool(data_sc1161,Tool_ID,dat_rlen,&rbuf[6],Tool_R1,sc_rbuf)==FALSE)   //if(SC1161_Decrypt(data_sc1161, dat_rlen, &rbuf[6],Tool_R1, sc_rbuf)==FALSE)
			{
				 dpa10x_ERROR(pport,ERROR,ERRO_BUSS_DECRYP);  // �쳣����:MAC���� (����ʧ��)   ��10x����
				 return;
			}
			le = ((uint16)sc_rbuf[3] << 8) + sc_rbuf[4];
			memcpy(dat_rbuf,  &sc_rbuf[5], le);
			pport->App_type = dat_rbuf[0];
		}
		else
		{
			memcpy(dat_rbuf, &rbuf[6], dat_rlen);//����           //dat_rbuf�ǽ��ܺ��Ӧ������+Ӧ��������+��Ϣ��ȫ��չ��
			pport->App_type = dat_rbuf[0];
		}
		  if(pport->Mess_type&0xC0==LINK_MASTER)
                {
                    if(!(pport->F_CONFIRM&0x01)&&(pport->App_type==0x62||pport->App_type==0x64||pport->App_type==0x70))//��Կ���£��ָ���֤�����
                    {
                             dpa10x_ERROR(pport,ERROR,ERRO_BUSS_SAFEPROCESS);  // �쳣����:δͨ����ȫ��֤ ����վ101����  9107
                             return; 
                    } 
                }
                else if(pport->Mess_type&0xC0==LINK_TOOL)
               {
                        pport->Tool_Rectick=tick;
                        if(!(pport->F_CONFIRM&0x02)&& (pport->App_type==0x34||pport->App_type==0x42||pport->App_type==0x46))// ��ȡ��Կ�汾����Կ�ָ���
                        {
                                  dpa10x_ERROR(pport,ERROR,ERRO_BUSS_SAFEPROCESS); // �쳣����:δͨ����ȫ��֤ ��ά������101����  9107
                                  return;  
                        }
                }
		pport->dat_rlen=le;
		if(pport->App_type==0x08) //��������֤
                {
                     glb_GetDateTime(&tm);
                     rec_tm=*(SYS_TIME64*)&dat_rbuf[dat_rlen-79];
                     if(((rec_tm.hour*3600+rec_tm.min*60+rec_tm.sec)-(tm.hour*3600+tm.min*60+tm.sec)>60)
                            ||((tm.hour*3600+tm.min*60+tm.sec)-(rec_tm.hour*3600+rec_tm.min*60+rec_tm.sec)>60))
                     {
                              dpa10x_ERROR(pport,ERROR,ERRO_BUSS_TIME);
                              return;
                     }
                     memcpy(Rec_Rand,&dat_rbuf[dat_rlen-73],8);
                     if( memcmp(Rec_Rand,pport->Send_Rand,8)!=0)
                     {
                              dpa10x_ERROR(pport,ERROR,ERRO_BUSS_RAND);
                              return;
                     }
                     if (SC1161_Verify_DevSign(data_sc1161, dat_rlen, dat_rbuf, sc_rbuf) == FALSE)
                     {  
                              dpa10x_ERROR(pport,ERROR,ERRO_BUSS_SIGN);
                              return;
                      } 
                      pport->F_NeedACK=0;
                      memcpy(SverData,&sc_rbuf[19],le-14);//SverData:����������֤�����е�ǩ�����+ǩ����Կ 64+1
                      return;
                }
		else if(pport->App_type >= 0x20)
		{
			dpa10x_packetlayer_Nodata(data_sc1161, pport, dat_rbuf); 
			return;
		}
		rn += 2;
	}
	else
		memcpy(dat_rbuf, pport->rbuf, pport->rlen);
        
          if(pport->pcfg->commkey&&(pport->Mess_type&0xC0)==LINK_MASTER&&!(pport->F_CONFIRM&0x01))
        {
             dpa10x_ERROR(pport,ERROR,ERRO_BUSS_SAFEPROCESS);  // �쳣����:δͨ����ȫ��֤ ����վ101����  9107
             return; 
        }

	if ((dat_rbuf[rn] == 0x68 && (dat_rbuf[rn + 2] & 0x1) == FORMAT_I) || (dat_rbuf[rn] == 0x68 && (dat_rbuf[rn + 2] & 0x3) == FORMAT_S))
	{
		if (pport->noacknum)
		{
			pport->class1_buf_out = pport->class1_buf_tmpout;
			pport->acd_count -= pport->noacknum;
			pport->noacknum = 0;

			//sprintf(out, "Recv, find noack reset to 0, acd_count=%d, noacknum=%d", pport->acd_count, pport->noacknum);
			//db_PutPrtLog(out);
		}
		if (pport->acd_count == 0)
		{
			pport->class1_buf_out = pport->class1_buf_in = pport->class1_buf;
			pport->class1_buf_tmpout = pport->class1_buf_out;
		}
	}

	if (dat_rbuf[rn] == 0x68 && (dat_rbuf[rn + 2] & 0x1) == FORMAT_I)
	{
                if(pport->pcfg->commkey&&!(pport->Mess_type&0x08))
		{       
			  dpa10x_ERROR(pport,ERROR,ERRO_BUSS_NONSTANDARD);
			  return;
		}
		pport->remote_receive_sn = (*(UINT16*)&dat_rbuf[rn + 4]) >> 1;
		pport->remote_send_sn = (*(UINT16*)&dat_rbuf[rn + 2]) >> 1;
		pport->local_receive_sn = pport->remote_send_sn + 1;
		pport->f_sendframe = FORMAT_I;
		pport->k_num = 0;

		if (pport->startdt1 || pport->startdt2)	dpa10x_AppLayer(pport, &dat_rbuf[rn + 6], dat_rbuf[rn + 1] - 4, 1);//
	}
	else if (dat_rbuf[rn] == 0x68 && (dat_rbuf[rn + 2] & 0x3) == FORMAT_S)
	{
		pport->remote_receive_sn = (*(UINT16*)&dat_rbuf[rn + 4]) >> 1;
		pport->f_sendframe = FORMAT_S;
		pport->k_num = 0;
	}

	else if (dat_rbuf[rn] == 0x68)// FORMAT_U
	{
		switch (dat_rbuf[rn + 2] & 0xfc)
		{
		case TESTFR_ACT:
			pport->f_sendframe = TESTFR_CON | FORMAT_U;
			break;
		case STARTDT_ACT:
			pport->f_sendframe = STARTDT_CON | FORMAT_U;
			if (pport->activeport == 0)
			{
				pport->startdt1 = TRUE;//activeportָ�ĸ����յ�����startdt1��ָ�ÿ�ΪSTARTDT״̬������class1\2����
				pport->startdt2 = FALSE;
			}
			else
			{
				pport->startdt2 = TRUE;
				pport->startdt1 = FALSE;
			}
			dpa10x_ResetCounters(pport);//��SN��0����һ�����յ�STOPDT,��˷���STARTDT
			break;
		case STOPDT_ACT:
			pport->f_sendframe = STOPDT_CON | FORMAT_U;
			if (pport->activeport == 0) pport->startdt1 = FALSE;
			else pport->startdt2 = FALSE;
			break;
		default:
			break;
		}
	}
}


/*************************************************/


/*************************************************/
void dpa104V1_Init(void)
{
	int		 i, j;
	struDpa10xApp    *pappl;
	struDpa10xPort     *pport;
	struDpa10xFrm      *pfrm;
	struDpa10xPort_Cfg	*pportcfg;
	struDpa10xFrm_Cfg	*pfrmcfg;
	uint8 *ptmp;
	char out[80];

	sprintf(out, "dpa104 version %06x", APPVER_DPA104);
	db_PutInitLog(out);
	if (!glb_f_ApplsRunEn)return;


	pappl = &dpa104appl;
	memset(pappl, 0, sizeof(struDpa10xApp));

	pappl->pcfg = (struDpa10xApp_Cfg*)glb_FindAppCfg(APPID_DPA104 + ((APPVER_DPA104 & 0XFFFF00) << 8));
	if (pappl->pcfg == NULL)
	{
		db_PutInitLog("dpa104: no configuration file");
		return;
	}
	pappl->portnum = pappl->pcfg->portnum;						//g_numport
	if (pappl->portnum == NULL)
	{
		db_PutPrtLog("dpa104: no port configured");
		return;
	}

	pappl->pport = (struDpa10xPort*)malloc(sizeof(struDpa10xPort)*pappl->portnum);	//dpa101_pport
	if (pappl->pport == NULL)
	{
		db_PutPrtLog("dpa104: memory alloc err or portnum=0");
		return;
	}

	memset(pappl->pport, 0, sizeof(struDpa10xPort)*pappl->portnum);//��ʼ��
	pport = pappl->pport;
	ptmp = (uint8*)&pappl->pcfg->portcfg;
	for (i = 0; i<pappl->portnum; i++, pport++)
	{
		pportcfg = (struDpa10xPort_Cfg*)ptmp;	//pportcfg = dpa101_FindPortCfg(pappl->pcfg, i);
		pport->pcfg = pportcfg;					//pport->pcfg

		pport->frmnum = (int16)pportcfg->frmnum;		//pport->frmnum
		pport->pfrm = (struDpa10xFrm *)malloc(sizeof(struDpa10xFrm)*pport->frmnum);//pport->pfrm
		if (pport->pfrm == NULL)
		{
			db_PutPrtLog("dpa104: memory alloc err or frmnum=0");
			return;
		}

		memset(pport->pfrm, 0, sizeof(struDpa10xFrm)*pport->frmnum);
		pfrm = pport->pfrm;
		ptmp = (uint8*)&pportcfg->frmcfg;
		for (j = 0; j<pport->frmnum; j++, pfrm++)
		{
			pfrmcfg = (struDpa10xFrm_Cfg *)ptmp;//dpa101_FindFrmCfg(pportcfg, j);
			pfrm->pcfg = pfrmcfg;				//pfrm->pcfg

			pfrm->pntnum = pfrmcfg->pntnum;			//pfrm->pntnum
			pfrm->ppntcfg = &pfrmcfg->pntcfg;			//pfrm->ppntcfg

			ptmp = (uint8*)pfrm->ppntcfg;
			if (pfrmcfg->frmtype == M_SP_TA_1 || pfrmcfg->frmtype == M_SP_TB_1 || pfrmcfg->frmtype == 42)		//pntcfg
				ptmp += pfrmcfg->pntnum*sizeof(struDpa10xSp_Cfg);
			else if (pfrmcfg->frmtype == M_DP_TA_1 || pfrmcfg->frmtype == M_DP_TB_1)
				ptmp += pfrmcfg->pntnum*sizeof(struDpa10xDp_Cfg);
			else if (pfrmcfg->frmtype == M_ME_NA_1 || pfrmcfg->frmtype == M_ME_NB_1 || pfrmcfg->frmtype == M_ME_NC_1)
				ptmp += pfrmcfg->pntnum*sizeof(struDpa10xMe_Cfg);
			else if (pfrmcfg->frmtype == M_IT_NA_1)
				ptmp += pfrmcfg->pntnum*sizeof(struDpa10xIt_Cfg);
			else if (pfrmcfg->frmtype == C_SC_NA_1 || pfrmcfg->frmtype == C_DC_NA_1)
				ptmp += pfrmcfg->pntnum*sizeof(struDpa10xDc_Cfg);
			else if (pfrmcfg->frmtype == C_SE_NA_1 || pfrmcfg->frmtype == C_SE_NB_1 || pfrmcfg->frmtype == C_SE_NC_1)
				ptmp += pfrmcfg->pntnum*sizeof(struDpa10xSe_Cfg);
		}

		pport->ginum = *(int32*)ptmp;		//ginum
		ptmp += sizeof(int32);
		pport->pgicfg = (struDpa10xGrp_Cfg*)ptmp;
		ptmp += sizeof(struDpa10xGrp_Cfg)*pport->ginum;

		pport->cinum = *(int32*)ptmp;		//cinum
		ptmp += sizeof(int32);
		pport->pcicfg = (struDpa10xGrp_Cfg*)ptmp;
		ptmp += sizeof(struDpa10xGrp_Cfg)*pport->cinum;

		dpa10x_ResetCounters(pport);
		pport->dpaH = db_GetDpaHand();

		//dpa104_SocketOpen(pport);
	}

	memset(&SockInf, 0, sizeof(SockInf));

	sprintf(out, "dpa104: %d port configured, init ok", pappl->portnum);
	db_PutInitLog(out);

	f_Dpa104Init = TRUE;
}


void dpa104V1(void) //��main()��ѭ�������
{
	static BOOL f_appdelay = 1;
	struDpa10xPort *pport;
	int i;
	uint32 tick;

	if (f_Dpa104Init == FALSE)return;

	tick = glb_sysTick; 	//Ӧ����ʱappdelay���ʼִ��
	if (f_appdelay && tick<(uint32)dpa104appl.pcfg->appdelay * 1000)return;
	f_appdelay = 0;

	//--------
	dpa104_SocketOpen();//ɨ��˿���������ձ���

	for (pport = dpa104appl.pport, i = 0; i<dpa104appl.portnum; i++, pport++)
	{
		if (pport->frmnum == 0)continue;

		if (pport->portsts1 != TCP_WAIT && pport->portsts2 != TCP_WAIT)continue;
		dpa104_Scan(pport);//���SOEɨ�衢�����Զ����͡�ͨѶ״̬�жϵȷ��շ����֡�
		dpa104_Send(pport);
	}
}





/*
101��������ṹ��104�������
dpa101()_______dpa101_Scan()______SoeScan()
        |______dpa101_Recv()______dpa101_AppLayer()
		|______dpa101_Send()______dpa101_GetClass1Data()
		                    |_____dpa101_GetClass2Data()

==============================================================

dpa104()_______dpa104_Scan()______SoeScan()
		|______dpa101_Send()______dpa104_GetClass1Data()
		                    |_____dpa104_GetClass2Data()

DRIVER����dpa104_Recv()______dpa101_AppLayer()
==============================================================


1.dpa101_Scan()�Թ̶�������ִ�У�����SOE�������Զ����͡����豸ͨѶ״̬�ȡ�
2.dpa101_Recv()��������ȡ���ģ�������·�㣬
���ݽ��յ���·�������ͣ���Ӧ�����·�������ʹ����pport->sendframes��,
����dpa101_AppLayer()���Ӧ�ò㴦������ҪӦ���1������������class1_buffer.
3.dpa101_Send()������pport->sendframes�����װ���ģ�����Ӧ�ò㱨��ͨ��dpa101_GetClass1Data()��dpa101_GetClass2Data()�õ���
һ��ѯ��ֻ�����һ��Ӧ�����pport->sendframesÿ��Ӧ�����0.
4.����֧�������˿ڣ��ĸ����յ������ĸ���Ӧ�𣬲���λ�˿ڵ�ͨѶ״̬��


��Ҫʵ�ֵ�������ϵͳƽ̨���֣�
void glb_GetTime(SOETIME *time);//SOETIME����ϵͳTIME STRUCTURE����
void glb_SetTime(SOETIME *time);
uint8 * glb_FindAppCfg(uint32 appidver);//���ұ�Ӧ�����ã���������������ָ�룬������applid version size
uint32 glb_GetFreeTick(void);//��ȡϵͳfree running tick,32λ

uart_Init(uint8 portnr, uint32 baudrate, uint8 parity, RXSIZE, TXSIZE, COMMODE_FRM)//0:COMMODE_FRM֡��ʽ���Գ�ʱ�ж�֡���� 1:COMMODE_STREAM�����������
uart_RecvFrame(uint8 portnr, uint8 *rbuf);//portnr��0��ʼ
uart_Send(uint8 portnr, uint8 *tbuf, int16 len);
socke_Open, sock_Read, sock_Send....
�������ӡ��շ�������Ҫ����DRIVER���иĶ���
portnr: 0��ʾ�����ã� 1��63���ڣ� 64��69����


������һ����ʱ���Բ�ʵ�֣���س���ע�����
void glb_PutSCommLog(uint8 portnr, char*);//��ά�����ʹ��п�ͨѶLOG���籨�ķ�����
void glb_PutSCommCode(uint8 portnr, uint8*, int len, uint8 dir);//��ά�����ʹ��п�ͨѶ�룬 dirΪTX��RX
void glb_PutSCommSts(uint8 portnr, uint8 sts);//���ô���ͨѶ״̬���õ�Ϊϵͳ���е�
uint8 glb_GetSCommSts(uint8 portnr);//��ȡ����ͨѶ״̬

==============================================================


dpa101_PortOpen()���ϳ���Ϊ���ֱ��ġ����ֹ��ܵ��߼���Ϊ101 104���ò��֣���������Ҫ�޸ģ����Ƿ���BUG
���³���Ϊ��Լ��·��ͨѶ���ܣ��ɸĶ�ͨѶDRIVER�ӿں�Recv()��Send()���û��ƣ����Ķ���Э�鴦���йصĲ��֡�

���������ѻ������Ժã�����Ҫѭ������dpa101()��
#ifdef DDEBUGΪ���Դ��룬#elseΪʵ�ʴ���

�����DRIVER����RECEIVE�����ɽ����жϷ���receive��������
�������dpa101_Recv()�������������һ������������:
dpa101_Receive()
{
struDpa101Port *pport;
int i;

	for (pport = dpa101appl.pport, i = 0; i<dpa101appl.portnum; i++, pport++)
		dpa101_Recv(pport);
}


==============================================================

���������ڣ�
101�������Ƚϼ򵥣��ĸ������ĸ��ڻأ��ڲ�����ȫһ�׶�����

104�Ƚ��鷳���ж���������ʽ��
��0�֣�˫�ڻ�Ϊ���ƣ�ͬʱ��һ���ı��ġ�
��1�֣�˫��ͬʱ��������������վֻ��������һ���ڵģ�
��2�֣���ͨ����������ͨ��Ҳ�������ӣ�����ΪTEST֡��
��3�֣�ֻ����һ�����ӣ���һ��ֻ��PING,����pingҲû�У�
������2��3��ʽ�Ӷࡣ
V0100���������������: �����ڵ����ӷֱ������������Ӻ�portsts1/2��λPORTSTS_RUN;
Ȼ�󲻹��ĸ��ڹ�����STARTDT��U֡���ĸ������ĸ��ڻأ�startdt1/2��λ��
�Ժ���֡����ʱ��I,S֡��������startdt�Ŀڣ���ȻҲ�������ڶ�����������ΪֻҪ��վ˫�ڶ�STARTDT����װ�þ���Ҫ˫��ͬʱ����
�����վ�ǵ�2�з�ʽ����ֻ��һ����STARTDT��
�ж����ӹ���ʱ���ڶ����жϣ�����CLOSE SOCKET.��ĳ����RUN̬������̬�������δȷ��֡���ڵ���ʱû���յ�I,S֡��
��CLOSE�ÿ����ӣ�portsts1/2=0����RUN̬�Ŀ������������Ǳ�������һ��ʱ���յ�֡��δ�յ���CLOSE��δȷ��֡����˵��û��һ��
�����ڣ����Ա���Ҳ��CLOSE��
104Э��Ҫ�������½������Ӻ�SN��0����˫�����Э����û�涨������������Ǳ��ڣ���벻��Ҫ��SN���緽ʽ2��3��
�������յ�STARTDT����ʱ��SN��������0��2��3��ʽ�����ã�����1��ʽҪ����վ�Ĵ����ˣ���ʱ���ٿ�����İ�,
�����ټ�һ��SN��

*/
