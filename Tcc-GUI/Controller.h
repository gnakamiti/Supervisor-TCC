#ifndef _CONTROLLER_H_
#define _CONTROLLER_H_

#include <vector>
#include <iostream>
#include "constants.h"
#include "Utils.h"

class Phase
{
public:
	int duration; //It's in milisecs
	int duration1; //It's in milisecs
	int duration2; //It's in milisecs
	std::string phaseDef;
	Phase();
	Phase(const Phase &);

	Phase * clone();
};

class ControllerLogic
{
public:
	ControllerLogic();
	ControllerLogic(const ControllerLogic &);
	~ControllerLogic();

	std::string subID;
	int type;
	int subParameter;
	int currentPhaseIndex;
	std::vector<Phase *> *phases;

	std::string intToStrType();

	ControllerLogic *clone();
};

class Controller
{
private:
	std::string name;
	std::vector<ControllerLogic *>  logics;
	std::vector<std::string> controlledLanes;
	std::vector<Controller *> similarControllers; //This is used by fuzzy!
	bool active;
	int queueSize;
	int carStream;

	//void deleteLogics();

public:
	Controller();
	Controller(std::string name, std::vector<ControllerLogic *>  , std::vector<std::string>);
	//FOR DEEP COPY
	Controller(const Controller &);

	~Controller();
	

	void setActive(bool b) { active = b; }
	std::string getName() { return name; }
	std::vector<std::string> getControlledLanes() { return controlledLanes; }
	std::vector<ControllerLogic *> getLogics() { return logics; }
	int getQueueSize() { return queueSize; }
	int getCarStream() { return carStream; }
	void setCarStream(int n) { carStream = n; }
	void setQueueSize(int n) { queueSize = n; }
	bool isActive() { return active; }
	void setControllerLogics(std::vector<ControllerLogic *>);
	void addControllerToSimilarList(Controller *);

	Controller *clone();
};



#endif