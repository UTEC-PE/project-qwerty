#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <vector>
#include <list>

#include "node.h"
#include "edge.h"

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

			void denso(float cota){
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
					cout << "Es denso, " << ans << endl;
				}
				else{
					cout << "Es disperso, " << ans << endl;
				}
			}

      ~Graph(){
          vector<node*>().swap(nodes);
      }


};

typedef Graph<Traits> graph;


#endif
