#include <iostream>
#include <vector>
#include <list>
#include <iomanip>
#include <utility> // pair
#include <algorithm>
#include <map>
#include <cmath>

#include "node.h"
#include "edge.h"

#define INF 2147483647

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

	NodeIte ni;
	EdgeIte ei;

public:
	NodeSeq nodes;
	Graph2():nodes(0){}

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

	void insertNode(N name, double X, double Y){
		bool exists=false;
		for (ni=nodes.begin(); ni!=nodes.end(); ni++){
		    if (name==(*ni) -> getData()){
			exists=true;
		    }
		}
		if (!exists){
		    node* nodo=new node(name,X,Y);
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

	pair<vector<vector<E>>, vector<vector<N>>> floydWarshall(){
		const int size=nodes.size();
		vector<vector<E>> camino(size, vector<E>(size));//numeros
		vector<vector<E>> grafo(size, vector<E>(size));//intento de grafo
		vector<vector<N>> pasos(size, vector<N>(size));//Letras

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

	map<N,E> bellMan(N initial){
		int iteraciones=nodes.size()-1;
		vector<N> mystack;
		vector<N> visitados;
		bool change=false;
		int count=0;


		map<N,E> grafo;

		for (ni=nodes.begin(); ni!=nodes.end(); ni++){
			if ((*ni)->getData()==initial){
				grafo.insert(pair<N, E> ((*ni)->getData(),0));
			}
			else{
				grafo.insert(pair<N, E> ((*ni)->getData(),INF));
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

	map<N,E> Dijkstra(N source){
		map<N,E> distancias;
		NodeSeq q;
		int sourcePos = 0;
		for (int i = 0; i < nodes.size(); i++){
		    if (source == nodes[i]->getData()) {
			distancias[source] = 0;
			sourcePos = i;
		    }
		    else
			distancias[nodes[i]->getData()] = INF;
		}
		for (ei = (nodes[sourcePos])->edges.begin(); ei != (nodes[sourcePos])->edges.end(); ei++) {
		    if ((*ei)->getData() < distancias[(*ei)->nodes[1]->getData()])
			distancias[(*ei)->nodes[1]->getData()] = (*ei)->getData();
		    q.push_back((*ei)->nodes[1]);
		}
		while (!q.empty()){
		    sort(q.begin(),q.end(),[&distancias](node* nodo1, node* nodo2){
			return (distancias[nodo1->getData()] < distancias[nodo2->getData()]);
		    });
		    for (ei = q[0]->edges.begin(); ei != q[0]->edges.end(); ei++) {
			if (distancias[(*ei)->nodes[1]->getData()] == INF)
			    q.push_back((*ei)->nodes[1]);
			if (distancias[q[0]->getData()] + (*ei)->getData() < distancias[(*ei)->nodes[1]->getData()]){
			    distancias[(*ei)->nodes[1]->getData()] = distancias[q[0]->getData()] + (*ei)->getData();
			}
		    }
		    q.erase(q.begin());
		}
		return distancias;
	}

	pair<E,list<N>> Astar(N source, N final){
		map<N,double> h;
		node* nFinal, *nSource;
		bool t1 = false, t2 = false;
		for (ni = nodes.begin(); ni != nodes.end(); ++ni) {
		    if ((*ni)->getData() == final) {
			nFinal = *ni;
			t1 = true;
		    }
		    if ((*ni)->getData() == source){
			nSource = *ni;
			t2 = true;
		    }
		    if (t1 && t2)
			break;
		}
		for (ni = nodes.begin(); ni != nodes.end(); ++ni) {
		    double n = sqrt(pow((*ni)->getX() - nFinal->getX(),2) + pow((*ni)->getY() - nFinal->getY(),2));
		    h[(*ni)->getData()] = n; //Euclideano
		}
		map<N,pair<E,N>> distancias;
		NodeSeq q;
		q.push_back(nSource);
		distancias[source] = make_pair(0,source);
		while(distancias.find(final) == distancias.end()){
		    sort(q.begin(),q.end(),[&distancias,&h](node* nodo1, node* nodo2){
			return (distancias[nodo1->getData()].first + h[nodo1->getData()] < distancias[nodo2->getData()].first + h[nodo2->getData()]);
		    });
		    for (ei = q[0]->edges.begin(); ei != q[0]->edges.end(); ++ei){
			if (distancias.find((*ei)-> nodes[1]->getData()) == distancias.end() ){
			    q.push_back((*ei)->nodes[1]);
			    distancias[(*ei)->nodes[1]->getData()] = make_pair((*ei)->getData()+distancias[q[0]->getData()].first,q[0]->getData());
			}
			else if (distancias[(*ei)->nodes[1]->getData()].first > (*ei)->getData()+distancias[q[0]->getData()].first){
			    distancias[(*ei)->nodes[1]->getData()] = make_pair((*ei)->getData()+distancias[q[0]->getData()].first,q[0]->getData());
			}
		    }
		    q.erase(q.begin());
		    if (q.empty()){
                	list<N> path;
                	path.push_back(source);
                	return make_pair(2147483647,path);
            	    }
		}
		list<N> path;
        	N* ptr;
        	path.push_front(final);
        	ptr = &(distancias[final].second);
       		while(distancias[*ptr].second != *ptr){
            	    path.push_front(*ptr);
            	    ptr = &(distancias[*ptr].second);
        	}
        	path.push_front(source);
        	return make_pair(distancias[final].first,path);
	}

	vector< pair <N,E> > greedyBFS(N initial, N final){
		vector< pair <N,E> > visitados;
		//map<N,E> visitados;
		map <E,N> edges;

		edges.insert(make_pair(0, initial));

		while (!edges.empty()){
			for (ni=nodes.begin(); ni!=nodes.end(); ni++){
				if ((*ni)->getData()==edges.begin()->second){
					visitados.push_back(make_pair(edges.begin()->second, edges.begin()->first));
					edges.erase(edges.begin());
					for (ei=(*ni) -> edges.begin(); ei!=(*ni) -> edges.end(); ei++){
						bool einit=false;
						bool vinit=false;
						for (auto const& it : edges){
							if ((*ei) -> nodes[1] -> getData()==it.second){
								einit=true;
							}
						}
						for (auto const& it : visitados){
							if ((*ei) -> nodes[1] -> getData()==it.first){
								vinit=true;
							}
						}
						if ((*ei) -> nodes[1] -> getData()==final){
							visitados.push_back(make_pair(final, (*ei)->getData()));
							for (int i=visitados.size()-1; i>0; i--){
								for (NodeIte ni2=nodes.begin(); ni2!=nodes.end(); ni2++){
									if (visitados[i-1].first==(*ni2)->getData()){
										bool conecta=false;
										for (EdgeIte ei2=(*ni2) -> edges.begin(); ei2!=(*ni2) -> edges.end(); ei2++){
											if (visitados[i].first==(*ei2)->nodes[1]->getData() && (*ei2)->getData()==visitados[i].second){
												conecta=true;
											}
										}
										if (!conecta){
											visitados.erase(visitados.begin()+i-1);
										}
									}
								}
							}
							return visitados;
						}
						if (!einit && !vinit){
							edges.insert(make_pair((*ei)->getData(), (*ei)->nodes[1]->getData()));
						}
					}
				}
			}
		}
		return visitados;
	}

	~Graph2(){
		vector<node*>().swap(nodes);
	}
};

typedef Graph2<Traits2> graph2;
