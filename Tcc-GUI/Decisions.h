#ifndef _DECISIONS_H_
#define _DECISIONS_H_

#include <QThread>
#include <QTimer>
#include <QObject>
#include <QtCore>
#include "Genetic.h"
#include "Fuzzy.h"
#include "constants.h"

class Supervisor;

class Decisions:public QThread
{
	
	Q_OBJECT
	private slots:
		void fuzzyTimerTimeout();

	private:
		std::vector<int> sumTotalQueueAndStreamForController(Controller *);
		QTimer *fuzzyTimer;
		Fuzzy *fuzzyControllerSituation;
		Fuzzy *fuzzySimilarControllers;
		//Genetic genetic;

	public:
		Decisions();
		~Decisions();
		/*
			This is a thread!
		*/
		void run();

			

};
#endif