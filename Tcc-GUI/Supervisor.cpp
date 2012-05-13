#include "Supervisor.h"
#include "mainwindow.h"


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
	deleteInVector(this->controllers);
	sumoC.close();
	
	delete window;
	window = nullptr;
	
}

void Supervisor::startThreads(void)
{
	//TALVEZ MUDAR AQUI OS PARAMETROS!
	int i = 0;
	QApplication a(i, NULL);

	//DO NOT REMOVE THIS! OR IT WILL ERASE EVERYTHING!
	//this->decisions.setAutoDelete(false);
	
	this->window = new MainWindow();
	//this->window->setControllersAndMutex(&this->controllers, &mutexControllerList);
	this->window->show();
	
	connect(this, SIGNAL(stopValueChanged(bool)), &this->sumoC, SLOT(setStop(bool)));

	//threadPool->start(&this->decisions);
	this->decisions.start();

	this->sumoC.start();

	a.exec();

	//threadPool->waitForDone();
	emit this->stopValueChanged(true);

	this->sumoC.wait();
	this->decisions.quit();
	//this->sumoC.quit();
				
}
/*
QMutex * Supervisor::getMutextControllerListRef()
{
	return &this->mutexControllerList;
}

std::vector<Controller *> * Supervisor::getControllersListRef()
{
	return &this->controllers;
}
*/
void Supervisor::getControllersListClone(std::vector<Controller *> *clone)
{
	QMutexLocker locker(&this->mutexControllerList);
	
	for(int i = 0; i < this->controllers.size(); i++)
	{
		clone->push_back(this->controllers.at(i)->clone());
	}
}

void Supervisor::setQueueSizeForController(std::string controllerId, int queueSize)
{
	QMutexLocker locker(&this->mutexControllerList);
	Controller *c;

	for(int i = 0; i < this->controllers.size(); i++)
	{
		c = this->controllers.at(i);

		if(c->getName().compare(controllerId) == 0)
		{
			c->setQueueSize(queueSize);
			break;
		}
		
	}
}

