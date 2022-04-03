#include "StdAfx.h"
#include "AccessDB.h"


AccessDB::AccessDB(void)
{
	m_dbConnection = NULL;
	m_dbRecordSet = NULL;
}

AccessDB::~AccessDB(void)
{
}

BOOL AccessDB::OpenDataBase(char * dbName)
{
	try{
		//WriteLog(dbName);
		::CoInitialize(NULL);
		if (FAILED(m_dbConnection.CreateInstance("ADODB.Connection")))
			return false;
		char connectStr[128];
		strcpy(connectStr,"Provider=Microsoft.Jet.OLEDB.4.0;Data Source=");
		//strcpy(connectStr,"Provider=Microsoft.ACE.OLEDB.12.0;Data Source="); //2007及以上版本
		strcat(connectStr,dbName);
		strcat(connectStr,";Persist Security Info=False");
		m_dbConnection->Open((_bstr_t)connectStr,"","",adModeUnknown);
		return true;
	}catch(_com_error e)
	{
		//WriteLog(e.Description());
	
		return false;
	}
}

BOOL AccessDB::Query(char * strSql)
{
	//WriteLog(strSql);
	try{
		if (FAILED(m_dbRecordSet.CreateInstance("ADODB.RecordSet")))
			return false;
		_variant_t varSQL(strSql);
		if(FAILED(m_dbRecordSet->Open(varSQL,m_dbConnection.GetInterfacePtr(),adOpenDynamic,adLockOptimistic,adCmdText)))
		{
			//WriteLog("查询失败");
			return false;	
		}
		return true;
	}
	catch(_com_error e)
	{
		//WriteLog(e.Description());
		return false;
	}
}

BOOL AccessDB::Update(char * strSql)
{
	try{
		_variant_t RecordsAffected;
		_bstr_t varSQL(strSql);
		if(FAILED(m_dbConnection->Execute(varSQL,&RecordsAffected,adCmdText)))
		{
			//WriteLog("更新失败");
			return false;	
		}
		return true;
	}
	catch(_com_error e)
	{
		//WriteLog(e.Description());
		return false;
	}
}



void AccessDB::ReadString(char * col,char *value)
{
	try{
		_variant_t data;
		data = m_dbRecordSet->GetCollect(col);
		if (data.vt == VT_NULL)
			value[0] = 0;
		else
			strcpy(value,(char *)(_bstr_t)data);
	}catch(_com_error e)
	{
		value[0] = 0;
	}
}

double AccessDB::ReadDouble(char * col)
{
	try{
		_variant_t data;
		data = m_dbRecordSet->GetCollect(col);
		if (data.vt == VT_NULL)
			return 0;
		return data;
	}catch(_com_error e)
	{
		return 0;
	}	
}

MyDate AccessDB::ReadDate(char * col)
{
	MyDate dt;
	try{
		_variant_t data;
		data = m_dbRecordSet->GetCollect(col);
		if (data.vt == VT_DATE)
		{
			COleDateTime odt = COleDateTime(data);
			return MyDate(odt.GetYear(),odt.GetMonth(),odt.GetDay());
		}
		return dt;
	}catch(_com_error e)
	{
		return dt;
	}
}

MyDate AccessDB::ReadDateTime(char * col)
{
	MyDate dt;
	try{
		_variant_t data;
		data = m_dbRecordSet->GetCollect(col);
		if (data.vt == VT_DATE)
		{
			COleDateTime odt = COleDateTime(data);
			return MyDate(odt.GetYear(),odt.GetMonth(),odt.GetDay(),odt.GetHour(),odt.GetMinute(),odt.GetSecond());
		}
		return dt;
	}catch(_com_error e)
	{
		return dt;
	}
}