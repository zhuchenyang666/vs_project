#include"head.h"

//�ַ���תʮ��������
unsigned char* stringToHex(const unsigned char response_data[],unsigned int size) {
	
	unsigned char *ret=new unsigned char[size]; //����
	unsigned int retSize = 0; //���ؽ����С
	for (int i = 0; i < size && i + 1 < size; i += 3) {
		char c[3];
		c[0] = response_data[i], c[1] = response_data[i + 1]; c[2] = '\0';
		char* endptr;
		//���費�������� ���ַ���57ת��Ϊʮ������0x57
		unsigned char r = strtoul(c, &endptr, 16);
		//�洢�ڽ����
		ret[retSize++] = r;
	}
	printf("ת�����16������Ϊ:\n");
	printHex(ret, retSize);
	return ret;
}

//ʮ��������ת�ַ���
unsigned char* hexToString(unsigned char* hexs, int hexsSize) {
	//���ص��ַ�����С
	//int resultSize = hexsSize * 2 + 1;
	//unsigned char* result = new unsigned char[resultSize];
	//result[resultSize] = '\0';
	//int count = 0;
	//for (int i = 0; i < hexsSize; i++) {
	//	//��ȡÿ���ֽڵĸ�4λ�͵�λ4λ
	//	char c = hexs[i];
	//	result[count] = c >> 4;  //ȡ��4λ
	//	result[count+1] = c & 0x0f;  //ȡ��4λ
	//	count += 2;
	//}
	//return result;
	return NULL;
}