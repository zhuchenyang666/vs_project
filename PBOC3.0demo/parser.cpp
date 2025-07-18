#include"head.h"
//打印TLV的内容
void printTLV() {

}

//解析银行数据
void commandParser(unsigned char* ret, unsigned int retSize) {
	unsigned int i = 0;
	while (i < retSize) {
		//数据长度
		unsigned int dataLen;
		//数据内容
		unsigned char* data;
		//TAG标签含义
		const char* tagName;
		//迭代器
		auto it = tagList.find((unsigned short)ret[i]);
		//如果是单字节标签
		if (it != tagList.end()) {
			dataLen = ret[i + 1];
			tagName = it->second;
			i += 2;
		}
		else
		{

			//难点：如何将5F A2 拼接成一个十六进制数
			//方法一：移位， 方法二：内存复制
			unsigned short hex = (ret[i] << 8) | ret[i+1];  //推荐方法一
			it = tagList.find(hex);
			if (it == tagList.end()) cout << "出错！"<<endl; //禁止操作end()迭代器，会报错
			dataLen = ret[i + 2];
			tagName = it->second;
			i += 3;
		}
		//打印TLV
		cout << "TAG号为：0X";
		printf("%02X \n", it->first);
		cout << "TAG名称：" << tagName << endl;
		cout << "数据长度为：" << dataLen << "B" << endl;
		cout << "数据内容为：";
		data = new unsigned char(dataLen);
		//memcpy 或者 copy拷贝
		memcpy(data, ret + i, dataLen);
		//copy(ret + i, ret + i + dataLen, data);
		//printHex(ret + i, dataLen);
		printHex(data, dataLen);
		//处理具体的一个TLV
		tlvParser(it->first,data,dataLen);
		//移动指针 去寻找下一个TLV
		i += dataLen;
		cout << endl;
	}
}