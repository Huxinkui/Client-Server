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
		cout << "Commd: " << endl;
		cin >> m_msg;

		if (0 == strcmp(m_msg.c_str(), "exit"))
		{
			break;
		}
		else if(0 == strcmp(m_msg.c_str(), "Login")){

			Login login;
			login.name = "Huxinkui";
			login.password = "1234567890";
			login.nameLength = login.name.length();
			login.passwordLength = login.password.length();
			login.dataLenth = sizeof(login);
			login.cmd = LOGIN;
			char tmpbuf[2048] = {0};
			LoginSerialize(login, tmpbuf);
			send(client_socket,tmpbuf,sizeof(tmpbuf),0);

		}
		else if(0 == strcmp(m_msg.c_str(), "Logout")){
			Logout loginout;
			loginout.info = "Huxinkui";
			loginout.infoLength = loginout.info.length();
			loginout.dataLenth = sizeof(loginout);
			loginout.cmd = LOGOUT;
			cout << "Logout name :" << loginout.info <<endl;
			char tmpbuf[2048] = {0};
			InfoSerialize(loginout, tmpbuf);
			send(client_socket,tmpbuf,sizeof(tmpbuf),0);
		}

		memset(buf, 0, sizeof(buf[BUFSIZE]));
		int n = recv(client_socket,buf,BUFSIZE, 0);
		
		DataHeader dl;
		int tmpn = 0;
		DLDeserialize(dl, buf, tmpn);
		if(n != dl.dataLenth)
		{
			cout << "收到数据错误！收到数据长度 ： " << sizeof(buf) << " 发送数据长度： " << dl.dataLenth << endl;
			break;
		}

		ResultInfo lgRes;

		switch(dl.cmd)
		{
			case LOGINRESULT:
				//反序列化，将buf中的数据解析
				InfoDeserialize(lgRes, buf, tmpn);
				
				cout << "收到登录成功数据，数据长度："<< lgRes.dataLenth << "  应答信息： " << lgRes.info << endl;

				break;
			case LOGOUTRESULT:
				//反序列化，将buf中的数据解析
				InfoDeserialize(lgRes, buf, tmpn);
				
				cout << "收到登出成功数据，数据长度："<< lgRes.dataLenth << "  应答信息： " << lgRes.info << endl;


				break;
			case LOGINERR:
				//反序列化，将buf中的数据解析
				InfoDeserialize(lgRes, buf, tmpn);
				
				cout << "错误命令数据，数据长度："<< lgRes.dataLenth << "  应答信息： " << lgRes.info << endl;


				break;
		}

		
		// int n = recv(client_socket,buf,BUFSIZE, 0);
		// //cout << "recv size : " << n <<endl; 
		// DataPackage  dp ;
		// Deserialize(dp, buf, n);
		// if (n > 0 )
		// {
		// 	cout << "name : " << dp.name << " age: "<< dp.age << " Gender: "<< dp.Gender << endl;
		// }
		
	}
	close(client_socket);
	cout << "任务结束" << endl;
	return 0;

}