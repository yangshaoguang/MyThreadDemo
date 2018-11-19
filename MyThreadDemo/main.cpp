#include <iostream>
//#include "SFTimer.h"
#include "MyTestModule.h"
#include "SFThread.h"

using namespace std;
int main(int argc, char *argv[])  
{  
	CMyTestModule *module = CMyTestModule::GetMyTestModule();//具体业务类
	SFThread *thread2 = new SFThread(module);
	thread2->Start();

	int i = 0;
	while(1)
	{
		//CBaseTask task;
		if (i % 2 == 0)
		{
			CFirstTask *task = new CFirstTask;
			task->m_nCount = i;
			module->postFirstTask(task);
		}
		else
		{
 			CSecondTask *task = new CSecondTask;
			task->m_nCount = i;
 			module->postSecondTask(task);
		}
		//cout<<"计时开始："<<timer->getMinute()<<"分"<<timer->getSecond()<<"秒"<<endl; 
		Sleep(30);//Sleep看清楚间
		//system("cls");
		i++;
	}
	CMyTestModule::GetMyTestModule()->releaseMyTestModule();
	getchar();

	return 0;  
}
