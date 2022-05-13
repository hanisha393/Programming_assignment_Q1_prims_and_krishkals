#include<iostream>
#include<vector>
#include <bits/stdc++.h>
using namespace std;
typedef struct edges
{
	int child;
	int weight;
}edges;
// To check if graph is conncted
int is_connected(int num_vertices, vector< vector <int> > graph)
{
	int visited[num_vertices];
	int start=0,flag=0;
	for (int i=0;i<num_vertices;i++)
	{
		visited[i] = 0;
	}
	visited[start] = 1;
	while(1)
	{
		flag =0;
		for (int i=0;i<num_vertices;i++)
	    {
		    if(visited[i]!=1 && graph[start][i] != 0)
		    {
			    visited[i] = 1;
			    start = i;
			    flag =1;
			    break;
		    }
	    }
		if (flag == 0) break;	
	}
	for (int i=0;i<num_vertices;i++)
	{
		if (visited[i] == 0)
		{
			cout<<"graph is not connected";
			return 0;
		}
	}
	cout<<"graph is connected";
    return 1;
}
int find_min_unvisited_weight(vector<int> visited_weights, vector<int> visited)
{
	int min = INT_MAX, min_index=-1;
	for (int i=0;i<visited.size();i++)
	{
		if (visited[i] ==0 && min > visited_weights[i])
		{
			min = visited_weights[i];
			min_index = i;
		}
	}
	return min_index;
}
void prims(vector< vector <int> > graph, int num_vertices)
{
     vector<int> visited_weights, visited, parent;
	 int vertex;
	 
	 //Initializing visited to 0 and parent to -1 and weights to max
     for (int i=0;i<num_vertices;i++)
     {
     	visited_weights.push_back(INT_MAX);
     	parent.push_back(-1);
     	visited.push_back(0);
	 }
    visited_weights[0] = 0;
    
    // prims algo
    for (int j=0;j<num_vertices;j++)
    {
    	//finding min unvisited vertex
    	vertex = find_min_unvisited_weight(visited_weights, visited);

    	if (vertex == -1)
    	{
    		break;
		}
		//setting visited of vertex to true
    	visited[vertex] = 1;
    	for (int i=0;i<num_vertices;i++)
    	{
            // updating weights and parent of adjacent vertices of vertex 
    		if (visited[i]==0 && 0!=graph[vertex][i] && visited_weights[i] > graph[vertex][i])
    		{ 
    			visited_weights[i] = graph[vertex][i];
    			parent[i] = vertex;
			}
		}
	}
	
	// Printing minimal spanning tree
	int total_weight=0;
	cout<<"\n----------------------------------------Minimal Spanning Tree:--------------------------------------------\n";
	for(int i=1;i<num_vertices;i++)
	{
		cout<<parent[i]<<" - "<<i<<" "<<graph[i][parent[i]]<<endl;
		total_weight+=graph[i][parent[i]];
	}
	cout<<"\nTotal Weight of minimal spanning tree: "<<total_weight;
}
int main()
{
	int num_vertices;
	vector< vector <int> > graph;
    vector<int> temp;
    //Initialization and input
	num_vertices=6;
	for(int i=0;i<num_vertices;i++)
	{
		temp.push_back(0);
	}
	for(int i=0;i<num_vertices;i++)
	{
		graph.push_back(temp);
	}
	graph[0][1]=4;
	graph[0][5]=8;
	graph[1][2]=8;
	graph[1][5]=11;
	graph[2][3]=2;
	graph[3][4]=6;
	graph[3][5]=7;
	graph[4][5]=1;
	graph[1][0]=4;
	graph[5][0]=8;
	graph[2][1]=8;
	graph[5][1]=11;
	graph[3][2]=2;
	graph[4][3]=6;
	graph[5][3]=7;
	graph[5][4]=1;
	// custom input
	/*cout<<"enter number of vetices:";cin>>num_vertices;
	for(int i=0;i<num_vertices;i++)
	{
		temp.push_back(0);
	}
	// Taking graph input
	for(int i=0;i<num_vertices;i++)
	{
		graph.push_back(temp);
	}
	for (int i=0;i<num_vertices;i++)
	{
		for (int j=0;j<num_vertices;j++)
		{
			if ( i !=j && graph[i][j] == 0)
			{
				cout<<"enter weight if "<<i<<" and "<<j<<" are connected else 0: ";cin>>graph[i][j];
				graph[j][i] = graph[i][j];
			}
		}
	}*/

    // Printing graph
    cout<<"\n----------------------------------------Input graph:--------------------------------------------\n";
	for(int i=0;i<num_vertices;i++)
	{
		for(int j=0;j<num_vertices;j++)
		{
			cout<<graph[i][j]<<" ";
		}
		cout<<endl;
	}

    // checking if graph is connected or not
	if (is_connected(num_vertices, graph) == 0)
	{
		cout<<endl<<"Graph is not connected, finding minimum spanning tree is not possible!";
		return 0;
	}
	
	// callin gprims algo if graph is connected
    prims(graph, num_vertices);
}
