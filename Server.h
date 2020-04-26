#ifndef _SERVER_H_
#define _SERVER_H_

#include<iostream>
#include<cstring>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<memory>
#include<mutex>
#include<stdio.h>
using namespace std;

class Server
{

public:

	~Server();
	static Server * get_Instance();
	int Run();

private:
	Server();
	static Server * m_server;

	int m_port;
	struct sockaddr_in  server_sockaddr;


};

#endif