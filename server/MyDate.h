#pragma once

class MyDate
{
private:
	int m_year,m_month,m_day;
	int m_hour,m_minute,m_second;
public:
	MyDate(int year=0,int month=0,int day=0,int hour=0,int minute=0,int second=0);
	MyDate(char *);
	~MyDate(void);

	int GetYear(){
		return m_year;
	}

	int GetMonth(){
		return m_month;
	}

	int GetDay(){
		return m_day;
	}

	int GetHour(){
		return m_hour;
	}

	int GetMinute(){
		return m_minute;
	}

	int GetSecond(){
		return m_second;
	}

	void SetDate(int year,int month,int day)
	{
		this->m_year = year;
		this->m_month = month;
		this->m_day = day;
	}
	void SetTime(int hour,int minute,int second)
	{
		this->m_hour = hour;
		this->m_minute = minute;
		this->m_second = second;
	}

	void SetDay(int day)
	{
		this->m_day = day;
	}

	void SetPreMonth()
	{
		if (m_month == 1)
		{
			m_month = 12;
			m_year--;
		}else
			m_month--;
	}

	void SetLastDayOfMonth();

	void FormatYearMonthWith(const char * str,char * format);
	void FormatDateWithAbc(const char * str);
	void FormatDateWith(const char * str,char * format);
	void FormatDateTimeWith(const char * str,char * format);
	void FormatDateTimeWithAbc(const char * str);	

	void FormatYearMonth(char * pdata,char * formate="%04d-%02d")
	{	
		sprintf(pdata,formate,m_year,m_month);
	}

	void FormatDate(char * pdata,char * formate="%04d-%02d-%02d")
	{	
		sprintf(pdata,formate,m_year,m_month,m_day);
	}

	void FormatDateTime(char * pdata,char * formate="%04d-%02d-%02d %02d:%02d:%02d")
	{	
		sprintf(pdata,formate,m_year,m_month,m_day,m_hour,m_minute,m_second);
	}

	void FormatTime(char * pdata,char * formate="%02d:%02d:%02d")
	{	
		sprintf(pdata,formate,m_hour,m_minute,m_second);
	}

	void FormatYear(char * pdata,char * formate="%04d")
	{	
		sprintf(pdata,formate,m_year);
	}

	void FormatMonth(char * pdata,char * formate="%02d")
	{	
		sprintf(pdata,formate,m_month);
	}
	void FormatDay(char * pdata,char * formate="%02d")
	{	
		sprintf(pdata,formate,m_day);
	}

	void GetNowDate();

	bool operator < (MyDate & date);	
	bool operator <= (MyDate & date);
	bool operator > (MyDate & date);
	bool operator >= (MyDate & date);
	bool operator == (MyDate & date);
	bool operator != (MyDate & date);
};
