#ifndef _GENETIC_H_
#define _GENETIC_H_

#include <ga/GAGenome.h>
#include <ga/GAListGenome.h>
#include <ga/GASimpleGA.h>
#include <QDateTime>
#include <QMutex>
#include <QList>
#include <QString>
#include "Controller.h"


class Supervisor;
class StoredControllerLogic;

/*class Genetic: public QRunnable
{
private:
	
	std::vector<std::string> similarControllers;

	

public:
	Genetic();
	Genetic(std::string, std::vector<std::string>);
	~Genetic();
	void run();
};*/

//Inicializa a populacao para o algoritmo genetico
//void initPopulation(std::vector<StoredControllerLogic *> &, GAPopulation &);

//Nossa "main" do algoritmo genetico
void tryToFindABetterProgram(std::string, std::vector<std::string>);

//Funcao de fitness
float Objective(GAGenome &);

//Fitness helper
//float evaluateLogic(std::vector<int> &, int);

#endif