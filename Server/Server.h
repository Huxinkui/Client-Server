#ifndef _SERVER_H_
#define _SERVER_H_

#include<iostream>
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
#include "DataPackage.h"
using namespace std;

#define BUFSIZE  1024



class Server
{

public:

	~Server();
	static Server * get_Instance();
	int Start();
	int set_port();
	int get_port();

private:
	Server();
	static Server * m_server;

	int m_port;//监听端口
	string m_msg;
	//DataPackage m_dataPackage;
	int server_socket;//服务端监听套接字
	int client_socket;//客户端套接字
	struct sockaddr_in  server_sockaddr;//服务端网络地址结构体
	struct sockaddr_in  client_sockaddr;//客户端网络地址结构体

	char buf[BUFSIZE];//数据缓冲区

};

#endif