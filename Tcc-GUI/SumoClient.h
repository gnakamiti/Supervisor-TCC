#ifndef _SUMO_CLIENT_H
#define _SUMO_CLIENT_H
#include "socket.h"
#include "Controller.h"

using namespace tcpip;

#define LOCAL_HOST "localhost"
#define PORT_HOST 8814

#define CLOSE_SUMO 0x7F
#define SUMO_STEP 0x02

#define SUMO_TRAFFIC_LIGHTS 0xa2
#define SUMO_GET_TRAFFIC_LIGHTS 0x00
#define SUMO_GET_COMPLETE_TRAFFIC_LIGHTS_DEFINITION 0x2b
#define SUMO_GET_CONTROLLED_LANES  0x26

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

	
};

#endif