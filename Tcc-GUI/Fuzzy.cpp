#include "Fuzzy.h"


Fuzzy::Fuzzy()
{
	this->fuzzyEngine = new fl::FuzzyEngine();

	this->currentQueue = new fl::InputLVar(FUZZY_INPUTL_VAR_CURRENT_QUEUE);
	this->carStream = new fl::InputLVar(FUZZY_INPUTL_VAR_CAR_STREAM);
	this->adequationDegree = new fl::OutputLVar(FUZZY_INPUTL_VAR_QUEUE_AD_DEGREE);

	//Deleted by fuzzy engine
	fl::RuleBlock *ruleBlock = new fl::RuleBlock();

	this->initLVars(currentQueue, carStream, adequationDegree);

	this->fuzzyEngine->addInputLVar(this->currentQueue);
	this->fuzzyEngine->addInputLVar(this->carStream);
	this->fuzzyEngine->addOutputLVar(this->adequationDegree);

	this->setRuleBlock(ruleBlock);

	this->fuzzyEngine->addRuleBlock(ruleBlock);

	
	
}
//TODO - TA DANDO UM PARSE EXCEPTION!
void Fuzzy::setRuleBlock(fl::RuleBlock *ruleBlock)
{
	QString qStringRuleBase, qStringRuleToBeAdded;

	//Fuzzy Ling values - Normal, Big, Enoumous and etc...
	char fuzzyInputNames[FUZZY_INPUT_SIZE][FUZZY_STR_SIZE] = {FUZZY_INPUT_NOTHING, 
		FUZZY_INPUT_SMALL, FUZZY_INPUT_REGULAR, FUZZY_INPUT_BIG, FUZZY_INPUT_ENORMOUS};

	char fuzzyOutPutNames[FUZZY_INPUT_SIZE][FUZZY_INPUT_SIZE][FUZZY_STR_SIZE] =
	{ {FUZZY_INPUT_ENORMOUS, FUZZY_INPUT_ENORMOUS, FUZZY_INPUT_REGULAR, FUZZY_INPUT_NOTHING, FUZZY_INPUT_NOTHING},
	  {FUZZY_INPUT_BIG, FUZZY_INPUT_BIG, FUZZY_INPUT_REGULAR, FUZZY_INPUT_SMALL, FUZZY_INPUT_NOTHING},
	  {FUZZY_INPUT_BIG, FUZZY_INPUT_BIG, FUZZY_INPUT_REGULAR, FUZZY_INPUT_SMALL, FUZZY_INPUT_SMALL},
	  {FUZZY_INPUT_BIG, FUZZY_INPUT_BIG, FUZZY_INPUT_REGULAR, FUZZY_INPUT_NOTHING, FUZZY_INPUT_NOTHING},
	  {FUZZY_INPUT_BIG, FUZZY_INPUT_BIG, FUZZY_INPUT_REGULAR, FUZZY_INPUT_NOTHING, FUZZY_INPUT_NOTHING},
	};

	//Creating a generic rule string.
	//C++ won't let me string + string + string :(((((((
	qStringRuleBase = "if ";
	qStringRuleBase += FUZZY_INPUTL_VAR_CURRENT_QUEUE;
	qStringRuleBase += " is %1 and ";
	qStringRuleBase += FUZZY_INPUTL_VAR_CAR_STREAM;
	qStringRuleBase += " is %2 then ";
	qStringRuleBase += FUZZY_INPUTL_VAR_QUEUE_AD_DEGREE;
	qStringRuleBase += " is %3";

	for(int i = 0; i < FUZZY_INPUT_SIZE; i++)
	{
		for(int j = 0; j < FUZZY_INPUT_SIZE; j++)
		{
				//replacing the %1, %2 and %3
				qStringRuleToBeAdded = qStringRuleBase.arg(fuzzyInputNames[i]).
					arg(fuzzyInputNames[j]).arg(fuzzyOutPutNames[i][j]);
				
				ruleBlock->addRule(new fl::MamdaniRule(qStringRuleToBeAdded
					.toStdString(), *(this->fuzzyEngine)));
		}
	}

	
	
}

fl::flScalar Fuzzy::infer(int queueSize, int carStream)
{
	fl::flScalar value, inputQueue, inputStream;

	inputQueue = (fl::flScalar)queueSize;
	inputStream = (fl::flScalar)carStream;

	this->currentQueue->setInput(inputQueue);
	this->carStream->setInput(inputStream);
	this->fuzzyEngine->process();

	value = this->adequationDegree->output().defuzzify();

	return value;
}

void Fuzzy::initLVars(fl::InputLVar *currentQueue, fl::InputLVar *carStream, 
	fl::OutputLVar *adequationDegree)
{
	//Queue Terms
	currentQueue->addTerm(new fl::ShoulderTerm(FUZZY_INPUT_NOTHING, 3, 6, true));
	currentQueue->addTerm(new fl::TriangularTerm(FUZZY_INPUT_SMALL, 3, 9));
	currentQueue->addTerm(new fl::TriangularTerm(FUZZY_INPUT_REGULAR, 6, 12));
	currentQueue->addTerm(new fl::TriangularTerm(FUZZY_INPUT_BIG, 9, 15));
	currentQueue->addTerm(new fl::ShoulderTerm(FUZZY_INPUT_ENORMOUS, 12, 15, false));

	//End Queue Terms


	//car stream terms

	
	carStream->addTerm(new fl::ShoulderTerm(FUZZY_INPUT_NOTHING, 100, 250, true));
	carStream->addTerm(new fl::TriangularTerm(FUZZY_INPUT_SMALL, 100, 400));
	carStream->addTerm(new fl::TriangularTerm(FUZZY_INPUT_REGULAR, 250, 550));
	carStream->addTerm(new fl::TriangularTerm(FUZZY_INPUT_BIG, 400, 700));
	carStream->addTerm(new fl::ShoulderTerm(FUZZY_INPUT_ENORMOUS, 550, 700, false));

	//end car stream terms

	//Output var

	adequationDegree->addTerm(new fl::ShoulderTerm(FUZZY_INPUT_NOTHING, 10, 20, true));
	adequationDegree->addTerm(new fl::TriangularTerm(FUZZY_INPUT_SMALL, 10, 40));
	adequationDegree->addTerm(new fl::TriangularTerm(FUZZY_INPUT_REGULAR, 20, 60));
	adequationDegree->addTerm(new fl::TriangularTerm(FUZZY_INPUT_BIG, 40, 100));
	adequationDegree->addTerm(new fl::ShoulderTerm(FUZZY_INPUT_ENORMOUS, 60, 100, false));
	//end output var
}




Fuzzy::~Fuzzy()
{
	//The input/output vars are deleted when you delete the engine!
	delete this->fuzzyEngine;
	this->fuzzyEngine = nullptr;

	
}