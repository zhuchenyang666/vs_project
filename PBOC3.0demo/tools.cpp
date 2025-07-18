#include "head.h"

//求整数的幂次
int calPow(int base, int exp) {
    int result = 1;
    while (exp ) {
        result *= base;
        exp--;
    }
    return result;
}

//此处为处理2B的 BCD码
int BCD_TO_INT(unsigned short bcd_value) {
    // 提取每个半字节（4位）
    unsigned char thousands = (bcd_value >> 12) & 0x0F; // 千位
    unsigned char hundreds = (bcd_value >> 8) & 0x0F; // 百位
    unsigned char tens = (bcd_value >> 4) & 0x0F; // 十位
    unsigned char ones = bcd_value & 0x0F;         // 个位

    // 验证所有半字节都是有效的BCD数字（0-9）
    if (thousands > 9 || hundreds > 9 || tens > 9 || ones > 9) {
        printf("错误：无效的BCD码 0x%04X\n", bcd_value);
        return -1;
    }

    //返回最终的结果
    int x = (thousands * 1000 + hundreds * 100 + tens * 10 + ones);
    //cout << dec << "BCD转换结果：" << x << endl;
    //printf("BCD转换结果：%d\n", x);
    return x;
}

//处理1B的BCD码
int Single_BCD_TO_INT(unsigned char bcd_value) {
    //比如0x45
//截取高位4
    int high = (bcd_value >> 4) & 0x0f;
    //截取低位5
    int low = bcd_value & 0x0f;
    //返回十进制数45
    int x = high * 10 + low;
    //printf("BCD码转换的10进制数为：%d\n", x);
    return x;;
}

//批量处理多B的BCD码组
int Batch_BCD_TO_INT(unsigned char *bcd_values,int size) {
    int result = 0;
    for (int i = 0; i < size; i++) {
        //单个BCD码转换为10进制
        int x = Single_BCD_TO_INT(bcd_values[i]);
        //用数学方法 效率低 好理解点
        result = x * pow(10, 2 * (size - 1 - i)) + result;
        //用移位操作 效率高 难理解
    }

    //printf("BCD码组转换的结果为：%d", result);
    return result;
}
