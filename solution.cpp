#include "solution.h"
#include "graph.h"
#include <omp.h>

solution * createNewSolution(int n)
{
	solution *s = new solution;
	s->colors = new int[n];
	s->n = n;
	for (int i = 0; i < n; i++)
	{
		s->colors[i] = -1;
	}
	s->colorsCount = s->time = 0;
	return s;
}

bool isEqualSolutions(solution *first, solution *second)
{
	if (first->n != second->n)
	{
		return false;
	}
	for (int i = 0; i < first->n; i++)
	{
		if (first->colors[i] != second->colors[i])
		{
			return false;
		}
	}
	return true;
}

void deleteSolution(solution *s)
{
	delete s->colors;
	delete s;
}


bool checkSolution(graph *g, solution *s)
{
	if (s->n != g->n)
		return false;
	bool flag = true;
	#pragma omp parallel for
	for (int i = 0; i < g->n; i++)
	{
		for (int j = i + 1; j < g->n; j++)
		{
			if (g->a[i][j] && s->colors[i] == s->colors[j])
			{
				flag = false;
			}
		}
	}
	return flag;
}
