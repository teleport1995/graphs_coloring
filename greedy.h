#ifndef GREEDY_H
#define GREEDY_H
#include "solution.h"
#include "graph.h"

struct saturationNode
{
	int saturation;
	int degree;
	int num;
	
	bool operator<(const saturationNode &other)
	{
		return (saturation > other.saturation) || 
			(saturation == other.saturation && degree > other.degree) ||
			(saturation == other.saturation && degree > other.degree && num < other.num);
	}
};



solution * getSequentialGreedySolution(graph *g, int threads_num = 1);
solution * getSortedGreedySolution(graph *g, int threads_num = 1);
solution * getSortedSequentialGreedySolution(graph *g, int threads_num = 1);
solution * getSortedSaturationGreedySolution(graph *g, int threads_num = 1);

#endif
