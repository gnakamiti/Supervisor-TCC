#include "Decisions.h"

Decisions::Decisions()
{
	this->fuzzyTimer = new QTimer(this);
	connect(this->fuzzyTimer, SIGNAL(timeout()), this, SLOT(fuzzyTimerTimeout()));

	this->fuzzyTimer->start(FUZZY_TIMER_INTERVAL);
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
	/*QMutexLocker locker(&self->mutexControllerList);
				self->sumoC.setControllerProgram(self->controllers.at(0)->getName(), "off");
				self->controllers.at(0)->setControllerLogics(self->sumoC.getTrafficLightsDefinition(self->controllers.at(0)->getName()));
				/*
				for(int i = 0; i < 1000; i++)
				{
					self->sumoC.simulationStep();
				}*/
				//self->sumoC.simulationStep();
}


void Decisions::fuzzyTimerTimeout()
{
	fl::flScalar degree;

	degree = this->fuzzy.infer(0,0);

	if(degree >= FUZZY_SIMILAR_CONTROLLER_TRESHOLD)
	{
	}
}