#include "Server.h"

Server::Server():m_port(0){

}
Server::~Server()
{
	delete m_server;
}

//静态成员变量初始化，要放在cpp文件，否则会出现多重定义问题，
//因为Server.cpp和main.cpp同时包含了Server.h所以会出现多重定义
Server * Server::m_server = nullptr;

// 使用时才会创建Server,懒汉模式，只有new，而没有delete,所以使用智能指针
Server * Server::get_Instance()
{
	if(m_server == NULL)
	{
		m_server = new Server();
	}
	return m_server;
}

// 直接初始化m_server,饿汉模式
//Server * Server::m_server = new Server();
// Server * Server::get_Instance()
// {
// 	return server;
// }
// 
// 
int Server::set_port()
{	
	cout << "Please input listen Port :" <<endl;
	cin >> m_port;
	return 0;
}
int Server::get_port()
{
	return m_port;
}

int Server::Start()
{
	int ret = set_port();
	//初始化服务端监听套接字
	if((server_socket = socket(AF_INET, SOCK_STREAM, 0)) == -1 )
	{
		cout << "create socket error" << endl;
		return -1;
	}
	//初始化网络地址结构体
	memset(&server_sockaddr, 0, sizeof(server_sockaddr));
	server_sockaddr.sin_family = AF_INET;
	server_sockaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	server_sockaddr.sin_port = htonl(m_port);//监听端口

	if(bind(server_socket, (struct sockaddr *)&server_sockaddr, sizeof(server_sockaddr)) == -1)
	{
		cout << " Bind socket error " << endl;
		return -2;
	}

	if(listen(server_socket,10) == -1)
	{
		cout << " Listen socket error" << endl;
		return -3;
	}

	while(1)
	{	
		socklen_t  socksize = sizeof(client_sockaddr);
		if((client_socket = accept(server_socket,(struct sockaddr *)&client_sockaddr, &socksize)) == -1)
		{
			cout << "Accept socket error" << endl;
			continue;
		}
		int n = recv(client_socket,buf,BUFSIZE, 0);
		buf[n] = '\0';
		cout << " Recv msg form client : "<< buf <<endl;
		close(client_socket);
	}
	close(server_socket);
	return 0;
}