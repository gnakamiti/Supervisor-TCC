#ifndef _SUPERVISOR_H_
#define _SUPERVISOR_H_


#include "SumoClient.h"
#include "Controller.h"
#include "SupervisorLog.h"
#include "constants.h"
#include <QtGui/QApplication>
#include <QThreadPool>
#include <QMutexLocker>
#include <QMutex>
#include <QObject>
#include "Decisions.h"


class MainWindow; //For circular dependencies

class Supervisor: public QObject
{
	Q_OBJECT

private:
	static Supervisor *self;

	SumoClient sumoC;
	
	QThreadPool *threadPool;
	
	MainWindow *window;
	QMutex mutexControllerList;
	Decisions decisions;

	std::vector<Controller *> controllers;

	Street * getStreetByName(std::string, std::string);

signals:
     void stopValueChanged(bool newValue);


public:
	~Supervisor();
	Supervisor();
	void startThreads(void);

	static Supervisor * getInstance();

	//QMutex * getMutextControllerListRef();
	//std::vector<Controller *>  * getControllersListRef();

	void getControllersListClone(std::vector<Controller *> *);

	void setQueueSizeAndStreamForController(std::string, std::string, int, int);

	void setSituationForStreet(std::string, std::string, std::string);
	
	
	
};


#endif