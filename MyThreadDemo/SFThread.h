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
	开始运行线程
	@arg bSuspend 开始运行时是否挂起
	**/
	bool Start(bool bSuspend = false);

	/**
	运行的线程函数，可以使用派生类重写此函数
	**/
	virtual void Run();

	/**
	当前执行此函数线程等待线程结束
	@arg timeout 等待超时时间，如果为负数，等待无限时长
	**/
	void Join(int timeout = -1);
	/**
	恢复挂起的线程
	**/
	void Resume();
	/**
	挂起线程
	**/
	void Suspend();
	/**
	终止线程的执行
	**/
	bool Terminate(unsigned long ExitCode);

	unsigned int GetThreadID();
	std::string GetThreadName();
	void SetThreadName(std::string ThreadName);
	void SetThreadName(const char * ThreadName);

private:
	static unsigned int WINAPI StaticThreadFunc(void * arg);//线程处理函数

private:
	HANDLE m_handle;//线程句柄
	SFRunnable * const m_pRunnable;//执行逻辑的指针
	unsigned int m_ThreadID;//线程ID
	std::string m_ThreadName;//线程name
	volatile bool m_bRun;//线程是否运行
};

#endif


/*
volatile:A volatile specifier is a hint to a compiler that an object may change its value in ways not specified by the language so that aggressive optimizations must be avoided.
*/
