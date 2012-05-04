#ifndef _SUMO_CLIENT_H
#define _SUMO_CLIENT_H
#include "socket.h"
#include "Controller.h"

#include "constants.h"

using namespace tcpip;



class SumoClient
{
private:
	Socket *s;

	Storage * sendCommandForSumoTrafficLights(std::string, int );

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

	
};

#endif