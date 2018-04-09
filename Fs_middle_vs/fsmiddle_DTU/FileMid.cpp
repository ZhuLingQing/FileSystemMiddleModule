#include "dbmsV1.h"
//#include "flashshell.h"

bool flashshell_iFlash_Init(void);
bool flashshell_Erase(uint32 start, uint32 lengthInBytes);//lengthInBytes 16�����ֽڶ���
bool flashshell_Write(uint32 start, uint32 *src, uint32 lengthInBytes);//lengthInBytes 16�����ֽڶ���
bool flashshell_Read(uint32 start, uint32 *des, uint32 lengthInBytes);

//#include "board.h"

#include "dpa10x.h"
#include <string.h>

extern unsigned int dpaZzmaint_Crc16(void* pvBuff, int lens);


static bool f_ProgramUpgrade = false;
static uint8 confirmbuf[64];//�Ӳ�����ʶ��ʼ
static uint16 confirmlen;

enum
{
	TRANS_READ_FILE = 1,
	TRANS_WRITE_FILE,
};

typedef struct
{
	uint16 f_type;//��������
	uint32 addr;//�����ش洢Ŀ��λ�õ��׵�ַ
	uint32 totsize;//�ļ����ֽ���
	uint16 currsize;//���յ����ֽ���

}struFileMid_FileTrans;
static struFileMid_FileTrans FileTrans = { 0, 0, 0, 0 };


/*�����ļ���������*/
uint8 FileMid_101Requir(uint8 *rexbuf, uint16 rexlen, uint16 rcot)
{
	uint8 op;
	uint8 datacontinue = 0;
	uint16 i=0;
	uint16 m;
	uint16 tn;

	op = rexbuf[i++];//// ������ʶ
	switch (op)
	{
	case 1://��Ŀ¼����
		break;
	case 3://���ļ�����
		break;
	case 7://д�ļ����Ŀǰ�������������
		m = rexbuf[i++];//�ļ������� 
		i += m;//�ļ�������������������ļ���
		i += 4;//�ļ�ID;
		FileTrans.totsize = *(uint32*)&rexbuf[i];//�ļ���С
		i += 4;

		tn = 0;
		confirmbuf[tn++] = 8;//������ʶ��д�ļ�����ȷ��
		confirmbuf[tn++] = 0;//0�ɹ���1δ֪����2�ļ�����֧�֣�3���ȳ���Χ 
		memcpy(&confirmbuf[tn], &rexbuf[1], rexlen - 1);

		FileTrans.f_type = TRANS_WRITE_FILE;
		FileTrans.addr = 0x80000;//MEMADDR_FLASH_PRG1;
		FileTrans.currsize = 0;
		datacontinue = 2;//�к���class2
		break;

	case 9://д�ļ�����
		if (FileTrans.f_type == TRANS_WRITE_FILE)
		{
			uint32 addr = FileTrans.addr + FileTrans.currsize;
			if (flashshell_Write(addr, (uint32*)&rexbuf[10], rexlen - 10))//д��FLASH
			{
				FileTrans.currsize += rexlen - 10;

				tn = 0;
				confirmbuf[tn++] = 10;//������ʶ��д�ļ�����ȷ��
				memcpy(&confirmbuf[tn], &rexbuf[1], 8);//ID,���ݶκ�
				tn += 8;
				confirmbuf[tn++] = 0;//0�ɹ���1δ֪����2�ļ�����֧�֣�3���ȳ���Χ 
				datacontinue = 2;//�к���class2
			}
			else memset(&FileTrans, 0, sizeof(FileTrans));//д������Ӧ��ȷ��
		}
		else memset(&FileTrans, 0, sizeof(FileTrans));//д������Ӧ��ȷ��

		if(FileTrans.totsize && FileTrans.currsize == FileTrans.totsize)
		{
			memset(&FileTrans, 0, sizeof(FileTrans));

			if (f_ProgramUpgrade)
			{
				struPrgCfgCbk cbk;
				cbk.identify = MEMCTRLCBK_IDT;
				cbk.size = FileTrans.totsize;
				cbk.systick = glb_sysTick;
				cbk.chksum = dpaZzmaint_Crc16((uint8*)&cbk, sizeof(struPrgCfgCbk) - sizeof(uint16));
				flashshell_Write(0x80000+0x58000-64, (uint32*)&cbk, sizeof(struPrgCfgCbk));
				f_ProgramUpgrade = false;
			}
		}	
		break;
	}

	return datacontinue;
}


/*��ȡ����class1 class2����*/
uint8 FileMid_101Continue(uint8 *texbuf, uint16 *texlen, uint16 *tcot)
{
	uint8 datacontinue = 0;
	int datalen = 0;

	switch (FileTrans.f_type)
	{
	case TRANS_WRITE_FILE:
		if(confirmlen)
		{
			memcpy(texbuf, confirmbuf, confirmlen);
			datalen = confirmlen;
			confirmlen = 0;
		}
		break;

	case TRANS_READ_FILE:
		if(confirmlen)
		{
			memcpy(texbuf, confirmbuf, confirmlen);
			datalen = confirmlen;
			confirmlen = 0;
		}
		if(FileTrans.totsize && FileTrans.currsize < FileTrans.totsize)
			datacontinue = 2;
		break;
	}

	*texlen = datalen;
	return datacontinue;
}


/*�����������־*/
void FileMid_ProgramUpgrade(bool yes)
{
	f_ProgramUpgrade = yes;
	if(yes == true)
	{
		flashshell_Erase(0x80000/*MEMADDR_FLASH_PRG1, MEMSIZE_FLASH_PRG*/,0x58000);//����PRG1��CBK1
	}	
}

/************************************************************/
/************************************************************/


uint8 dpaH;

void FileMid_LogInit(void)
{
	dpaH = db_GetDpaHand();
}


typedef struct
{
	SYS_TIME64	time;//ʱ�䣬������sysTimer.h��
	uint8	val;//��ֵ 1�� 0��
	uint32 inf;
	int16 otherpnt;//˫���е���һ���㣬Ԥ�ڵ���һ��soe��ϵͳ���
}struSoeLog;

void FileMid_LogSave(void)
{
	int i, j;
	struDpa10xFrm *pfrm;
	void *ppntcfg = NULL;
	struDpa10xIt_Cfg *pItCfg;
	struDpa10xMe_Cfg *pMeCfg;
	struDpa10xDp_Cfg *pDpCfg;
	struDpa10xSp_Cfg *pSpCfg;

	struSoeLog soe1;
	SOEEVENT *psoe;

	uint32 inf;
	int8 frm;
	int16 pnt, otherpnt;
	bool flag=0;//��ʾ����ʱsoeδ����


	//����5���ӣ���ֵ1���1�Σ�0��档
	//1.�����¼, ʱ�䵽��������ң�����ñ���㱣��
	//2.��ֵ��¼�� ��������ң�����ñ���㴦�����ֵ����0:0:0��㱣��
	pfrm = dpa101appl.pport->pfrm;
	for (i = 0; i < dpa101appl.pport->frmnum; i++, pfrm++)
	{
		if (pfrm->pcfg->frmtype == M_ME_NC_1)//��������ң��֡
		{
			inf = pfrm->pcfg->frminf;//��ʼ��Ϣ����
			pMeCfg = (struDpa10xMe_Cfg *)pfrm->ppntcfg;//ָ��flash�еĸ���ң�����ñ�
			for (j = 0; j < pfrm->pntnum; j++, pMeCfg++, inf++)
			{
				int16 syspnt = pMeCfg->syspnt;
				float val = db_GetAi(dpaH, syspnt);
				//......save(inf,val)
			}
		}
	}

	//����������
	pfrm = dpa101appl.pport->pfrm;
	for (i = 0; i < dpa101appl.pport->frmnum; i++, pfrm++)
	{
		if (pfrm->pcfg->frmtype == M_IT_NB_1)//���������ۻ���
		{
			pItCfg = (struDpa10xMe_Cfg *)pfrm->ppntcfg;//ָ��flash�еĸ���ң�����ñ�
			for (j = 0; j < pfrm->pntnum; j++, pItCfg++, inf++)
			{
				int16 syspnt = pItCfg->syspnt;
				float val = db_GetPa(syspnt);
				//......save(inf,val)
			}
		}
	}

	//�¼������ļ�¼��
	//1.SOE��¼ ά����+ 101
	//2.trd��¼ ά����+ 101
	//3.ulog  ��101
	//4.prtlog ��ά����
	pfrm = dpa101appl.pport->pfrm;//ָ���1֡
	while (psoe = db_GetSoe(dpaH))
	{
		//1.save soeevent, ������event��¼��������ά���ڶ�ȡ��ά���ڽ�����¼��ȡ�����ļ��޹�
		//����soe trd prtlog
		;//save_raw_soe(*psoe);


		//2.save soe for 101
		//����soe trd ulog, ��soe��˫�㴦��, ulog����Ҫsearch��inf,ֱ�ӱ���
		//�������soeΪ������soe1Ϊ��ʱ����(struSoeLog soe1)
		ppntcfg = dpa10x_SearchSyspntInFrms(dpa101appl.pport, psoe->pnt, TypeidDi, &frm, &pnt, &otherpnt, &inf);//����ϵͳ���Ӧ�ĵ����õȣ����õ�inf

		if (ppntcfg == NULL)//û�ҵ���˵���㲻��101������
		{
			if(flag)
			{
				flag = 0;
				;//savesoelog(soe1.inf, soe1.val, soe1.time);
			}
			continue;
		}


		if (pfrm[frm].pcfg->frmtype == M_DP_TA_1 || pfrm[frm].pcfg->frmtype == M_DP_TB_1)	//�ҵ���˫��֡��
		{	
			pDpCfg = (struDpa10xDp_Cfg *)ppntcfg;//ָ�������

			if(flag == 1)//����ʱ������δ��SOE
			{
				if(psoe->pnt == soe1.otherpnt)//�ҵ���2��soe�������ϴ�soe�����汾��soe
				{
					flag = 0;
					soe1.time = psoe->time;
					soe1.val = ((db_GetDi(pDpCfg->syspnton)&1)<<1) | (db_GetDi(pDpCfg->syspntoff)&1);
					soe1.inf = inf;
					;//savesoelog(soe1.inf, soe1.val, soe1.time);
				}
				else //����ͬһ��˫��˫��ң�ŵ㣬�򱣴���ʱ����soe��Ȼ��ѱ�soe������ʱ����
				{
					;//savesoelog(soe1.inf, soe1.val, soe1.time);//�����ϴ�soe

					flag = 1;
					soe1.time = psoe->time;
					soe1.val = ((db_GetDi(pDpCfg->syspnton)&1)<<1) | (db_GetDi(pDpCfg->syspntoff)&1);
					soe1.inf = inf;
					soe1.otherpnt = otherpnt;
				}
			}
			else //û��δ������ʱ�������ѱ�soe������ʱ����soe1��
			{		
				flag = 1;
				soe1.time = psoe->time;
				soe1.val = ((db_GetDi(pDpCfg->syspnton)&1)<<1) | (db_GetDi(pDpCfg->syspntoff)&1);
				soe1.inf = inf;
				soe1.otherpnt = otherpnt;
			}
		}
		else //����֡�ĵ㣬ֱ�ӱ���log
		{
			if(flag)
				;//savesoelog(soe1.inf, soe1.val, soe1.time);

			pSpCfg = (struDpa10xSp_Cfg *)ppntcfg;
			flag = 0;
			soe1.time = psoe->time;
			soe1.val = (db_GetDi(pSpCfg->syspnt)&1)<<1;//�ѵ���SIQ����˫��DIQ
			soe1.inf = inf;
			;//savesoelog(soe1.inf, soe1.val, soe1.time);
		}
	}

	if(flag)
		;//savesoelog(soe1.inf, soe1.val, soe1.time);
}
