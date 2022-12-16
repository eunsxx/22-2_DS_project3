#include "ListGraph.h"

ListGraph::ListGraph(bool type, int size) : Graph(type, size)
{
	m_Type = type;
	m_List = new map<int, int>[size];
}

ListGraph::~ListGraph()
{
	delete[] m_List;
}

void ListGraph::getAdjacentEdges(int vertex, map<int, int>* m) {
    for (int i = 0; i < m_Size; i++) {
        map<int, int> :: iterator it_ = m_List[i].begin();
        while (it_ != m_List[i].end()) {
//            cout << "i = " << i << endl;
            if (i != vertex) {
                it_ = m_List[i].find(vertex);
                if (it_ != m_List[i].end()) {
//                    cout << i << "->" << it_->first << endl;
                    m->insert(make_pair(i, it_->second));
                    it_ = m_List[i].end();
                } else it_ = m_List[i].end();
            } else if (i == vertex) {
//                cout << "vertex = " << vertex << endl;
//                cout << i << " " << it_->first << endl;
                m->insert(make_pair(it_->first, it_->second));
                it_++;
            }
        }
    }
}
void ListGraph::getAdjacentEdgesWithDirection(int vertex, map<int, int>* m) {
    for (int i = 0; i < m_Size; i++) {
        map<int, int> :: iterator it_ = m_List[vertex].begin();
        while (it_ != m_List[vertex].end()) {
//            cout << "i = " << i << endl;
//                cout << "vertex = " << vertex << endl;
//                cout << i << " " << it_->first << endl;
            m->insert(make_pair(it_->first, it_->second));
            it_++;
        }
    }
}

void ListGraph::insertEdge(int from, int to, int weight) {
    m_List[from][to] = weight;
}

bool ListGraph::printGraph(ofstream& fout)
{
//	cout<<"Graph is ListGraph!"<<endl;

    fout << "==========PRINT===========" << endl;
	for(int i=0; i<m_Size; i++)
	{
		fout<<"["<<i<<"]";

		for(auto it_=m_List[i].begin(); it_!=m_List[i].end() && fout<<" -> "; it_++)
		{
			fout<<"("<<it_->first<<","<<it_->second<<")";
		}
		fout<<endl;
	}
    fout << "=========================" << endl;
    return 1;
}
