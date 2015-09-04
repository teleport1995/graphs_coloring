#include "greedy.h"
#include "solution.h"
#include "graph.h"
#include <omp.h>
#include <algorithm>
#include <vector>
#include <iostream>

using namespace std;

solution * getSequentialGreedySolution(graph *g, int threads_num)
{
	omp_set_num_threads(threads_num);
	solution *s = createNewSolution(g->n);
	int *adjacentColors = new int[g->n];
	for (int i = 0; i < g->n; i++)
	{
		adjacentColors[i] = 0;
	}
	int *thread_min_color = new int[threads_num];
	double startTime = omp_get_wtime();
	for (int i = 0; i < g->n; i++)
	{
		#pragma omp parallel for
		for (int j = 0; j < i; j++)
		{
			adjacentColors[j] = 0;
		}
		
		#pragma omp parallel for
		for (int j = 0; j < i; j++)
		{
			if (g->a[i][j])
			{
				adjacentColors[s->colors[j]] = 1;
			}
		}
		
		for (int j = 0; j < threads_num; j++)
		{
			thread_min_color[j] = g->n;
		}
		
		#pragma omp parallel for
		for (int j = 0; j <= i; j++)
		{
			if (!adjacentColors[j])
			{
				int num = omp_get_thread_num();
				if (thread_min_color[num] > j)
				{
					thread_min_color[num] = j;
				}
			}
		}
		
		int color = g->n;
		for (int j = 0; j < threads_num; j++)
		{
			if (color > thread_min_color[j])
			{
				color = thread_min_color[j];
			}
		}
		
		s->colors[i] = color;
		
		if (s->colorsCount < color + 1)
		{
			s->colorsCount = color + 1;
		}
	}
	
	s->time = omp_get_wtime() - startTime;
	delete thread_min_color;
	delete adjacentColors;
	
	return s;
}

solution *getSortedGreedySolution(graph *g, int threads_num)
{
	omp_set_num_threads(threads_num);	
	int *deg = new int[g->n];
	for (int i = 0; i < g->n; i++)
	{
		deg[i] = 0;
	}
	#pragma omp parallel for
	for (int i = 0; i < g->n; i++)
	{
		for (int j = 0; j < g->n; j++)
		{
			deg[i] += g->a[i][j];
		}
	}
	vector < pair < int , int > > v;
	for (int i = 0; i < g->n ;i++)
	{
		v.push_back(make_pair(deg[i], i));
	}
	sort(v.begin(), v.end());
	reverse(v.begin(), v.end());
	
	solution *s = createNewSolution(g->n);
	double startTime = omp_get_wtime();
	int *component = new int[g->n];
	int cnt = 0;
	int color = 0;
	while (cnt < g->n)
	{
		int size = 0;
		for (int i = 0; i < (int)v.size(); i++)
		{
			int num = v[i].second;
			if (s->colors[num] == -1)
			{
				bool flag = true;
				if (size)
				{
					#pragma omp parallel for
					for (int j = 0; j < size; j++)
					{
						if (g->a[num][component[j]])
						{
							flag = false;
						}
					}
				}
				if (flag)
				{
					cnt++;
					s->colors[num] = color;
					component[size++] = num;
				}
			}
		}
		color++;
	}
	
	s->time = omp_get_wtime() - startTime;
	s->colorsCount = color;
	delete deg;
	
	return s;
}


solution *getSortedSequentialGreedySolution(graph *g, int threads_num)
{
	omp_set_num_threads(threads_num);	
	int *deg = new int[g->n];
	for (int i = 0; i < g->n; i++)
	{
		deg[i] = 0;
	}
	#pragma omp parallel for
	for (int i = 0; i < g->n; i++)
	{
		for (int j = 0; j < g->n; j++)
		{
			deg[i] += g->a[i][j];
		}
	}
	vector < pair < int , int > > v;
	for (int i = 0; i < g->n ;i++)
	{
		v.push_back(make_pair(deg[i], i));
	}
	sort(v.begin(), v.end());
	reverse(v.begin(), v.end());
	
	solution *s = createNewSolution(g->n);
		
	int *adjacentColors = new int[g->n];
	for (int i = 0; i < g->n; i++)
	{
		adjacentColors[i] = 0;
	}
	int *thread_min_color = new int[threads_num];
	double startTime = omp_get_wtime();
	
	for (int i = 0; i < (int)v.size(); i++)
	{
		int pos = v[i].second;
		#pragma omp parallel for
		for (int j = 0; j < i; j++)
		{
			adjacentColors[j] = 0;
		}
		
		#pragma omp parallel for
		for (int j = 0; j < i; j++)
		{
			if (g->a[pos][v[j].second])
			{
				adjacentColors[s->colors[v[j].second]] = 1;
			}
		}
		
		for (int j = 0; j < threads_num; j++)
		{
			thread_min_color[j] = g->n;
		}
		
		#pragma omp parallel for
		for (int j = 0; j <= i; j++)
		{
			if (!adjacentColors[j])
			{
				int num = omp_get_thread_num();
				if (thread_min_color[num] > j)
				{
					thread_min_color[num] = j;
				}
			}
		}
		
		int color = g->n;
		for (int j = 0; j < threads_num; j++)
		{
			if (color > thread_min_color[j])
			{
				color = thread_min_color[j];
			}
		}
		
		s->colors[pos] = color;
		if (s->colorsCount < color + 1)
		{
			s->colorsCount = color + 1;
		}
	}
	
	s->time = omp_get_wtime() - startTime;
	delete thread_min_color;
	delete adjacentColors;	
	delete deg;
	
	return s;
}



solution *getSortedSaturationGreedySolution(graph *g, int threads_num)
{
	omp_set_num_threads(threads_num);	
	
	saturationNode *saturations = new saturationNode[g->n];
	for (int i = 0; i < g->n; i++)
	{
		saturations[i].saturation = 0;
		saturations[i].degree = 0;
		saturations[i].num = i;
	}
	
	#pragma omp parallel for
	for (int i = 0; i < g->n; i++)
	{
		for (int j = 0; j < g->n; j++)
		{
			saturations[i].degree += g->a[i][j];
		}
	}
	
	solution *s = createNewSolution(g->n);
		
	int *adjacentColors = new int[g->n];
	for (int i = 0; i < g->n; i++)
	{
		adjacentColors[i] = 0;
	}
	int *thread_min_color = new int[threads_num];
	int *thread_min_saturation = new int[threads_num];
	int *used_nums = new int[g->n];
	for (int i = 0; i < g->n; i++)
	{
		used_nums[i] = 0;
	}
	double startTime = omp_get_wtime();
	
	for (int i = 0; i < g->n; i++)
	{
		for (int j = 0; j < threads_num; j++)
		{
			thread_min_saturation[j] = -1;
		}
		
		#pragma omp parallel for
		for (int j = 0; j < g->n; j++)
		{
			if (!used_nums[j])
			{
				int num = omp_get_thread_num();
				if (thread_min_saturation[num] == -1 || saturations[j] < saturations[thread_min_saturation[num]])
				{
					thread_min_saturation[num] = j;
				}
			}
		}
		
		for (int j = 1; j < threads_num; j++)
		{
			if (thread_min_saturation[j] != -1 && 
				(thread_min_saturation[0] == -1 || saturations[thread_min_saturation[j]] < saturations[thread_min_saturation[0]]))
			{
				thread_min_saturation[0] = thread_min_saturation[j];
			}
		}
		
		int pos = thread_min_saturation[0];
		
		#pragma omp parallel for
		for (int j = 0; j < i; j++)
		{
			adjacentColors[j] = 0;
		}
		
		#pragma omp parallel for
		for (int j = 0; j < g->n; j++)
		{
			if (used_nums[j] && g->a[pos][j])
			{
				adjacentColors[s->colors[j]] = 1;
			}
		}
		
		for (int j = 0; j < threads_num; j++)
		{
			thread_min_color[j] = g->n;
		}
		
		#pragma omp parallel for
		for (int j = 0; j <= i; j++)
		{
			if (!adjacentColors[j])
			{
				int num = omp_get_thread_num();
				if (thread_min_color[num] > j)
				{
					thread_min_color[num] = j;
				}
			}
		}
		
		int color = g->n;
		for (int j = 0; j < threads_num; j++)
		{
			if (color > thread_min_color[j])
			{
				color = thread_min_color[j];
			}
		}
		
		s->colors[pos] = color;
		if (s->colorsCount < color + 1)
		{
			s->colorsCount = color + 1;
		}
		used_nums[pos] = 1;
		
		#pragma omp parallel for
		for (int j = 0; j < g->n; j++)
		{
			if (g->a[pos][j])
			{
				saturations[j].saturation++;
			}
		}
	}
	
	s->time = omp_get_wtime() - startTime;
	delete used_nums;
	delete thread_min_saturation;
	delete thread_min_color;
	delete adjacentColors;	
	delete saturations;
	
	return s;
}
