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

	void changePhaseDurationIfAskedTo(Controller *);
	

public slots:
     void setStop(bool newValue);

public:
	SumoClient();
	~SumoClient();

	void connect();
	void close();
	void simulationStep(int  step = 0);

	std::vector<std::string>  getTrafficLightsId();
	std::vector<ControllerLogic *>  getTrafficLightsDefinition(std::string);
	std::vector<std::string> getControllerLanes(std::string);
	void getControllerLinks(std::string);
	void setControllerProgram(std::string, std::string);
	std::string getCurrentLogicForController(std::string);

	void setPhaseDuration(std::string, int);


	void sendNewProgram(std::string, ControllerLogic *);

	void run();

	
};

#endif