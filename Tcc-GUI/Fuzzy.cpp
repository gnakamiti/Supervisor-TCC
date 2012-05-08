#include "Fuzzy.h"

Fuzzy::Fuzzy()
{
	this->fuzzyEngine = new fl::FuzzyEngine();

	fl::InputLVar *currentQueue = new fl::InputLVar(FUZZY_INPUTL_VAR_CURRENT_QUEUE);
	fl::InputLVar *waitTime = new fl::InputLVar(FUZZY_INPUTL_VAR_WAIT_TIME);
	fl::OutputLVar *queueGrowedFast = new fl::OutputLVar(FUZZY_INPUTL_VAR_QUEUE_GROWED_FAST);

	fl::RuleBlock *ruleBlock = new fl::RuleBlock();

	this->initInputLVar(currentQueue, waitTime);

	this->initOutputLVar(queueGrowedFast);

	this->fuzzyEngine->addInputLVar(currentQueue);
	this->fuzzyEngine->addInputLVar(waitTime);
	this->fuzzyEngine->addOutputLVar(queueGrowedFast);

	this->setRuleBlock(ruleBlock);

	this->fuzzyEngine->addRuleBlock(ruleBlock);

	
}

void Fuzzy::setRuleBlock(fl::RuleBlock *ruleBlock)
{
}

void Fuzzy::initInputLVar(fl::InputLVar *currentQueue, fl::InputLVar *waitTime)
{
	//Queue Terms
	currentQueue->addTerm(new fl::ShoulderTerm("NOTHING", 3, 6, true));
	currentQueue->addTerm(new fl::TriangularTerm("SMALL", 3, 9));
	currentQueue->addTerm(new fl::TriangularTerm("REGULAR", 6, 12));
	currentQueue->addTerm(new fl::TriangularTerm("BIG", 9, 15));
	currentQueue->addTerm(new fl::ShoulderTerm("ENORMOUS", 12, 15, false));

	//End Queue Terms


	//waitTime terms

	//waitTime->addTerm();

	//end waitTime terms
}




void Fuzzy::initOutputLVar(fl::OutputLVar *queueGrowedFast)
{
	//queueGrowedFast->addTerm();
}

Fuzzy::~Fuzzy()
{
	//The input/output vars are deleted when you delete the engine!
	delete this->fuzzyEngine;

	this->fuzzyEngine = nullptr;
}