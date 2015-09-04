#include "graph.h"
#include <cstdlib>
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

graph * getRandomGraph(int n, int m)
{
	graph *g = new graph;
	g->n = n;
	g->a = new int*[n];
	for (int i = 0; i < n; i++)
	{
		g->a[i] = new int[n];
		for (int j = 0; j < n; j++)
		{
			g->a[i][j] = 0;
		}
	}
		
	if (m == -1)
	{
		m = rand() % ((n * (n - 1)) / 2 + 1);
	}
	
	vector < pair < int , int > > v;
	for (int i = 0; i < n; i++)
	{
		for (int j = i + 1; j < n; j++)
		{
			v.push_back(make_pair(i, j));
		}
	}
	while (v.size() > 0 && m--)
	{
		int pos = rand() % v.size();
		g->a[v[pos].first][v[pos].second] = g->a[v[pos].second][v[pos].first] = 1;
		swap(v[pos], v[v.size() - 1]);
		v.pop_back();
	}
	return g;
}

graph * getEmptyGraph(int n)
{
	graph *g = new graph;
	g->n = n;
	g->a = new int*[n];
	for (int i = 0; i < n; i++)
	{
		g->a[i] = new int[n];
		for (int j = 0; j < n; j++)
		{
			g->a[i][j] = 0;
		}
	}
	return g;
}

void clearGraph(graph *g)
{
	for (int i = 0; i < g->n; i++)
		for (int j = 0; j < g->n; j++)
			g->a[i][j] = 0;
}

void deleteGraph(graph *g)
{
	for (int i = 0; i < g->n; i++)
		delete g->a[i];
	delete g->a;
	delete g;
}
