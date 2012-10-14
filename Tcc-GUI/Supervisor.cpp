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

		this->controllers.push_back(c);

		controlledLanes.clear();
		detectorNamePerLane.clear();
		lanes.clear();
	}

	ControllerLogic::readLogicDataBase(controllerNames);
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
	this->window->show();
	
	connect(this, SIGNAL(stopValueChanged(bool)), &this->sumoC, SLOT(setStop(bool)), Qt::QueuedConnection);
	connect(this, SIGNAL(sigLogControllerSituation(QString)), this->window, SLOT(logControllerSituation(QString)), Qt::QueuedConnection);
	connect(this, SIGNAL(sigLogFitness(QString)), this->window, SLOT(logFitness(QString)), Qt::QueuedConnection);
	connect(this, SIGNAL(sigLogQueue(QString)), this->window, SLOT(logQueue(QString)), Qt::QueuedConnection);
	connect(this, SIGNAL(sigLogPrograms(QString)), this->window, SLOT(logPrograms(QString)), Qt::QueuedConnection);
	connect(this, SIGNAL(sigLogPrograms(QString)), this->window, SLOT(logPrograms(QString)), Qt::QueuedConnection);
	connect(this, SIGNAL(sigPopulationPrograms(QString)), this->window, SLOT(logInitPrograms(QString)), Qt::QueuedConnection);
	connect(this, SIGNAL(sigFuzzyOut(QString)), this->window, SLOT(logFuzzyOut(QString)), Qt::QueuedConnection);
	connect(this, SIGNAL(sigFuzzyIn(QString)), this->window, SLOT(logFuzzyIn(QString)), Qt::QueuedConnection);
	connect(this, SIGNAL(sigTimerOn()), &this->decisions, SLOT(startFuzzyTimer()), Qt::QueuedConnection);
	connect(this, SIGNAL(sigTimerOff()), &this->decisions, SLOT(stopFuzzyTimer()), Qt::QueuedConnection);

	this->decisions.start();

	this->sumoC.start();
	
	//ControllerLogic  *l = ControllerLogic::createLogicForSumo(10, 10, 10, 10);
	//this->sumoC.sendNewProgram(this->controllers.at(0)->getName(), l); 
	//this->sumoC.setControllerProgram(this->controllers.at(0)->getName(), "off");
	
	a.exec();
	emit this->stopValueChanged(true);

	this->sumoC.wait();
	this->decisions.quit();

	//delete l;
				
}

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
	Street *street = nullptr;

	for(int i = 0; i < this->controllers.size(); i++)
	{
		c = this->controllers.at(i);

		if(c->getName().compare(controllerId) == 0)
		{
			streets = c->getControlledStreets();

			for(int k = 0; k < streets->size(); k++)
			{
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

	if(street == nullptr)
		throw "FUCK THE STREET IS NULL - method setQueueSizeAndStreamForController";
	
	street->carStream += carStream;
	street->queueSize = queueSize;
	
	
}
void Supervisor::setSituationForStreet
	(std::string controllerId, std::string streetName, std::string situation)
{
	QMutexLocker locker(&this->mutexControllerList);

	Street *street = this->getStreetByName(controllerId, streetName);

	if(street == nullptr)
		throw "FUCK THE STREET IS NULL - method setSituationForStreet";
	
	street->situation = situation;
	
	
}

void Supervisor::setTrafficLightProgramForController(std::string controllerName, std::vector<ControllerLogic *> logics){

	QMutexLocker locker(&this->mutexControllerList);

	for(int i = 0; i < this->controllers.size(); i++)
	{
		if(this->controllers.at(i)->getName().compare(controllerName) == 0)
		{
			this->controllers.at(i)->setControllerLogics(logics);
			break;
		}
	}
}

void Supervisor::setCurrentProgramForController(std::string controllerId, std::string programId)
{
	QMutexLocker locker(&this->mutexControllerList);

	Controller *c;

	for(int i = 0; i < this->controllers.size(); i++)
	{
		c = controllers.at(i);
		if(c->getName().compare(controllerId) == 0)
		{
			c->setCurrentLogicId(programId);
		}
	}
}

Controller * Supervisor::getControllerByName(std::string controllerName)
{
	QMutexLocker locker(&this->mutexControllerList);
	Controller *c = nullptr;

	for(int i = 0; i < this->controllers.size(); i++)
	{
		if(this->controllers.at(i)->getName().compare(controllerName) == 0)
		{
			c = this->controllers.at(i)->clone();
			break;
		}
	}

	return c;
}

void Supervisor::sendSumoCProgramForController(std::string controller, std::string program)
{
	this->sumoC.setControllerProgram(controller, program);
}

void Supervisor::sendSumoCNewProgramForController(std::string controller, ControllerLogic *logic)
{
	this->sumoC.sendNewProgram(controller, logic);
}

void Supervisor::emitLogControllerSituation(QString s)
{
	emit this->sigLogControllerSituation(s);
}

void Supervisor::emitLogFitness(QString s)
{
	emit this->sigLogFitness(s);
}

void Supervisor::emitLogQueue(QString s)
{
	emit this->sigLogQueue(s);
}

void Supervisor::emitPopulationPrograms(QString s)
{
	emit this->sigPopulationPrograms(s);
}

void Supervisor::emitLogPrograms(QString s)
{
	emit this->sigLogPrograms(s);
}

void Supervisor::emitFuzzyOut(QString s)
{
	emit this->sigFuzzyOut(s);
}
void Supervisor::emitFuzzyIn(QString s)
{
	emit this->sigFuzzyIn(s);
}

void Supervisor::turnIAOnOff(bool b)
{
	if (!b)
		emit this->sigTimerOff();
	else
		emit this->sigTimerOn();
}

