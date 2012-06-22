#include "Controller.h"

Controller::Controller()
{
}


Controller::Controller(std::string name, std::vector<ControllerLogic *> logics, std::vector<Lane> lanes)
{
	this->name = name;
	this->setControllerLogics(logics);
	
	//this->lanes = lanes;
	this->createStreets(lanes);

	newPhaseDurations[0] = 10;
	newPhaseDurations[1] = 20;
	newPhaseDurations[2] = 30;
	newPhaseDurations[3] = 40;
}

std::string Controller::laneToStreet(std::string lane)
{
	std::string findStr = "E";
	return lane.substr(0, lane.find(findStr));
}

void Controller::createStreets(std::vector<Lane> lanes)
{
	Street street;
	Lane lane;
	std::string actualLaneName;
	std::string lastLane = lanes.at(0).laneName;

	lastLane = this->laneToStreet(lastLane);

	for(int i = 0; i < lanes.size(); i++)
	{
		lane = lanes.at(i);
		actualLaneName = this->laneToStreet(lane.laneName);
		if(lastLane.compare(actualLaneName) == 0)
		{
			street.lanes.push_back(lane);
		}
		else
		{
			street.carStream = 0;
			street.queueSize = 0;
			street.streetName = lastLane;
			street.situation = FUZZY_OUTPUT_VALUE_SHOW_SCREEN_NOTHING;
			this->streets.push_back(street);
			//the new lane
			street.lanes.clear();
			street.lanes.push_back(lane);
		}

		lastLane = actualLaneName;
	}
	street.carStream = 0;
	street.queueSize = 0;
	street.situation = FUZZY_OUTPUT_VALUE_SHOW_SCREEN_NOTHING;
	street.streetName = lastLane;
	this->streets.push_back(street);
}
/*
void Controller::addControllerToSimilarList(Controller *c)
{
	this->similarControllers.push_back(c);
}*/
void Controller::setControllerLogics(std::vector<ControllerLogic *> logics)
{
	//Because im going to clear the vector
	//this->deleteLogics();

	deleteInVector(this->logics);

	//this->logics.clear();
	this->logics = logics;
	bool active = true;

	for(int i = 0; i < this->logics.size(); i++)
	{
		ControllerLogic *logic = this->logics.at(i);

		if(logic->subID.compare("off") == 0)
		{
			active = false;
			break;
		}
	}

	this->setActive(active);
}
Controller::Controller(const Controller &copy)
{
	name = copy.name;
	active = copy.active;
//	controlledLanes = copy.controlledLanes;
//	queueSize = copy.queueSize;
//	carStream = copy.carStream;
//	queuePerLane = copy.queuePerLane;
//	lanes = copy.lanes;
	streets = copy.streets;
	newPhaseDurations = copy.newPhaseDurations;
	currentLogicId = copy.currentLogicId;

	for(int i = 0; i < copy.logics.size(); i++)
	{
		logics.push_back(copy.logics.at(i)->clone());
	}
	/*
	for(int i = 0; i < copy.similarControllers.size(); i++)
	{
		similarControllers.push_back(copy.similarControllers.at(i)->clone());
	}*/

}

ControllerLogic * Controller::getCurrentLogic()
{
	ControllerLogic *actual, *ret = nullptr;

	for(int i = 0; i < logics.size(); i++)
	{
		actual = logics.at(i);

		if(actual->subID.compare(currentLogicId) == 0)
		{
			ret = actual;
			break;
		}
	}

	return ret;
}

Controller::~Controller()
{
	deleteInVector(this->logics);
	//deleteInVector(this->similarControllers);
}

ControllerLogic::ControllerLogic()
{
}

Controller *Controller::clone()
{
	return new Controller(*this);
}

ControllerLogic::~ControllerLogic()
{
	deleteInVector(this->phases);
}

std::string ControllerLogic::intToStrType()
{
	std::string typeStr;

	switch(this->type)
	{
		case 0:
			typeStr = "Static";
			break;
		case 1:
			typeStr = "Actuated";
			break;
		default:
			typeStr = "Agent Based";
	}

	return typeStr;
}
Phase::Phase()
{
}
Phase::Phase(const Phase &copy)
{
	duration = copy.duration;
	duration1 = copy.duration1;
	duration2 = copy.duration2; 
	phaseDef = copy.phaseDef;
}
Phase * Phase::clone()
{
	return new Phase(*this);
}

ControllerLogic::ControllerLogic(const ControllerLogic &copy)
{

	subID = copy.subID;
	type = copy.type;
	subParameter = copy.subParameter;
	currentPhaseIndex = copy.currentPhaseIndex;
	phases = new std::vector<Phase *>();

	for(int i = 0; i < copy.phases->size(); i++)
	{
		phases->push_back(copy.phases->at(i)->clone());
	}
}

ControllerLogic * ControllerLogic::clone()
{
	return new ControllerLogic(*this);
}

ControllerLogic * ControllerLogic::createLogicForSumo(std::string logicName,int durationPhase1, int durationPhase2, 
	                                                  int durationPhase3, int durationPhase4)
{
	std::vector<Phase *> *phases = new std::vector<Phase *>();
	ControllerLogic *logic = new ControllerLogic();
	Phase *phase;

	//its miliseconds!
	durationPhase1 *= 1000;
	durationPhase2 *= 1000;
	durationPhase3 *= 1000;
	durationPhase4 *= 1000;

	logic->subID = logicName;
	logic->currentPhaseIndex = 0;
	logic->type = 0;
	logic->subParameter = 0;
	logic->phases = phases;

	phase = new Phase();
	phase->phaseDef = "GGGGrrr";
	phase->duration = durationPhase1;
	phase->duration1 = durationPhase1;
	phase->duration2 = durationPhase1;
	phases->push_back(phase);

	phase = new Phase();
	phase->phaseDef = "yyyyrrr";
	phase->duration = durationPhase2;
	phase->duration1 = durationPhase2;
	phase->duration2 = durationPhase2;
	phases->push_back(phase);

	phase = new Phase();
	phase->phaseDef = "rrrrGGG";
	phase->duration = durationPhase3;
	phase->duration1 = durationPhase3;
	phase->duration2 = durationPhase3;
	phases->push_back(phase);

	phase = new Phase();
	phase->phaseDef = "rrrryyy";
	phase->duration = durationPhase4;
	phase->duration1 = durationPhase4;
	phase->duration2 = durationPhase4;
	phases->push_back(phase);

	return logic;
}

std::vector<std::string> ControllerLogic::getDefaultPhaseDefForTheSimulation()
{
	std::vector<std::string> phaseDefs;

	phaseDefs.push_back("GGGGrrr");
	phaseDefs.push_back("yyyyrrr");
	phaseDefs.push_back("rrrrGGG");
	phaseDefs.push_back("rrrryyy");

	return phaseDefs;
}

void ControllerLogic::createDirs(std::vector<std::string> controllers)
{
	QString str;
	if(!QDir().mkdir(CONTROLLER_LOGIC_BASE_DIR))
	{
		std::cerr << "Could not create base dir for logic database" << std::endl;
		exit(-55);
	}

	for(int i = 0; i < controllers.size(); i++)
	{
		str = CONTROLLER_LOGIC_BASE_DIR;
		str += "/";
		str += controllers.at(i).c_str();
		QDir().mkdir(str);
	}
}

std::map<std::string, std::vector<StoredControllerLogic *>> ControllerLogic::logicBase;

void ControllerLogic::createDataBaseLogic(std::vector<std::string> controllers)
{
	std::string actualController, logicName;
	StoredControllerLogic *stl;
	std::vector<StoredControllerLogic *> toBeAdded;
	int totalLogics, queue, stream;

	qsrand(QTime::currentTime().msec()); //iniciar seed de random
	
	for(int i = 0; i < controllers.size(); i++)
	{
		actualController = controllers.at(i);

		//+1 para nao dar 0 logicas
		totalLogics = ((qrand() % MAX_LOGICS_PER_CONTROLLER) + 1);

		for(int j = 0; j < totalLogics; j++)
		{
			queue = (qrand() % LOGICS_DATA_BASE_MAX_QUEUE_SIZE); //pode ser 0
			stream = (qrand() % LOGICS_DATA_BASE_MAC_CAR_STREAM); //pode ser 0
			logicName = actualController;
			logicName += "-";
			logicName += QString::number(j).toStdString();
			stl = new StoredControllerLogic();
			stl->setTotalCarStream(stream); 
			stl->setTotalQueueSize(queue); 
			stl->setControllerLogic(ControllerLogic::createALogicBasedOnQueue(queue, logicName));
			stl->setUsedDate(QDateTime::currentDateTime());
			
			toBeAdded.push_back(stl);
		}

		logicBase[actualController] = toBeAdded;
		writeLogicOnDisk(toBeAdded, actualController);
		toBeAdded.clear();
	}
}

ControllerLogic * ControllerLogic::createALogicBasedOnQueue(int queue, std::string name)
{
	int duration1, duration2; //No sumo apesar de ter 4 fases, os valores de tempo sao intercalados

	
	//pequeno 
	if(queue >= 0 && queue <= 10) 
	{
		duration1 = (qrand() % LOGIC_MAX_TIME) + 10;
		duration2 = duration1 - (qrand() % 5) + (qrand() % 10);
	}
	else if(queue > 10 && queue <= 18) //med
	{
		duration1 = (qrand() % LOGIC_MED_TIME) + 10;
		duration2 = duration1 - (qrand() % 5) + (qrand() % 10);;
	}
	else //grande
	{
		duration1 = (qrand() % LOGIC_SMALL_TIME) + 10;
		duration2 = duration1 - (qrand() % 5) + (qrand() % 10);;
	}

	return ControllerLogic::createLogicForSumo(name, duration1, duration2, duration1, duration2);
}

void ControllerLogic::readLogicDataBase(std::vector<std::string> controllers)
{
	if(!QDir(CONTROLLER_LOGIC_BASE_DIR).exists())
	{
		createDirs(controllers);	
	}

	createDataBaseLogic(controllers);
}

void ControllerLogic::destroyLogicDataBase()
{
	std::vector<StoredControllerLogic *> storedLogics;

	for (std::map<std::string, std::vector<StoredControllerLogic *>>::iterator it = 
		logicBase.begin(); it != logicBase.end(); ++it) 
	{
		storedLogics = it->second;
		deleteInVector(storedLogics);
		storedLogics.clear();
	}


}

//TODO
void ControllerLogic::writeLogicOnDisk(std::vector<StoredControllerLogic *> logicsToDisk, std::string controller)
{
	for(int i = 0; i < logicsToDisk.size(); i++)
	{
	}
}

//TODO
void ControllerLogic::readLogicFromDisk(std::vector<std::string> controllers)
{
	for(int i = 0; i < controllers.size(); i++)
	{
	}
}

StoredControllerLogic::StoredControllerLogic()
{

}

StoredControllerLogic::~StoredControllerLogic()
{
	delete logic;
	logic = nullptr;
}