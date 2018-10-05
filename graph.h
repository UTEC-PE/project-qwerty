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
					if (name==(nodes[i]) -> getData()){
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
					if (nodo1==(nodes[i]) -> getData()){
						tmp=nodes[i];
						exists1=true;
					}
					if (nodo2==(nodes[i]) -> getData()){
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
				bool exists=false;
				for (int i=0; i<nodes.size(); i++){
					if (name==(nodes[i]) -> getData()){
						for (EdgeIte it=(nodes[i]) -> edges.begin(); it!=(nodes[i]) -> edges.end(); it++){
							if ((*it) ->  getDir()==0){
								for (EdgeIte it2=((*it) -> nodes[1]) -> edges.begin(); it2!=((*it) -> nodes[1]) -> edges.end(); it2++){
									if (((*it2) -> nodes[1]) -> getData()==name){
										removeEdge((((*it) -> nodes[1]) -> getData()), name);
									}
								}
							}
						}
						node* tmp=(nodes[i]);
						delete tmp;
						nodes.erase(nodes.begin()+i);
						exists=true;
					}
				}
				if (!exists){
					cout << "No existe ";
				}
			}

			void removeEdge(N nodo1, N nodo2){
				bool exists=false;
				for(int i=0; i<nodes.size(); i++){
					if (nodo1==(nodes[i]) -> getData()){
						for (EdgeIte it=(nodes[i]) -> edges.begin(); it!=(nodes[i]) -> edges.end(); it++){
							if (((*it) -> nodes[1]) -> getData()==nodo2){
								edge *tmp=(*it);
								delete tmp;
								exists=true;
							}
						}
					}
					if (nodo2==(nodes[i]) -> getData()){
						for (EdgeIte it=(nodes[i]) -> edges.begin(); it!=(nodes[i]) -> edges.end(); it++){
							if (((*it) -> nodes[1]) -> getData()==nodo1){
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
				cout << "Nodes: ";
				for (int i=0; i<nodes.size(); i++){
					cout << (nodes[i]) -> getData() << " ";
				}
				cout << endl;
			}

			void imprimeEdges(N nodo){
				cout << "Edges de " << nodo << ": ";
				for (int i=0; i< nodes.size(); i++){
					if (nodo==(nodes[i]) -> getData()){
						cout << (nodes[i]) -> edges.size() << " ";
					}
				}
				cout << endl;
			}

			// ~Graph(){
			// 	for (int i=0; i<nodes.size(); i++){
			// 		removeNode((nodes[i]) -> getData());
			// 	}
			// }

};

typedef Graph<Traits> graph;


#endif
