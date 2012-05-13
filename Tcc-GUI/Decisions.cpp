#include "Decisions.h"
#include "Supervisor.h"

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
	Controller *c;

	Supervisor::getInstance()->getControllersListClone(&controllers);

	for(int i = 0; i < controllers.size(); i++)
	{
		c = controllers.at(i);
		degree = this->fuzzy.infer(c->getQueueSize(), c->getCarStream());

		if(degree >= FUZZY_SIMILAR_CONTROLLER_TRESHOLD)
		{
		}
	}

	deleteInVector(controllers);
}