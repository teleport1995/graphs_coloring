#ifndef SOLUTION_H
#define SOLUTION_H
#include "graph.h"

struct solution
{
	int n;
	int colorsCount;
	int *colors;
	double time;
};

solution * createNewSolution(int n);
bool isEqualSolutions(solution *first, solution *second);
void deleteSolution(solution *s);
bool checkSolution(graph *g, solution *s);

#endif
