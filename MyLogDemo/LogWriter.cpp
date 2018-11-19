//LogWriter.cpp
//#include "stdafx.h"
#include "LogWriter.h"
#include <assert.h>
#include <share.h>
#include <stdarg.h>
#include <time.h>
#include <iostream>
#include <Windows.h>
using namespace std;

#define MAX_PATH 260

LogWriter *LogWriter::logger = NULL;
LogWriter * LogWriter::GetLoggerInstance()
{
	if (logger == NULL)
	{
		logger = new LogWriter;
	}
	return logger;
}
void LogWriter::ReleaseLogger()
{
	if (logger)
	{
		delete logger;
		logger = NULL;
	}
}
LogWriter::LogWriter()
{
	//获取应用程序目录
// 	char szPath[MAX_PATH] = {0};
// 	int r = GetModuleFileName(NULL, szPath, MAX_PATH);
// 	if (r <= 0 || r >= MAX_PATH)
// 		return ;
// 
// 	char* mid = szPath + r;
// 	while (*(--mid) != '\\' && mid > szPath);
// 	if (mid <= szPath)
// 		return ;
// 	*(++mid) = '\0';
// 	std::string strDir = szPath; 
// 
// 	char szapipath[MAX_PATH];
// 	memset(szapipath,0,MAX_PATH);
// 	GetModuleFileNameA(NULL,szapipath,MAX_PATH);
// 
// 	//获取应用程序名称
// 	char szExe[MAX_PATH] = "";
// 	char *pbuf = NULL;
// 	char* szLine = strtok_s(szapipath,"\\",&pbuf);
// 	while (NULL != szLine)
// 	{
// 		strcpy_s(szExe, szLine);
// 		szLine = strtok_s(NULL,"\\",&pbuf);
// 	}
// 	//删除.exe
// 	strncpy_s(szapipath, szExe, strlen(szExe)-4);
// 
// 
// 	char name[50] = { 0 };
// 	int timecount = GetTickCount();
// 	sprintf(name, "log\\%s.%d.log",szapipath, timecount);
// 	strDir.append(name);
	std::string  filepath = GetLogFileName();
 	fp = _fsopen(filepath.c_str(), "a+", _SH_DENYNO);
 	assert(fp != NULL);
}
std::string  LogWriter::GetLogFileName()
{
	char szPath[MAX_PATH] = {0};
	int r = GetModuleFileName(NULL, szPath, MAX_PATH);
	if (r <= 0 || r >= MAX_PATH)
		return "defaultName";

	char* mid = szPath + r;
	while (*(--mid) != '\\' && mid > szPath);
	if (mid <= szPath)
		return "defaultName";
	*(++mid) = '\0';
	std::string strDir = szPath; 

	char szapipath[MAX_PATH];
	memset(szapipath,0,MAX_PATH);
	GetModuleFileNameA(NULL,szapipath,MAX_PATH);

	//获取应用程序名称
	char szExe[MAX_PATH] = "";
	char *pbuf = NULL;
	char* szLine = strtok_s(szapipath,"\\",&pbuf);
	while (NULL != szLine)
	{
		strcpy_s(szExe, szLine);
		szLine = strtok_s(NULL,"\\",&pbuf);
	}
	//删除.exe
	strncpy_s(szapipath, szExe, strlen(szExe)-4);


	char name[50] = { 0 };
	int timecount = GetTickCount();
	sprintf(name, "log\\%s.%d.log",szapipath, timecount);
	strDir.append(name);
	return strDir;
}


LogWriter::~LogWriter(void)
{
	if (fp) 
	{
		fclose(fp);
		fp = NULL;
	}
}

void LogWriter::LOGINFO(std::string msg)
{
	string head = "[INFO :]";
	msg = head.append(msg.c_str());
	write(msg.c_str());
}

void LogWriter::LOGWARN(std::string msg)
{
	string head = "[WARN :]";
	msg = head.append(msg.c_str());
	write(msg.c_str());
}
void LogWriter::LOGERROR(std::string msg)
{
	string head = "[ERROR:]";
	msg = head.append(msg.c_str());
	write(msg.c_str());
}

bool LogWriter::write(const char * format, ...)
{
	if (fp == NULL)
		return false;

	int nsize = 0;
	int prelen = 0;
	char * str = m_buffer;
	prelen = preMark(str);
	str += prelen;

	va_list args;
	va_start(args, format);
	nsize = _vsnprintf(str, LOG_BUFFER_SIZE - prelen, format, args);
	va_end(args);

	fprintf(fp, "%s [:]\n", m_buffer);
	fflush(fp);
	int size = ftell(fp);
	if (size /(1024*1024) >20)
	{
		fclose(fp);
		fp = NULL;
		std::string  filepath = GetLogFileName();
		fp = _fsopen(filepath.c_str(), "a+", _SH_DENYNO);
		assert(fp != NULL); 
	}
	return true;
}

int LogWriter::preMark(char * buffer)
{
	time_t now;
	now = time(&now);
	struct tm vtm = *localtime(&now);
	return _snprintf(buffer, LOG_BUFFER_SIZE, "[%04d-%02d-%02d %02d:%02d:%02d]:",
		vtm.tm_year + 1900, vtm.tm_mon+1, vtm.tm_mday, vtm.tm_hour, vtm.tm_min, vtm.tm_sec);
}
