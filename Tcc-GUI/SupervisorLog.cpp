#include "SupervisorLog.h"
#include <QString>
#include <QDir>


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
	QString path = QDir::homePath().append("/logs");
	if(!QDir(path).exists())
		QDir().mkdir(path);
	this->fileOut.open(QDir::homePath().append(LOG_FILE_NAME).toStdString());
	this->fileQueue.open(QDir::homePath().append(LOG_FILE_QUEUE).toStdString());
	this->fitness.open(QDir::homePath().append(LOG_FILE_FITNESS).toStdString());
	this->newProgramLog.open(QDir::homePath().append(LOG_FILE_PROGRAM).toStdString());
}

void SupervisorLog::writeOnLog(std::string str)
{
	this->fileOut << str.c_str() << std::endl;
	this->fileOut.flush();
}

void SupervisorLog::writeOnQueue(std::string str)
{
	this->fileQueue << str.c_str() << std::endl;
	this->fileQueue.flush();
}

void SupervisorLog::writeOnFitness(std::string str)
{
	QMutexLocker(&this->mutexFitness);
	this->fitness << str.c_str() << std::endl;
	this->fitness.flush();
}

void SupervisorLog::writeOnNewProgram(std::string str)
{
	QMutexLocker(&this->mutexProgram);
	this->newProgramLog << str.c_str() << std::endl;
	this->newProgramLog.flush();
}

SupervisorLog::~SupervisorLog()
{
	if(this->fileOut.is_open())
		this->fileOut.close();
	if(this->fileQueue.is_open())
		this->fileQueue.close();
	if(this->fitness.is_open())
		this->fitness.close();
	if(this->newProgramLog.is_open())
		this->newProgramLog.close();
}