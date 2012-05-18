#ifndef _FUZZY_H_
#define _FUZZY_H_

#include "FuzzyLite.h"
#include "FunctionTerm.h"
#include "constants.h"
#include <QString>
#include "Controller.h"



class Fuzzy
{
	

private:
	fl::FuzzyEngine *fuzzyEngine;
	//They are deleted by fuzzyEngine
	fl::InputLVar *currentQueue; 
	fl::InputLVar *carStream; 
	fl::OutputLVar *adequationDegree;

	void initLVars(fl::InputLVar *, fl::InputLVar *, fl::OutputLVar *, int);
	
	void setRuleBlockWithStream(fl::RuleBlock *);
	void setRuleBlockNoStream(fl::RuleBlock *);


public:
	Fuzzy();
	Fuzzy(int);

	~Fuzzy();

	fl::flScalar infer(int, int);
	fl::flScalar infer(int);
};

#endif