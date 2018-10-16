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
				node* set1 = set.findParent(nodo1);
				node* set2 = set.findParent(nodo2);

				if (set1 != set2) {
					cout << (*nodo1).getData() << " - " << (*nodo2).getData() << "    (" << (*it) -> getData() << ")" << endl;
					peso += (*it) -> getData();
					set.mergeSet(set1, set2);
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
	}
	
	~Graph(){
		vector<node*>().swap(nodes);
	}
};

typedef Graph<Traits> graph;


#endif

