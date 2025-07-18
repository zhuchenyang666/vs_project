#include"head.h"
//��ӡTLV������
void printTLV() {

}

//������������
void commandParser(unsigned char* ret, unsigned int retSize) {
	unsigned int i = 0;
	while (i < retSize) {
		//���ݳ���
		unsigned int dataLen;
		//��������
		unsigned char* data;
		//TAG��ǩ����
		const char* tagName;
		//������
		auto it = tagList.find((unsigned short)ret[i]);
		//����ǵ��ֽڱ�ǩ
		if (it != tagList.end()) {
			dataLen = ret[i + 1];
			tagName = it->second;
			i += 2;
		}
		else
		{

			//�ѵ㣺��ν�5F A2 ƴ�ӳ�һ��ʮ��������
			//����һ����λ�� ���������ڴ渴��
			unsigned short hex = (ret[i] << 8) | ret[i+1];  //�Ƽ�����һ
			it = tagList.find(hex);
			if (it == tagList.end()) cout << "����"<<endl; //��ֹ����end()���������ᱨ��
			dataLen = ret[i + 2];
			tagName = it->second;
			i += 3;
		}
		//��ӡTLV
		cout << "TAG��Ϊ��0X";
		printf("%02X \n", it->first);
		cout << "TAG���ƣ�" << tagName << endl;
		cout << "���ݳ���Ϊ��" << dataLen << "B" << endl;
		cout << "��������Ϊ��";
		data = new unsigned char(dataLen);
		//memcpy ���� copy����
		memcpy(data, ret + i, dataLen);
		//copy(ret + i, ret + i + dataLen, data);
		//printHex(ret + i, dataLen);
		printHex(data, dataLen);
		//��������һ��TLV
		tlvParser(it->first,data,dataLen);
		//�ƶ�ָ�� ȥѰ����һ��TLV
		i += dataLen;
		cout << endl;
	}
}