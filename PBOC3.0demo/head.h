#pragma once

#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include <algorithm>
using namespace std;

//宏定义   之后还有什么TAG都可以在这里定义
#define Track_2_Equivalent_Data 0x57     //二磁道数据 卡号(PAN) + 分隔符D + 有效期 + 服务码
#define Transaction_Date 0x9A		//交易日期
#define Transaction_Type 0x9C		//交易类型
#define Transaction_Currency_Code 0x5F2A		//交易货币代码
#define Application_Interchange_Profile 0x82  //应用交互特征
#define Application_Transaction_Counter 0x9F36  //应用交互计数器
#define Issuer_Application_Data 0x9F10  //发卡行应用数据

//其它的在扩展
#define RMB 156 //人民币

//TAG合集的声明 key value <===>十六进制数  含义  比如tagList[0x9A]="Transaction_Date" 
//假设所有的TAG标签都在这个tagList表里面
//全局变量
extern unordered_map<unsigned short, const char*> tagList;  //所有的TAG
extern unordered_map<unsigned int, string> currencyType;//所有的货币类型


//用到的函数方法
void printHex(unsigned char c[], int length);//十六进制数打印
unsigned int stringToUInt(const char c);
unsigned char* stringToHex(const unsigned char cc[], unsigned int size);//字符串转化为16进制数
unsigned char* hexToString(unsigned char* hexs, int hexsSize);//将十六进制数转化为字符串
void commandParser(unsigned char* ret, unsigned int retSize);//根据规范去解析数据
void tlvParser(unsigned short tag, unsigned char* data, int dataLen);//具体的TLV数据处理



//工具方法 
int BCD_TO_INT(unsigned short bcd_value);//假设默认BCD码都是0x0156  占2B
int Single_BCD_TO_INT(unsigned char bcd_value);//处理1B的BCD码 通法
int Batch_BCD_TO_INT(unsigned char* bcd_values, int size);//处理批量的BCD码 
int calPow(int base, int exp);//求幂级数 仅限小整数