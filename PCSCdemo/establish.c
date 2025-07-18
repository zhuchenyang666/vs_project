#include "PCSCdemo.h"

void establish() {
	LONG ir = SCardEstablishContext(SCARD_SCOPE_SYSTEM, NULL, NULL, &hContext);
	//连接失败
	if (ir != SCARD_S_SUCCESS) fprintf(stderr, "上下文连接失败，错误代码%lu", ir);
	//上下文连接成功
	printf("连接上下文成功!\n");
	system("pause");
}