// PBOC3.0demo.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "head.h"

unsigned int stringToUInt(const char c) {
	return 0;
}

//打印16进制数字
void printHex(unsigned char c[], int length) {
	for (int i = 0; i < length; i++) {
		printf("%02x ", c[i]);
	}
	printf("\n");
}


void test() {
	//接收到的数据是以字符串类型返回的 如9A 03 20 12 30 中间有空格字符" "隔开的，不能忽略
	const unsigned char response_data[] = "57 0F 62 12 34 56 78 90 12 34 56 7D 15 12 07 01 00 9A 03 20 12 30 9C 01 00 5F 2A 02 01 56 82 02 00 00 9F 36 02 00 0C 9F 10 12 06 01 0A 03 A0 00 00 00 00 00 00 00 00 00 00 00 00 FF ";
	//1.要将所有的字符串转换为16进制数(16进制10进制只是显示样子，计算机内部都是以2进制0/1存储的)，然后才能对这些数据进行处理
	unsigned char* ret = stringToHex(response_data, sizeof(response_data));
	unsigned int retSize = sizeof(response_data) / 3;

	//2.对指令进行解析 PBOC规范 TLV规范
	commandParser(ret, retSize);

	//3.对每一个TLV进一步解析 
}

void test2() {
	const unsigned char ss[] = "57 13 62 12 34 56 78 90 12 34 56 7D 15 12 07 01 00 9A 03 20 12 30 9C 01 00 5F 2A 02 01 56 82 02 00 00 9F 36 02 00 0C 9F 10 12 06 01 0A 03 A0 00 00 00 00 00 00 00 00 00 00 00 00 FF ";
	unsigned char ret[sizeof(ss)];
	int count = 0;
	for (int i = 0; i < sizeof(ss) && i + 1 < sizeof(ss); i += 3) {
		char c[3];
		c[0] = ss[i], c[1] = ss[i + 1], c[2] = '\0';
		char* endptr;
		unsigned char r = strtoul(c, &endptr, 16);
		ret[count++] = r;
	}
	printHex(ret, count);
}

int main()
{
	test();
	system("pause");
	return 0;
}


