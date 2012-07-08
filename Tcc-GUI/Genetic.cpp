#include "Genetic.h"
/*
Genetic::Genetic()
{
}

Genetic::Genetic(std::string m, std::vector<std::string> s)
{
	mController = m;
	similarControllers = s;
}

Genetic::~Genetic()
{
}

void Genetic::run()
{
	tryToFindABetterProgram();
}*/

void initPopulation(std::vector<StoredControllerLogic *> &vec, GAPopulation &initialPop)
{
	for(int i = 0; i < vec.size(); i++)
		initialPop.add(vec.at(i)->toGene());
}

//fazer retornar uma logica. talvez trocar isso para uma thread.
void tryToFindABetterProgram(std::string mController, std::vector<std::string> similarControllers)
{
	GAPopulation initialPop;
	int ngen     = 400;
	float pmut   = 0.001;
	float pcross = 0.9;


	initPopulation(ControllerLogic::getStoredLogicFromLogicBase(mController), initialPop);

	for(int i = 0; i < similarControllers.size(); i++)
		initPopulation(ControllerLogic::getStoredLogicFromLogicBase(similarControllers.at(i)), initialPop);
	

	GASimpleGA ga(initialPop);
	ga.nGenerations(ngen);
	ga.pMutation(pmut);
	ga.pCrossover(pcross);
	ga.evolve();

	GAListGenome<LogicGene> &best = (GAListGenome<LogicGene> &) ga.statistics().bestIndividual();
	//tirar isso.
	GAListIter<LogicGene> iter(best);
	int t,v,s;
	s = 0;

	while(s != best.size())
	{
		LogicGene *lg = iter.next();
		t = lg->type;
		v = lg->value;
		s++;
	}
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
		result = evaluateLogic(phasesVec, 120000); //milisecs
	}
	else if(queueMax > 10 && queueMax <= 18) //med
	{
		result = evaluateLogic(phasesVec, 60000);
	}
	else //grande
	{
		result = evaluateLogic(phasesVec, 30000);
	}

	return result;
}

float evaluateLogic(std::vector<int> &phases, int acceptableTime)
{
	float result = 0.0;
	float step;
	int duration;

	step = 1.0 / phases.size();

	for(int i = 0; i < phases.size(); i++)
	{
		duration = phases.at(i);

		if(duration <= acceptableTime)
			result += step;
		else if(duration > acceptableTime && duration <= acceptableTime * 1.5)
			result += (step/2.0);
		else
			result += (step/4.0);
		
	}
	return result;
}