#pragma once
#include "SFThread.h"

SFThread::SFThread(void) : m_pRunnable(NULL),m_bRun(false)//进入构造函数之前 先初始化 成员变量 有一些成员变量 必须先初始化 比如常量什么的
{
}

SFThread::~SFThread(void)
{
}

SFThread::SFThread(SFRunnable * pRunnable) : m_ThreadName(""),m_pRunnable(pRunnable),m_bRun(false)
{
}

SFThread::SFThread(const char * ThreadName, SFRunnable * pRunnable) : m_ThreadName(ThreadName),m_pRunnable(pRunnable),m_bRun(false)
{
}

SFThread::SFThread(std::string ThreadName, SFRunnable * pRunnable) : m_ThreadName(ThreadName),m_pRunnable(pRunnable),m_bRun(false)
{
}

bool SFThread::Start(bool bSuspend)
{
	if(m_bRun)
	{
		return true;
	}
	if(bSuspend)
	{
		m_handle = (HANDLE)_beginthreadex(NULL, 0, StaticThreadFunc, this, CREATE_SUSPENDED, &m_ThreadID);
	}
	else
	{
		m_handle = (HANDLE)_beginthreadex(NULL, 0, StaticThreadFunc, this, 0, &m_ThreadID);
	}
	m_bRun = (NULL != m_handle);
	return m_bRun;
}

void SFThread::Run()
{
	if(!m_bRun)//如果没运行
	{
		return;
	}
	if(NULL != m_pRunnable)//如果句柄不为空
	{
		m_pRunnable->Run();
	}
	m_bRun = false;
}

void SFThread::Join(int timeout)
{
	if(NULL == m_handle || !m_bRun)
	{
		return;
	}
	if(timeout <= 0)
	{
		timeout = INFINITE;
	}
	::WaitForSingleObject(m_handle, timeout);
}

void SFThread::Resume()
{
	if(NULL == m_handle || !m_bRun)
	{
		return;
	}
	::ResumeThread(m_handle);
}

void SFThread::Suspend()
{
	if(NULL == m_handle || !m_bRun)
	{
		return;
	}
	::SuspendThread(m_handle);
}

bool SFThread::Terminate(unsigned long ExitCode)
{
	if(NULL == m_handle || !m_bRun)
	{
		return true;
	}
	if(::TerminateThread(m_handle, ExitCode))
	{
		::CloseHandle(m_handle);
		m_bRun  =   false;//设置线程的运行状态为假
		return true;
	}
	return false;
}

unsigned int SFThread::GetThreadID()
{
	return m_ThreadID;
}

std::string SFThread::GetThreadName()
{
	return m_ThreadName;
}

void SFThread::SetThreadName(std::string ThreadName)
{
	m_ThreadName = ThreadName;
}

void SFThread::SetThreadName(const char * ThreadName)
{
	if(NULL == ThreadName)
	{
		m_ThreadName = "";
	}
	else
	{
		m_ThreadName = ThreadName;
	}
}

unsigned int SFThread::StaticThreadFunc(void * arg)
{
	SFThread * pThread = (SFThread *)arg;
	pThread->Run();
	return 0;
}

// 作者：csx66406602 
// 来源：CSDN 
// 原文：https://blog.csdn.net/csx66406602/article/details/54862950 
// 版权声明：本文为博主原创文章，转载请附上博文链接！