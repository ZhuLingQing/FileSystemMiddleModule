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

void systimeToCp56(const SYS_TIME64 *tm64,CP56TIME2A * cp56)
{
	fsmid_assert(cp56&&tm64,__FUNCTION__,__LINE__);
	cp56->year = tm64->year;
	cp56->month = tm64->mon;
	cp56->monthDay = tm64->day;

	cp56->hour = tm64->hour;
	cp56->minute = tm64->min;
	cp56->milliSecond = tm64->sec;
	cp56->milliSecond *= 1000;
	cp56->milliSecond += tm64->msec;

	cp56->summerTime = 0;
	cp56->invalid = 0;
	if(tm64->mon < 2)
		cp56->weekDay = (tm64->year-1)+(tm64->year-1)/4-35+26*(cp56->month+13)/10+tm64->day-1;
	else
		cp56->weekDay = tm64->year+tm64->year/4-35+26*(cp56->month+1)/10+tm64->day-1;
}

void cp56ToSystime(const CP56TIME2A *cp56, SYS_TIME64 *tm64)
{
	fsmid_assert(cp56&&tm64,__FUNCTION__,__LINE__);
	tm64->year = cp56->year;
	tm64->mon = cp56->month;
	tm64->day = cp56->monthDay;

	tm64->hour = cp56->hour;
	tm64->min = cp56->minute;
	tm64->sec = cp56->milliSecond/1000;
	tm64->msec = cp56->milliSecond%1000;
}


unsigned char byteChecksum(unsigned char seed, unsigned char *buf, unsigned int length)
{
	unsigned char res = seed;
	while(length--)
		res = *buf++;
	return res;
}