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
		LogWriter::GetLoggerInstance()->LOGINFO("AAAAAAAABBBBBBB中文文字哈哈123456789AAAAAAAA中文文字哈哈BBBBBBB123456789中文文字哈哈AAAAAAAABBBBBBB123456789");
		LogWriter::GetLoggerInstance()->LOGWARN("AAAAAAAABBBBBBB中文文字哈哈123456789AAAAAAAA中文文字哈哈BBBBBBB123456789中文文字哈哈AAAAAAAABBBBBBB123456789");
		LogWriter::GetLoggerInstance()->LOGERROR("AAAAAAAABBBBBBB中文文字哈哈123456789AAAAAAAA中文文字哈哈BBBBBBB123456789中文文字哈哈AAAAAAAABBBBBBB123456789");
	}
	end = clock(); //yangshg 2018/10/25 17:46:35  30万行日志，耗时6.5秒左右。
	cout << end - start << endl;
	getchar();
	return 0;
}