#include "PCSCdemo.h"
void connection() {
	LONG ir = SCardConnect(
		hContext,
		//ACS ACR1281 1S Dual Reader ICC 0 �ǲ������ӵ�
		//Microsoft Virtual Smart Card 3  num3
		all_readers[3],
		SCARD_SHARE_SHARED,
		SCARD_PROTOCOL_T0 | SCARD_PROTOCOL_T1,
		&hCard,
		&dwActiveProtocol
	);
	//����ʧ��
	if (ir != SCARD_S_SUCCESS) fprintf(stderr, "���Ӷ�����ʧ�ܣ��������Ϊ��%lu", ir);
	//�ɹ�����
	//printf("����Microsoft Virtual Smart Card 3�������ɹ�!\n");
	printf("����%s�������ɹ�!\n",all_readers[3]);
}