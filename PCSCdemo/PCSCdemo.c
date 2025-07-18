// PCSCdemo.cpp: 定义应用程序的入口点。
//

#include "PCSCdemo.h"



//测试程序
void test() {

	//上下文连接
	establish();
	//列出所有读卡器
	listReaders();
	//连接读卡器和卡 默认连接第一个读卡器 也可以指定
	connection();
	//发送指令
	sendCommand();
	//响应处理
	handleData();
}

int main()
{
	test();

	return 0;
}
