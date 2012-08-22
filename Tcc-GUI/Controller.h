#ifndef _CONTROLLER_H_
#define _CONTROLLER_H_

#include <vector>
#include <iostream>
#include <ostream>
#include <QDir>
#include <QDateTime>
#include <QList>
#include <QMutexLocker>
#include <QMutex>
#include <map>
#include <ga/GAListGenome.h>
#include "constants.h"
#include "Utils.h"
#include "Genetic.h"
#include "DataStreamUtils.h"

class ControllerLogic; //class forwading

//Faixa de transito
typedef struct LaneStruct
{
	std::string laneName;
	std::string detectorName;
} Lane;

//Representa uma rua
typedef struct StreetStruct
{
	std::vector<Lane> lanes;
	std::string streetName;
	std::string situation;
	int queueSize;
	int carStream;
} Street;

class LogicGene
{
public:
	int value;
	int type;
	LogicGene() {}
	LogicGene(int t, int v) { type = t; value = v; }
	~LogicGene() {}
	LogicGene(const LogicGene &g) { value = g.value; type = g.type; }

	const bool operator==(LogicGene &g) 
	{
		if(g.value == value && g.type == type)
			return true;
		return false;
	}

	const bool operator!=(LogicGene &g) 
	{
		if(g.value != value && g.type != type)
			return true;
		return false;
	}

	LogicGene operator=(LogicGene &g)
	{
		value = g.value;
		type = g.type;
		return *this;
	}

};

//Logica para base de dados das logicas
//Essa classe vai sera usada no algoritmo genetico
class StoredControllerLogic
{
private:
	
	ControllerLogic *logic;
	QList<Street> streets;
	QDateTime usedIn;
	int goodDegree;

public:
	StoredControllerLogic();
	StoredControllerLogic(const StoredControllerLogic &);
	~StoredControllerLogic();

	//int getTotalQueueSize() const { return totalQueueSize; } 
	//int getTotalCarStream() const { return totalCarStream; }
	ControllerLogic * getControllerLogic() const { return logic; }
	QDateTime getUsedIn() const { return usedIn; }
	QList<Street> getStreets() const { return streets; }

	void setControllerLogic(ControllerLogic *l) { logic = l; }
	//void setTotalQueueSize(int t) { totalQueueSize = t; }
	//void setTotalCarStream(int t) { totalCarStream = t; }
	void setUsedDate(QDateTime t) { usedIn = t; }
	void addStreet(Street s) { streets.push_back(s); }
	void setStreets(QList<Street> s) { streets.clear(); streets = s; }

	int getGoodDegree() const { return goodDegree; }
	void setGoodDegree(int i) { goodDegree = i; }

	GAListGenome<LogicGene> toGene();
};

//Fase do semaforo
class Phase
{
public:
	int duration; //It's in milisecs
	int duration1; //It's in milisecs - nao usado pelo sumo
	int duration2; //It's in milisecs - nao usado pelo sumo
	std::string phaseDef; //Definicao da faze - (Verde, vermelho e amarelo)
	Phase();
	Phase(int, int, int, std::string);
	Phase(const Phase &);

	Phase * clone();



};

//Representa um modo de operacao de um controlador
class ControllerLogic
{
private:

	static QMutex logicBaseLock;
	static std::map<std::string, std::vector<StoredControllerLogic *>> logicBase;

	//Cria diretorios para amarzenar as base de casos
	static void createDirs(std::vector<std::string>);

	//Cria todas as StoredControllerLogic para os controladores
	static void createDataBaseLogic(std::vector<std::string>);

	//Cria uma logica para um controlador baseado no tamanho TOTAL de filas
	static ControllerLogic * createALogicBasedOnQueue(int, std::string, int *);

	//Salva no disco a base de dados de logicas
	static void readAllLogicsFromDisk(std::vector<std::string>);
	
	//Le todas as logicas de um controlador que estao numa pasta
	static std::vector<StoredControllerLogic *> readLogicFromDir(QFileInfoList);

	//Le a base de dados de logicas do disco
	static void writeLogicOnDisk(std::vector<StoredControllerLogic *>, std::string);
	
public:
	ControllerLogic();
	ControllerLogic(std::string, int, int, int, std::vector<Phase*>*);
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
	
	//Devolve a definicao de fase padrao
	static std::vector<std::string> getDefaultPhaseDefForTheSimulation();

	//Gera a base de casos
	static void readLogicDataBase(std::vector<std::string>);

	//da um free na base de casos - CUIDADO AO USAR ISSO!
	static void destroyLogicDataBaseInMemory();

	//Retorna o vetor de logicas na base para um controlador. é thread safe.
	static std::vector<StoredControllerLogic *>  getStoredLogicFromLogicBase(std::string, int);
	static std::vector<StoredControllerLogic *>  getAllStoredLogicFromLogicBase(std::string);
	//Inseri uma nova logica na base. é thread safe.
	static void addNewControllerLogicToTheBase(std::string controller, StoredControllerLogic *);

	static int evaluateGoodDegree(int queue, ControllerLogic *logic);

	static void setGoodDegreeOnStoredLogic(std::string, ControllerLogic *, int);

	std::string toString();
};


//Semaforo
class Controller
{
private:
	std::string name;
	std::vector<ControllerLogic *>  logics;
	std::vector<Street> streets;
	std::string currentLogicId;
	bool active;

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
	//Logica atual
	ControllerLogic * getCurrentLogic();
	//Nome da logica atual
	std::string getCurrentLogicAsString() { return currentLogicId; }
	//Seta o nome da logica atual
	void setCurrentLogicId(std::string c) { currentLogicId = c; }

	Controller *clone();
};

#endif