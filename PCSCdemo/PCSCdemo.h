// PCSCdemo.h: 标准系统包含文件的包含文件
// 或项目特定的包含文件。

#pragma once

#include <stdio.h> //基本输入输出流
#include "winscard.h"//PC/SC接口库
// TODO: 在此处引用程序需要的其他标头。

//全局变量
SCARDCONTEXT hContext; //上下文管理器
SCARDHANDLE hCard;//管理器句柄
DWORD dwActiveProtocol;//权限

char** all_readers;	//读卡器列表
int all_readers_count;//读卡器个数
int* readersLen;//每一个读卡器的字符串长度
//函数方法
void establish();    //建立上下文
void listReaders();	 //列出所有读写器+一维字符串的分割
void connection();	 //连接读写器
void sendCommand();  //发送指令
void handleData();	 //响应处理


