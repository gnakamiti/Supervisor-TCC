#include "Decisions.h"
#include "Supervisor.h"
#include "SupervisorLog.h"
#include <cmath>

Decisions::Decisions()
{
	this->fuzzySimilarControllers = new Fuzzy(FUZZY_USE_CAR_STREAM);
	this->fuzzyControllerSituation = new Fuzzy(FUZZY_DONT_USE_CAR_STREAM);
}

Decisions::~Decisions()
{
	if(this->fuzzyTimer->isActive())
		this->fuzzyTimer->stop();

	delete this->fuzzyTimer;
	delete this->fuzzyControllerSituation;
	delete this->fuzzySimilarControllers;

	this->fuzzyControllerSituation = nullptr;
	this->fuzzySimilarControllers = nullptr;
	this->fuzzyTimer = nullptr;
}
void Decisions::run()
{
	this->fuzzyTimer = new QTimer();
	connect(this->fuzzyTimer, SIGNAL(timeout()), this, SLOT(fuzzyTimerTimeout()));
	this->fuzzyTimer->start(FUZZY_TIMER_INTERVAL);

	exec();

}
std::vector<int> Decisions::sumTotalQueueAndStreamForController(Controller *c)
{
	int queue = 0, stream = 0;
	std::vector<int> result;
	std::vector<Street> *streets = c->getControlledStreets();

	for(int i = 0; i < streets->size(); i++)
	{
		queue += streets->at(i).queueSize;
		stream += streets->at(i).carStream;
	}

	result.push_back(queue);
	result.push_back(stream);

	return result;
}
void Decisions::fuzzyTimerTimeout()
{
	std::vector<Controller *> controllers;
	FuzzyResult fuzzyResultI, fuzzyResultCompare;
	Controller *cI, *cJ;
	std::vector<Street> *controlledStreetsI;
	int queueFinal, streamFinal;
	std::vector<int> resultI, resultJ;

	Supervisor::getInstance()->getControllersListClone(&controllers);
	SupervisorLog::getInstance()->writeOnLog("----- Begin -----");
	for(int i = 0; i < controllers.size(); i++)
	{
		cI = controllers.at(i);
		controlledStreetsI = cI->getControlledStreets();
		
		for(int j = 0; j < controlledStreetsI->size(); j++)
		{
			fuzzyResultI = this->fuzzyControllerSituation->infer
				(controlledStreetsI->at(j).queueSize);

			Supervisor::getInstance()->
					setSituationForStreet(cI->getName(), 
					controlledStreetsI->at(j).streetName,
					fuzzyResultI.LinguisticValue);

			//I'm bad if the invere of degree is bad
			if(fuzzyResultI.value <= FUZZY_SITUATION_NOT_GOOD_TRESHOLD)
			{
				
				for(int k = 0; k < controllers.size(); k++)
				{
					//I'm not comparing myself
					if(i == k)
						continue;

					cJ = controllers.at(k);

					resultI = this->sumTotalQueueAndStreamForController(cI);
					resultJ = this->sumTotalQueueAndStreamForController(cJ);

					queueFinal = resultI.at(0) - resultJ.at(0);
					streamFinal = abs((resultI.at(1) - resultJ.at(1)));

					fuzzyResultCompare = this->fuzzySimilarControllers->infer(queueFinal, streamFinal);

					if(fuzzyResultCompare.value >= FUZZY_SIMILAR_CONTROLLER_TRESHOLD)
					{
						std::string similarOutput = "";
						similarOutput += "Controller ";
						similarOutput += cI->getName();
						similarOutput += " is similar to ";
						similarOutput += cJ->getName();
						similarOutput += ".\n***\n";
						SupervisorLog::getInstance()->writeOnLog(similarOutput);
					}
					resultI.clear();
					resultJ.clear();
				}
			}
		}
	}
	SupervisorLog::getInstance()->writeOnLog("----- End -----");
	deleteInVector(controllers);
}