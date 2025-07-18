#include"head.h"

//字符串转十六进制数
unsigned char* stringToHex(const unsigned char response_data[],unsigned int size) {
	
	unsigned char *ret=new unsigned char[size]; //存结果
	unsigned int retSize = 0; //返回结果大小
	for (int i = 0; i < size && i + 1 < size; i += 3) {
		char c[3];
		c[0] = response_data[i], c[1] = response_data[i + 1]; c[2] = '\0';
		char* endptr;
		//假设不报错的情况 将字符串57转化为十六进制0x57
		unsigned char r = strtoul(c, &endptr, 16);
		//存储在结果中
		ret[retSize++] = r;
	}
	printf("转换后的16进制数为:\n");
	printHex(ret, retSize);
	return ret;
}

//十六进制数转字符串
unsigned char* hexToString(unsigned char* hexs, int hexsSize) {
	//返回的字符串大小
	//int resultSize = hexsSize * 2 + 1;
	//unsigned char* result = new unsigned char[resultSize];
	//result[resultSize] = '\0';
	//int count = 0;
	//for (int i = 0; i < hexsSize; i++) {
	//	//截取每个字节的高4位和低位4位
	//	char c = hexs[i];
	//	result[count] = c >> 4;  //取高4位
	//	result[count+1] = c & 0x0f;  //取低4位
	//	count += 2;
	//}
	//return result;
	return NULL;
}