#include "Client.h"

#include "DataPackage.h"
#include "Serialize.h"

Client::Client(){

}
Client::~Client(){

}


int Client::SetIp(string ip)
{
	m_ip = ip;
	return 0;
}
string Client::GetIp(){
	return m_ip;
}
int Client::SetPort(int port)
{
	m_port = port;
	return 0;
}
int Client::GetPort(){
	return m_port;
}
int Client::Process(int tmp_socket)
{
		memset(buf, 0, sizeof(buf[BUFSIZE]));
			//cout << "RECV Before !" << endl;
		DataHeader dl;
		int n = recv(tmp_socket,buf,dl.ReturnSize(), 0);
			//cout << "RECV After !" << endl;
		if(n < 0)
		{
			cout << "接收消息错误"<<endl;
			return -1 ;
		}
		
		int tmpn = 0;
		DLDeserialize(dl, buf, tmpn);
		//cout << "DL dataLenth : " << dl.dataLenth << endl;
		

		ResultInfo lgRes;

		switch(dl.cmd)
		{
			case LOGINRESULT:
				memset(buf, 0, sizeof(buf[BUFSIZE]));
				n = recv(tmp_socket,buf,dl.dataLenth - dl.ReturnSize(), 0);

				cout << "sizeof buf :" << sizeof(buf) << endl;
				//反序列化，将buf中的数据解析
				InfoDeserialize(lgRes, buf, tmpn);

				if(lgRes.ReturnSize() != (dl.dataLenth - dl.ReturnSize()))
				{
					cout << "Login收到数据错误！客户端收到数据长度 ： " << lgRes.ReturnSize() << " 服务端发送数据长度： " << dl.dataLenth << endl;
					break;
				}
				cout << "收到登录成功数据，数据长度："<< dl.dataLenth << "  应答信息： " << lgRes.info << endl;

				break;
			case LOGOUTRESULT:
				memset(buf, 0, sizeof(buf[BUFSIZE]));
				n = recv(tmp_socket,buf,dl.dataLenth - dl.ReturnSize(), 0);
				//反序列化，将buf中的数据解析
				InfoDeserialize(lgRes, buf, tmpn);
				
				if(lgRes.ReturnSize() != (dl.dataLenth - dl.ReturnSize()))
				{
					cout << "Logout收到数据错误！客户端收到数据长度 ： " << lgRes.ReturnSize() << " 服务端发送数据长度： " << dl.dataLenth << endl;
					break;
				}
				cout << "收到登出成功数据，数据长度："<< dl.dataLenth << "  应答信息： " << lgRes.info << endl;


				break;
			case LOGINERR:
				memset(buf, 0, sizeof(buf[BUFSIZE]));
				n = recv(tmp_socket,buf,dl.dataLenth - dl.ReturnSize(), 0);
				//反序列化，将buf中的数据解析
				InfoDeserialize(lgRes, buf, tmpn);
				if(lgRes.ReturnSize() != (dl.dataLenth - dl.ReturnSize()))
				{
					cout << "Logerr收到数据错误！客户端收到数据长度 ： " << lgRes.ReturnSize() << " 服务端发送数据长度： " << dl.dataLenth << endl;
					break;
				}
				
				cout << "错误命令数据，数据长度："<< dl.dataLenth << "  应答信息： " << lgRes.info << endl;


				break;
		}
	return 0;
}


int Client::Start(){

	//cout << "ip: " << endl;
	//cin >> m_ip;
	m_ip = "192.168.31.30";
	//cout << "prot: " << endl;
	//cin >> m_port;
	m_port = 2000;
	// cout << "Commd: " << endl;
	// cin >> m_msg;

	if((client_socket = socket(AF_INET, SOCK_STREAM, 0)) == -1 )
	{
		cout << "create socket error" << endl;
		return -1;
	}
	memset(&server_sockaddr, 0, sizeof(server_sockaddr));

	server_sockaddr.sin_family = AF_INET;
	server_sockaddr.sin_addr.s_addr = inet_addr(m_ip.c_str());
	server_sockaddr.sin_port = htons(m_port);//监听端口
	connect(client_socket,(struct sockaddr*)&server_sockaddr, sizeof(server_sockaddr));

	while(1)
	{

		//伯克利 socket 
		fd_set fdRead;

		FD_ZERO(&fdRead);

		FD_SET(client_socket, &fdRead);
		timeval t = {0,0};
		int ret = select(client_socket + 1, &fdRead, NULL,NULL,&t);
		if(ret < 0)
		{
			cout << "select 任务结束。" <<endl;
			break;
		}

		if(FD_ISSET(client_socket, &fdRead))
		{
			//将client_socket在fdRead中清除
			FD_CLR(client_socket, &fdRead);
			Process(client_socket);
		}
		else 
		{
			m_msg = "Login";
			//cin >> m_msg;
			if (0 == strcmp(m_msg.c_str(), "exit"))
			{
				
				break;
			}
			else if(0 == strcmp(m_msg.c_str(), "Login")){

				Login login;
				DataHeader dl;
				login.name = "Huxinkui";
				login.password = "1234567890";
				login.nameLength = login.name.length();
				login.passwordLength = login.password.length();
				login.cmd = LOGIN;
				login.dataLenth = login.ReturnSize() + dl.ReturnSize();
				char tmpbuf[BUFSIZE] = {0};
				LoginSerialize(login, tmpbuf);
				//cout << "Send Before !" << endl;
				send(client_socket,tmpbuf,login.dataLenth,0);

				//cout << "Send After !" << endl;
			}
			else if(0 == strcmp(m_msg.c_str(), "Logout")){
				Logout loginout;
				DataHeader dl;
				loginout.info = "Huxinkui";
				loginout.infoLength = loginout.info.length();
				loginout.cmd = LOGOUT;
				loginout.dataLenth = loginout.ReturnSize() + dl.ReturnSize();
				cout << "Logout name :" << loginout.info <<endl;
				char tmpbuf[BUFSIZE] = {0};
				InfoSerialize(loginout, tmpbuf);
				//cout << "Send Before !" << endl;
				send(client_socket,tmpbuf,loginout.dataLenth,0);
				//cout << "Send After !" << endl;
			}
			else
			{
				cout << "命令输入错误，请重新输入： Login, Logout, exit" << endl;
				continue;
			}

		}
		cout << " 处理其他数据 ！" << endl;


	
		

		
		
	}
	close(client_socket);
	cout << "任务结束" << endl;
	return 0;

}