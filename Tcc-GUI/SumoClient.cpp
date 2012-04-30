#include "SumoClient.h"
#include <iostream>

SumoClient::SumoClient()
{
	s = new Socket(LOCAL_HOST, PORT_HOST);
}

SumoClient::~SumoClient()
{
	if( s != nullptr)
	{
		s->close();
		delete s;
		s = nullptr;
	}
}
//TODO - CONTINUAR ISSO?
void SumoClient::getControllerLinks(std::string controllerId)
{
	int nbSignals, nbControlledLinks;
	std::vector<std::string> links;
	Storage *in;

	in = this->sendCommandForSumoTrafficLights(controllerId, SUMO_GET_CONTROLLED_LINKS);

	if(in->readUnsignedByte() <= 0)
	   in->readInt();

	nbSignals = in->readInt();

	for(int i = 0; i < nbSignals; i++)
	{
		in->readByte();
		nbControlledLinks = in->readInt();

		for(int k = 0; k < nbControlledLinks; k++)
		{
			in->readByte();
			links = in->readStringList();
		}
	}

	delete in;
	in = nullptr;
}

std::vector<ControllerLogic *>  SumoClient::getTrafficLightsDefinition(std::string controllerId)
{
	Storage *in;
	int numberOfLogics;
	std::vector<ControllerLogic *> logics;
	ControllerLogic *logic;
	int nbLogic;
	std::vector<Phase *> phases;
	Phase *phase;

	in = this->sendCommandForSumoTrafficLights(controllerId, SUMO_GET_COMPLETE_TRAFFIC_LIGHTS_DEFINITION);

	if(in->readUnsignedByte() <= 0)
	   in->readInt();

	numberOfLogics = in->readInt();

	for(int i = 0; i < numberOfLogics; i++)
	{
		logic = new ControllerLogic();

		in->readUnsignedByte();
		logic->subID = in->readString();

		in->readUnsignedByte();
		logic->type = in->readInt();

		in->readUnsignedByte();
		logic->subParameter = in->readInt();

		in->readUnsignedByte();
		logic->currentPhaseIndex = in->readInt();

		in->readUnsignedByte();
		nbLogic = in->readInt();

		for(int k = 0; k < nbLogic; k++)
		{
			phase = new Phase();

			in->readUnsignedByte();
			phase->duration = in->readInt();

			in->readUnsignedByte();
			phase->duration1 = in->readInt();

			in->readUnsignedByte();
			phase->duration2 = in->readInt();

			in->readUnsignedByte();
			phase->phaseDef = in->readString();

			phases.push_back(phase);
		}
		
		logic->phases = phases;

		logics.push_back(logic);
	}

	delete in;
	in = nullptr;

	return logics;
}

void SumoClient::connect()
{
	s->connect();
}

void SumoClient::simulationStep(int step)
{
	Storage out, in;

	out.writeUnsignedByte(1+1+4);
	out.writeUnsignedByte(SUMO_STEP);
	out.writeInt(step);
	std::cout << step;
	
	s->sendExact(out);
	s->receiveExact(in);
}
//Only used for traffic lights functions for now.
Storage * SumoClient::sendCommandForSumoTrafficLights(std::string controllerId, int flag)
{
	Storage *in, out;

	int length;

	length = 1+1+1+4+controllerId.size();

	in = new Storage();

	if(length <= 255)
	{
		out.writeUnsignedByte(length);
		out.writeUnsignedByte(SUMO_TRAFFIC_LIGHTS);
		out.writeUnsignedByte(flag);
		out.writeString(controllerId);
		
	}
	else
	{
		out.writeUnsignedByte(0);
		out.writeInt(length+4);
		out.writeUnsignedByte(SUMO_TRAFFIC_LIGHTS);
		out.writeUnsignedByte(flag);
		out.writeString(controllerId);
	}

	s->sendExact(out);
	s->receiveExact(*in);

	//REMOVING GARBAGE FROM THE MESSAGE!

	in->readUnsignedByte();
	in->readUnsignedByte();
	in->readUnsignedByte();
	in->readString();
	if(in->readUnsignedByte() <= 0)
	   in->readInt();
	
	in->readUnsignedByte();
	in->readUnsignedByte();
	in->readString();
	in->readUnsignedByte();

	//End removing garbage
	
	return in;
}
std::vector<std::string> SumoClient::getControllerLanes(std::string controllerId)
{
	Storage *in;
	std::vector<std::string> controlledLanes;

	in = this->sendCommandForSumoTrafficLights(controllerId, SUMO_GET_CONTROLLED_LANES);
	controlledLanes = in->readStringList();

	delete in;
	in = nullptr;

	return controlledLanes;
}
std::vector<std::string> SumoClient::getTrafficLightsId()
{
	Storage *in;
	std::vector<std::string> controllerNames;

	in = this->sendCommandForSumoTrafficLights("", SUMO_GET_TRAFFIC_LIGHTS);
	controllerNames = in->readStringList();

	delete in;
	in = nullptr;

	return controllerNames;
	
}

void SumoClient::close()
{
	Storage msg, inMsg;
	msg.writeUnsignedByte(1 + 1);
	msg.writeUnsignedByte(CLOSE_SUMO);

	s->sendExact(msg);
	s->receiveExact(inMsg);
	s->close();

	delete s;

	s = nullptr;
}