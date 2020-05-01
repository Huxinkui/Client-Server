#include <iostream>
#include"Server.h"

using namespace std;

int main()
{
	Server * m_ptr1 = Server::get_Instance();
	m_ptr1->Start();
	cout << " prot : " << m_ptr1->get_port() << endl;
	return 0;
}