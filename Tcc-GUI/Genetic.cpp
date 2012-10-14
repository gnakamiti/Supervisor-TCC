#include "Genetic.h"
#include "Supervisor.h"

static QMutex alreadyRunningMutex;
static QList<QString> alreadyRunning;

//Get the genes
static void _initPopulation(std::vector<StoredControllerLogic *> &vec, GAPopulation &initialPop)
{
	for(int i = 0; i < vec.size(); i++)
	{
		initialPop.add(vec.at(i)->toGene());
		QString grade = "\nGrade:";
		grade += QString::number(vec.at(i)->getGoodDegree())+"\n";
		Supervisor::getInstance()->emitPopulationPrograms(grade);
		Supervisor::getInstance()->emitPopulationPrograms(vec.at(i)->getControllerLogic()->toString().c_str());
	}
}

//Fitness helper
static float _evaluateLogic(std::vector<int> &phases, int acceptableTime)
{
	float result = 0.0;
	float step;
	int duration;

	step = 1.0 / phases.size();

	for(int i = 0; i < phases.size(); i++)
	{
		duration = phases.at(i);
		if (duration >= acceptableTime)
			result -= step;
		else if (duration >= (acceptableTime/phases.size()))
			result += (step/2);
		else
			result += step;


		/*if(duration <= acceptableTime)
			result += step;
		else if(duration > acceptableTime && duration <= acceptableTime * 1.5)
			result += (step/2.0);
		else
			result += (step/4.0);*/
		
	}
	return result;
}

//Send to sumo
static void _sendNewProgramToSumo(std::string &mController, GAListGenome<LogicGene> &best)
{
	//tirar isso.
	GAListIter<LogicGene> iter(best);
	//QList<Street> streets;
	int s;
	std::vector<int> durations, queue, stream;
	QList<Street> streets;
	s = 0;
	//Street *street = nullptr;

	while(s != best.size())
	{
		LogicGene *lg = iter.next();

		if(lg->type == LOGIC_GENE_TYPE_PHASE)
		{
			durations.push_back(lg->value);
		}
		else if(lg->type == LOGIC_GENE_TYPE_QUEUE)
		{
			queue.push_back(lg->value);
		}
		else if(lg->type == LOGIC_GENE_TYPE_STREAM)
		{
			stream.push_back(lg->value);
		}

		s++;
	}

	QDateTime currentDateTime = QDateTime::currentDateTime();
	std::string logicsName = mController;
	logicsName += "-genetic-";
	logicsName += currentDateTime.toString("dd-MM-yyyy-hh-mm-ss-z").toStdString();

	ControllerLogic *newLogic = ControllerLogic::createLogicForSumo(logicsName, 
		(durations.at(0)/1000), (durations.at(1)/1000), (durations.at(2)/1000), (durations.at(3)/1000), mController);

	Supervisor::getInstance()->sendSumoCNewProgramForController(mController, newLogic);
	int *p = (int *)best.userData();
	std::string str = "------------";
	str += "\nId:";
	str += QString::number(*p).toStdString();
	str += "\nNew Logic for controller: ";
	str += mController;
	str += "\nLogic:\n";
	str += newLogic->toString();
	str += "------------\n";
	SupervisorLog::getInstance()->writeOnNewProgram(str);
	Supervisor::getInstance()->emitLogPrograms(str.c_str());

	StoredControllerLogic *storedLogic = new StoredControllerLogic();

	storedLogic->setControllerLogic(newLogic);
	storedLogic->setUsedDate(currentDateTime);
	storedLogic->setGoodDegree(-1);

	if(queue.size() == stream.size())
	{
		for(int i = 0; i < queue.size(); i++)
		{
			Street street;
			street.carStream = stream.at(i);
			street.queueSize = queue.at(i);
			streets.push_back(street);
		}
	}

	storedLogic->setStreets(streets);

	ControllerLogic::addNewControllerLogicToTheBase(mController, storedLogic);
	delete p;
}

//fazer retornar uma logica. talvez trocar isso para uma thread.
void tryToFindABetterProgram(std::string mController, std::vector<std::string> similarControllers)
{
	GAPopulation initialPop;
	int ngen     = 400;
	float pmut   = 0.001;
	float pcross = 0.9;
	QString qController = mController.c_str();

	alreadyRunningMutex.lock();
	if(alreadyRunning.contains(qController))
	{
		alreadyRunningMutex.unlock();
		return;
	}
	alreadyRunning.push_back(qController);
	alreadyRunningMutex.unlock();


	_initPopulation(ControllerLogic::getStoredLogicFromLogicBase(mController, CASE_BASED_THRESHOULD), initialPop);

	for(int i = 0; i < similarControllers.size(); i++)
		_initPopulation(ControllerLogic::getStoredLogicFromLogicBase(similarControllers.at(i), CASE_BASED_THRESHOULD), initialPop);
	
	if (initialPop.size() <= 0)
		goto end;
	{
		GASimpleGA ga(initialPop);
		ga.nGenerations(ngen);
		ga.pMutation(pmut);
		ga.pCrossover(pcross);
		ga.evolve();
		_sendNewProgramToSumo(mController, (GAListGenome<LogicGene> &)ga.statistics().bestIndividual());
	}

end:
	alreadyRunningMutex.lock();
	alreadyRunning.removeOne(qController);
	alreadyRunningMutex.unlock();

}

float Objective(GAGenome &genome)
{
	float result = 0.0;
	int listSize, pos;
	GAListGenome<LogicGene> &listGenome = (GAListGenome<LogicGene> &)genome;
	LogicGene *gene;
	GAListIter<LogicGene> iter(listGenome);
	std::vector<int> queueVec, streamVec, phasesVec;
	if((listSize = listGenome.size()) != LOGIC_GENE_SIZE)
		return result;

	pos = 0;

	while(listSize != pos)
	{
		gene = iter.next();

		if(gene->type == LOGIC_GENE_TYPE_STREAM)
		{
			streamVec.push_back(gene->value);
		}
		else if (gene->type == LOGIC_GENE_TYPE_QUEUE)
		{
			queueVec.push_back(gene->value);
		}
		else if(gene->type == LOGIC_GENE_TYPE_PHASE)
		{
			phasesVec.push_back(gene->value);
		}

		pos++;
	}

	if(streamVec.size() != 2 || queueVec.size() != 2 || phasesVec.size() != 4)
		return result;

	int queueMax;

	if(queueVec.at(0) > queueVec.at(1))
		queueMax = queueVec.at(0);
	else
		queueMax = queueVec.at(1);

	//pequeno 
	if(queueMax >= 0 && queueMax <= 10) 
	{
		result = _evaluateLogic(phasesVec, 120000); //milisecs
	}
	else if(queueMax > 10 && queueMax <= 18) //med
	{
		result = _evaluateLogic(phasesVec, 60000);
	}
	else //grande
	{
		result = _evaluateLogic(phasesVec, 30000);
	}
	int *p = new int;
	*p = (int)&genome;
	genome.userData(p);
	std::string str;
	str = "---------\n";
	str += "Candidate";
	str += "\nId:";
	str += QString::number(*p).toStdString();
	str += "\nQueue: ";
	str += QString::number((queueVec.at(0) + queueVec.at(1))).toStdString();
	str += "\nPhases:\n";
	for(int i = 0; i < phasesVec.size(); i++) {
		str += "Phase: ";
		str += QString::number((phasesVec.at(i)/1000)).toStdString();
		str += "\n";
	}
	str += "\nFitnes: ";
	str += QString::number(result).toStdString();
	str += "\n---------\n";
	SupervisorLog::getInstance()->writeOnFitness(str);
//	Supervisor::getInstance()->emitLogFitness(str.c_str());

	return result;
}