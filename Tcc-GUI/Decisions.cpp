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

void Decisions::fuzzyTimerTimeout()
{
	std::vector<Controller *> controllers;
	fl::flScalar degree;
	Controller *cI, *cJ;
	int queueSizeI, queueSizeJ, carStreamI, carStreamJ, streamFinal, queueFinal;

	Supervisor::getInstance()->getControllersListClone(&controllers);

	for(int i = 0; i < controllers.size(); i++)
	{
		cI = controllers.at(i);
		queueSizeI = cI->getQueuePerLane();
		carStreamI = cI->getCarStream();

		degree = this->fuzzyControllerSituation->infer(queueSizeI);
		//I'm bad if the invere of degree is bad
		if(degree <= FUZZY_SITUATION_NOT_GOOD_TRESHOLD)
		{
			//I'm in a bad situation. Who is similar to me?
			//Maybe it can help!
			for(int j = 0; j < controllers.size(); j++)
			{
			
				if(i == j) //Do not compare equal controllers
					continue;

				cJ = controllers.at(j);

				queueSizeJ = cJ->getQueuePerLane();
				queueFinal = (queueSizeI - queueSizeJ);

				//I will only calculate similarity if my queue is bigger than the another controller
				if(queueSizeI < queueSizeJ)
					continue;

				carStreamJ = cJ->getCarStream();
				streamFinal = abs((carStreamI - carStreamJ));
			

				degree = this->fuzzySimilarControllers->infer(queueFinal, streamFinal);

				if(degree >= FUZZY_SIMILAR_CONTROLLER_TRESHOLD)
				{
					std::string similarOutput = "";
					similarOutput += "Controller ";
					similarOutput += cI->getName();
					similarOutput += " is similar to ";
					similarOutput += cJ->getName();
					similarOutput += ".";
					SupervisorLog::getInstance()->writeOnLog(similarOutput);
				}
			}
		}
	}

	deleteInVector(controllers);
}