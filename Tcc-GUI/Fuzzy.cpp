#include "Fuzzy.h"

Fuzzy::Fuzzy()
{
}

Fuzzy::Fuzzy(int fuzzyCase)
{
	this->fuzzyEngine = new fl::FuzzyEngine();

	this->currentQueue = new fl::InputLVar(FUZZY_INPUTL_VAR_CURRENT_QUEUE);

	if(fuzzyCase == FUZZY_USE_CAR_STREAM)
		this->carStream = new fl::InputLVar(FUZZY_INPUTL_VAR_CAR_STREAM);

	this->adequationDegree = new fl::OutputLVar(FUZZY_INPUTL_VAR_QUEUE_AD_DEGREE);

	//Deleted by fuzzy engine
	fl::RuleBlock *ruleBlock = new fl::RuleBlock();

	this->initLVars(currentQueue, carStream, adequationDegree, fuzzyCase);

	this->fuzzyEngine->addInputLVar(this->currentQueue);

	if(fuzzyCase == FUZZY_USE_CAR_STREAM)
		this->fuzzyEngine->addInputLVar(this->carStream);

	this->fuzzyEngine->addOutputLVar(this->adequationDegree);

	if(fuzzyCase == FUZZY_USE_CAR_STREAM)
		this->setRuleBlockWithStream(ruleBlock);
	else
		this->setRuleBlockNoStream(ruleBlock);

	this->fuzzyEngine->addRuleBlock(ruleBlock);

	fuzzyOutValuesToShow[FUZZY_INPUT_NOTHING] = FUZZY_OUTPUT_VALUE_SHOW_SCREEN_ENOURMOUS;
	fuzzyOutValuesToShow[FUZZY_INPUT_SMALL] = FUZZY_OUTPUT_VALUE_SHOW_SCREEN_BIG;
	fuzzyOutValuesToShow[FUZZY_INPUT_REGULAR] = FUZZY_OUTPUT_VALUE_SHOW_SCREEN_REGULAR;
	fuzzyOutValuesToShow[FUZZY_INPUT_BIG] = FUZZY_OUTPUT_VALUE_SHOW_SCREEN_SMALL;
	fuzzyOutValuesToShow[FUZZY_INPUT_ENORMOUS] = FUZZY_OUTPUT_VALUE_SHOW_SCREEN_NOTHING;
	
}

void  Fuzzy::setRuleBlockNoStream(fl::RuleBlock *ruleBlock)
{
	QString qStringRuleBase, qStringRuleToBeAdded;

	char fuzzyInputNames[FUZZY_INPUT_SIZE][FUZZY_STR_SIZE] = {FUZZY_INPUT_NOTHING, 
		FUZZY_INPUT_SMALL, FUZZY_INPUT_REGULAR, FUZZY_INPUT_BIG, FUZZY_INPUT_ENORMOUS};

	char fuzzyOutputNames[FUZZY_INPUT_SIZE][FUZZY_STR_SIZE] = {FUZZY_INPUT_ENORMOUS, 
		FUZZY_INPUT_BIG, FUZZY_INPUT_REGULAR, FUZZY_INPUT_SMALL, FUZZY_INPUT_NOTHING};

	//Creating a generic rule string.
	//C++ won't let me string + string + string :(((((((
	qStringRuleBase = "if ";
	qStringRuleBase += FUZZY_INPUTL_VAR_CURRENT_QUEUE;
	qStringRuleBase += " is %1 then ";
	qStringRuleBase += FUZZY_INPUTL_VAR_QUEUE_AD_DEGREE;
	qStringRuleBase += " is %2";

	for(int i = 0; i < FUZZY_INPUT_SIZE; i++)
	{
		qStringRuleToBeAdded = qStringRuleBase.arg(fuzzyInputNames[i]).
				arg(fuzzyOutputNames[i]);

		ruleBlock->addRule(new fl::MamdaniRule(qStringRuleToBeAdded
					.toStdString(), *(this->fuzzyEngine)));
	}
}

void Fuzzy::setRuleBlockWithStream(fl::RuleBlock *ruleBlock)
{
	QString qStringRuleBase, qStringRuleToBeAdded;

	//Fuzzy Ling values - Normal, Big, Enoumous and etc...
	char fuzzyInputNames[FUZZY_INPUT_SIZE][FUZZY_STR_SIZE] = {FUZZY_INPUT_NOTHING, 
		FUZZY_INPUT_SMALL, FUZZY_INPUT_REGULAR, FUZZY_INPUT_BIG, FUZZY_INPUT_ENORMOUS};

	char fuzzyOutPutNames[FUZZY_INPUT_SIZE][FUZZY_INPUT_SIZE][FUZZY_STR_SIZE] =
	{ {FUZZY_INPUT_ENORMOUS, FUZZY_INPUT_ENORMOUS, FUZZY_INPUT_REGULAR, FUZZY_INPUT_NOTHING, FUZZY_INPUT_NOTHING},
	  {FUZZY_INPUT_BIG, FUZZY_INPUT_BIG, FUZZY_INPUT_REGULAR, FUZZY_INPUT_SMALL, FUZZY_INPUT_NOTHING},
	  {FUZZY_INPUT_BIG, FUZZY_INPUT_BIG, FUZZY_INPUT_REGULAR, FUZZY_INPUT_SMALL, FUZZY_INPUT_SMALL},
	  {FUZZY_INPUT_SMALL, FUZZY_INPUT_SMALL, FUZZY_INPUT_REGULAR, FUZZY_INPUT_BIG, FUZZY_INPUT_BIG},
	  {FUZZY_INPUT_NOTHING, FUZZY_INPUT_SMALL, FUZZY_INPUT_SMALL, FUZZY_INPUT_BIG, FUZZY_INPUT_BIG},
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

FuzzyResult Fuzzy::infer(int queueSize, int carStream)
{
	fl::flScalar inputQueue, inputStream;
	FuzzyResult result;

	inputQueue = (fl::flScalar)queueSize;
	inputStream = (fl::flScalar)carStream;

	this->currentQueue->setInput(inputQueue);
	this->carStream->setInput(inputStream);
	this->fuzzyEngine->process();

	result.value = this->adequationDegree->output().defuzzify();
	//Not used for this one
	result.LinguisticValue = "";
	
	return result;
}
FuzzyResult Fuzzy::infer(int queueSize)
{
	fl::flScalar inputQueue;
	FuzzyResult result;

	inputQueue = (fl::flScalar)queueSize;

	this->currentQueue->setInput(inputQueue);
	this->fuzzyEngine->process();

	result.value = this->adequationDegree->output().defuzzify();
	result.LinguisticValue = this->
		parseOutPutString(this->adequationDegree->fuzzify(result.value));

	return result;
}
//Modify the string to a more human readeble way
std::string Fuzzy::parseOutPutString(std::string output)
{
	//QString has better functions, YAY QT! :)
	QString qOutput = output.c_str();
	QString qActualString, qActualString2;
	std::string result;
	QStringList strList = qOutput.split("+");
	fl::flScalar value = -50.0;

	for(int i = 0; i < strList.size(); i++)
	{
		qActualString = strList.at(i);
		QStringList strList2 = qActualString.split("/");

		for(int j = 0; j < strList2.size(); j++)
		{
			qActualString2 = strList2.at(j);

			if(value < qActualString2.toDouble())
			{
				value = qActualString2.toDouble();
				result = strList2.at((j+1)).trimmed().toStdString();
			}
		}

		strList2.clear();
	}
	
	return fuzzyOutValuesToShow[result];
}

void Fuzzy::initLVars(fl::InputLVar *currentQueue, fl::InputLVar *carStream, 
	fl::OutputLVar *adequationDegree, int fuzzyCase)
{
	//Queue Terms
	currentQueue->addTerm(new fl::ShoulderTerm(FUZZY_INPUT_NOTHING, 3, 6, true));
	currentQueue->addTerm(new fl::TriangularTerm(FUZZY_INPUT_SMALL, 3, 9));
	currentQueue->addTerm(new fl::TriangularTerm(FUZZY_INPUT_REGULAR, 6, 12));
	currentQueue->addTerm(new fl::TriangularTerm(FUZZY_INPUT_BIG, 9, 15));
	currentQueue->addTerm(new fl::ShoulderTerm(FUZZY_INPUT_ENORMOUS, 12, 15, false));

	//End Queue Terms


	//car stream terms

	if(fuzzyCase == FUZZY_USE_CAR_STREAM)
	{
		carStream->addTerm(new fl::ShoulderTerm(FUZZY_INPUT_NOTHING, 100, 250, true));
		carStream->addTerm(new fl::TriangularTerm(FUZZY_INPUT_SMALL, 100, 400));
		carStream->addTerm(new fl::TriangularTerm(FUZZY_INPUT_REGULAR, 250, 550));
		carStream->addTerm(new fl::TriangularTerm(FUZZY_INPUT_BIG, 400, 700));
		carStream->addTerm(new fl::ShoulderTerm(FUZZY_INPUT_ENORMOUS, 550, 700, false));
	}

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