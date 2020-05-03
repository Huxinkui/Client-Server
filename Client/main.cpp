#include <iostream>
#include"Client.h"

using namespace std;

int main()
{
	Client cl;
	cl.Start();
	cout << " prot : " << cl.GetPort() << endl;
	return 0;
}