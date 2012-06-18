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
	int duration1; //It's in milisecs - nao usado pelo sumo
	int duration2; //It's in milisecs - nao usado pelo sumo
	std::string phaseDef; //Definicao da faze - (Verde, vermelho e amarelo)
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

	//Tipo do controlador (Fixo, inteligente e blalbal) no caso apenas fixo
	std::string intToStrType();

	ControllerLogic *clone();

	//Cria uma nova logica para enviar ao sumo
	static ControllerLogic * createLogicForSumo(std::string, int, int, int, int);
};

class Controller
{
private:
	std::string name;
	std::vector<ControllerLogic *>  logics;
	std::vector<Street> streets;
	std::string currentLogicId;
	bool active;
	std::map<int, int> newPhaseDurations;

	//Cria as rua a partir da lena
	void createStreets(std::vector<Lane>);
	//Retorna o nome de uma rua
	std::string laneToStreet(std::string);


public:
	Controller();
	Controller(std::string, std::vector<ControllerLogic *>, std::vector<Lane>);
	//FOR DEEP COPY
	Controller(const Controller &);

	~Controller();
	
	//Seta se um controlador esta ativo
	void setActive(bool b) { active = b; }
	//Nome do controlador
	std::string getName() { return name; }
	//Retorna logica do controlador
	std::vector<ControllerLogic *> getLogics() { return logics; }
	//Esta ativo?
	bool isActive() { return active; }
	//Seta logica
	void setControllerLogics(std::vector<ControllerLogic *>);
	//Retorna ruas controladas
	std::vector<Street> * getControlledStreets() { return &streets; }
	//Tirar isso aqui
	std::map<int, int> getNewPhaseDuration() { return newPhaseDurations; }
	//Logica atual
	ControllerLogic * getCurrentLogic();
	//Nome da logica atual
	std::string getCurrentLogicAsString() { return currentLogicId; }
	//Seta o nome da logica atual
	void setCurrentLogicId(std::string c) { currentLogicId = c; }

	Controller *clone();
};



#endif