#ifndef _CLIENT_H
#define _CLIENT_H
#include <iostream>
#include<string>
#include<cstring>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<memory>
#include<mutex>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

using namespace std;

#define BUFSIZE 1024

class Client
{
public:
	Client();
	~Client();
	int Start();
	int SetIp(string ip);
	string GetIp();
	int SetPort(int port);
	int GetPort();

private:
	int m_port;//监听端口
	string m_ip;
	string m_msg;
	int client_socket;//客户端套接字
	struct sockaddr_in  server_sockaddr;//服务端网络地址结构体

	char buf[BUFSIZE];//数据缓冲区
	
};
#endif