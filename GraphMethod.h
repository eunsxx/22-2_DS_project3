#ifndef _GRAPHMETHOD_H_
#define _GRAPHMETHOD_H_

#include "ListGraph.h"
#include "MatrixGraph.h"
//#include "vertexSet.h"

bool BFS(Graph* graph, int vertex, ofstream& fout);
bool DFS(Graph* graph, int vertex, ofstream& fout);
bool DFS_R(Graph* graph, vector<bool>* visit, int vertex, ofstream& fout);
bool Kruskal(Graph* graph, ofstream& fout);
bool Dijkstra(Graph* graph, int vertex, ofstream& fout);
bool Bellmanford(Graph* graph, int s_vertex, int e_vertex, ofstream& fout);
bool FLOYD(Graph* graph, ofstream& fout);

int FIND(int vertex, int * parent);
void UNION(int vertex1, int vertex2, int * parent);
vector<tuple<int,int,int>> QuickSort(vector<tuple<int,int,int>> edgeList, int left, int right);
vector<tuple<int,int,int>> InsertionSort(vector<tuple<int,int,int>> * edgeList, int left, int right);

#endif
