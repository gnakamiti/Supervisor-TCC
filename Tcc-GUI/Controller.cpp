#include "Controller.h"

Controller::Controller()
{
}

Controller::Controller(std::string name, std::vector<ControllerLogic *>  logics, std::vector<std::string> controlledLanes)
{
	this->name = name;
	this->setControllerLogics(logics);
	this->controlledLanes = controlledLanes;
	this->carStream = -1;
	this->queueSize = -2;
}

void Controller::addControllerToSimilarList(Controller *c)
{
	this->similarControllers.push_back(c);
}
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
	controlledLanes = copy.controlledLanes;
	queueSize = copy.queueSize;
	carStream = copy.carStream;
	queuePerLane = copy.queuePerLane;

	for(int i = 0; i < copy.logics.size(); i++)
	{
		logics.push_back(copy.logics.at(i)->clone());
	}

	for(int i = 0; i < copy.similarControllers.size(); i++)
	{
		similarControllers.push_back(copy.similarControllers.at(i)->clone());
	}

}
Controller::~Controller()
{
	deleteInVector(this->logics);
	deleteInVector(this->similarControllers);
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