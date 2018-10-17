#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <vector>
#include <list>
#include <algorithm>

#include "node.h"
#include "edge.h"
#include "disjointset.h"

using namespace std;

class Traits {
public:
	typedef char N;
	typedef int E;
};

template <typename Tr>
class Graph {
public:
	typedef Graph<Tr> self;
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
	Graph():nodes(0){}

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

	E kruskal(){
		if ((*((nodes[0]) -> edges.begin())) -> getDir() == 0) {
			E peso = 0;
			vector<edge*> kEdges;
			for (ni = nodes.begin(); ni != nodes.end(); ni++) {
				for (ei = (*ni) -> edges.begin(); ei != (*ni) -> edges.end(); ei++) {
					kEdges.push_back(*ei);
				}
			}

			sort(kEdges.begin(),kEdges.end(),[](edge* edge1, edge* edge2){
				return (edge1->getData() < edge2->getData());
			});

			for (int i = 0; i < kEdges.size(); i++){
				for (int j = i+1; j < kEdges.size(); j++){
					if ((kEdges[i]->nodes[0]->getData()==kEdges[j]->nodes[1]->getData())&&(kEdges[i]->nodes[1]->getData()==kEdges[j]->nodes[0]->getData())){
						kEdges.erase(kEdges.begin()+j);
						break;
					}
				}
			}
			DisjointSet<self> set(nodes);
			int n = nodes.size() - 1;
			cout << "Kruskal MST: \n";
			for (typename vector<edge*>::iterator it = kEdges.begin(); it != kEdges.end(); it++) {
				node* nodo1 = (*it) -> nodes[0];
				node* nodo2 = (*it) -> nodes[1];
				nodo1 = set.findParent(nodo1);
				nodo2 = set.findParent(nodo2);

				if (nodo1 != nodo2) {
					cout << (*nodo1).getData() << " - " << (*nodo2).getData() << "    (" << (*it) -> getData() << ")" << endl;
					peso += (*it) -> getData();
					set.mergeSet(nodo1, nodo2);
					--n;
				}
				if (n == 0)
					break;
			}
			return peso;
		}
		else
			cout << "Grafo es direccionado\n";
	}

	E prim(N start) {
		if ((*((nodes[0]) -> edges.begin())) -> getDir() == 0) {
			NodeSeq inMST;
			E peso = 0;
			vector<edge*> pEdges;
			int n = 0;
			for (ni = nodes.begin(); ni != nodes.end(); ni++) {
				if ((*ni)->getData() == start) {
					inMST.push_back(*ni);
					break;
				}
				else
					cout << "Nodo no existe\n";
			}
			cout << "Prim MST: \n";
			while (n+1 < nodes.size() && inMST.size() > 0) {
				for (ei = (*(inMST.begin()+n)) -> edges.begin(); ei != (*(inMST.begin()+n)) -> edges.end(); ei++)
					pEdges.push_back(*ei);

				sort(pEdges.begin(),pEdges.end(),[](edge* edge1, edge* edge2){
					return (edge1->getData() < edge2->getData());
				});

				for (int i = 0; i < pEdges.size(); i++){
					bool exists = false;
					for (int j = 0; j < inMST.size(); j++){
						if (pEdges[i]->nodes[1] == inMST[j]){
							exists = true;
							break;
						}
					}
					if (exists){
						pEdges.erase(pEdges.begin()+i);
						i--;
					}
					else{
						cout << pEdges[i]->nodes[0]->getData() << " - " << pEdges[i]->nodes[1]->getData() << "    (" << pEdges[i] -> getData() << ")" << endl;
						peso += pEdges[i]->getData();
						inMST.push_back(pEdges[i]->nodes[1]);
						n++;
						break;
					}
				}
				if (pEdges.size() == 0)
					n++;
			}
			return peso;
		}
		else
			cout << "Grafo es direccionado\n";
	}

	bool denso(float cota){
		int sumNodos = 0;
		float sumAristas = 0;
		float ans =0;
		for(ni = nodes.begin(); ni != nodes.end(); ni++){
			sumNodos+=1;
			for(ei = (*ni)->edges.begin(); ei != (*ni)->edges.end(); ei++){
				sumAristas+=1;
			}
		}
		ans = (sumAristas)/(sumNodos*(sumNodos-1));
		//Es  igual por que en no dirigido cuento todas las aristas que hay
		//Habria el doble de aristas en la suma
		//La diferencia en la ecuacion con la dirigida es que se multiplica por 2
		//La division por 2 en la suma y la mult por 2 en la ecu se cancelan

		if (ans > cota){
			return true;
		}
		else{
			return false;
		}
		cout << endl;
	}

	void grado(){

		bool dir;
        	for (ni = nodes.begin(); ni != nodes.end(); ni++){
            		if ((*ni)->edges.size() > 0){
               			if ((*((*ni)->edges.begin()))->getDir() == 1)
                    			dir = true;
                		else
                    			dir = false;
                		break;
            		}
        	}
        	for(ni = nodes.begin(); ni != nodes.end(); ni++){
            	int gradoTotal=0;
            	int gradoEntrada=0;
            	int gradoSalida=0;
            	if (!dir)
                	gradoTotal = (*ni)->edges.size();
            	else{
                	gradoSalida = (*ni)->edges.size();
                	dir = true;
                	for (NodeIte ni1 = nodes.begin(); ni1 != nodes.end(); ni1++){
                    		for(ei = (*ni1)->edges.begin(); ei != (*ni1)->edges.end(); ei++){
                        		if ((*ei) -> nodes[1]==(*ni)){
                            			gradoEntrada+=1;
                        		}
                    		}
                	}
                	gradoTotal = gradoEntrada + gradoSalida;
                	cout << "Grado de entrada de " << (*ni) -> getData() << " es: " << gradoEntrada << endl;
                	cout << "Grado de salida de " << (*ni) -> getData() << " es: " << gradoSalida << endl;
            	}
            	cout << "Grado total de " << (*ni) -> getData() << " es: " << gradoTotal << endl;
            	cout << endl;
        	}
	}

	void fuente_hundido(){
		vector<N> fuente;
		vector<N> hundido;
		bool nodo2=false;
		int sumAristas=0;
		for(ni = nodes.begin(); ni != nodes.end(); ni++){
			for(ei = (*ni)->edges.begin(); ei != (*ni)->edges.end(); ei++){
				sumAristas+=1;
			}
			for (NodeIte ni1 = nodes.begin(); ni1 != nodes.end(); ni1++){
				for(EdgeIte ei1 = (*ni1)->edges.begin(); ei1 != (*ni1)->edges.end(); ei1++){
					if ((*ei1) -> nodes[1]==(*ni)){
						nodo2=true;
					}
				}
			}
			if (sumAristas==0 && nodo2){
				hundido.push_back((*ni) -> getData());
			}
			if (sumAristas>0 && !nodo2){
				fuente.push_back((*ni) -> getData());
			}
			sumAristas=0;
			nodo2=false;
		}
		cout << "Hundidos: ";
		for (typename vector<N>::iterator it = hundido.begin(); it != hundido.end(); ++it){
			cout << (*it) << " " ;
		}
		cout << endl;
		cout << "Fuente: ";
		for (typename vector<N>::iterator it = fuente.begin(); it != fuente.end(); ++it){
			cout << (*it) << " " ;
		}
		cout << endl;
	}

	bool conexo(){
		bool salida=false;
		bool entrada=false;
		for(ni = nodes.begin(); ni != nodes.end(); ni++){
			for(ei = (*ni)->edges.begin(); ei != (*ni)->edges.end(); ei++){
				salida=true;
			}
			for (NodeIte ni1 = nodes.begin(); ni1 != nodes.end(); ni1++){
				for(EdgeIte ei1 = (*ni1)->edges.begin(); ei1 != (*ni1)->edges.end(); ei1++){
					if ((*ei1) -> nodes[1]==(*ni)){
						entrada=true;
					}
				}
			}
			if (!salida && !entrada){
				return false;
			}
			salida=false;
			entrada=false;
		}
		return true;
	}

	bool findNode(N node){
		for(ni = nodes.begin(); ni != nodes.end(); ni++){
			if ((*ni) -> getData() == node){
				return true;
				break;
			}
		}
		return false;
	}

	bool findEdge (N nodo1, N nodo2){
		for(ni = nodes.begin(); ni != nodes.end(); ni++){
			if ((*ni) -> getData() == nodo1){
				for(ei = (*ni)->edges.begin(); ei != (*ni)->edges.end(); ei++){
					if  ((*ei) -> nodes[1] -> getData() == nodo2){
						return true;
						break;
					}
				}
			}
		}
		return false;
	}

	void BFS(N vertice){
		vector<N> visitados;
		vector<N> myqueue;
		myqueue.push_back(vertice);
		while (myqueue.size() != 0){
			for(ni = nodes.begin(); ni != nodes.end(); ni++){
				if ((*ni) -> getData() == myqueue.front()){
					myqueue.erase(myqueue.begin());
					for(ei = (*ni)->edges.begin(); ei != (*ni)->edges.end(); ei++){
						if (find (myqueue.begin(), myqueue.end(), (*ei) -> nodes[1] -> getData()) == myqueue.end() &&
						find (visitados.begin(), visitados.end(), (*ei) -> nodes[1] -> getData()) == visitados.end()){
							myqueue.push_back((*ei) -> nodes[1] -> getData());
						}
					}
					for (typename vector<N>::iterator it = myqueue.begin(); it != myqueue.end(); ++it){
						if (find (visitados.begin(), visitados.end(), (*it)) == visitados.end()){
							visitados.push_back((*ni)->getData());
							visitados.push_back((*it));
						}
					}
				}
			}
			int i=0;
			cout << "Visitados: ";
			for (typename vector<N>::iterator it = visitados.begin(); it != visitados.end(); ++it){
				if (i%2){
					cout << (*it) << " " ;
				}
				else{
					cout << (*it) << "" ;
				}
				i++;
			}
			cout << endl;
		}
	}

	void DFS(N vertice){
		vector<N> visitados;
		vector<N> mystack;
		mystack.insert(mystack.begin(),vertice);
		while (mystack.size() != 0){
			for(ni = nodes.begin(); ni != nodes.end(); ni++){
				if ((*ni) -> getData() == mystack.front()){
					mystack.erase(mystack.begin());
					for(ei = (*ni)->edges.begin(); ei != (*ni)->edges.end(); ei++){
						if (find (mystack.begin(), mystack.end(), (*ei) -> nodes[1] -> getData()) == mystack.end() &&
						find (visitados.begin(), visitados.end(), (*ei) -> nodes[1] -> getData()) == visitados.end()){
							mystack.push_back((*ei) -> nodes[1] -> getData());
						}
					}
					for (typename vector<N>::iterator it = mystack.begin(); it != mystack.end(); ++it){
						if (find (visitados.begin(), visitados.end(), (*it)) == visitados.end()){
							visitados.push_back((*ni)->getData());
							visitados.push_back((*it));
						}
					}
				}
			}
			int i=0;
			cout << "Visitados: ";
			for (typename vector<N>::iterator it = visitados.begin(); it != visitados.end(); ++it){
				if (i%2){
					cout << (*it) << " " ;
				}
				else{
					cout << (*it) << "" ;
				}
				i++;
			}
			cout << endl;
		}
	}

	~Graph(){
		vector<node*>().swap(nodes);
	}
};

typedef Graph<Traits> graph;


#endif
