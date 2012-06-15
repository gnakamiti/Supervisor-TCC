#ifndef _CONTROLLER_H_
#define _CONTROLLER_H_

#include <vector>
#include <iostream>
#include <map>
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
	std::string streetName;
	std::string situation;
	int queueSize;
	int carStream;
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

	static ControllerLogic createLogicForSumo();
};

class Controller
{
private:
	std::string name;
	std::vector<ControllerLogic *>  logics;
	//std::vector<Controller *> similarControllers; //This is used by fuzzy! but not yet....
	//std::vector<Lane> lanes;
	std::vector<Street> streets;
	std::string currentLogicId;
	bool active;
//	int queueSize;
//	int carStream;
//	int queuePerLane;
	//New phase duration for a phase
	//key = phase and value = phase duration
	std::map<int, int> newPhaseDurations;
	void createStreets(std::vector<Lane>);
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
	//std::vector<Lane> getLanes() { return lanes; }
//	int getQueueSize() { return queueSize; }
//	int getCarStream() { return carStream; }
//	int getQueuePerLane() { return queuePerLane; }
//	void setQueuePerLane(int n) { queuePerLane = n; }
//	void setCarStream(int n) { carStream += n; }
//	void setQueueSize(int n) { queueSize = n; this->setQueuePerLane((int)(n / this->getLanes().size())); }
	bool isActive() { return active; }
	void setControllerLogics(std::vector<ControllerLogic *>);
	//void addControllerToSimilarList(Controller *);
	//Isso aqui me causou problemas, acostumado com referencias em java :(
	//Eu estava apenas retornando uma copia!
	std::vector<Street> * getControlledStreets() { return &streets; }
	std::map<int, int> getNewPhaseDuration() { return newPhaseDurations; }
	ControllerLogic * getCurrentLogic();
	std::string getCurrentLogicAsString() { return currentLogicId; }
	void setCurrentLogicId(std::string c) { currentLogicId = c; }

	Controller *clone();
};



#endif