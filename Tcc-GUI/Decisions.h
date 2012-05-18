#ifndef _DECISIONS_H_
#define _DECISIONS_H_

#include <QThread>
#include <QTimer>
#include <QObject>
#include "Fuzzy.h"
#include "constants.h"

class Supervisor;

class Decisions:public QThread
{
	Q_OBJECT

	private:
		Fuzzy *fuzzySimilarControllers;
		Fuzzy *fuzzyControllerSituation;
		QTimer *fuzzyTimer;

private slots:
	void fuzzyTimerTimeout();

	public:
		//Decisions(Supervisor *ml): self(ml) {}
		//Supervisor *self;
		Decisions();
		~Decisions();
		/*
			This is a thread!
		*/
		void run();
			

};
#endif