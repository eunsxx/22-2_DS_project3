#include "GraphMethod.h"
#include <queue>
#include <stack>
#include <list>
#include <tuple>
#include <cmath>

#define INF 0x3f3f3f3f
bool BFS(Graph* graph, int vertex, ofstream& fout) {
    map<int, int> adjEdge; // adjacent edge
    graph->getAdjacentEdges(vertex, &adjEdge); // adjcent edge from vertex
    map<int, int> :: iterator it = adjEdge.begin();
    if (it == adjEdge.end()) return false;
    fout << "==========BFS===========" << endl;
    queue<int> q; // queue
    int size = graph->getSize();
    bool * visited = new bool[size]{0}; // fill 0

    q.push(vertex);

    while (!q.empty()) { // if q is not empty
        vertex = q.front();
        visited[vertex] = true;
        q.pop();
        fout << vertex;
        map<int, int> adjEdge;
        graph->getAdjacentEdges(vertex, &adjEdge);
        map<int, int> :: iterator it = adjEdge.begin();

        while (it != adjEdge.end()) { 
            if (!visited[it->first]) { // if not visit adjacent edge from vertex
                q.push(it->first);
                visited[it->first] = true;
            }
            it++;
        }
        if (q.size()!=0) fout << " -> ";
    }
    fout << endl;
    fout << "=========================" << endl;
    delete[] visited;
    return true;
}

bool DFS(Graph* graph, int vertex, ofstream& fout) {
    map<int, int> adjEdge; // adjcent edge
    graph->getAdjacentEdges(vertex, &adjEdge);
    map<int, int> :: iterator it = adjEdge.begin();
    if (it == adjEdge.end()) return false; // if vertex is not exist in the graph, return false
    fout << "==========DFS===========" << endl;
    stack<int> stack;
    int size = graph->getSize();
    bool * visited = new bool[size]{0}; // fill 0

    stack.push(vertex);
    while (!stack.empty()) { // if stack is not empty
        bool findStatus = false; // fvertex ind status,
        vertex = stack.top();
        if (!visited[vertex]) fout << vertex; // if not visited the adjcent edge from vertex
        visited[vertex]=true; // visit this edge, end visited is true;
        map<int, int> adjEdge; // map is ascending default
        graph->getAdjacentEdges(vertex, &adjEdge);
        map<int, int> :: iterator it = adjEdge.begin();
        while (it != adjEdge.end()) {
            if (!visited[it->first]) {
                stack.push(it->first); // push in the stack
                findStatus = true;
                it = adjEdge.end();
            } else {
                it++;
            }
        }
        if (!findStatus) stack.pop();
        if (findStatus) fout << " -> ";
    }
    delete[] visited;
    fout << endl;
    fout << "=========================" << endl;
    return true;
}

bool DFS_R(Graph* graph, vector<bool>* visit, int vertex, ofstream& fout) {
    visit->at(vertex) = true;
    map<int, int> adjEdge; // map is ascending default
    graph->getAdjacentEdges(vertex, &adjEdge); // get adjcent edges from vertex

    fout << vertex;
    map<int, int>::iterator it = adjEdge.begin();
    while (it != adjEdge.end()) {
        if (visit->at(it->first) == false) { // if not visit the edge
            fout << " -> ";
            DFS_R(graph, visit, it->first, fout); // recursive
            it++;
        } else it++;
    }
    return true;
}

bool Kruskal(Graph* graph, ofstream& fout) {
    int size = graph->getSize();
    int *parent= new int[size]; // parent need to find the vertex's union
	// if vertex's parents are same, this graph occur cycle
    for (int i = 0; i < graph->getSize(); i++) { // initialization
        parent[i] = i;
    }
    vector<tuple<int, int, int>> edge; // edge is set of vertex's path
	// first value is From vertex, second is To vertex, Third is weight
    for (int i = 0; i < size; i++) {
        map<int, int> adjEdge;
        graph->getAdjacentEdges(i, &adjEdge);
        map<int, int>::iterator mit = adjEdge.begin();
        while (mit != adjEdge.end()) {
            edge.push_back(make_tuple(i, mit->first, mit->second)); // push to edge
            mit++;
        }
    }
   
    edge = QuickSort(edge, 0, edge.size()-1); // Quick Sort by descending

    int ver1, ver2, count=0, cost = 0;
    for (int edgeCount=0; edgeCount < size-1;) {
        ver1 = get<0>(edge[count]);
        ver2 = get<1>(edge[count]);
        if (FIND(ver1, parent) != FIND(ver2, parent)) { // if ver1, ver2 are not same union,
            UNION(ver1, ver2, parent); // union ver1 and ver2
            cost += get<2>(edge[count]); // and cost update ( + weight )
            count++; // count is edge's order
            edgeCount++; // edgeCounter is check the V-1 lop (V is vertex num)
        } else count++;
    }
    fout << "==========KRUSKAL===========" << endl;
    for (int i = 0; i < edge.size(); ++i) { // ascending output
        fout << "[" <<get<0>(edge[i]) << "] " << get<1>(edge[i]) << "(" << get<2>(edge[i]) << ")" << endl;
    }
    fout << "cost = " << cost << endl;
    fout << "=========================" << endl;
    return true;
}

vector<tuple<int,int,int>> InsertionSort(vector<tuple<int,int,int>> edgeList, int left, int right) {
    tuple<int,int,int> temp; // temp is key that is moved to left
    int i, j, key;
    for (i = left + 1; i < right ; i++) {
        key = get<2>(edgeList[i]);
        temp = edgeList[i];
        for (j = i-1; j >= 0; j--) {
            if (get<2>(edgeList[j]) > key) {
                edgeList[j+1] = edgeList[j]; // update j edge to j+1
            }
            else break;
        }
        edgeList[j+1] = temp;
    }
    return edgeList;
}

vector<tuple<int,int,int>> QuickSort(vector<tuple<int,int,int>> edgeList, int left, int right) {
    if (left < right) {
        if (right - left + 1 <= 6) {
            edgeList = InsertionSort(edgeList, left, right+1);
        } else {
            int i = left;
            int j = right+1;
            int pivot = get<2>(edgeList[left]);
            do {
                do i++; while (get<2>(edgeList[i]) < pivot); // a[i] < pivot
                do j--; while (get<2>(edgeList[j]) > pivot); // a[j] > pivot
                if (i < j) swap(edgeList[i], edgeList[j]);
            } while (i < j);
            swap(edgeList[left], edgeList[j]);
            edgeList = QuickSort(edgeList, left, j-1);
            edgeList = QuickSort(edgeList, j + 1, right);
        }
    }
    return edgeList;
}

int FIND(int vertex, int * parent) { // Find vertex's parent
    if (parent[vertex] == vertex) return vertex; // if Vertex's parent is vertex, this is root.
    return parent[vertex] = FIND(parent[vertex], parent); // if vertex's parent is not vertex, go to parent until meet the root.
}

void UNION(int vertex1, int vertex2, int * parent) {
    vertex1 = parent[vertex1]; // vertex1 is vertex1's parent
    vertex2 = parent[vertex2]; // vertex2 is vertex2's parent
    if (vertex1 == vertex2) return; // if vertex1 and vertex2 have same parent, it is already union.
    parent[vertex2] = vertex1; // ver2's parent is ver1. union ver1 and ver2. ver1 is root.
}

bool Dijkstra(Graph* graph, int vertex, ofstream& fout) {
    int startvertex = vertex;
    int size = graph->getSize();
	// all vertex's distance initialzation 
    vector<int> distance(size, INF); 
    vector<bool> visit(size, false);
    vector<int> path(size, -1);
    distance[vertex] = 0; // start vertex's distance initialization 0

    for (int i = 0; i < size; i++) {
        visit[vertex] = true;
        map<int, int> adjEdge;
        graph->getAdjacentEdgesWithDirection(vertex, &adjEdge);
        map<int, int>::iterator mit = adjEdge.begin();
        while (mit != adjEdge.end()) {
            if (mit->second < 0) return false; // negative weight
            if (mit->second + distance[vertex] < distance[mit->first]) {
                distance[mit->first] = mit->second + distance[vertex];
                path[mit->first] = vertex;
            }
            mit++;
        }

        int min = INF;
        int next_vertex;

		// Find min 
        for (int i = 0; i < size; i++) {
            if (min > distance[i] && !visit[i]) {
                min = distance[i];
                next_vertex = i;
            }
        }
        vertex = next_vertex;
    }
    stack<int> s;
    fout << "============DIJKSTRA=============" << endl;
    fout << "startvertex: " << startvertex << endl;
    for (int i = 0; i < size; i++) {
        if (i == startvertex) continue;
        fout << "[" << i << "] ";
        int temp = i;

        if (distance[i] == INF) fout << 'x' << endl; // if value is INFINITE -> 'x' print
        else {
            int j = i;
            while (path[j] != -1) {
                s.push(j);
                j = path[j];
                if (path[j] == -1) s.push(j);
            }
            while (!s.empty()) {
                int v = s.top();
                fout << v;
                s.pop();
                if (!s.empty()) fout << " -> ";
            }
            fout << "(" << distance[temp] << ")" << endl;
        }
    }
    fout << "================================" << endl;
    return true;
}

bool Bellmanford(Graph* graph, int s_vertex, int e_vertex, ofstream& fout)
{
    int size = graph->getSize();
    vector<int> distance(size, INF);
    vector<int> path(size, -1);
    distance[s_vertex] = 0;

    int vertex = s_vertex;
    for (int j = 0; j < size; j++) {
        for (int i = 0; i < size; i++) {
            map<int, int> adjEdge;
            graph->getAdjacentEdgesWithDirection(i, &adjEdge);
            map<int, int>::iterator mit = adjEdge.begin();
            while (mit != adjEdge.end()) {
                if (distance[i] == INF) break; // if value is infinite, break;
                if (mit->second + distance[i] < distance[mit->first]) { // dist[i] + weight < dist[vertex]
                    if (j == size-1) return false; // loop v occurs negative cycle
                    distance[mit->first] = mit->second + distance[i];
                    path[mit->first] = i;
                }
                mit++;
            }
        }
    }
    // +1 loop
    for(int i = 0; i < size; i++) {
        map<int, int> adjEdge;
        graph->getAdjacentEdgesWithDirection(i, &adjEdge);
        map<int, int>::iterator mit = adjEdge.begin();
        while (mit != adjEdge.end()) {
            if (distance[i] == INF) break; // if value is infinite, break;
            if (mit->second + distance[i] < distance[mit->first]) {
                distance[mit->first] = mit->second + distance[i];
                path[mit->first] = i; // path update
            }
            mit++;
        }
    }

    stack<int> s; // stack

    fout << "============BELLMAN FORD=============" << endl;
    bool find = false;
    if (distance[e_vertex] == INF) fout << 'x' << endl;
    else {
        int j = e_vertex;
        while(path[j] != -1) {
            s.push(j);
            j = path[j];
            if (j == s_vertex) find = true;
            if (path[j] == -1) s.push(j);
        }
        if (find == false) fout << 'x' << endl;
    }
    while (!s.empty()) {
        int v = s.top();
        fout << v;
        s. pop();
        if (!s.empty()) fout << " -> ";
    }
    fout << endl;
    if (find) fout << "cost: " << distance[e_vertex] << endl;
    
    fout << "================================" << endl;
    return true;
}

bool FLOYD(Graph* graph, ofstream& fout) {
    int size = graph->getSize();
    int ** arr = new int * [size];
    for (int i = 0; i < size; i++) { // dynamic allocation.
        arr[i] = new int [size];
    }

    for (int i = 0; i < size; i++) { // if vertex is entering oneself, initialization 0, else initialization infinite
        for (int j = 0; j < size; j++) {
            if (i==j) arr[i][j] = 0;
            else arr[i][j] = INF;
        }
    }

    for (int i = 0; i < size; i++) { // Put the saved value
        map<int, int> adjEdge;
        graph->getAdjacentEdgesWithDirection(i, &adjEdge);
        map<int, int>::iterator mit = adjEdge.begin();
        while (mit != adjEdge.end()) {
            arr[i][mit->first] = mit->second;
            mit++;
        }
        arr[i][i]=0;
    }

    for (int k = 0; k < size; k++) { // Find short path
        for (int j = 0; j < size; j++) {
            for (int i = 0; i < size; i++)
                arr[i][j] = min(arr[i][j], arr[i][k] + arr[k][j]);
        }
    }
	
    for (int i = 0; i < size; i++) { // if negative cycle occurs, return false
        if(arr[i][i] < 0) return false;
    }

    fout << "==========FLOYD===========" << endl;

    fout<<'\t';
    for(int i=0; i<size; i++) // print
    {
        fout<<"["<<i<<"]"<<'\t';
    }
    fout<<endl;

    for(int i=0; i<size; i++)
    {
        fout<<"["<<i<<"]";
        for(int j=0; j<size && fout<<'\t'; j++)
        {
            if (arr[i][j] == INF) fout << 'x';
            else fout<<arr[i][j];
        }
        fout<<endl;
    }
    fout << "=========================" << endl;
    return true;
}