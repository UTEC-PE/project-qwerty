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

			void insertEdge(node* nodo1, node* nodo2, E value, bool dir){
				edge arista1=new edge(nodo1, nodo2, value, dir);
				nodo1 -> edges.push_back(arista1);
				if (!dir){
					edge arista2=new edge(nodo2, nodo1, value, dir);
					nodo2 -> edges.push_back(arista2);
				}
			}

			void removeNode(N name){
				for (int i=0; i<nodes.size(); i++){
					if (name==(nodes[i]) -> data){
						for (int j=0; j<(nodes[i]) -> edges.size(); j++){
							if ((nodes[i]) -> edges[j] ->  dir==0){
								for (int k=0; k<(nodes[i]) -> edges[j] -> nodes[1] -> edges.size(); k++){
									if ((nodes[i]) -> edges[j] -> nodes[1] -> edges[k] -> nodes[1] -> data==name){
										removeEdge((nodes[i]) -> edges[j] -> nodes[1], name);
									}
								}
							}
						}
						node tmp=nodes[i];
						delete tmp;
					}
					else{
						cout << "No existe";
					}
				}
			}

			void removeEdge(N nodo1, N nodo2){
				for(int i=0; i<nodes.size(); i++){
					if (nodo1==(nodes[i]) -> data){
						for (int j=0; j<(nodes[i]) -> edges.size(); j++){
							if ((nodes[i]) -> edges[j] -> nodes[1] -> data==nodo2){
								edge tmp=nodes[i] -> edges[j];
								delete tmp;
							}
						}
					}
					if (node2 -> data==(nodes[i]) -> data){
						for (int j=0; j<(nodes[i]) -> edges.size(); j++){
							if ((nodes[i]) -> edges[j] -> nodes[1] -> data==nodo1){
								edge tmp=nodes[i] -> edges[j];
								delete tmp;
							}
						}
					}
					else{
						cout << "No existe";
					}
				}
			}


			~Graph(){}

};

typedef Graph<Traits> graph;


#endif
