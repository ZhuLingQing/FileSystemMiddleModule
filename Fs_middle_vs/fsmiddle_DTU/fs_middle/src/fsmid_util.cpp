#include "fsmid_def.h"
#include "fsmid_port.h"
#include "fsmid_config.h"
#include <string.h>

//static const unsigned char ctbl_counter[8] = {0xFF,0x7F,0x3F,0x1F,0x0F,0x07,0x03,0x01};

unsigned int bitmap2number(unsigned char* bitmap, unsigned int length)
{
	unsigned int result = 0;
	int j;

	while(length)
	{
		if(*bitmap == 0)
			result += 8;
		else
		{
			for(j = 0; j < 8; j++ )
			{
				if(*bitmap == (0xFF>>j))
					return (result + j);
			}
			fsmid_assert(0,__FILE__,__LINE__);
		}
		bitmap++;
		length--;
	}

	return result;
}

void number2bitmap(unsigned int number, unsigned char* bitmap, unsigned int length)
{
	fsmid_assert(number <= (length*8),__FILE__,__LINE__);

	memset(bitmap,0,number/8);
	bitmap += number/8;
	length -= number/8;

	if(number%8)
	{
		*bitmap = 0xFF>>(number%8);
		bitmap++;
		length--;
	}
	memset(bitmap,0xFF,length);
}

bool systimeSameDay(const SYS_TIME64 *tm1, const SYS_TIME64 *tm2)
{
	if(SYSTM64_SAMEDAY(tm1,tm2))
		return true;
	return false;
}

#include <time.h>
static const int MON1[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};   //ƽ��  
static const int MON2[12] = {31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};   //����  
static const int FOURYEARS = (366 + 365 +365 +365); //ÿ�������������  
static const int SEC_PER_DAY = 24*3600;   //ÿ�������  

bool unixSameDay(unsigned int tm1, unsigned int tm2)
{
	tm1 /= SEC_PER_DAY;
	tm2 /= SEC_PER_DAY;
	if(tm1 == tm2)
		return true;
	return false;
}

void __get_day(int nDays, SYS_TIME64 *systime, bool IsLeapYear)  
{  
	const int *pMonths = IsLeapYear?MON2:MON1;  
	//ѭ����ȥ12������ÿ���µ�������ֱ��ʣ������С�ڵ���0�����ҵ��˶�Ӧ���·�  
	for ( int i=0; i<12; ++i )  
	{  
		int nTemp = nDays - pMonths[i];  
		if ( nTemp<=0 )  
		{  
			systime->mon = i+1;  
			if ( nTemp == 0 )//��ʾ�պ�������µ����һ�죬��ô������������µ���������  
				systime->day = pMonths[i];  
			else  
				systime->day = nDays;  
			break;  
		}  
		nDays = nTemp;  
	}  
}  

unsigned int time_sys2unix(const SYS_TIME64 *systime)
{
	struct tm stm; 
	memset(&stm,0,sizeof(stm)); 

	stm.tm_year=systime->year - 1900 + 2000; 
	stm.tm_mon=systime->mon-1; 
	stm.tm_mday=systime->day; 
	stm.tm_hour=systime->hour; 
	stm.tm_min=systime->min; 
	stm.tm_sec=systime->sec; 

	return (unsigned int)_mktime32(&stm);  
}

void time_unix2sys(unsigned int unix, SYS_TIME64 *systime)
{
	unix += 8*3600;//����ʱ�� +8Сʱ
	int nDays = unix/SEC_PER_DAY + 1;    //time������ȡ���Ǵ�1970�������ĺ������������Ҫ�ȵõ�����  
	int nYear4 = nDays/FOURYEARS;   //�õ���1970�����������ڣ�4�꣩�Ĵ���  
	int nRemain = nDays%FOURYEARS;  //�õ�����һ�����ڵ�����  
	systime->year = 1970 + nYear4*4 - 2000;  
	bool bLeapYear = false;
	if ( nRemain<365 )//һ�������ڣ���һ��  
	{//ƽ��  

	}  
	else if ( nRemain<(365+365) )//һ�������ڣ��ڶ���  
	{//ƽ��  
		systime->year += 1;  
		nRemain -= 365;  
	}  
	else if ( nRemain<(365+365+365) )//һ�������ڣ�������  
	{//ƽ��  
		systime->year += 2;  
		nRemain -= (365+365);  
	}  
	else//һ�������ڣ������꣬��һ��������  
	{//����  
		systime->year += 3;  
		nRemain -= (365+365+365);  
		bLeapYear = true;  
	}  
	__get_day(nRemain, systime, bLeapYear);
	systime->hour = (unix % SEC_PER_DAY)/3600;
	systime->min = (unix% 3600)/60;
	systime->sec = unix % 60;
	systime->msec = 0;
}
