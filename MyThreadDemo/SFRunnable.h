#pragma once
class SFRunnable
{
public:
	virtual ~SFRunnable() {};
	virtual void Run() = 0;
};