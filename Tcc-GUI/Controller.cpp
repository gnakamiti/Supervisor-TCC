#include "Controller.h"

Controller::Controller()
{
}


Controller::Controller(std::string name, std::vector<ControllerLogic *>  logics, std::vector<std::string> controlledLanes)
{
	this->name = name;
	this->logics = logics;
	this->controlledLanes = controlledLanes;
}

Controller::~Controller()
{
	ControllerLogic *cl;

	for(int i = 0; i < this->logics.size(); i++)
	{
		cl = this->logics.at(i);
		delete cl;
		cl = nullptr;
		
	}

}

ControllerLogic::ControllerLogic()
{
}
ControllerLogic::~ControllerLogic()
{
	Phase *phase;

	for(int i = 0; i < phases.size(); i++)
	{
		phase = phases.at(i);
		delete phase;
		phase = nullptr;

	}
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