#include "Supervisor.h"
#include <iostream>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#ifdef WIN32 //Detect memory leaks, only for windows!
	#include <vld.h>
#endif
//using namespace std;

int main(int argc, char *argv[])
{
	//Supervisor s(argc, argv);
	Supervisor::getInstance()->startThreads();

	delete Supervisor::getInstance();
	SupervisorLog::closeLog();

	return 0;
}