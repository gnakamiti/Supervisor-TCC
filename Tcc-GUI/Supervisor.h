#ifndef _SUPERVISOR_H_
#define _SUPERVISOR_H_

#include "mainwindow.h"
#include "SumoClient.h"
#include "Controller.h"
#include <QtGui/QApplication>
#include <QThreadPool>
#include <QRunnable>
#include <QMutexLocker>
#include <QMutex>
#include "constants.h"
#include "Fuzzy.h"


class Supervisor
{

private:
	SumoClient sumoC;
	
	QThreadPool *threadPool;
	int argc;
	char **argv;
	MainWindow *window;
	QMutex mutexControllerList;

	std::vector<Controller *> controllers;
	
	class Decisions:public QRunnable
	{
		private:
			Fuzzy fuzzy;
			

		public: 
			Decisions(Supervisor *ml): self(ml) {}

			/*
				This is a thread!
			*/
			void run() 
			{
				
				/*QMutexLocker locker(&self->mutexControllerList);
				self->sumoC.setControllerProgram(self->controllers.at(0)->getName(), "off");
				self->controllers.at(0)->setControllerLogics(self->sumoC.getTrafficLightsDefinition(self->controllers.at(0)->getName()));
				/*
				for(int i = 0; i < 1000; i++)
				{
					self->sumoC.simulationStep();
				}*/
				self->sumoC.simulationStep();
			}
			Supervisor *self; 

	} decisions;


public:
	Supervisor();
	~Supervisor();
	Supervisor(int, char **);
	void startThreads(void);
	
	
};


#endif