#include <iostream>
#include <fstream>
#include <omp.h>
#include <ctime>
#include <cstdlib>
#include "graph.h"
#include "solution.h"
#include "greedy.h"
#include "fullsearch.h"
#include <vector>

using namespace std;

ofstream log("log.txt");

void testSolution(solution * (*f)(graph *g, int threads_num), graph *g, int min_threads_num, int max_threads_num, int iterations)
{
	bool flag = true;
	solution *prevSolution = NULL;
	for (int i = min_threads_num; i <= max_threads_num; i++)
	{
		double timeSum = 0;
		for (int iter = 1; iter <= iterations; iter++)
		{
			solution *s = (*f)(g, i);
			timeSum += s->time;
			if (prevSolution == NULL)
			{
				prevSolution = s;
			}
			else
			{
				if (!isEqualSolutions(s, prevSolution))
				{
					flag = false;
				}
				deleteSolution(prevSolution);
				prevSolution = s;
			}
		}
		cout << i << " : " << timeSum / iterations << "\n";
		log << i << " " << timeSum / iterations << "\n";
	}
	if (flag)
	{
		cout << "Everything is OK.\n";
	}
	else
	{
		cout << "Not equal solutions\n";
	}
}

void checkOut(graph *g, solution *s)
{
	if (!checkSolution(g, s))
		cout << "WRONG SOLUTION\n";
}

void testGreedySolutionsAnswers(int iterations, int n, int m)
{
	while (iterations--)
	{
		graph *g = getRandomGraph(n, m);
		solution *s;
		s = getSequentialGreedySolution(g, 8);
		checkOut(g, s);
		cout << s->colorsCount << " ";
		deleteSolution(s);
		s = getSortedGreedySolution(g, 8);
		checkOut(g, s);
		cout << s->colorsCount << " ";
		deleteSolution(s);
		s = getSortedSequentialGreedySolution(g, 8);
		checkOut(g, s);
		cout << s->colorsCount << " ";
		deleteSolution(s);
		s = getSortedSaturationGreedySolution(g, 8);
		checkOut(g, s);
		cout << s->colorsCount << " ";
		deleteSolution(s);
		s = getSimpleFullSearchSolution(g, 4);
		checkOut(g, s);
		cout << s->colorsCount << " ";
		deleteSolution(s);
		s = getHardFullSearchSolution(g, 4);
		cout << s->colorsCount << " ";
		deleteSolution(s);
		deleteGraph(g);
		cout << "\n";
	}
}

void testGreedySolutions(int iterations, int n, int m)
{
	graph *g = getRandomGraph(n, m);
	testSolution(getSequentialGreedySolution, g, 1, 10, iterations);
	testSolution(getSortedGreedySolution, g, 1, 10, iterations);
	testSolution(getSortedSequentialGreedySolution, g, 1, 10, iterations);
	testSolution(getSortedSaturationGreedySolution, g, 1, 10, iterations);
}

void test()
{
	solution *s;
	for (int i = 1; i <= 50; i++)
	{
		int n = i * 200;
		graph *g = getRandomGraph(n);
		s = getSequentialGreedySolution(g, 8);
		log << s->time << "\n";
		deleteSolution(s);
		s = getSortedGreedySolution(g, 1);
		log << s->time << "\n";
		deleteSolution(s);
		s = getSortedSequentialGreedySolution(g, 8);
		log << s->time << "\n";
		deleteSolution(s);
		s = getSortedSaturationGreedySolution(g, 8);
		log << s->time << "\n";
		deleteSolution(s);
		deleteGraph(g);
		cout << i << "\n";
	}
}

int main()
{
	srand(time(NULL));
	/*graph *g = getRandomGraph(8000, -1);
	cout << "Graph is created\n";
	
	solution * (*f)(graph *g, int threads_num);
	f = getSortedSaturationGreedySolution;
	testGreedySolution(f, g, 1, 10, 10);
	*/
	//testGreedySolutions(10, 5000, -1);
	//testGreedySolutionsAnswers(20, 17, -1);
	test();
	//graph *g = getRandomGraph(23, -1);
	//testSolution(getHardFullSearchSolution, g, 1, 20, 1);
	//deleteGraph(g);
	return 0;
}
