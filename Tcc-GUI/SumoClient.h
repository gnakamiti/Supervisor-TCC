#ifndef _SUMO_CLIENT_H
#define _SUMO_CLIENT_H

#include "socket.h"
#include "Controller.h"

#include "constants.h"
#include <QThread>
#include <map>
#include <QMutex>

using namespace tcpip;


class Supervisor;

class SumoClient: public QThread
{
	Q_OBJECT

private:

	Socket *s;
	QMutex socketLock;
	QMutex stopLock;
	bool stop;
	Storage * sendCommandForSumoTrafficLights(std::string, int);
	

	int getQueueSizeOrFlowForALane(std::string, int, int);

public slots:
     void setStop(bool newValue);

public:
	SumoClient();
	~SumoClient();

	//Conecta com o sumo
	void connect();
	//Fecha conexao
	void close();
	//Anda com a simulacao
	void simulationStep(int  step = 0);

	//Pega lista de controladores
	std::vector<std::string>  getTrafficLightsId();
	//Definicar dos programas de um controlador
	std::vector<ControllerLogic *>  getTrafficLightsDefinition(std::string);
	//Pega faixas de rua controladas
	std::vector<std::string> getControllerLanes(std::string);
	//Nao terminei - nem eh usado
	void getControllerLinks(std::string);
	//Seta um programa existente
	void setControllerProgram(std::string, std::string);
	//Logica(programa) de um controlador
	std::string getCurrentLogicForController(std::string);

	//Seta duracao de uma fase - nao usado
	void setPhaseDuration(std::string, int);

	//Envia um novo programa
	void sendNewProgram(std::string, ControllerLogic *);

	//Thread que anda com a simulacao
	void run();

	
};

#endif