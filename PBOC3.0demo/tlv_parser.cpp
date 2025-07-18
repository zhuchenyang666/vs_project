#include"head.h"

//������ʾ YYMMDD��ʽ
void showDate(int year, int mouth, int day) {
	cout << dec 
		<< "20" << year << "��"
		<< mouth << "��"
		<< day << "��"
		<< endl;
}

//������ʾ MMDD��ʽ
void showDate(int mouth, int day) {
	cout << dec << "�������ڣ�"
		<< mouth << "��"
		<< day << "��"
		<< endl;
}

//������ʾ  ����   ����Ҳ��BCD���ʽ �������ݹ��ڴ󲻽���ƴ�ӳ�һ����������
//�����й̶��ĳ��Ⱥ͸�ʽ
void showPAN(unsigned char* PAN, int PAN_Len) {
	for (int i = 0; i < PAN_Len; i++) {
		if (i == 6) cout << "  ";
		cout << dec << Single_BCD_TO_INT(PAN[i]);
	}
	cout << endl;
}
//PAN + �ָ��� + ��Ч�� +�����봦��
void Track_2_Equivalent_Data_Handle(unsigned char* data, int dataLen) {
	//���� 0x    
	//62 12 34 56 78 90 12 34 56  ����
	//7d �ָ���
	//15 12 07 ����Ч����
	//01 00 ������

	//��ȡ�ַ��� 
	/*
	* �Ӻ���ǰ ��2BΪ������ ��ǰ��3BΪ���� ȥ��7d�ָ��� ʣ�ಿ��Ϊ���� 
	*/
	//PAN
	int PAN_Len = dataLen - 6;
	unsigned char* PAN = new unsigned char[PAN_Len+1];
	PAN[PAN_Len] = '\0';
	memcpy(PAN, data, PAN_Len);
	//������BCD��Ļ�����ʾ���������ݾ�̫���ˣ����ô洢 �������ַ�����ʽ�洢
	cout << "PAN���ţ�";
	showPAN(PAN, PAN_Len);
	//date
	unsigned char* date = new unsigned char[3];
	memcpy(date, data + PAN_Len + 1, 3);
	int year = Single_BCD_TO_INT(date[0]);
	int mouth = Single_BCD_TO_INT(date[1]);
	int day = Single_BCD_TO_INT(date[2]);
	cout << "��Ƭ��Ч���ڣ�";
	showDate(year, mouth, day);
	//������
	int serviceCode = Batch_BCD_TO_INT(data + dataLen - 2, 2);
	cout << dec << "�����룺" << serviceCode << endl;
	//�ֶ��ͷŶ�
	delete[] PAN;
	delete[] date;
}

//�������ڴ���
void Transaction_Date_Handle(unsigned char* data, int dataLen) {
	//��������BCD���ʽ��ʾ  ת��Ϊ10���Ʒ�������
	//���ѵ������BCD����ʽ��ʾ
	//����һ ���淶�� ������ʾ��ȷ
	/*
	* unsigned char�洢0x60  ����洢����16��������
	* ���ֱ��cout�Ľ������a 
	* static_cast<int>0x60  ת��Ϊ10�������ֶ����ַ�  ת��Ϊ��������������
	* �ټ���hex��ʽ�� ��16������ʾ
	*/
	//0x20  0x12  0x30
	cout <<hex<<"�������ڣ�"
		<< "20"  <<static_cast<int>(data[0]) << "��"    //����16����������
		<<static_cast<int>(data[1]) << "��"
		<<static_cast<int>(data[2]) << "��"
		<< endl;

	//������ �淶��תBCD��
	int year = Single_BCD_TO_INT(data[0]) ; //��
	int mouth = Single_BCD_TO_INT(data[1]);	//�� 
	int day = Single_BCD_TO_INT(data[2]);	//��
	cout << "�������ڣ�";
	showDate(year, mouth, day);
}

//�������ʹ���
void Transaction_Type_Handle(unsigned char* data, int dataLen) {

}

//���׻������ʹ���
void Transaction_Currency_Code_Handle(unsigned char* data, int dataLen) {
	//��2Bƴ�ӳ�һ��16������
	unsigned short bcd_value = (data[0] << 8) | data[1];
	//����Ĭ�Ϸ���  2B BCD��Ĵ�����
	//BCD_TO_INT(bcd_value);
	cout << "��������:";
	int x = Batch_BCD_TO_INT(data, dataLen);
	switch (x) {
	case RMB:
		cout << "�����";
		break;
	default:
		cout << "�Ƿ�����!";
		break;
	}
	cout << endl;
}

void tlvParser(unsigned short tag,unsigned char* data,int dataLen) {
	switch (tag) {
		//0x57 PAN
	case Track_2_Equivalent_Data:
		Track_2_Equivalent_Data_Handle(data, dataLen);
		break;
		//0x9A �������� YYMMDD��ʽ
	case Transaction_Date: 
		Transaction_Date_Handle(data,dataLen);
		break;
		//0x9C ��������
	case Transaction_Type:
		Transaction_Type_Handle(data, dataLen);
		break;
	case Transaction_Currency_Code:
		//0x5F2A ���׻�������
		Transaction_Currency_Code_Handle(data, dataLen);
		break;
	default:
		break;
	}
}