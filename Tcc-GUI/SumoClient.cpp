#include "SumoClient.h"
#include <iostream>
#include "Supervisor.h"

SumoClient::SumoClient()
{
	s = new Socket(LOCAL_HOST, PORT_HOST);
	this->stop = false;
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
	std::vector<Phase *> *phases;
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

		phases = new std::vector<Phase *>();

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

			phases->push_back(phase);
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
	socketLock.lock();

	s->connect();

	socketLock.unlock();
}

void SumoClient::simulationStep(int step)
{
	Storage out, in;

	out.writeUnsignedByte(1+1+4);
	out.writeUnsignedByte(SUMO_STEP);
	out.writeInt(step);
	//std::cout << step;
	socketLock.lock();

	s->sendExact(out);
	s->receiveExact(in);

	socketLock.unlock();
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
	socketLock.lock();

	s->sendExact(out);
	s->receiveExact(*in);

	socketLock.unlock();

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

	socketLock.lock();

	s->sendExact(msg);
	s->receiveExact(inMsg);
	s->close();

	delete s;

	s = nullptr;

	socketLock.unlock();
}

void SumoClient::setControllerProgram(std::string controllerID, std::string programID)
{
	Storage out, in;

	int length,flag;
	flag = SUMO_SET_TRAFFIC_LIGHT_PROGRAM;

	length = (1+4+programID.size()+1+1+1+4+controllerID.size());


	if(length <= 255)
	{
		out.writeUnsignedByte(length);
		out.writeUnsignedByte(SUMO_SET_TRAFFIC_LIGHTS_VALUE);
		out.writeUnsignedByte(flag);
		out.writeString(controllerID);
		
	}
	else
	{
		out.writeUnsignedByte(0);
		out.writeInt(length+4);
		out.writeUnsignedByte(SUMO_SET_TRAFFIC_LIGHTS_VALUE);
		out.writeUnsignedByte(flag);
		out.writeString(controllerID);
	}
	out.writeUnsignedByte(SUMO_TYPE_STRING);
	out.writeString(programID);

	socketLock.lock();

	s->sendExact(out);
	s->receiveExact(in);

	socketLock.unlock();
}
int SumoClient::getQueueSizeOrFlowForALane(std::string laneId, int flag, int domain)
{
	Storage in,out;
	int length;

	//flag = SUMO_GET_QUEUE_SIZE;

	length = 1+1+1+4+laneId.size();
	

	if(length <= 255)
	{
		out.writeUnsignedByte(length);
		out.writeUnsignedByte(domain);
		out.writeUnsignedByte(flag);
		out.writeString(laneId);
		
	}
	else
	{
		out.writeUnsignedByte(0);
		out.writeInt(length+4);
		out.writeUnsignedByte(domain);
		out.writeUnsignedByte(flag);
		out.writeString(laneId);
	}

	socketLock.lock();

	s->sendExact(out);
	s->receiveExact(in);

	socketLock.unlock();
	
	in.readUnsignedByte();
	in.readUnsignedByte();
	in.readUnsignedByte();
	in.readString();


	if(in.readUnsignedByte() <= 0)
		in.readInt();

	in.readUnsignedByte();
	in.readUnsignedByte();
	in.readString();
	in.readUnsignedByte();

	return in.readInt();
}

void SumoClient::setStop(bool newValue)
{
	stopLock.lock();

	this->stop = newValue;

	stopLock.unlock();
}
/*
int SumoClient::getCarStreamByDetector(std::string)
{
	Storage in,out;


	socketLock.lock();

	s->sendExact(out);
	s->receiveExact(in);

	socketLock.unlock();
}*/

void SumoClient::run()
{
	Supervisor *supervisor;
	std::vector<Controller *> controllers;
	Controller *controller;
	std::vector<Lane> controlledLanes;
	std::vector<Street> *controlledStreets;
	Lane lane;
	Street street;
	int queueSize, carStream;

	//TALVEZ VOLTAR ISSO PRA DENTRO DO LOOP
	supervisor = Supervisor::getInstance();

	stopLock.lock();
	while(this->stop == false)
	{
		stopLock.unlock();
		
		

		//TALVEZ EU POSSA TIRAR ESSA CLONE, POIS ESSA THREAD NUNCA PARA
		//E EU SO ATUALIZO PROPRIEDADES DOS CONTROLADORES
		//ALEM DISSO SERIA UM GRANDE GANHO DE MEMORIA!
		supervisor->getControllersListClone(&controllers);

		this->simulationStep();

		for(int i = 0; i < controllers.size(); i++)
		{
			controller = controllers.at(i);
			controlledStreets = controller->getControlledStreets();

			for(int j = 0; j < controlledStreets->size(); j++)
			{
				queueSize = 0;
				carStream = 0;
				street = controlledStreets->at(j);
				controlledLanes = street.lanes;

				for(int k = 0; k < controlledLanes.size(); k++)
				{
					lane = controlledLanes.at(k);

					queueSize += this->getQueueSizeOrFlowForALane
						(lane.laneName, SUMO_GET_QUEUE_SIZE, SUMO_LANE_VARIABLE);

					carStream += this->getQueueSizeOrFlowForALane
						(lane.detectorName, SUMO_GET_CAR_FLOW, SUMO_INDUCTION_LOOP);
				}
				supervisor->setQueueSizeAndStreamForController
					(controller->getName(), street.streetName, queueSize, carStream);
				controlledLanes.clear();
			}

			//controlledStreets.clear();
		}

		deleteInVector(controllers);
		controllers.clear();

		stopLock.lock();
	}
}