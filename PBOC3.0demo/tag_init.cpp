#include "head.h"

//TAG定义
unordered_map<unsigned short, const char*> tagList{
	{Track_2_Equivalent_Data,"卡号+分隔符+有效期+服务码"},
	{Transaction_Date,"交易日期"},
	{Transaction_Type,"交易类型"},
	{Transaction_Currency_Code,"交易货币代码"},
	{Application_Interchange_Profile,"应用交互特征"},
	{Application_Transaction_Counter,"应用交互计数器"},
	{Issuer_Application_Data,"发卡行应用数据"},
};

//货币类型定义
