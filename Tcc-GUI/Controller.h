#ifndef _CONTROLLER_H_
#define _CONTROLLER_H_

#include <vector>
#include <iostream>

class Phase
{
public:
	int duration;
	int duration1;
	int duration2;
	std::string phaseDef;
};

class ControllerLogic
{
public:
	ControllerLogic();
	~ControllerLogic();

	std::string subID;
	int type;
	int subParameter;
	int currentPhaseIndex;
	std::vector<Phase *> phases;
};

class Controller
{
private:
	std::string name;
	std::vector<ControllerLogic *>  logics;
	std::vector<std::string> controlledLanes;

public:
	Controller();
	Controller(std::string name, std::vector<ControllerLogic *>  , std::vector<std::string>);
	~Controller();

	std::string getName() { return name; }
	std::vector<std::string> getControlledLanes() { return controlledLanes; }
	std::vector<ControllerLogic *> getLogics() { return logics; }
};



#endif