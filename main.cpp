#include <iostream>
#include"Server.h"

using namespace std;

int main()
{
	Server * m_ptr1 = Server::get_Instance();
	Server * m_ptr2 = Server::get_Instance();
	cout << " m_ptr1 : " << m_ptr1 << " m_ptr2 : "<< m_ptr2 << endl;
	return 0;
}