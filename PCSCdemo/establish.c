#include "PCSCdemo.h"

void establish() {
	LONG ir = SCardEstablishContext(SCARD_SCOPE_SYSTEM, NULL, NULL, &hContext);
	//����ʧ��
	if (ir != SCARD_S_SUCCESS) fprintf(stderr, "����������ʧ�ܣ��������%lu", ir);
	//���������ӳɹ�
	printf("���������ĳɹ�!\n");
	system("pause");
}