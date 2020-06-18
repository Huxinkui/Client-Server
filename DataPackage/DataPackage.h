#ifndef _DATAPACKAGE_H
#define _DATAPACKAGE_H

#include <iostream>
#include <cstring>
using namespace std;


enum CMD
{
	LOGIN,
	LOGINRESULT,
	LOGOUT,
	LOGOUTRESULT,
	LOGINERR
};

class DataHeader
{
public:
	int dataLenth;
	short cmd;
	int LenthReturn() // 不能使用sizeof()来计算类对象数据的大小
	{
		return sizeof(dataLenth) + sizeof(cmd) ;
	}
};


class Login:public DataHeader
{
public:
	int nameLength; //用户名长度
	int passwordLength;//密码长度
	string name;//登录用户名
	string password;//登录密码
	int LenthReturn()
	{
		return sizeof(nameLength) + sizeof(passwordLength) + name.length() +password.length();
	}
};



class Logout:public DataHeader
{
public:
	int infoLength;
	string info;//退出用户信息
	int LenthReturn()
	{
		return sizeof(infoLength) +  info.length() ;
	}
};

class ResultInfo:public DataHeader
{
public:
	int infoLength;
	string info;//返回用户成功退出信息
	int LenthReturn()
	{
		return sizeof(infoLength) +  info.length() ;
	}

};





#endif