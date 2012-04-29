#include "Supervisor.h"
#include <iostream>


using namespace std;

int main(int argc, char *argv[])
{
	/*
	SumoClient sumoC;
	std::vector<std::string> controllers;

	sumoC.connect();
	controllers = sumoC.getTrafficLightsId();
	sumoC.close();

	QApplication a(argc, argv);
	MainWindow w;
	w.show();
	return a.exec();*/
	//_CrtDumpMemoryLeaks();
	Supervisor s(argc, argv);
	s.startThreads();
	// _CrtDumpMemoryLeaks();
	

	
	return 0;
}
