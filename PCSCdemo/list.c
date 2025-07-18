#include "PCSCdemo.h"


//打印所有的读卡器
void printReaders() {
	printf("分割后的二维数组后的内容:\n");
	for (int i = 0; i < all_readers_count; i++) {
		for (int j = 0; j < readersLen[i]; j++) {
			printf("%c", all_readers[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}

//将一维数组按照regex格式拆分
void stringSplit(char *cc,int len) {
	int count = -1;
	for (int i = 0; i < len; i++) {
		char c = cc[i];
		if (c == '\0') count++;
	}
	system("pause");
	all_readers = (char**)malloc(count);
	readersLen = (int*)malloc(count);
	char* p = cc;
	for (int i = 0; i < count; i++) {
		int perLen = strlen(p);
		all_readers[i] = (char*)malloc(perLen + 1);
		all_readers[i][perLen] = '\0';
		readersLen[i] = perLen;
		for (int j = 0; j < perLen; j++) {
			all_readers[i][j] = p[j];
		}
		p = p + perLen + 1;
	}
}

//列出所有的读写器
void listReaders() {
	char readers[256];
	DWORD len = sizeof(readers);
	LONG ir = SCardListReaders(hContext, NULL, (LPSTR)readers, &len);
	//错误
	if (ir != SCARD_S_SUCCESS) fprintf(stderr, "列出读卡器失败，错误代码：%lu", ir);
	//正确获取所有读卡器
	//打印读卡器列表
	//reader1\0reader2\0reader3\0\0   是这样的字符串
	printf("原一维数组readers内容:\n");
	int count = -1;
	for (int i = 0; i < len; i++) {
		if (readers[i] == '\0') count++;
		printf("%c", readers[i]);
	}
	printf("\n读写器数目为：%d\n",count);
	//添加进读卡器列表中
	//统计读写器个数
	if (count == 0 || count == -1) {
		printf("无读写器连接...\n");
		return;
	}
	all_readers_count = count;
	stringSplit(readers, len);
	//打印所有的读卡器  分割后的
	printReaders();
	system("pause");
}