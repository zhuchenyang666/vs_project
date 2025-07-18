#include "head.h"

//���������ݴ�
int calPow(int base, int exp) {
    int result = 1;
    while (exp ) {
        result *= base;
        exp--;
    }
    return result;
}

//�˴�Ϊ����2B�� BCD��
int BCD_TO_INT(unsigned short bcd_value) {
    // ��ȡÿ�����ֽڣ�4λ��
    unsigned char thousands = (bcd_value >> 12) & 0x0F; // ǧλ
    unsigned char hundreds = (bcd_value >> 8) & 0x0F; // ��λ
    unsigned char tens = (bcd_value >> 4) & 0x0F; // ʮλ
    unsigned char ones = bcd_value & 0x0F;         // ��λ

    // ��֤���а��ֽڶ�����Ч��BCD���֣�0-9��
    if (thousands > 9 || hundreds > 9 || tens > 9 || ones > 9) {
        printf("������Ч��BCD�� 0x%04X\n", bcd_value);
        return -1;
    }

    //�������յĽ��
    int x = (thousands * 1000 + hundreds * 100 + tens * 10 + ones);
    //cout << dec << "BCDת�������" << x << endl;
    //printf("BCDת�������%d\n", x);
    return x;
}

//����1B��BCD��
int Single_BCD_TO_INT(unsigned char bcd_value) {
    //����0x45
//��ȡ��λ4
    int high = (bcd_value >> 4) & 0x0f;
    //��ȡ��λ5
    int low = bcd_value & 0x0f;
    //����ʮ������45
    int x = high * 10 + low;
    //printf("BCD��ת����10������Ϊ��%d\n", x);
    return x;;
}

//���������B��BCD����
int Batch_BCD_TO_INT(unsigned char *bcd_values,int size) {
    int result = 0;
    for (int i = 0; i < size; i++) {
        //����BCD��ת��Ϊ10����
        int x = Single_BCD_TO_INT(bcd_values[i]);
        //����ѧ���� Ч�ʵ� ������
        result = x * pow(10, 2 * (size - 1 - i)) + result;
        //����λ���� Ч�ʸ� �����
    }

    //printf("BCD����ת���Ľ��Ϊ��%d", result);
    return result;
}
