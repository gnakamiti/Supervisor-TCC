#ifndef _SUPERVISOR_LOG_H_
#define _SUPERVISOR_LOG_H_

#include "constants.h"
#include <iostream>
#include <fstream>

class SupervisorLog
{
private:
	static  SupervisorLog *self;
	std::ofstream  fileOut;
	

public:
	SupervisorLog();
	~SupervisorLog();

	static SupervisorLog * getInstance();
	static void closeLog();
	void writeOnLog(std::string);
	
};

#endif