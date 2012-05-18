#ifndef _CONTROLLER_H_
#define _CONTROLLER_H_

#include <vector>
#include <iostream>
#include "constants.h"
#include "Utils.h"

typedef struct LaneStruct
{
	std::string laneName;
	std::string detectorName;
} Lane;

typedef struct StreetStruct
{
	std::vector<Lane> lanes;
	int queueSize;
	int queueSizePerLane;
	int carStream;
	std::string streetName;
} Street;

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
	std::vector<Controller *> similarControllers; //This is used by fuzzy! but not yet....
	std::vector<Lane> lanes;
	std::vector<Street> streets;
	bool active;
	//int queueSize;
	//int carStream;
	//int queuePerLane;

	void createStreets();
	std::string laneToStreet(std::string);
	//void deleteLogics();

public:
	Controller();
	Controller(std::string, std::vector<ControllerLogic *>, std::vector<Lane>);
	//FOR DEEP COPY
	Controller(const Controller &);

	~Controller();
	

	void setActive(bool b) { active = b; }
	std::string getName() { return name; }
	std::vector<ControllerLogic *> getLogics() { return logics; }
	std::vector<Lane> getLanes() { return lanes; }
	//int getQueueSize() { return queueSize; }
	//int getCarStream() { return carStream; }
	//int getQueuePerLane() { return queuePerLane; }
	//void setQueuePerLane(int n) { queuePerLane = n; }
	//void setCarStream(int n) { carStream += n; }
	//void setQueueSize(int n) { queueSize = n; this->setQueuePerLane((int)(n / this->getLanes().size())); }
	bool isActive() { return active; }
	void setControllerLogics(std::vector<ControllerLogic *>);
	void addControllerToSimilarList(Controller *);

	Controller *clone();
};



#endif