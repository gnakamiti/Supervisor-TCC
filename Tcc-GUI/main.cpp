#include "Supervisor.h"
#include <iostream>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
//using namespace std;

int main(int argc, char *argv[])
{
	int *i = nullptr;
	delete i;
	//Supervisor s(argc, argv);
	Supervisor::getInstance()->startThreads();
	

	delete Supervisor::getInstance();
	SupervisorLog::closeLog();

	return 0;
}
