#ifndef _FUZZY_H_
#define _FUZZY_H_

#include "FuzzyLite.h"
#include "FunctionTerm.h"
#include "constants.h"

class Fuzzy
{
private:
	fl::FuzzyEngine *fuzzyEngine;

	void initInputLVar(fl::InputLVar *, fl::InputLVar *);
	void initOutputLVar(fl::OutputLVar *);
	void setRuleBlock(fl::RuleBlock *);

public:
	Fuzzy();
	~Fuzzy();
};

#endif