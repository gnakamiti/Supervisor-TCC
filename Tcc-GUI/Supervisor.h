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
	
	MainWindow *window;
	QMutex mutexControllerList;
	Decisions decisions;

	std::vector<Controller *> controllers;

	//Retorna uma rua pelo seu nome
	Street * getStreetByName(std::string, std::string);

signals:
	//Envia sinal para thread do sumoC para parar execucao
     void stopValueChanged(bool newValue);


public:
	~Supervisor();
	Supervisor();
	void startThreads(void);

	static Supervisor * getInstance();

	//Cria um clone da lista de controladores
	void getControllersListClone(std::vector<Controller *> *);

	//Seta fluxo e tamanho de fila para um controlador
	void setQueueSizeAndStreamForController(std::string, std::string, int, int);

	//Seta situacao da rua para uma rua do controlador - Fuzzy
	void setSituationForStreet(std::string, std::string, std::string);

	//Seta os programas de um controlador
	void setTrafficLightProgramForController(std::string, std::vector<ControllerLogic *>);

	//Retorna um controlador 
	Controller * getControllerByName(std::string);

	//Seta programa atual do controlador
	void setCurrentProgramForController(std::string , std::string );

	//Set a new program for a controller
	//This will send a message to sumoC
	void sendSumoCProgramForController(std::string , std::string);

	//Sets a completly new program for a controller
	void sendSumoCNewProgramForController(std::string, ControllerLogic *);
	
	
	
};


#endif