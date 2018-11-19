#pragma once
#include<windows.h>
#include"SFThread.h"
#include <queue>
using namespace std;

class CBaseTask
{
public:
	CBaseTask(void);
	virtual~CBaseTask(void){};
	int m_ntasktype;   //yangshg 2018/10/24 15:05:54 任务类型
	int m_nCount;      //yangshg 2018/10/24 15:06:10 任务编号
};

class CFirstTask:public CBaseTask
{
public:
	CFirstTask();
	~CFirstTask(void){};
	string m_strdata;
	char carr[102400];
};
class CSecondTask:public CBaseTask
{
public:
	CSecondTask();
	~CSecondTask(void){};
	string m_strdata;
	char carr[102400];
};


//yangshg 2018/10/24 15:32:54 单例
class CMyTestModule:public SFRunnable 
{
private:
	CMyTestModule(void);
	~CMyTestModule(void);
	static CMyTestModule*  m_testModule;
	static int m_nCount;
public:
	static CMyTestModule *GetMyTestModule();
	void releaseMyTestModule();
	void Run();
	void postFirstTask(CBaseTask *task);
	void postSecondTask(CBaseTask *task);
private:
	queue<CBaseTask*> m_taskqueue;
	void process(CBaseTask *task);
	void HandleFirstTask(CBaseTask *task);
	void HandleSecondTask(CBaseTask *task);
	void add_task(CBaseTask *task);
};

