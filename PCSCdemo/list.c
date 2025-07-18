#include "PCSCdemo.h"


//��ӡ���еĶ�����
void printReaders() {
	printf("�ָ��Ķ�ά����������:\n");
	for (int i = 0; i < all_readers_count; i++) {
		for (int j = 0; j < readersLen[i]; j++) {
			printf("%c", all_readers[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}

//��һά���鰴��regex��ʽ���
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

//�г����еĶ�д��
void listReaders() {
	char readers[256];
	DWORD len = sizeof(readers);
	LONG ir = SCardListReaders(hContext, NULL, (LPSTR)readers, &len);
	//����
	if (ir != SCARD_S_SUCCESS) fprintf(stderr, "�г�������ʧ�ܣ�������룺%lu", ir);
	//��ȷ��ȡ���ж�����
	//��ӡ�������б�
	//reader1\0reader2\0reader3\0\0   ���������ַ���
	printf("ԭһά����readers����:\n");
	int count = -1;
	for (int i = 0; i < len; i++) {
		if (readers[i] == '\0') count++;
		printf("%c", readers[i]);
	}
	printf("\n��д����ĿΪ��%d\n",count);
	//��ӽ��������б���
	//ͳ�ƶ�д������
	if (count == 0 || count == -1) {
		printf("�޶�д������...\n");
		return;
	}
	all_readers_count = count;
	stringSplit(readers, len);
	//��ӡ���еĶ�����  �ָ���
	printReaders();
	system("pause");
}