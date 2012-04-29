#include "Supervisor.h"

Supervisor::Supervisor() : decisions(this)
{
}
Supervisor::Supervisor(int argc, char **argv): decisions(this)
{
	Controller *c;
	std::vector<std::string> controllerNames;

	this->argc = argc;
	this->argv = argv;
	
	threadPool = QThreadPool::globalInstance();

	sumoC.connect();

	controllerNames = sumoC.getTrafficLightsId();

	

	for(std::vector<std::string>::const_iterator it = controllerNames.begin(); it!=controllerNames.end() ; it++)
	{
		c = new Controller(*it, sumoC.getTrafficLightsDefinition((*it)), sumoC.getControllerLanes((*it)));
		
		this->controllers.push_back(c);
	}
	
	
}

Supervisor::~Supervisor()
{
	Controller *c;
	sumoC.close();
	
	delete window;
	window = nullptr;

	for(int i = 0; i < controllers.size(); i++)
	{
		c = controllers.at(i);
		delete c;
		c = nullptr;
		
	}

	
}

void Supervisor::startThreads(void)
{
	
	QApplication a(this->argc, this->argv);

	//DO NOT REMOVE THIS! OR IT WILL ERASE EVERYTHING!
	this->decisions.setAutoDelete(false);
	
	
	
	this->window = new MainWindow();
	this->window->getControllers(this->controllers);
	this->window->show();

	threadPool->start(&this->decisions);
	a.exec();

	threadPool->waitForDone();
	
				
}

