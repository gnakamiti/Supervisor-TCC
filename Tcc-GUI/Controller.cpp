#include "Controller.h"

Controller::Controller()
{
}


Controller::Controller(std::string name, std::vector<ControllerLogic *>  logics, std::vector<std::string> controlledLanes)
{
	this->name = name;
	this->setControllerLogics(logics);
	this->controlledLanes = controlledLanes;
	/*
	this->logics.push_back(new ControllerLogic());
	this->logics.push_back(new ControllerLogic());
	this->logics.push_back(new ControllerLogic());
	this->logics.push_back(new ControllerLogic());*/
}
void Controller::deleteLogics()
{
	ControllerLogic *cl;

	for(int i = 0; i < this->logics.size(); i++)
	{
		cl = this->logics.at(i);
		delete cl;
		cl = nullptr;
		
	}
}
void Controller::setControllerLogics(std::vector<ControllerLogic *> logics)
{
	//Because im going to clear the vector
	this->deleteLogics();

	this->logics.clear();
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

Controller::~Controller()
{
	this->deleteLogics();
}

ControllerLogic::ControllerLogic()
{
}

ControllerLogic::~ControllerLogic()
{
	Phase *phase;

	for(int i = 0; i < phases->size(); i++)
	{
		phase = phases->at(i);	
		delete phase;
		phase = nullptr;
	}

	delete phases;
	phases = nullptr;
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