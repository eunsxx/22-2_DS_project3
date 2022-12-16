#include "Manager.h"
#include <cstring>

Manager::Manager() {
	graph = nullptr;
	fout.open("log.txt", ios::app);
	load = 0;
}

Manager::~Manager() {
	if(load) delete graph;
	fout.close();
}

void Manager::run(const char* command_txt){
	ifstream fin;
	fin.open(command_txt);
		
	if(!fin) {
		cout <<"[ERROR] command file open error!"<<endl;
		return;
	}
	
	char* str=NULL;
	char* str2=NULL;
	char buf[129]={0}; // 0 initialization

	while(fin.getline(buf, 128)) {
        str = strtok(buf, " ");
        if (strcmp(str, "LOAD") == 0) { // LOAD
            str2 = strtok(NULL, " ");
            if(LOAD(str2)) {
                fout << "==========LOAD===========" << endl;
                fout << "Success" << endl;
                fout << "=========================" << endl;
            } else printErrorCode(100);
        } else if (strcmp(str, "PRINT")==0) { // PRINT
            if (!PRINT()) printErrorCode(200);
            else continue;
        } else if (strcmp(str, "BFS")==0) { // BFS
            str2 = strtok(NULL, " ");
            if (str2 == NULL) {
                printErrorCode(300);
                continue;
            }
            else if (!mBFS(stoi(str2))) printErrorCode(300);
            else continue;

        } else if (strcmp(str, "DFS") == 0) { // DFS
            str2 = strtok(NULL, " ");
            if (str2 == NULL or (!mDFS(stoi(str2)))) printErrorCode(400); 
        } else if (strcmp(str, "DFS_R") == 0) { // DFS_R
            str2 = strtok(NULL, " ");
            if (str2 == NULL or (!mDFS_R(stoi(str2)))) printErrorCode(500);
        } else if (strcmp(str, "KRUSKAL")==0) { // KRUSKAL
            if (!mKRUSKAL()) printErrorCode(600);
        } else if (strcmp(str, "DIJKSTRA") == 0) { // DIJKSTRA
            str2 = strtok(NULL, " ");
            if (str2 == NULL or !mDIJKSTRA(stoi(str2))) printErrorCode(700);
        } else if (strcmp(str,"BELLMANFORD") == 0) { // BELLMANFORD
            str2 = strtok(NULL, " ");
            char* str3 = strtok(NULL, " ");
            if (str2 == NULL or str3 == NULL or !mBELLMANFORD(stoi(str2), stoi(str3))) printErrorCode(800);
        } else if (strcmp(str, "FLOYD") == 0) { // FLOYD
            if (!mFLOYD()) printErrorCode(900);
        } else if (strcmp(str, "EXIT")) break;
    }
    load=1;
	fin.close();
}

bool Manager::LOAD(char* filename) {
    if (!graph) {
    } else {
        graph = nullptr;
    }
    ifstream file;
    file.open(filename);
    if (!file) {
        cout << "[ERROR]" << filename << " file open error!" << endl;
        return false;
    }

    char* str=NULL;
    char* str2=NULL;
    char buf[129]={0}; // 0 initialization
    bool type;

    file.getline(buf, 128); // find type
    if (buf[0] =='L') type = 0;
    else if (buf[0] == 'M') type = 1;
    else return false;
    file.getline(buf, 128); // find size
    int size = stoi(buf);

    int from, to, weight;

    if (type == 0) {
        ListGraph *lg = new ListGraph(type, size);

        while (file.getline(buf, 128)) {
            str = strtok(buf, " ");
            str2 = strtok(NULL, " ");
            if (str2 == NULL) {
                from = stoi(str);
            } else {
                to = stoi(str);
                weight = stoi(str2);
                lg->insertEdge(from, to, weight);
            }
        }
        graph = lg;
        load=1;
    } else if (type == 1) {
        MatrixGraph * mg = new MatrixGraph(type, size);
        from = 0;
        while (file.getline(buf, 128)) {
            to = 0;
            str = strtok(buf, " ");
            while (str != nullptr) {
                mg->insertEdge(from, to, stoi(str));
                str = strtok(NULL, " ");
                to++;
            }
            from++;
        }
        graph = mg;
        load=1;
    }
//    ListGraph lg;
    file.close();
    return true;
}

bool Manager::PRINT() {
    if (graph == nullptr) return false;
	if(graph->printGraph(fout)) return true;
	return false;
}

bool Manager::mBFS(int vertex)
{
    if (graph == nullptr) return false;
    if(BFS(graph, vertex, fout)) return true;
    else return false;
}

bool Manager::mDFS(int vertex)
{
    if (graph == nullptr) return false;
    if(DFS(graph, vertex, fout)) return true;
    else return false;
}


bool Manager::mDFS_R(int vertex)
{
    if (graph == nullptr) return false;
    map<int, int> adjEdge;
    graph->getAdjacentEdges(vertex, &adjEdge);
    map<int, int> :: iterator it = adjEdge.begin();
    if (it == adjEdge.end()) return false;
    fout << "==========DFS_R===========" << endl;
    vector<bool> * visit = new vector<bool>(graph->getSize(), false); // fill 0
    if(DFS_R(graph, visit, vertex, fout)) {
        fout << endl;
        fout << "=========================" << endl;
        delete visit;
        return true;
    }
    else {
        return false;
    }
}

bool Manager::mDIJKSTRA(int vertex) {
    if (graph == nullptr) return false;
    if(Dijkstra(graph, vertex, fout)) return true;
    else return false;
}

bool Manager::mKRUSKAL()
{
    if (graph == nullptr) return false;
    if (Kruskal(graph, fout)) return true;
    else return false;
}

bool Manager::mBELLMANFORD(int s_vertex, int e_vertex) {
    if (graph == nullptr) return false;
    if (Bellmanford(graph, s_vertex, e_vertex, fout)) return true;
    else return false;
}

bool Manager::mFLOYD() {
    if (graph == nullptr) return false;
    if(FLOYD(graph, fout)) return true;
    else return false;
}

void Manager::printErrorCode(int n)
{
	fout<<"======== ERROR ========"<<endl;
	fout<<n<<endl;
	fout<<"======================="<<endl;
}
