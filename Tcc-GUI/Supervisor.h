#ifndef _SUPERVISOR_H_
#define _SUPERVISOR_H_

#include "mainwindow.h"
#include "SumoClient.h"
#include "Controller.h"
#include "SupervisorLog.h"
#include "constants.h"
#include <QtGui/QApplication>
#include <QThreadPool>
#include <QMutexLocker>
#include <QMutex>
#include "Decisions.h"



class Supervisor
{

private:
	static Supervisor *self;
	

	SumoClient sumoC;
	
	QThreadPool *threadPool;
	
	MainWindow *window;
	QMutex mutexControllerList;
	Decisions decisions;

	std::vector<Controller *> controllers;
	


public:
	~Supervisor();
	Supervisor();
	void startThreads(void);

	static Supervisor * getInstance();
	
	
};


#endif