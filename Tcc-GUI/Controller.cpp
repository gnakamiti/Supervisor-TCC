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
			street.situation = "REGULAR";
			this->streets.push_back(street);
			//the new lane
			street.lanes.clear();
			street.lanes.push_back(lane);
		}

		lastLane = actualLaneName;
	}
	street.carStream = 0;
	street.queueSize = 0;
	street.situation = "REGULAR";
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