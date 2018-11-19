#ifndef __SFTHREAD_H__
#define __SFTHREAD_H__

#include <string>
#include <windows.h>
#include <process.h>

#include "SFRunnable.h"


class SFThread : public SFRunnable
{
private:
	explicit SFThread(const SFThread & rhs);//explicit

public:
	SFThread();
	SFThread(SFRunnable * pRunnable);
	SFThread(const char * ThreadName, SFRunnable * pRunnable = NULL);
	SFThread(std::string ThreadName, SFRunnable * pRunnable = NULL);
	~SFThread(void);

	/**
	��ʼ�����߳�
	@arg bSuspend ��ʼ����ʱ�Ƿ����
	**/
	bool Start(bool bSuspend = false);

	/**
	���е��̺߳���������ʹ����������д�˺���
	**/
	virtual void Run();

	/**
	��ǰִ�д˺����̵߳ȴ��߳̽���
	@arg timeout �ȴ���ʱʱ�䣬���Ϊ�������ȴ�����ʱ��
	**/
	void Join(int timeout = -1);
	/**
	�ָ�������߳�
	**/
	void Resume();
	/**
	�����߳�
	**/
	void Suspend();
	/**
	��ֹ�̵߳�ִ��
	**/
	bool Terminate(unsigned long ExitCode);

	unsigned int GetThreadID();
	std::string GetThreadName();
	void SetThreadName(std::string ThreadName);
	void SetThreadName(const char * ThreadName);

private:
	static unsigned int WINAPI StaticThreadFunc(void * arg);//�̴߳�����

private:
	HANDLE m_handle;//�߳̾��
	SFRunnable * const m_pRunnable;//ִ���߼���ָ��
	unsigned int m_ThreadID;//�߳�ID
	std::string m_ThreadName;//�߳�name
	volatile bool m_bRun;//�߳��Ƿ�����
};

#endif


/*
volatile:A volatile specifier is a hint to a compiler that an object may change its value in ways not specified by the language so that aggressive optimizations must be avoided.
*/
