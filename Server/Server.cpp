#include "Server.h"
#include "Serialize.h"





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
	//cout << "Please input listen Port :" <<endl;
	m_port = 2000;
	return 0;
}
int Server::get_port()
{
	return m_port;
}
int Server::Process(int client_socket)
{
	int n = recv(client_socket,buf,BUFSIZE, 0);
	if(n < 0)
	{
		cout << "接收消息错误" << endl;
		return -1;
	}
	DataHeader dl;
	int tmpn = 0;
	DLDeserialize(dl, buf, tmpn);
	

	Login login;
	Logout logout;
	ResultInfo lgRes;
	switch(dl.cmd)
	{
		case LOGIN:
			//反序列化，将buf中的数据解析
			LoginDeserialize(login, buf, n);
			if(sizeof(login) != login.dataLenth)
			{
				cout << "Login收到数据错误！服务端收到数据长度 ： " << sizeof(login) << " 客户端发送数据长度： " << login.dataLenth << endl;
				break;
			}
			cout << "Login: Name : " << login.name << " Password : " << login.password << endl;
			//设置接受消息应答数据
			lgRes.info = "用户登录成功";
			lgRes.cmd = LOGINRESULT;
			break;
		case LOGOUT:
			InfoDeserialize(logout, buf, n);

			if(sizeof(logout) != logout.dataLenth)
			{
				cout << "Logout收到数据错误！服务端收到数据长度 ： " << sizeof(logout) << " 客户端发送数据长度： " << logout.dataLenth << endl;
				break;
			}
			cout <<"Logout: Data Length : " << n <<" Name : " << logout.info << endl;
			//设置接受消息应答数据
			lgRes.info = "用户登出成功";
			lgRes.cmd = LOGOUTRESULT;

			break;
		default:
			cout << "The cmd is error !" << endl;
			//设置接受消息应答数据
			lgRes.info = "命令输入错误，请检查命令";
			lgRes.cmd = LOGINERR;

			break;
	}

	lgRes.infoLength = lgRes.info.length();
	lgRes.dataLenth = sizeof(lgRes);

	//序列化
	char tmpbuf[BUFSIZE];
	memset(tmpbuf, 0, sizeof(char[BUFSIZE]));
	InfoSerialize(lgRes,tmpbuf);
	//发送应答数据
	send(client_socket,tmpbuf,sizeof(tmpbuf),0);
}

int Server::Start()
{
	//m_msg = " This is Server" ;
	//int ret = set_port();
	//初始化服务端监听套接字
	m_port = 2000;
	if((server_socket = socket(AF_INET, SOCK_STREAM, 0)) == -1 )
	{
		cout << "create socket error" << endl;
		return -1;
	}

	memset(buf, 0, sizeof(buf[BUFSIZE]));
	//初始化网络地址结构体
	memset(&server_sockaddr, 0, sizeof(server_sockaddr));
	server_sockaddr.sin_family = AF_INET;
	server_sockaddr.sin_addr.s_addr = INADDR_ANY;
	server_sockaddr.sin_port = htons(m_port);//监听端口

	if(bind(server_socket, (struct sockaddr *)&server_sockaddr, sizeof(server_sockaddr)) == -1)
	{
		cout << " 绑定端口错误 " << endl;
		return -2;
	}
	else
	{
		cout << " 绑定端口成功 " << endl;
	}


	if(listen(server_socket,10) == -1)
	{
		cout << "监听网络端口失败" << endl;
		return -3;
	}
	else
	{
		cout << "监听网络端口成功" << endl;
	}
	socklen_t  socksize = sizeof(client_sockaddr);
	// m_dataPackage.name = "HuXinkui";
	// m_dataPackage.Gender = "Male";
	// m_dataPackage.age = 28;
	// m_dataPackage.name_size = sizeof(m_dataPackage.name);
	// m_dataPackage.Gender_size = sizeof(m_dataPackage.Gender);

	// cout << "DataPackage size :" << sizeof(m_dataPackage) << endl;
	// cout << "DataPackage size :" << sizeof(DataPackage) << endl;
	
	while(1)
	{	
		//伯克利 socket 
		fd_set fdRead;
		fd_set fdWrite;
		fd_set fdExp;
		//清空
		FD_ZERO(&fdRead);
		FD_ZERO(&fdWrite);
		FD_ZERO(&fdExp);

		FD_SET(server_socket, &fdRead);
		FD_SET(server_socket, &fdWrite);
		FD_SET(server_socket, &fdExp);
		//将所有的客户端连接的socket套接字设置到fdRead中，调用select()判断是否有数据
		for(auto n = 0 ; n <g_clients.size(); n++)
		{
			FD_SET(g_clients[n], &fdRead);
		}

		//select 网络模型 第一个参数nfds 是一个整数，是指fd_set集合中所有描述符（socket）的范围，而不是数量
		//就是所有文件描述符+1
		int ret = select(server_socket+1, &fdRead, &fdWrite,&fdExp,NULL);
		if(ret < 0)
		{
			cout << "select 任务结束。" <<endl;
			break;
		}
		//判断server_socket是不在fdRead中
		if(FD_ISSET(server_socket, &fdRead))
		{
			//将server_socket在fdRead中清除
			FD_CLR(server_socket, &fdRead);
			if((client_socket = accept(server_socket,(struct sockaddr *)&client_sockaddr, &socksize)) == -1)
			{
				cout << "客户端连接失败" << endl;
				//continue;
			}
			g_clients.push_back(client_socket);
		
			cout << "新客户端加入： IP = " << inet_ntoa(client_sockaddr.sin_addr) << endl;
		}

		//需要对客户端连接池中的所有连接的消息进行处理
		for(auto i = 0; i < g_clients.size(); i++)
		{
			Process(g_clients[i]);
		}
		


	}
	close(client_socket);
	close(server_socket);
	cout << "任务结束" << endl;

	return 0;
}