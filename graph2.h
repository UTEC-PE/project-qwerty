#include <iostream>
#include <vector>
#include <list>
#include <iomanip>
#include <utility> // pair
#include <algorithm>
#include <map>

#include "node.h"
#include "edge.h"

#define INF 99999

using namespace std;

class Traits2 {
public:
	typedef char N;
	typedef int E;
};

template <typename Tr>
class Graph2 {
public:
	typedef Graph2<Tr> self;
	typedef Node<self> node;
	typedef Edge<self> edge;
	typedef vector<node*> NodeSeq;
	typedef list<edge*> EdgeSeq;
	typedef typename Tr::N N;
	typedef typename Tr::E E;
	typedef typename NodeSeq::iterator NodeIte;
	typedef typename EdgeSeq::iterator EdgeIte;

private:
	NodeSeq nodes;
	NodeIte ni;
	EdgeIte ei;

public:
	Graph2():nodes(0){}

	void pqq(){
		for (ni=nodes.begin(); ni!=nodes.end(); ni++){
			cout << *ni;
		}
		cout << "HOLA";
	}

	void insertNode(N name){
		bool exists=false;
		for (ni=nodes.begin(); ni!=nodes.end(); ni++){
			if (name==(*ni) -> getData()){
				exists=true;
			}
		}
		if (!exists){
			node* nodo=new node(name);
			nodes.push_back(nodo);
		}
	}

	void insertEdge(N nodo1, N nodo2, E value, bool dir){
		bool exists1=false;
		bool exists2=false;
		node* tmp=nullptr;
		node* tmp2=nullptr;
		for (ni=nodes.begin(); ni!=nodes.end(); ni++){
			if (nodo1==(*ni) -> getData()){
				tmp=*ni;
				exists1=true;
			}
			if (nodo2==(*ni) -> getData()){
				tmp2=*ni;
				exists2=true;
			}
		}
		if (exists1 && exists2){
			edge *arista1=new edge(tmp, tmp2, value, dir);
			tmp -> edges.push_back(arista1);
			if (!dir){
				edge *arista2=new edge(tmp2, tmp, value, dir);
				tmp2 -> edges.push_back(arista2);
			}
		}
	}

	void removeNode(N name){
		bool exists=false;
		for (ni=nodes.begin(); ni!=nodes.end(); ni++){
			if (name==(*ni) -> getData()){
				node* tmp=(*ni);
				delete tmp;
				nodes.erase(ni);
				exists=true;
				break;
			}
		}
		for (ni=nodes.begin(); ni!=nodes.end(); ni++){
			for (ei=(*ni) -> edges.begin(); ei!=(*ni) -> edges.end(); ei++) {
				if ((*ei)->nodes[1]->getData() == name){
					(*ni) -> edges.remove(*ei);
					break;
				}
			}
		}
		if (!exists){
			cout << "No existe node ";
		}
	}

	void removeEdge(N nodo1, N nodo2){
		bool exists=false;
		for(ni=nodes.begin(); ni!=nodes.end(); ni++){
			if (nodo1==(*ni) -> getData()){
				for (ei=(*ni) -> edges.begin(); ei!=(*ni) -> edges.end(); ei++){
					if (((*ei) -> nodes[1]) -> getData()==nodo2){
						(*ni) -> edges.remove(*ei);
						exists=true;
						break;
					}
				}
			}
			if (nodo2==(*ni) -> getData()){
				for (ei=(*ni) -> edges.begin(); ei!=(*ni) -> edges.end(); ei++){
					if (((*ei) -> nodes[1]) -> getData()==nodo1){
						(*ni) -> edges.remove(*ei);
						break;
					}
				}
			}
		}
		if (!exists){
			cout << "No existe edge ";
		}
	}

	void imprimeNodes(){
		cout << "Nodes: ";
		for (ni=nodes.begin(); ni!=nodes.end(); ni++){
			cout << (*ni) -> getData() << " ";
		}
		cout << endl;
	}

	void imprimeEdges(N nodo){
		cout << "Edges de " << nodo << ": ";
		for (ni=nodes.begin(); ni!=nodes.end(); ni++){
			if (nodo==(*ni) -> getData()){
				cout << (*ni) -> edges.size() << " ";
			}
		}
		cout << endl;
	}

	void print(){
    cout << "Vertices / Aristas" << endl;
		for(ni = nodes.begin(); ni != nodes.end(); ni++){
			cout << (*ni)->getData() << ' ';
			for(ei = (*ni)->edges.begin(); ei != (*ni)->edges.end(); ei++){
				cout << (*ei)->getData() << ' ';
			}
			cout << endl;
		}
	}

	pair<vector<vector<int>>, vector<vector<char>>> floydWarshall(){
		const int size=nodes.size();
		vector<vector<int>> camino(size, vector<int>(size));//numeros
		vector<vector<int>> grafo(size, vector<int>(size));//intento de grafo
		vector<vector<char>> pasos(size, vector<char>(size));//Letras

		int row=0;
		for (ni = nodes.begin(); ni != nodes.end(); ni++){
			int col=0;
			for (NodeIte ni2= nodes.begin(); ni2 != nodes.end(); ni2++){
				for (ei = (*ni)->edges.begin(); ei != (*ni)->edges.end(); ei++){
					if ((*ni)->getData() == (*ni2)->getData()){
						grafo[row][col]=0;
					}
					else if ((*ni2)->getData()==(*ei)->nodes[1]->getData()){
						grafo[row][col]=(*ei)->getData();
						break;
					}
					else{
						grafo[row][col]=INF;
					}
				}
				col++;
			}
			row++;
		}
//-------------------------------------------------------
    for (int i = 0; i < size; i++){//copiar el grafo a camino
			for (int j = 0; j < size; j++){
				camino[i][j] = grafo[i][j];
			}
		}

		int i=0;
		for (ni = nodes.begin(); ni != nodes.end(); ni++){
			for (int j = 0; j < size; j++){
				if (i == j){//diagonal de pasos nula
					pasos[i][j]='-';
				}
				else{
					pasos[j][i]=(*ni)->getData();
				}
			}
			i++;
		}

		i=0;
    for (ni = nodes.begin(); ni != nodes.end(); ni++){//fila y col
      for (int j = 0; j < size; j++){//con el que se suma en la fila i
        for (int k = 0; k < size; k++){//con el que se suma en la col i
					if (camino[j][i] == INF || camino[i][k] == INF){//INF + x = INF, no evaluar INF
						continue;
					}
					if (camino[j][i] == 0 || camino[i][k] == 0){//no evaluar diagonal (0)
						continue;
					}
          if (camino[j][i] + camino[i][k] < camino[j][k]){
						camino[j][k] = camino[j][i] + camino[i][k];
						pasos[j][k] = (*ni) -> getData();
					}
        }
      }
			i++;
    }
		return make_pair(camino, pasos);
	}

	map<N,E> bellMan(char initial){
		int iteraciones=nodes.size()-1;
		vector<N> mystack;
		vector<N> visitados;
		bool change=false;
		int count=0;


		map<N,E> grafo;

		for (ni=nodes.begin(); ni!=nodes.end(); ni++){
			if ((*ni)->getData()==initial){
				grafo.insert(pair<char, int> ((*ni)->getData(),0));
			}
			else{
				grafo.insert(pair<char, int> ((*ni)->getData(),INF));
			}
		}

		for (int i=0; i<iteraciones; i++){
			count+=1;
			mystack.push_back(initial);
			visitados.push_back(initial);
			while(!mystack.empty()){
				change=false;
				for (ni=nodes.begin(); ni!=nodes.end(); ni++){
					if ((*ni)->getData()==mystack.front()){
						mystack.erase(mystack.begin());
						for (ei = (*ni)->edges.begin(); ei != (*ni)->edges.end(); ei++){
							if (find (mystack.begin(), mystack.end(), (*ei) -> nodes[1] -> getData()) == mystack.end() &&
							find (visitados.begin(), visitados.end(), (*ei) -> nodes[1] -> getData()) == visitados.end()){
								mystack.push_back((*ei) -> nodes[1] -> getData());
							}
							if (grafo[(*ei)->nodes[1]->getData()]>grafo[(*ni)->getData()]+(*ei)->getData()){
								grafo[(*ei)->nodes[1]->getData()]=grafo[(*ni)->getData()]+(*ei)->getData();
								change=true;
							}
						}
						for (typename vector<N>::iterator it = mystack.begin(); it != mystack.end(); ++it){
							if (find (visitados.begin(), visitados.end(), (*it)) == visitados.end()){
								visitados.push_back((*it));
							}
						}
					}
				}
			}
			visitados.clear();
			if (!change && count>1){
				break;
			}
		}
		// for (auto& t : grafo){
		// 	cout << t.first << " "<< t.second << "\n";
		// }

		return grafo;

	}

	~Graph2(){
		vector<node*>().swap(nodes);
	}
};

typedef Graph2<Traits2> graph2;
