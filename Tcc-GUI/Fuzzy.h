#ifndef _FUZZY_H_
#define _FUZZY_H_

#include "FuzzyLite.h"
#include "FunctionTerm.h"
#include "constants.h"
#include <QString>
#include <QStringList>
#include <map>
#include "Controller.h"


typedef struct FuzzyOutValue
{
	fl::flScalar value;
	std::string LinguisticValue;
}FuzzyResult;

class Fuzzy
{
	

private:
	fl::FuzzyEngine *fuzzyEngine;
	//They are deleted by fuzzyEngine
	fl::InputLVar *currentQueue; 
	fl::InputLVar *carStream; 
	fl::OutputLVar *adequationDegree;
	std::map<std::string, std::string> fuzzyOutValuesToShow;

	void initLVars(fl::InputLVar *, fl::InputLVar *, fl::OutputLVar *, int);
	
	void setRuleBlockWithStream(fl::RuleBlock *);
	void setRuleBlockNoStream(fl::RuleBlock *);

	std::string parseOutPutString(std::string);

public:
	Fuzzy();
	Fuzzy(int);

	~Fuzzy();

	FuzzyResult infer(int, int);
	FuzzyResult infer(int);
};

#endif