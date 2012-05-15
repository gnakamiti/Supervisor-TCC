#include "Decisions.h"
#include "Supervisor.h"
#include "SupervisorLog.h"
#include <cmath>

Decisions::Decisions()
{
}

Decisions::~Decisions()
{
	if(this->fuzzyTimer->isActive())
		this->fuzzyTimer->stop();

	delete this->fuzzyTimer;
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
			

			degree = this->fuzzy.infer(queueFinal, streamFinal);

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

	deleteInVector(controllers);
}