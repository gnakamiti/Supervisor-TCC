#ifndef _GENETIC_H_
#define _GENETIC_H_

#include <ga/GAGenome.h>
#include <ga/GASimpleGA.h>
#include "Controller.h"


class Genetic
{
private:

public:
	Genetic();
	~Genetic();
};

float Objective(GAGenome &);

#endif