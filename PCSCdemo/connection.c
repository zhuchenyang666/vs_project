#include "PCSCdemo.h"
void connection() {
	LONG ir = SCardConnect(
		hContext,
		//ACS ACR1281 1S Dual Reader ICC 0 是不能连接的
		//Microsoft Virtual Smart Card 3  num3
		all_readers[3],
		SCARD_SHARE_SHARED,
		SCARD_PROTOCOL_T0 | SCARD_PROTOCOL_T1,
		&hCard,
		&dwActiveProtocol
	);
	//连接失败
	if (ir != SCARD_S_SUCCESS) fprintf(stderr, "连接读卡器失败，错误代码为：%lu", ir);
	//成功连接
	//printf("连接Microsoft Virtual Smart Card 3读卡器成功!\n");
	printf("连接%s读卡器成功!\n",all_readers[3]);
}