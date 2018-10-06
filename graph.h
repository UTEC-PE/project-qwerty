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
						edge *arista2=new edge(tmp, tmp2, value, dir);
						tmp2 -> edges.push_back(arista2);
					}
				}
			}

			void removeNode(N name){
				bool exists=false;
				for (ni=nodes.begin(); ni!=nodes.end(); ni++){
					if (name==(*ni) -> getData()){
						for (ei=(*ni) -> edges.begin(); ei!=(*ni) -> edges.end(); ei++){
							if ((*ei) ->  getDir()==0){
								for (EdgeIte ei2=((*ei) -> nodes[1]) -> edges.begin(); ei2!=((*ei) -> nodes[1]) -> edges.end(); ei2++){
									if (((*ei2) -> nodes[1]) -> getData()==name){
										removeEdge((((*ei) -> nodes[1]) -> getData()), name);
									}
								}
							}
						}
						node* tmp=(*ni);
						delete tmp;
						nodes.erase(ni);
						exists=true;
					}
				}
				if (!exists){
					cout << "No existe nodo ";
				}
			}

			void removeEdge(N nodo1, N nodo2){
				bool exists=false;
				for(ni=nodes.begin(); ni!=nodes.end(); ni++){
					if (nodo1==(*ni) -> getData()){
						for (ei=(*ni) -> edges.begin(); ei!=(*ni) -> edges.end(); ei++){
							if (((*ei) -> nodes[1]) -> getData()==nodo2){
								edge *tmp=(*ei);
								delete tmp;
								exists=true;
								break;
							}
						}
					}
					if (nodo2==(*ni) -> getData()){
						for (ei=(*ni) -> edges.begin(); ei!=(*ni) -> edges.end(); ei++){
							if (((*ei) -> nodes[1]) -> getData()==nodo1){
								edge *tmp=*ei;
								delete tmp;
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

            ~Graph(){
                vector<node*>().swap(nodes);
            }


};

typedef Graph<Traits> graph;


#endif
