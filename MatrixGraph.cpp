#include "MatrixGraph.h"

MatrixGraph::MatrixGraph(bool type, int size) : Graph(type, size)
{
	m_Mat = new int*[size];
	for(int i=0; i<size; i++)
	{
		m_Mat[i] = new int[size];
		memset(m_Mat[i], 0, sizeof(int)*size);
	}
}

MatrixGraph::~MatrixGraph()
{
	for(int i=0; i<getSize(); i++)
	{
		delete[] m_Mat[i];
	}
	delete[] m_Mat;
}

void MatrixGraph::getAdjacentEdges(int vertex, map<int, int>* m)
{
    for(int i=0; i<m_Size; i++) {
        for (int j = 0; j < m_Size; j++) {
            if (i == vertex) {
                if (m_Mat[i][j] != 0) {
//                    cout << i << "->" << j << endl;
                    m->insert(make_pair(j, m_Mat[i][j]));
                }
            } else if (j == vertex) {
                if (m_Mat[i][j] != 0) {
//                    cout << i << "->" << j << endl;
                    m->insert(make_pair(i, m_Mat[i][j]));
                }
            }
        }
    }
}

void MatrixGraph::getAdjacentEdgesWithDirection(int vertex, map<int, int>* m) {
    for(int i=0; i<m_Size; i++) {
        for (int j = 0; j < m_Size; j++) {
            if (i == vertex) {
                if (m_Mat[i][j] != 0) {
//                    cout << i << "->" << j << endl;
                    m->insert(make_pair(j, m_Mat[i][j]));
                }
            }
        }
    }
}

void MatrixGraph::insertEdge(int from, int to, int weight)
{
    m_Mat[from][to] = weight;
}

bool MatrixGraph::printGraph(ofstream &fout)
{
	if( m_Size < 0 )
		return 0;

//	cout<<"Graph is MatrixGraph!"<<endl;
    fout << "==========PRINT===========" << endl;

	fout<<'\t';
	for(int i=0; i<m_Size; i++)
	{
		fout<<"["<<i<<"]"<<'\t';
	}
	fout<<endl;

	for(int i=0; i<m_Size; i++)
	{
		fout<<"["<<i<<"]";
		for(int j=0; j<m_Size && fout<<'\t'; j++)
		{
			fout<<m_Mat[i][j];
		}
		fout<<endl;
	}
    fout << "=========================" << endl;
    return 1;
}
