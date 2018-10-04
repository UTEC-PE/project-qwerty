#ifndef GRAPH_H
#define GRAPH_H

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
				for (int i=0; i<nodes.size(); i++){
					if (name==(nodes[i]) -> data){
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
				for (int i=0; i<nodes.size(); i++){
					if (nodo1==(nodes[i]) -> data){
						tmp=nodes[i];
						exists1=true;
					}
					if (nodo2==(nodes[i]) -> data){
						tmp2=nodes[i];
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
				cout <<"Remove ------ \n";
				bool exists=false;
				for (int i=0; i<nodes.size(); i++){
					cout << (nodes[i]) -> data << endl;
					if (name==(nodes[i]) -> data){
						cout << "\nEcintre";
						for (EdgeIte it=(nodes[i]) -> edges.begin(); it!=(nodes[i]) -> edges.end(); it++){
							if ((*it) ->  dir==0){
								for (EdgeIte it2=((*it) -> nodes[1]) -> edges.begin(); it2!=((*it) -> nodes[1]) -> edges.end(); it2++){
									if (((*it2) -> nodes[1]) -> data==name){
										removeEdge((((*it) -> nodes[1]) -> data), name);
									}
								}
							}
						}
						cout << "\nSI\n";
						node* tmp=(nodes[i]);
						delete tmp;
						nodes.erase(nodes.begin()+i);
						exists=true;
						cout << "1Exists: " <<exists <<endl;
					}
				}

				cout << "2Exists: " <<exists <<endl;
				if (!exists){
					cout << "No existe ";
				}
			}

			void removeEdge(N nodo1, N nodo2){
				bool exists=false;
				for(int i=0; i<nodes.size(); i++){
					if (nodo1==(nodes[i]) -> data){
						for (EdgeIte it=(nodes[i]) -> edges.begin(); it!=(nodes[i]) -> edges.end(); it++){
							if (((*it) -> nodes[1]) -> data==nodo2){
								edge *tmp=(*it);
								delete tmp;
								exists=true;
							}
						}
					}
					if (nodo2==(nodes[i]) -> data){
						for (EdgeIte it=(nodes[i]) -> edges.begin(); it!=(nodes[i]) -> edges.end(); it++){
							if (((*it) -> nodes[1]) -> data==nodo1){
								edge *tmp=*it;
								delete tmp;
							}
						}
					}
				}
				if (!exists){
					cout << "No existe";
				}
			}

			void imprimeNodes(){
				for (int i=0; i<nodes.size(); i++){
					cout << (nodes[i]) -> data;
				}
			}

			void imprimeEdges(N nodo){
				for (int i=0; i< nodes.size(); i++){
					if (nodo==(nodes[i]) -> data){
						cout << (nodes[i]) -> edges.size();
					}
				}
			}

			// ~Graph(){
			// 	for (int i=0; i<nodes.size(); i++){
			// 		removeNode((nodes[i]) -> data);
			// 	}
			// }

};

typedef Graph<Traits> graph;


#endif
