#include "Supervisor.h"
//#include <iostream>

//using namespace std;

int main(int argc, char *argv[])
{
	Supervisor s(argc, argv);
	s.startThreads();

	return 0;
}
