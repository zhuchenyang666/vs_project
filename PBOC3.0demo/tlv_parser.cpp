#include"head.h"

//日期显示 YYMMDD格式
void showDate(int year, int mouth, int day) {
	cout << dec 
		<< "20" << year << "年"
		<< mouth << "月"
		<< day << "日"
		<< endl;
}

//日期显示 MMDD格式
void showDate(int mouth, int day) {
	cout << dec << "交易日期："
		<< mouth << "月"
		<< day << "日"
		<< endl;
}

//卡号显示  卡号   卡号也是BCD码格式 不过数据过于大不建议拼接成一个整形数据
//卡号有固定的长度和格式
void showPAN(unsigned char* PAN, int PAN_Len) {
	for (int i = 0; i < PAN_Len; i++) {
		if (i == 6) cout << "  ";
		cout << dec << Single_BCD_TO_INT(PAN[i]);
	}
	cout << endl;
}
//PAN + 分隔符 + 有效期 +服务码处理
void Track_2_Equivalent_Data_Handle(unsigned char* data, int dataLen) {
	//数据 0x    
	//62 12 34 56 78 90 12 34 56  卡号
	//7d 分隔符
	//15 12 07 卡生效日期
	//01 00 服务码

	//截取字符串 
	/*
	* 从后往前 后2B为服务码 往前推3B为日期 去掉7d分隔符 剩余部分为卡号 
	*/
	//PAN
	int PAN_Len = dataLen - 6;
	unsigned char* PAN = new unsigned char[PAN_Len+1];
	PAN[PAN_Len] = '\0';
	memcpy(PAN, data, PAN_Len);
	//卡号是BCD码的话，显示的整形数据就太大了，不好存储 卡号以字符串型式存储
	cout << "PAN卡号：";
	showPAN(PAN, PAN_Len);
	//date
	unsigned char* date = new unsigned char[3];
	memcpy(date, data + PAN_Len + 1, 3);
	int year = Single_BCD_TO_INT(date[0]);
	int mouth = Single_BCD_TO_INT(date[1]);
	int day = Single_BCD_TO_INT(date[2]);
	cout << "卡片生效日期：";
	showDate(year, mouth, day);
	//服务码
	int serviceCode = Batch_BCD_TO_INT(data + dataLen - 2, 2);
	cout << dec << "服务码：" << serviceCode << endl;
	//手动释放堆
	delete[] PAN;
	delete[] date;
}

//交易日期处理
void Transaction_Date_Handle(unsigned char* data, int dataLen) {
	//数据是以BCD码格式显示  转换为10进制反而出错
	//疑难点如何以BCD码型式显示
	//方法一 不规范法 仅仅显示正确
	/*
	* unsigned char存储0x60  里面存储的是16进制数字
	* 如果直接cout的结果就是a 
	* static_cast<int>0x60  转换为10进制数字而且字符  转化为真正的整型数据
	* 再加上hex格式换 以16进制显示
	*/
	//0x20  0x12  0x30
	cout <<hex<<"交易日期："
		<< "20"  <<static_cast<int>(data[0]) << "年"    //当做16进制数处理
		<<static_cast<int>(data[1]) << "月"
		<<static_cast<int>(data[2]) << "日"
		<< endl;

	//方法二 规范法转BCD码
	int year = Single_BCD_TO_INT(data[0]) ; //年
	int mouth = Single_BCD_TO_INT(data[1]);	//月 
	int day = Single_BCD_TO_INT(data[2]);	//日
	cout << "交易日期：";
	showDate(year, mouth, day);
}

//交易类型处理
void Transaction_Type_Handle(unsigned char* data, int dataLen) {

}

//交易货币类型处理
void Transaction_Currency_Code_Handle(unsigned char* data, int dataLen) {
	//把2B拼接成一个16进制数
	unsigned short bcd_value = (data[0] << 8) | data[1];
	//调用默认方法  2B BCD码的处理方法
	//BCD_TO_INT(bcd_value);
	cout << "货币类型:";
	int x = Batch_BCD_TO_INT(data, dataLen);
	switch (x) {
	case RMB:
		cout << "人民币";
		break;
	default:
		cout << "非法货币!";
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
		//0x9A 交易日期 YYMMDD格式
	case Transaction_Date: 
		Transaction_Date_Handle(data,dataLen);
		break;
		//0x9C 交易类型
	case Transaction_Type:
		Transaction_Type_Handle(data, dataLen);
		break;
	case Transaction_Currency_Code:
		//0x5F2A 交易货币类型
		Transaction_Currency_Code_Handle(data, dataLen);
		break;
	default:
		break;
	}
}