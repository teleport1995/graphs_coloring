#ifndef FULLSEARCH_H
#define FULLSEARCH_H
#include "solution.h"
#include "graph.h"

solution * getSimpleFullSearchSolution(graph *g, int threads_num = 1);
solution * getHardFullSearchSolution(graph *g, int threads_num = 1);

#endif
