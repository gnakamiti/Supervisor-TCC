#ifndef _DECISIONS_H_
#define _DECISIONS_H_

#include <QRunnable>
#include <QTimer>
#include <QObject>
#include "Fuzzy.h"
#include "constants.h"

class Decisions:public QObject, public QRunnable
{
	Q_OBJECT

	private slots:
		void fuzzyTimerTimeout();

	private:
		Fuzzy fuzzy;
		QTimer *fuzzyTimer;
			

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