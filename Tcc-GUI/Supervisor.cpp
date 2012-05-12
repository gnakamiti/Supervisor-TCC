#include "Supervisor.h"

Supervisor * Supervisor::self= nullptr;

Supervisor * Supervisor::getInstance()
{
	if(self == nullptr)
	{
		self = new Supervisor();
	}
	return self;
}


Supervisor::Supervisor()
{
	Controller *c;
	std::vector<std::string> controllerNames;
	/*
	argc = argc;
	argv = argv;*/
	
	threadPool = QThreadPool::globalInstance();

	try
	{
		sumoC.connect();
	}
	catch(...)
	{
		exit(-1);
	}

	controllerNames = sumoC.getTrafficLightsId();

	

	for(std::vector<std::string>::const_iterator it = controllerNames.begin(); it!=controllerNames.end() ; it++)
	{
		c = new Controller(*it, sumoC.getTrafficLightsDefinition((*it)), sumoC.getControllerLanes((*it)));
		c->setActive(true);
		//sumoC.getControllerLinks(*it);

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
	//TALVEZ MUDAR AQUI OS PARAMETROS!
	int i = 0;
	QApplication a(i, NULL);

	//DO NOT REMOVE THIS! OR IT WILL ERASE EVERYTHING!
	this->decisions.setAutoDelete(false);
	
	this->window = new MainWindow();
	this->window->setControllersAndMutex(&this->controllers, &mutexControllerList);
	this->window->show();
	
	

	threadPool->start(&this->decisions);

	
	a.exec();

	threadPool->waitForDone();


	
				
}
