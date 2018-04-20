#include <string.h>
#ifndef CPU_MK64FN1M0VMD12
#include "dbmsV1.h"
#endif
#include "fs_middle.h"
#include "dpa10x.h"

#ifdef CPU_MK64FN1M0VMD12
static unsigned int numInfoAddrLen;
#endif
static FSMID_POINT* tableMeasure = NULL;
static unsigned int numMeasure;

static LOG_EXTREME *tableMaximum = NULL;
static LOG_EXTREME *tableMinimum = NULL;


static FSMID_POINT* tableFrozen = NULL;
static unsigned int numFrozen;

#define MEASURE_CONFIG_SIG		0x5341454D	//"FSMD"
#define FROZEN_CONFIG_SIG		0x4E5A5246	//"FRZN"

typedef struct __st_fsmid_config{
	unsigned int signature;
	unsigned int number;
	FSMID_POINT point[0];
}FSMID_CONFIG;

#define START_ADDRESS_CONFIG		(START_BLOCK_CONFIG*FLASH_BLOCK_SIZE)

#ifdef CPU_MK64FN1M0VMD12
unsigned int db_GetInfoAddressLength(void)
{
	return numInfoAddrLen;
}
const char *db_GetTerminalID()
{
	return (const char *)BOARD_STR_DEVTYP;
}
#endif

void FSMID_InitConfig()
{
	int bChanged = 0;
	int i, j;
	struDpa10xFrm *pfrm;
	void *ppntcfg = NULL;
	struDpa10xMe_Cfg *pMeCfg;
	struDpa10xIt_Cfg *pItCfg;
	uint32 inf;
	FSMID_POINT *pPoint;
	FSMID_CONFIG *pConfig;

	#ifdef CPU_MK64FN1M0VMD12
	numInfoAddrLen = (unsigned int)dpa101appl.pcfg->portcfg.inflen;
	#endif

	pfrm = dpa101appl.pport->pfrm;
	for (i = 0,numMeasure = 0; i < dpa101appl.pport->frmnum; i++, pfrm++)
	{
		if (pfrm->pcfg->frmtype == M_ME_NC_1)//��������ң��֡
		{
			numMeasure += pfrm->pntnum;
		}
		else if (pfrm->pcfg->frmtype == M_IT_NB_1)//���������ۻ���
		{
			numFrozen += pfrm->pntnum;
		}
	}

	tableMaximum = fsmid_malloc(LOG_EXTREME,numMeasure);
	memset(tableMaximum,0,sizeof(LOG_EXTREME)*numMeasure);
	tableMinimum = fsmid_malloc(LOG_EXTREME,numMeasure);
	memset(tableMinimum,0,sizeof(LOG_EXTREME)*numMeasure);
	for(i = 0; i < numMeasure; i++)
	{
		tableMaximum[i].pointIndex = i;
		tableMaximum[i].type = 0;
		tableMinimum[i].pointIndex = i;
		tableMinimum[i].type = 1;
	}

	tableMeasure = fsmid_malloc(FSMID_POINT,numMeasure);
	tableFrozen = fsmid_malloc(FSMID_POINT,numFrozen);
	fsmid_assert(tableMeasure && tableFrozen,__FILE__,__LINE__);

	pPoint = tableMeasure;
	pfrm = dpa101appl.pport->pfrm;
	for (i = 0; i < dpa101appl.pport->frmnum; i++, pfrm++)
	{
		if (pfrm->pcfg->frmtype == M_ME_NC_1)//��������ң��֡
		{
			inf = pfrm->pcfg->frminf;//��ʼ��Ϣ����
			pMeCfg = (struDpa10xMe_Cfg *)pfrm->ppntcfg;//ָ��flash�еĸ���ң�����ñ�
			for (j = 0; j < pfrm->pntnum; j++, pMeCfg++, inf++,pPoint++)
			{
				pPoint->information = inf;
				pPoint->point = pMeCfg->syspnt;
			}
		}
	}

	pPoint = tableFrozen;
	pfrm = dpa101appl.pport->pfrm;
	for (i = 0; i < dpa101appl.pport->frmnum; i++, pfrm++)
	{
		if (pfrm->pcfg->frmtype == M_IT_NB_1)//���������ۻ���
		{
			inf = pfrm->pcfg->frminf;//��ʼ��Ϣ����
			pItCfg = (struDpa10xIt_Cfg *)pfrm->ppntcfg;//ָ��flash�еĸ����ۻ������ñ�
			for (j = 0; j < pfrm->pntnum; j++, pItCfg++, inf++,pPoint++)
			{
				pPoint->information = inf;
				pPoint->point = pItCfg->syspnt;
			}
		}
	}

	if(numMeasure == 0 || numFrozen == 0)
	{
		fsmid_warning("No measure or frozen point.",__FILE__,__LINE__);
		return;
	}

	pConfig = fsmid_malloc(FSMID_CONFIG,1 + max(numMeasure,numFrozen)/2 + 1);
	FSLOG_GetRegistedInterface()->read(START_ADDRESS_CONFIG,pConfig,sizeof(FSMID_CONFIG) + numMeasure*4);
	if(pConfig->signature != MEASURE_CONFIG_SIG || pConfig->number != numMeasure || memcmp(pConfig->point,tableMeasure,numMeasure*sizeof(int)))
	{
		bChanged = 1;
	}
	FSLOG_GetRegistedInterface()->read(START_ADDRESS_CONFIG+FLASH_BLOCK_SIZE,pConfig,sizeof(FSMID_CONFIG) + numFrozen*4);
	if(pConfig->signature != FROZEN_CONFIG_SIG || pConfig->number != numFrozen || memcmp(pConfig->point,tableFrozen,numFrozen*sizeof(int)))
	{
		bChanged = 1;
	}

	if(bChanged)
	{
		FSLOG_GetRegistedInterface()->erase(START_ADDRESS_CONFIG,FLASH_MEMORY_SIZE - START_ADDRESS_CONFIG);

		pConfig->signature = MEASURE_CONFIG_SIG;
		pConfig->number = numMeasure;
		memcpy(pConfig->point,tableMeasure,numMeasure*sizeof(int));
		FSLOG_GetRegistedInterface()->write(START_ADDRESS_CONFIG,pConfig,sizeof(FSMID_CONFIG) + numMeasure*4);

		pConfig->signature = FROZEN_CONFIG_SIG;
		pConfig->number = numFrozen;
		memcpy(pConfig->point,tableFrozen,numFrozen*sizeof(int));
		FSLOG_GetRegistedInterface()->write(START_ADDRESS_CONFIG+FLASH_BLOCK_SIZE,pConfig,sizeof(FSMID_CONFIG) + numFrozen*4);
	}

	fsmid_free(pConfig);
}

FSMID_POINT * const GetMeasureTable()
{
	return tableMeasure;
}

unsigned int GetMeasureCount()
{
	return numMeasure;
}

LOG_EXTREME * const GetMaximumTable()
{
	return tableMaximum;
}

LOG_EXTREME * const GetMinimumTable()
{
	return tableMinimum;
}

void ResetExtremeTable()
{
	#define FLT_MAX         3.402823466e+38F
	#define FLT_MIN         1.175494351e-38F
	unsigned int i;
// 	unsigned int *pMax = (unsigned int*)tableMaximum;
// 	unsigned int *pMin = (unsigned int*)tableMinimum;
	for( i = 0; i < numMeasure; i++ )
	{
		tableMaximum[i].value = FLT_MIN;
		tableMinimum[i].value = FLT_MAX;
	}
}

void UpdateExtremeValue(const SYS_TIME64 *t64, unsigned int index, float fValue)
{
	if(tableMaximum[index].value >= 0 && fValue >= 0)
	{
		if(fValue > tableMaximum[index].value)
		{
			memcpy(&tableMaximum[index].time,t64,sizeof(SYS_TIME64));
			tableMaximum[index].value = fValue;
			//fsmid_info("MAX[%2d] = %7.3f\n",index,fValue);
		}
	}
	else if(tableMaximum[index].value >= 0 && fValue < 0)
	{
		if( fValue * -1.0 > tableMaximum[index].value)
		{
			memcpy(&tableMaximum[index].time,t64,sizeof(SYS_TIME64));
			tableMaximum[index].value = fValue;
			//fsmid_info("MAX[%2d] = %7.3f\n",index,fValue);
		}
	}
	else if(tableMaximum[index].value < 0 && fValue >= 0)
	{
		if( fValue > tableMaximum[index].value * -1.0 )
		{
			memcpy(&tableMaximum[index].time,t64,sizeof(SYS_TIME64));
			tableMaximum[index].value = fValue;
			//fsmid_info("MAX[%2d] = %7.3f\n",index,fValue);
		}
	}
	else if(tableMaximum[index].value < 0 && fValue < 0)
	{
		if(fValue < tableMaximum[index].value)
		{
			memcpy(&tableMaximum[index].time,t64,sizeof(SYS_TIME64));
			tableMaximum[index].value = fValue;
			//fsmid_info("MAX[%2d] = %7.3f\n",index,fValue);
		}
	}

	if(tableMinimum[index].value >= 0 && fValue >= 0)
	{
		if(fValue < tableMinimum[index].value)
		{
			memcpy(&tableMinimum[index].time,t64,sizeof(SYS_TIME64));
			tableMinimum[index].value = fValue;
			//fsmid_info("MIN[%2d] = %7.3f\n",index,fValue);
		}
	}
	else if(tableMinimum[index].value >= 0 && fValue < 0)
	{
		if( fValue * -1.0 < tableMinimum[index].value)
		{
			memcpy(&tableMinimum[index].time,t64,sizeof(SYS_TIME64));
			tableMinimum[index].value = fValue;
			//fsmid_info("MIN[%2d] = %7.3f\n",index,fValue);
		}
	}
	else if(tableMinimum[index].value < 0 && fValue >= 0)
	{
		if( fValue < tableMinimum[index].value * -1.0 )
		{
			memcpy(&tableMinimum[index].time,t64,sizeof(SYS_TIME64));
			tableMinimum[index].value = fValue;
			//fsmid_info("MIN[%2d] = %7.3f\n",index,fValue);
		}
	}
	else if(tableMinimum[index].value < 0 && fValue < 0)
	{
		if(fValue > tableMinimum[index].value)
		{
			memcpy(&tableMinimum[index].time,t64,sizeof(SYS_TIME64));
			tableMinimum[index].value = fValue;
			//fsmid_info("MIN[%2d] = %7.3f\n",index,fValue);
		}
	}
}


FSMID_POINT * const GetFrozenTable()
{
	return tableFrozen;
}

unsigned int GetFrozenCount()
{
	return numFrozen;
}
