#include "dbmsV1.h"
#include "dpa10x.h"
#include <string.h>
#include "fs_middle.h"

#ifdef CPU_MK64FN1M0VMD12
static unsigned int numInfoAddrLen;
#endif
static FSMID_POINT* tableMeasure = NULL;
static unsigned int numMeasure = 0;

static LOG_EXTREME *tableMaximum = NULL;
static LOG_EXTREME *tableMinimum = NULL;


static FSMID_POINT* tableFrozen = NULL;
static unsigned int numFrozen = 0;

#define MEASURE_CONFIG_SIG		0x5341454D	//"FSMD"
#define FROZEN_CONFIG_SIG		0x4E5A5246	//"FRZN"
#define INFORMATION_CONFIG_SIG	0x4F464E49	//"INFO"

typedef struct __st_fsmid_config_point{
	unsigned int signature;
	unsigned int number;
	FSMID_POINT point[0];
}FSMID_CONFIG_POINT;

typedef struct __st_fsmid_config_information{
	unsigned int signature;
	unsigned int number;
	FSLOG_INFORMATION information[0];
}FSMID_CONFIG_INFORMATION;

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

int FSMID_InitConfig()
{
	int i, j;
	struDpa10xFrm *pfrm;
	void *ppntcfg = NULL;
	struDpa10xMe_Cfg *pMeCfg;
	struDpa10xIt_Cfg *pItCfg;
	uint32 inf;
	FSMID_POINT *pPoint;
	FSMID_CONFIG_POINT *pConfigPoint;
	FSMID_CONFIG_INFORMATION *pConfigInformation;
	unsigned int numInformation = 0;

	#ifdef CPU_MK64FN1M0VMD12
	numInfoAddrLen = (unsigned int)dpa101appl.pcfg->portcfg.inflen;
	#endif

	pfrm = dpa101appl.pport->pfrm;
	if(pfrm == NULL) return FSMIDR_ACCESS;
	for (i = 0,numMeasure = 0; i < dpa101appl.pport->frmnum; i++, pfrm++)
	{
		if (pfrm->pcfg->frmtype == M_ME_NC_1)//仅处理浮点遥测帧
		{
			numMeasure += pfrm->pntnum;
		}
		else if (pfrm->pcfg->frmtype == M_IT_NB_1)//仅处理浮点累积量
		{
			numFrozen += pfrm->pntnum;
		}
	}
	if(numMeasure)
	{
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

		pPoint = tableMeasure;
		pfrm = dpa101appl.pport->pfrm;
		for (i = 0; i < dpa101appl.pport->frmnum; i++, pfrm++)
		{
			if (pfrm->pcfg->frmtype == M_ME_NC_1)//仅处理浮点遥测帧
			{
				inf = pfrm->pcfg->frminf;//起始信息对象
				pMeCfg = (struDpa10xMe_Cfg *)pfrm->ppntcfg;//指向flash中的浮点遥测配置表
				for (j = 0; j < pfrm->pntnum; j++, pMeCfg++, inf++,pPoint++)
				{
					pPoint->information = inf;
					pPoint->point = pMeCfg->syspnt;
				}
			}
		}
	}

	if(numFrozen)
	{
		tableFrozen = fsmid_malloc(FSMID_POINT,numFrozen);
		fsmid_assert(tableMeasure && tableFrozen,__FILE__,__LINE__);

		pPoint = tableFrozen;
		pfrm = dpa101appl.pport->pfrm;
		for (i = 0; i < dpa101appl.pport->frmnum; i++, pfrm++)
		{
			if (pfrm->pcfg->frmtype == M_IT_NB_1)//仅处理浮点累积量
			{
				inf = pfrm->pcfg->frminf;//起始信息对象
				pItCfg = (struDpa10xIt_Cfg *)pfrm->ppntcfg;//指向flash中的浮点累积量配置表
				for (j = 0; j < pfrm->pntnum; j++, pItCfg++, inf++,pPoint++)
				{
					pPoint->information = inf;
					pPoint->point = pItCfg->syspnt;
				}
			}
		}
	}

	if(numMeasure == 0 || numFrozen == 0)
	{
		fsmid_warning("No measure or frozen point.");
		return FSMIDR_BAD_ARGUMENT;
	}
	while(pInfoTable[numInformation])
		numInformation++;

	pConfigPoint = (FSMID_CONFIG_POINT*)fsmid_malloc(unsigned char,sizeof(FSMID_CONFIG_POINT) + max(numMeasure,numFrozen)*sizeof(int));
	pConfigInformation = (FSMID_CONFIG_INFORMATION*)fsmid_malloc(unsigned char,sizeof(FSMID_CONFIG_INFORMATION) + numInformation*sizeof(FSLOG_INFORMATION));

	FSLOG_GetRegistedInterface()->read(START_ADDRESS_CONFIG+FLASH_BLOCK_SIZE*0,pConfigPoint,sizeof(FSMID_CONFIG_POINT) + numMeasure*4);
	if(pConfigPoint->signature != MEASURE_CONFIG_SIG || pConfigPoint->number != numMeasure || memcmp(pConfigPoint->point,tableMeasure,numMeasure*sizeof(int)))
	{
		fsmid_warning("Measure table changed.\r\n");
		goto ChangeCondition;
	}
	FSLOG_GetRegistedInterface()->read(START_ADDRESS_CONFIG+FLASH_BLOCK_SIZE*1,pConfigPoint,sizeof(FSMID_CONFIG_POINT) + numFrozen*4);
	if(pConfigPoint->signature != FROZEN_CONFIG_SIG || pConfigPoint->number != numFrozen || memcmp(pConfigPoint->point,tableFrozen,numFrozen*sizeof(int)))
	{
		fsmid_warning("Frozen table changed.\r\n");
		goto ChangeCondition;
	}
	FSLOG_GetRegistedInterface()->read(START_ADDRESS_CONFIG+FLASH_BLOCK_SIZE*2,pConfigInformation,sizeof(FSMID_CONFIG_INFORMATION) + numInformation*sizeof(FSLOG_INFORMATION));
	if(pConfigInformation->signature == INFORMATION_CONFIG_SIG && pConfigInformation->number == numInformation)
	{
		for(i = 0; i < numInformation; i++)
		{
			if(memcmp(&pConfigInformation->information[i],pInfoTable[i],sizeof(FSLOG_INFORMATION)) != 0)
			{
				fsmid_warning("Information table changed.\r\n");
				goto ChangeCondition;
			}
		}
	}
	else
	{
		fsmid_warning("Information table changed.\r\n");
		goto ChangeCondition;
	}

	fsmid_info("Configuartion not changed.\r\n");
	fsmid_free(pConfigPoint);
	fsmid_free(pConfigInformation);
	return FSMIDR_OK;

ChangeCondition:
	FSLOG_GetRegistedInterface()->erase(START_ADDRESS_CONFIG,FLASH_MEMORY_SIZE - START_ADDRESS_CONFIG);

	pConfigPoint->signature = MEASURE_CONFIG_SIG;
	pConfigPoint->number = numMeasure;
	memcpy(pConfigPoint->point,tableMeasure,numMeasure*sizeof(int));
	FSLOG_GetRegistedInterface()->write(START_ADDRESS_CONFIG+FLASH_BLOCK_SIZE*0,pConfigPoint,sizeof(FSMID_CONFIG_POINT) + numMeasure*sizeof(int));

	pConfigPoint->signature = FROZEN_CONFIG_SIG;
	pConfigPoint->number = numFrozen;
	memcpy(pConfigPoint->point,tableFrozen,numFrozen*sizeof(int));
	FSLOG_GetRegistedInterface()->write(START_ADDRESS_CONFIG+FLASH_BLOCK_SIZE*1,pConfigPoint,sizeof(FSMID_CONFIG_POINT) + numFrozen*sizeof(int));

	pConfigInformation->signature = INFORMATION_CONFIG_SIG;
	pConfigInformation->number = numInformation;
	for(i = 0; i < numInformation; i++)
		memcpy(&pConfigInformation->information[i],pInfoTable[i],sizeof(FSLOG_INFORMATION));
	FSLOG_GetRegistedInterface()->write(START_ADDRESS_CONFIG+FLASH_BLOCK_SIZE*2,pConfigInformation,sizeof(FSMID_CONFIG_INFORMATION) + numInformation*sizeof(FSLOG_INFORMATION));

	fsmid_free(pConfigPoint);
	fsmid_free(pConfigInformation);
	return FSMIDR_OK;
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
			//fsmid_info("MAX[%2d] = %7.3f\r\n",index,fValue);
		}
	}
	else if(tableMaximum[index].value >= 0 && fValue < 0)
	{
		if( fValue * -1.0 > tableMaximum[index].value)
		{
			memcpy(&tableMaximum[index].time,t64,sizeof(SYS_TIME64));
			tableMaximum[index].value = fValue;
			//fsmid_info("MAX[%2d] = %7.3f\r\n",index,fValue);
		}
	}
	else if(tableMaximum[index].value < 0 && fValue >= 0)
	{
		if( fValue > tableMaximum[index].value * -1.0 )
		{
			memcpy(&tableMaximum[index].time,t64,sizeof(SYS_TIME64));
			tableMaximum[index].value = fValue;
			//fsmid_info("MAX[%2d] = %7.3f\r\n",index,fValue);
		}
	}
	else if(tableMaximum[index].value < 0 && fValue < 0)
	{
		if(fValue < tableMaximum[index].value)
		{
			memcpy(&tableMaximum[index].time,t64,sizeof(SYS_TIME64));
			tableMaximum[index].value = fValue;
			//fsmid_info("MAX[%2d] = %7.3f\r\n",index,fValue);
		}
	}

	if(tableMinimum[index].value >= 0 && fValue >= 0)
	{
		if(fValue < tableMinimum[index].value)
		{
			memcpy(&tableMinimum[index].time,t64,sizeof(SYS_TIME64));
			tableMinimum[index].value = fValue;
			//fsmid_info("MIN[%2d] = %7.3f\r\n",index,fValue);
		}
	}
	else if(tableMinimum[index].value >= 0 && fValue < 0)
	{
		if( fValue * -1.0 < tableMinimum[index].value)
		{
			memcpy(&tableMinimum[index].time,t64,sizeof(SYS_TIME64));
			tableMinimum[index].value = fValue;
			//fsmid_info("MIN[%2d] = %7.3f\r\n",index,fValue);
		}
	}
	else if(tableMinimum[index].value < 0 && fValue >= 0)
	{
		if( fValue < tableMinimum[index].value * -1.0 )
		{
			memcpy(&tableMinimum[index].time,t64,sizeof(SYS_TIME64));
			tableMinimum[index].value = fValue;
			//fsmid_info("MIN[%2d] = %7.3f\r\n",index,fValue);
		}
	}
	else if(tableMinimum[index].value < 0 && fValue < 0)
	{
		if(fValue > tableMinimum[index].value)
		{
			memcpy(&tableMinimum[index].time,t64,sizeof(SYS_TIME64));
			tableMinimum[index].value = fValue;
			//fsmid_info("MIN[%2d] = %7.3f\r\n",index,fValue);
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
