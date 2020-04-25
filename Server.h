#ifndef _SERVER_H_
#define _SERVER_H_

#include<iostream>
#include<cstring>
#include<sys/socket.h>
#include<memory>
#include<mutex>
using namespace std;

class Server
{

public:

	~Server();
	
	static Server * get_Instance();

private:
	Server();
	static Server * m_server;

};

#endif