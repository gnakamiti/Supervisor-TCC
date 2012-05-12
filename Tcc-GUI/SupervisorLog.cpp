#include "SupervisorLog.h"

SupervisorLog * SupervisorLog::self= nullptr;

SupervisorLog * SupervisorLog::getInstance()
{
	if(self == nullptr)
	{
		self = new SupervisorLog();
	}

	return self;
	
}
void SupervisorLog::closeLog()
{

	if(self != nullptr)
	{
		delete self;
		self = nullptr;
	}

}

SupervisorLog::SupervisorLog()
{
	this->fileOut.open(LOG_FILE_NAME);
}

void SupervisorLog::writeOnLog(std::string str)
{
	this->fileOut << str.c_str() << std::endl;
}

SupervisorLog::~SupervisorLog()
{
	if(this->fileOut.is_open())
		this->fileOut.close();
}