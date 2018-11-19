#pragma once
#include <iostream>
#include "MyTestModule.h"
#include <Windows.h>

using namespace std;
CRITICAL_SECTION cs = { 0 };
enum TaskType
{
	Task_type_Null,
	Task_type_1,
	Task_type_2,
};

CBaseTask::CBaseTask(void)
{

}
CFirstTask::CFirstTask(void)
{
	m_ntasktype = Task_type_1;
	m_strdata = "this is first task class.";
}
CSecondTask::CSecondTask(void)
{
	m_ntasktype = Task_type_2;
	m_strdata = "this is second task class.";
}



CMyTestModule*  CMyTestModule::m_testModule = NULL;
int CMyTestModule::m_nCount = 0;

CMyTestModule::CMyTestModule(void)
{
	InitializeCriticalSection(&cs);//初始化一个临界区
}

CMyTestModule::~CMyTestModule(void)
{
	DeleteCriticalSection(&cs); //删除临界区
}
void CMyTestModule::Run()
{
	while (true)
	{
		if (!m_taskqueue.empty())
		{
			EnterCriticalSection(&cs);
			CBaseTask *task = m_taskqueue.front();
			m_taskqueue.pop();
			LeaveCriticalSection(&cs);
			process(task);
		}

		Sleep(10);
	}
}

void CMyTestModule::postFirstTask(CBaseTask *task)
{
	add_task(task);
}
void CMyTestModule::postSecondTask(CBaseTask *task)
{
	add_task(task);
}

void CMyTestModule::process(CBaseTask *task)
{
	switch (task->m_ntasktype)
	{
	case Task_type_1:
		HandleFirstTask(task);
		break;
	case Task_type_2:
		HandleSecondTask(task);
		break;
	default:
		break;
	}
}
void CMyTestModule::HandleFirstTask(CBaseTask *task)
{
	CFirstTask *tk = (CFirstTask *) task;
	cout << tk->m_strdata.c_str() <<"第" <<task->m_nCount<< "个任务"<< " 队列大小 "<<m_taskqueue.size() <<endl;
	delete tk;
	task = NULL;
}
void CMyTestModule::HandleSecondTask(CBaseTask *task)
{
	CSecondTask *tk = (CSecondTask *) task;
	cout << tk->m_strdata.c_str() <<"第" <<task->m_nCount<< "个任务"<< " 队列大小 "<<m_taskqueue.size() << endl;
	delete tk;
	task = NULL;
}
void CMyTestModule::add_task(CBaseTask *task)
{
	if(m_taskqueue.size() >= 1000000)
		return;
	EnterCriticalSection(&cs);
	m_taskqueue.push(task);
	LeaveCriticalSection(&cs);
}
void CMyTestModule::releaseMyTestModule()
{
	if (m_nCount && --m_nCount == 0)
	{
		delete m_testModule;
		m_testModule = NULL;
	}
}
CMyTestModule *CMyTestModule::GetMyTestModule()
{
	if(m_testModule == NULL)
	{
		m_testModule = new CMyTestModule;
	}
	++ m_nCount;
	return m_testModule;
}
