#ifndef _SERVER_H_
#define _SERVER_H_

#include<iostream>
#include<string>
#include<cstring>
#include<vector>
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

#define BUFSIZE  2048



class Server
{

public:

	~Server();
	static Server * get_Instance();
	int Start();
	int set_port();
	int get_port();
	int max_fd(vector<int> fd);
	int Process(int client_socket);
private:
	Server();
	static Server * m_server;

	int m_port;//监听端口
	string m_msg;
	//DataPackage m_dataPackage;
	int server_socket;//服务端监听套接字
	int client_socket;//客户端套接字
	struct sockaddr_in  server_sockaddr;//服务端网络地址结构体
	//struct sockaddr_in  client_sockaddr;//客户端网络地址结构体
	
	char buf[BUFSIZE];//数据缓冲区

	std::vector<int> g_clients; //客户端连接池

};

#endif