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



class Supervisor
{

private:
	SumoClient sumoC;
	
	QThreadPool *threadPool;
	int argc;
	char **argv;
	MainWindow *window;
	QMutex mutex;

	std::vector<Controller *> controllers;
	
	class Decisions:public QRunnable
	{
		private:
		

		public: 
			Decisions(Supervisor *ml): self(ml) {} 
			void run()
			{
				int x = 12;
				//QMutexLocker locker(&self->mutex);
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