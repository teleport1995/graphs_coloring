#ifndef GRAPH_H
#define GRAPH_H

struct graph
{
	int n;
	int **a;
};

graph * getRandomGraph(int n, int m = -1);
graph * getEmptyGraph(int n);
void clearGraph(graph *g);
void deleteGraph(graph *g);

#endif
