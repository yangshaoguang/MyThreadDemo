#include <iostream>
#include <ctime>
#include "LogWriter.h"
#include <Windows.h>
using namespace std;
int main()
{

	clock_t start,end;
	start = clock();
	for (int i = 0;i < 1000000;i++)
	{
//		Sleep(10);
		LogWriter::GetLoggerInstance()->LOGINFO("AAAAAAAABBBBBBB�������ֹ���123456789AAAAAAAA�������ֹ���BBBBBBB123456789�������ֹ���AAAAAAAABBBBBBB123456789");
		LogWriter::GetLoggerInstance()->LOGWARN("AAAAAAAABBBBBBB�������ֹ���123456789AAAAAAAA�������ֹ���BBBBBBB123456789�������ֹ���AAAAAAAABBBBBBB123456789");
		LogWriter::GetLoggerInstance()->LOGERROR("AAAAAAAABBBBBBB�������ֹ���123456789AAAAAAAA�������ֹ���BBBBBBB123456789�������ֹ���AAAAAAAABBBBBBB123456789");
	}
	end = clock(); //yangshg 2018/10/25 17:46:35  30������־����ʱ6.5�����ҡ�
	cout << end - start << endl;
	getchar();
	return 0;
}