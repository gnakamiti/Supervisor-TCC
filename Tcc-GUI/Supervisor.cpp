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
	std::vector<std::string> controlledLanes;
	std::vector<std::string> detectorNamePerLane;
	std::vector<Lane> lanes;

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
		controlledLanes = sumoC.getControllerLanes((*it));

		for(int i = 0; i < controlledLanes.size(); i++)
		{
			Lane lane;
			lane.laneName = controlledLanes.at(i);
			lane.detectorName = "e1det_";
			lane.detectorName += lane.laneName;
			lanes.push_back(lane);
		}

		c = new Controller(*it, sumoC.getTrafficLightsDefinition((*it)), lanes);
		c->setActive(true);
		//sumoC.getControllerLinks(*it);

		this->controllers.push_back(c);

		controlledLanes.clear();
		detectorNamePerLane.clear();
		lanes.clear();
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
//WHEN I ENTER HERE I MUST HAVE  mutexControllerList LOCK!
Street * Supervisor::getStreetByName(std::string controllerId, std::string streetName)
{
	Controller *c;
	std::vector<Street> *streets;
	Street *street;

	for(int i = 0; i < this->controllers.size(); i++)
	{
		c = this->controllers.at(i);

		if(c->getName().compare(controllerId) == 0)
		{
			streets = c->getControlledStreets();

			for(int k = 0; k < streets->size(); k++)
			{
				//street = streets->at(k);
				if(streets->at(k).streetName.compare(streetName) == 0)
				{
					street = &streets->at(k);
					break;
				}
			}
			break;
		}
		
	}

	return street;
}
void Supervisor::setQueueSizeAndStreamForController
	(std::string controllerId, std::string streetName, int queueSize, int carStream)
{
	QMutexLocker locker(&this->mutexControllerList);

	Street *street = this->getStreetByName(controllerId, streetName);

	street->carStream += carStream;
	street->queueSize = queueSize;
}
void Supervisor::setSituationForStreet
	(std::string controllerId, std::string streetName, std::string situation)
{
	QMutexLocker locker(&this->mutexControllerList);

	Street *street = this->getStreetByName(controllerId, streetName);

	street->situation = situation;
}

