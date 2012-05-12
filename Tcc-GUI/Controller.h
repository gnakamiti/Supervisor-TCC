#ifndef _CONTROLLER_H_
#define _CONTROLLER_H_

#include <vector>
#include <iostream>
#include "constants.h"

class Phase
{
public:
	int duration; //It's in milisecs
	int duration1; //It's in milisecs
	int duration2; //It's in milisecs
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
	std::vector<Phase *> *phases;

	std::string intToStrType();
};

class Controller
{
private:
	std::string name;
	std::vector<ControllerLogic *>  logics;
	std::vector<std::string> controlledLanes;
	std::vector<Controller *> similarControllers; //This is used by fuzzy!
	bool active;
	void deleteLogics();

public:
	Controller();
	Controller(std::string name, std::vector<ControllerLogic *>  , std::vector<std::string>);
	~Controller();

	void setActive(bool b) { active = b; }
	std::string getName() { return name; }
	std::vector<std::string> getControlledLanes() { return controlledLanes; }
	std::vector<ControllerLogic *> getLogics() { return logics; }
	bool isActive() { return active; }
	void setControllerLogics(std::vector<ControllerLogic *>);
	void addControllerToSimilarList(Controller *);
};



#endif