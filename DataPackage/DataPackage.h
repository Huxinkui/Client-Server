#ifndef _DATAPACKAGE_H
#define _DATAPACKAGE_H

#include <iostream>
#include <cstring>
using namespace std;

// class DataPackage
// {
// public:
// 	int age;
// 	int name_size;
// 	int Gender_size;
// 	string name;
// 	string Gender;
// };

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
	// DataHeader(){}
	// DataHeader(int dl, short cmd){
	// 	dataLenth = dl;
	// 	cmd = cmd;
	// }
	int dataLenth;
	short cmd;
};


class Login:public DataHeader
{
public:
	// Login(){}
	// Login(int dl, short cmd, string &name, string &password):DataHeader(dl,cmd){
	// 	name = name;
	// 	password = password;
	// 	nameLength = name.length();
	// 	passwordLength = password.length();
	// }
	int nameLength; //用户名长度
	int passwordLength;//密码长度
	string name;//登录用户名
	string password;//登录密码
};

class LoginResult:public DataHeader
{
public:
	// LoginResult(int dl, short cmd, string name):DataHeader(dl,cmd){
	// 	info = info;
	// 	infoLength = info.length();
	// }
	int infoLength;
	string info;//返回登录成功用户信息
};

class Logout:public DataHeader
{
public:
	// Logout(int dl, short cmd, string info):DataHeader(dl,cmd){
	// 	info = info;
	// 	infoLength = info.length();
	// }
	int infoLength;
	string info;//退出用户信息
};

class LogoutResult:public DataHeader
{
public:
	// LogoutResult(int dl, short cmd, string info):DataHeader(dl,cmd){
	// 	info = info;
	// 	infoLength = info.length();
	// }
	int infoLength;
	string info;//返回用户成功退出信息
};



#endif