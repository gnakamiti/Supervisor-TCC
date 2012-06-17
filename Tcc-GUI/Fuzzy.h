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

	//Inicia variveis
	void initLVars(fl::InputLVar *, fl::InputLVar *, fl::OutputLVar *, int);
	
	////Seta Bloco de regras para fuzzy com fluxo
	void setRuleBlockWithStream(fl::RuleBlock *);
	//Seta Bloco de regras para fuzzy sem fluxo
	void setRuleBlockNoStream(fl::RuleBlock *);
	//Retorna situacao da rua como string
	std::string parseOutPutString(std::string);

public:
	Fuzzy();
	Fuzzy(int);

	~Fuzzy();
	//Infere resultado para fuzzy com fluxo
	FuzzyResult infer(int, int);
	//Infere - fuzzy sem fluxo
	FuzzyResult infer(int);
};

#endif