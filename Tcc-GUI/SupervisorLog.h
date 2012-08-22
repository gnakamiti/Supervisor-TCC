#ifndef _SUPERVISOR_LOG_H_
#define _SUPERVISOR_LOG_H_

#include "constants.h"
#include <iostream>
#include <fstream>
#include <QMutex>
#include <QMutexLocker>

class SupervisorLog
{
private:
	static  SupervisorLog *self;
	std::ofstream  fileOut;
	std::ofstream fileQueue;
	std::ofstream newProgramLog;
	std::ofstream fitness;
	QMutex mutexFitness;
	QMutex mutexProgram;
	

public:
	SupervisorLog();
	~SupervisorLog();

	static SupervisorLog * getInstance();
	static void closeLog();
	void writeOnLog(std::string);
	void writeOnQueue(std::string);
	void writeOnNewProgram(std::string str);
	void writeOnFitness(std::string str);
	
};

#endif