#include "StdAfx.h"
#include "MyDate.h"
#include <time.h>

MyDate::MyDate(int year,int month,int day,int hour,int minute,int second)
{
	m_year = year;
	m_month = month;
	m_day = day;
	m_hour = hour;
	m_minute = minute;
	m_second = second;
}

MyDate::MyDate(char * str)
{
	sscanf(str,"%d/%d/%d",&m_year,&m_month,&m_day);
}

MyDate::~MyDate(void)
{
}
void MyDate::FormatYearMonthWith(const char * str,char * format)
{
	sscanf(str,format,&m_year,&m_month);
}

void MyDate::FormatDateWithAbc(const char * str)
{
	m_year = (str[0]-'0')*1000+(str[1]-'0')*100+(str[2]-'0')*10+str[3]-('0');
	m_month = (str[4]-'0')*10+(str[5]-'0');
	m_day = (str[6]-'0')*10+(str[7]-'0');
}

void MyDate::FormatDateWith(const char * str,char * format)
{
	sscanf(str,format,&m_year,&m_month,&m_day);
}

void MyDate::FormatDateTimeWith(const char * str,char * format)
{
	sscanf(str,format,&m_year,&m_month,&m_day,&m_hour,&m_minute,&m_second);
}

void MyDate::FormatDateTimeWithAbc(const char * str)
{
	FormatDateWithAbc(str);
	sscanf(str+8,"%d:%d:%d",&m_hour,&m_minute,&m_second);
}

void MyDate::GetNowDate()
{
	struct tm now;
	_getsystime(&now);
	m_year = now.tm_year+1900;
	m_month = now.tm_mon+1;
	m_day = now.tm_mday;
	m_hour = now.tm_hour;
	m_minute = now.tm_min;
	m_second = now.tm_sec;
}

bool MyDate::operator < (MyDate & date)
{
	if (m_year == date.m_year)
	{
		if (m_month == date.m_month)
		{
			if (m_day == date.m_day)
			{
				if (m_hour == date.m_hour)
				{
					if (m_minute == date.m_minute)
					{						
						if (m_second < date.m_second)
							return true;
						else
							return false;
					}
					else if (m_minute < date.m_minute)
						return true;
					else
						return false;
				}
				else if (m_hour < date.m_hour)
					return true;
				else
					return false;
			}
			else if (m_day < date.m_day)
				return true;
			else
				return false;
		}
		else if (m_month < date.m_month)
			return true;
		else
			return false;
	}
	else if (m_year < date.m_year)
		return true;
	else
		return false;	
}

bool MyDate::operator <= (MyDate & date)
{
	if (m_year == date.m_year)
	{
		if (m_month == date.m_month)
		{
			if (m_day == date.m_day)
			{
				if (m_hour == date.m_hour)
				{
					if (m_minute == date.m_minute)
					{						
						if (m_second <= date.m_second)
							return true;
						else
							return false;
					}
					else if (m_minute < date.m_minute)
						return true;
					else
						return false;
				}
				else if (m_hour < date.m_hour)
					return true;
				else
					return false;
			}
			else if (m_day < date.m_day)
				return true;
			else
				return false;
		}
		else if (m_month < date.m_month)
			return true;
		else
			return false;
	}
	else if (m_year < date.m_year)
		return true;
	else
		return false;
}

bool MyDate::operator > (MyDate & date)
{
	if (m_year == date.m_year)
	{
		if (m_month == date.m_month)
		{
			if (m_day == date.m_day)
			{
				if (m_hour == date.m_hour)
				{
					if (m_minute == date.m_minute)
					{						
						if (m_second > date.m_second)
							return true;
						else
							return false;
					}
					else if (m_minute > date.m_minute)
						return true;
					else
						return false;
				}
				else if (m_hour > date.m_hour)
					return true;
				else
					return false;
			}
			else if (m_day > date.m_day)
				return true;
			else
				return false;
		}
		else if (m_month > date.m_month)
			return true;
		else
			return false;
	}
	else if (m_year > date.m_year)
		return true;
	else
		return false;
}
bool MyDate::operator >= (MyDate & date)
{
	if (m_year == date.m_year)
	{
		if (m_month == date.m_month)
		{
			if (m_day == date.m_day)
			{
				if (m_hour == date.m_hour)
				{
					if (m_minute == date.m_minute)
					{						
						if (m_second >= date.m_second)
							return true;
						else
							return false;
					}
					else if (m_minute > date.m_minute)
						return true;
					else
						return false;
				}
				else if (m_hour > date.m_hour)
					return true;
				else
					return false;
			}
			else if (m_day > date.m_day)
				return true;
			else
				return false;
		}
		else if (m_month > date.m_month)
			return true;
		else
			return false;
	}
	else if (m_year > date.m_year)
		return true;
	else
		return false;
}
bool MyDate::operator == (MyDate & date)
{
	if (m_year == date.m_year 
		&& m_month == date.m_month
		&& m_day == date.m_day
		&& m_hour == date.m_hour
		&& m_minute == date.m_minute
		&& m_second == date.m_second)
		return true;
	else
		return false;
}

bool MyDate::operator != (MyDate & date)
{
	if (m_year == date.m_year 
		&& m_month == date.m_month
		&& m_day == date.m_day
		&& m_hour == date.m_hour
		&& m_minute == date.m_minute
		&& m_second == date.m_second)
		return false;
	else
		return true;
}

void MyDate::SetLastDayOfMonth()
{
	switch(m_month)
	{
	case 2:
		if ((m_year%4 == 0 && m_year%100 != 0) || m_year%400 == 0)
			m_day = 29;
		else
			m_day = 28;
		break;
	case 4:
	case 6:
	case 9:
	case 11:
		m_day = 30;
		break;
	default:
		m_day = 31;
		break;
	}
}