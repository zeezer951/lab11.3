#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <cstdlib>
#include <unordered_map>
#include "DfsTreeNode.h"

using namespace std;

void buildGraph(vector<vector<int>> &graph, 
	int graph_size, 
	int num_connections)
{
    srand(time(NULL));

    //zero out graph and ensure that graph is 
	//large enough
    if (graph.size() < graph_size)
    {
        graph.resize(graph_size);
    }
    for (int i = 0; i < graph.size(); i++)
    {
        if (graph[i].size() < graph_size)
        {
            graph[i].resize(graph_size);
        }
        for (int j = 0; j < graph[i].size(); j++)
        {
            graph[i][j] = 0;
        }
    }
    for (int i = 0; i < num_connections; i++)
    {
        int x = rand() % graph_size;
        int y = rand() % graph_size;
        graph[x][y] = 1;
    }

	//zero out diagonal (do not allow self-connections)
	for (int i = 0; i < graph_size; i++)
	{
		graph[i][i] = 0;
	}
}
void buildDfsTree(
	vector<vector<int>>& graph, 
	int node, 
	int visit_order,
	unordered_map<int, int>& visited
	)
{
	
	visited[node]++; 

	graph[node][node] = visit_order; 

	for (int outgoing = 0; outgoing < graph[node].size(); outgoing++)
	{
		if (node == outgoing)
		{	
			continue; 
		}
	
		if (graph[node][outgoing] > 0)
		{
		
			if (visited[outgoing] > 0)

				graph[node][outgoing] = -1; 
				graph[outgoing][node] = 0; 
		
		}
		else
		{
		
			graph[outgoing][node] = 0; 
			visit_order++;
			buildDfsTree(graph, outgoing, visit_order, visited); 
		
		}
	
	}







	return;
}

void getArticulationPoints(
	vector<vector<int>>& graph,
	int node,
	unordered_map<int, int>& low_values,
	vector<int>& articulation_points
)
{
	for (int outgoing = 0; outgoing < graph[node].size(); outgoing++)
	{
		if (outgoing == node)
		{
			continue; 
		
		}
		if (graph[node][outgoing] > 0)
		{

			getArticulationPoints
			(
				graph,
				outgoing,
				low_values,
				articulation_points
			);
		}
	
	}

	 // max low values 

	int low = graph[node][node]; 

	for (int outgoing = 0; outgoing < graph[node].size(); outgoing++)
	{
	
		if (outgoing == node)
		{
			continue; 
		}
	
		if (graph[node][outgoing] < 0)
		{
		
			if (low > graph[outgoing][outgoing])
			{
				low = graph[outgoing][outgoing]; 
			
			}
		
		
		}
		else if (graph[node][outgoing] > 0)
		{
				if(low > low_values[outgoing]) 
					{ 
						low = low_values[outgoing]; 
					}
		
		
		}
	
	}

	// record final low value 

	low_values[node] = low; 

	if (graph[node][node] == 1)
	{
	
		int counter = 0; 
		for (int outgoing = 0; outgoing < graph[node].size(); outgoing++)
		{
			
			if (node == outgoing)
			{
			
				continue; 
			}
			if (graph[node][outgoing] > 0)
			{
			
				counter++; 
			
			}
		
		}
	
		if (counter > 1)
		{

			articulation_points.push_back(node);

		}
	
	}
	else
	{
	
		for (int outgoing = 0; outgoing < graph[node].size(); outgoing++)
		{
			if (node == outgoing)
			{
				continue; 
			}
			if (graph[node][outgoing] > 0)
			{
				if (low_values[outgoing] >= graph[node][node])
				{
					articulation_points.push_back(node); 
					break; 
				
				}
				
			}
		
		
		}
		
	
	}


}

int main(void)
{
    vector<vector<int>> graph{};
    buildGraph(graph, 6, 0);
	graph[0][1] = 1;
	graph[0][4] = 1;
	graph[1][0] = 1;
	graph[1][2] = 1;
	graph[1][3] = 1;
	graph[2][1] = 1;
	graph[3][1] = 1;
	graph[3][4] = 1;
	graph[3][5] = 1;
	graph[4][0] = 1;
	graph[4][3] = 1;
	graph[5][3] = 1;
	unordered_map<int, int> visited{};
	buildDfsTree(graph, 0, 1, visited);
	unordered_map<int, int> low_values{};
	vector<int> articulation_points{};
	getArticulationPoints(
		graph, 
		3, 
		low_values, 
		articulation_points
	);
}