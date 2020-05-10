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
	memset(buf, 0, sizeof(buf[BUFSIZE]));
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
			cout << "Login name :" << login.name <<endl;
			char tmpbuf[2048] = {0};
			LoginSerialize(login, tmpbuf);
			cout << "Length :" << login.dataLenth << endl;
			send(client_socket,tmpbuf,sizeof(tmpbuf),0);
		}
		else if(0 == strcmp(m_msg.c_str(), "Logout")){
			Logout loginout;
			loginout.info = "Huxinkui";
			loginout.infoLength = loginout.info.length();
			loginout.dataLenth = sizeof(loginout);
			cout << "Logout name :" << loginout.info <<endl;
			char tmpbuf[2048] = {0};
			InfoSerialize(loginout, tmpbuf);
			send(client_socket,tmpbuf,sizeof(tmpbuf),0);
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