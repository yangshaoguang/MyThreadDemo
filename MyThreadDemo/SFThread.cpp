#pragma once
#include "SFThread.h"

SFThread::SFThread(void) : m_pRunnable(NULL),m_bRun(false)//���빹�캯��֮ǰ �ȳ�ʼ�� ��Ա���� ��һЩ��Ա���� �����ȳ�ʼ�� ���糣��ʲô��
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
	if(!m_bRun)//���û����
	{
		return;
	}
	if(NULL != m_pRunnable)//��������Ϊ��
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
		m_bRun  =   false;//�����̵߳�����״̬Ϊ��
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

// ���ߣ�csx66406602 
// ��Դ��CSDN 
// ԭ�ģ�https://blog.csdn.net/csx66406602/article/details/54862950 
// ��Ȩ����������Ϊ����ԭ�����£�ת���븽�ϲ������ӣ�