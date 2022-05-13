#include<iostream>
#include<vector>
#include <bits/stdc++.h>
using namespace std;
typedef struct edge
{
	int dest,src,weight;
}E;
typedef struct Graph
{
	int num_vertices,num_edges;
	E* edges;
}g;
typedef struct Parent
{
	int p,w;
}parent;
int find(parent* mst, int V)
{
	if (mst[V].p == -1)
	{
		return V;
	}
	else
	{
		return find(mst,mst[V].p);
	}
}
void Union(parent* mst, int src, int dst, int weight)
{
	if (mst[dst].p == -1 || (mst[dst].p != -1 && mst[dst].w > weight))
	{
	    mst[dst].p = src;
	    mst[dst].w = weight;
	}
}
void sorting(g* graph)
{
	int temp;
	for (int i=0;i<graph->num_edges;i++)
	{
		for(int j=i+1;j<graph->num_edges;j++)
		{
			if(graph->edges[i].weight > graph->edges[j].weight)
			{
				temp = graph->edges[j].weight;
				graph->edges[j].weight = graph->edges[i].weight;
				graph->edges[i].weight = temp;
				temp = graph->edges[j].src;
				graph->edges[j].src = graph->edges[i].src;
				graph->edges[i].src = temp;
				temp = graph->edges[j].dest;
				graph->edges[j].dest = graph->edges[i].dest;
				graph->edges[i].dest = temp;
			}
		}
	}
}
void find_mst(g* graph)
{
	// sorting edges w.r.t to weights
	sorting(graph);
	cout<<"sorted edges:\n";
	for(int i=0;i<graph->num_edges;i++)
	{
		cout<<graph->edges[i].src<<" - "<<graph->edges[i].dest<<" - "<<graph->edges[i].weight<<endl;
	}

    parent* mst = new parent[graph->num_vertices * sizeof(parent)];
    // initialising parents to -1 and weights to max
    for(int i=0;i<graph->num_vertices;i++)
    {
    	mst[i].p = -1;
    	mst[i].w = INT_MAX;
	}
    int count =0, num_edges=0;
    // going through all the edges
    for(int i=0;i<graph->num_edges;i++)
    {
    	// if parents of two vertices are not same then doing union on them
    	if (find(mst, graph->edges[count].src) != find(mst, graph->edges[count].dest))
    	{
    		Union(mst, graph->edges[count].src, graph->edges[count].dest, graph->edges[count].weight);
		}
		count ++;
	}
	int total_weight =0;
	cout<<"\n------------------------------------Minimal Spannig tree:-----------------------------------------\n";
	for (int i=0;i<graph->num_vertices;i++)
	{
		if (mst[i].p != -1)
		{
			cout<<mst[i].p<<" - "<<i<<" - "<<mst[i].w<<endl;
			total_weight += mst[i].w;
		}
	}
	cout<<"Total weight:"<<total_weight<<endl;
}
int main()
{
	cout<<"allocating memory";
	g* graph = new g();
	
	//pre-defined input
	graph->num_vertices = 6;
	graph->num_edges = 8;
	graph->edges = new E[graph->num_edges * sizeof(E)];
	graph->edges[0].src = 0;
	graph->edges[0].dest = 1;
	graph->edges[0].weight = 4;
	graph->edges[1].src = 0;
	graph->edges[1].dest = 5;
	graph->edges[1].weight = 8;
	graph->edges[2].src = 1;
	graph->edges[2].dest = 2;
	graph->edges[2].weight = 8;
	graph->edges[3].src = 1;
	graph->edges[3].dest = 5;
	graph->edges[3].weight = 11;
	graph->edges[4].src = 2;
	graph->edges[4].dest = 3;
	graph->edges[4].weight = 2;
	graph->edges[5].src = 3;
	graph->edges[5].dest = 4;
	graph->edges[5].weight = 6;
	graph->edges[6].src = 4;
	graph->edges[6].dest = 5;
	graph->edges[6].weight = 1;
	graph->edges[7].src = 3;
	graph->edges[7].dest = 5;
	graph->edges[7].weight = 7;

	// For custom input
	/*cout<<"enter number of vertices";cin>>graph->num_vertices;
    cout<<"enter number of edges";cin>>graph->num_edges;
    graph->edges = new E[graph->num_edges * sizeof(E)];
    cout<<"enter edges:"<<endl;
    for(int i=0;i<graph->num_edges;i++)
    {
    	cout<<"enter src";cin>>graph->edges[i].src;
		cout<<" enter dest:";cin>>graph->edges[i].dest;
		cout<<"enter weight:";cin>>graph->edges[i].weight;
	}*/

    find_mst(graph);
}
