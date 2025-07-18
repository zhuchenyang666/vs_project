#pragma once

#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include <algorithm>
using namespace std;

//�궨��   ֮����ʲôTAG�����������ﶨ��
#define Track_2_Equivalent_Data 0x57     //���ŵ����� ����(PAN) + �ָ���D + ��Ч�� + ������
#define Transaction_Date 0x9A		//��������
#define Transaction_Type 0x9C		//��������
#define Transaction_Currency_Code 0x5F2A		//���׻��Ҵ���
#define Application_Interchange_Profile 0x82  //Ӧ�ý�������
#define Application_Transaction_Counter 0x9F36  //Ӧ�ý���������
#define Issuer_Application_Data 0x9F10  //������Ӧ������

//����������չ
#define RMB 156 //�����

//TAG�ϼ������� key value <===>ʮ��������  ����  ����tagList[0x9A]="Transaction_Date" 
//�������е�TAG��ǩ�������tagList������
//ȫ�ֱ���
extern unordered_map<unsigned short, const char*> tagList;  //���е�TAG
extern unordered_map<unsigned int, string> currencyType;//���еĻ�������


//�õ��ĺ�������
void printHex(unsigned char c[], int length);//ʮ����������ӡ
unsigned int stringToUInt(const char c);
unsigned char* stringToHex(const unsigned char cc[], unsigned int size);//�ַ���ת��Ϊ16������
unsigned char* hexToString(unsigned char* hexs, int hexsSize);//��ʮ��������ת��Ϊ�ַ���
void commandParser(unsigned char* ret, unsigned int retSize);//���ݹ淶ȥ��������
void tlvParser(unsigned short tag, unsigned char* data, int dataLen);//�����TLV���ݴ���



//���߷��� 
int BCD_TO_INT(unsigned short bcd_value);//����Ĭ��BCD�붼��0x0156  ռ2B
int Single_BCD_TO_INT(unsigned char bcd_value);//����1B��BCD�� ͨ��
int Batch_BCD_TO_INT(unsigned char* bcd_values, int size);//����������BCD�� 
int calPow(int base, int exp);//���ݼ��� ����С����