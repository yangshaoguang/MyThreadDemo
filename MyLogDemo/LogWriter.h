//LogWriter.h
#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <iostream>
using namespace std;
#define LOG_BUFFER_SIZE 1024
class LogWriter
{
private:
	LogWriter();
	~LogWriter(void);
public:
	static LogWriter * GetLoggerInstance();
	static std::string GetLogFileName();
	void ReleaseLogger();
	void LOGINFO(std::string msg);
	void LOGWARN(std::string msg);
	void LOGERROR(std::string msg);
private:
	static int preMark(char * buffer);
	bool write(const char * format, ...);
private:
	FILE * fp;
	char   m_buffer[LOG_BUFFER_SIZE];
	static LogWriter *logger;
};

