#include <iostream>
#include <vector>
#include <array>
#include <list>
#include <utility> // pair
#include <algorithm>

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

	int sizes(){
		int size=0;
		for (ni = nodes.begin(); ni!= nodes.end(); ni++){
			size+=1;
		}
		return size;
	}
	//static const int size=5;
	pair<vector<vector<int>>, vector<vector<char>>> floydWarshall(){
		const int size=nodes.size();
		vector<vector<int>> grafo {{0,   INF,  6, 3, INF},
	                        {3, 0,   INF, INF, INF},
	                        {INF, INF, 0,   2, INF},
	                        {INF, 1, 1, 0, INF},
	                        {INF, 4, INF, 2, 0}
	                      };
		vector<vector<int>> camino(size, vector<int>(size));
		vector<vector<int>> prueba(size, vector<int>(size));
		vector<vector<char>> pasos(size, vector<char>(size));

		// for (ni = nodes.begin(); ni != nodes.end(); ni++){
		// 	sort((*ni)->edges.begin(),(*ni)->edges.end(),[](edge* edge1, edge* edge2){
		// 		return (edge1->node[1]->getData() < edge2->node[1]->getData());
		// 	});
		// }
		//
		// for (int i = 0; i < size; i++){
		// 	for (int  j = 0; j < size; j++){
		// 		int row=0;
		// 		for (ni = nodes.begin(); ni != nodes.end(); ni++){
		// 			int col=0;
		// 			for (NodeSeq ni2=nodes.begin(); ni2!= nodes.end(); ni2++){
		// 				if (row==col){
		// 					prueba[row][col]=0;
		// 				}
		// 				else if ((*ni)->edges->node[1]->getData()==(*ni2)->edges->node[1]->getData()){
		// 					prueba[row][col]=(*ni)->edges->getData();
		// 				}
		// 				else{
		// 					prueba[row][col]=INF;
		// 				}
		// 				row++;
		// 			}
		// 		}
		// 	}
		// }

    for (int i = 0; i < size; i++){
			for (int j = 0; j < size; j++){
				camino[i][j] = grafo[i][j];
			}
		}

		int i=0;
		for (ni = nodes.begin(); ni != nodes.end(); ni++){
			for (int j = 0; j < size; j++){
				if (i == j){
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


	~Graph2(){
		vector<node*>().swap(nodes);
	}
};

typedef Graph2<Traits2> graph2;
