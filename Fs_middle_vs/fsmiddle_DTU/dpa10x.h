
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



typedef enum
{
	TypeidDi,
	TypeidAi,
	TypeidDo,
	TypeidPa,
	TypeidPara,
}enumTYPID_GRP;


#define RXSIZE	263
#define TXSIZE  272
#define CLASS1BUFSIZE	1024
#define CLASS2BUFSIZE	128

#define DPA10x_SUPPORT_LOG	
/***************************************************************/

//����structures, ��cpu internal flash���������ݵĽṹ��ʽ

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



////////////////////////////////////////////////////////////

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



//////////////////////////////////
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

extern struDpa10xApp dpa101appl;


/*
input:
pport: &dpa101appl.pport[0]
syspnt:Ҫsearch��ϵͳ���
typgrp:ң�š�ң��Ĵ���

output:
frm: ��������pport��֡ƫ��
pnt: �����֡��ƫ��
otherpnt: �����ҵ�����˫��ң��֡ʱ��������һ��ϵͳ���syspnt��
inf: ����õ���Ϣ�����

return:
ָ������ã���struDpa10xSp_Cfg *����ָ��
*/
extern void* dpa10x_SearchSyspntInFrms(struDpa10xPort *pport, int16 syspnt, enumTYPID_GRP typgrp, int8 *frm, int16 *pnt, int16 *otherpnt, uint32 *inf);

