#ifndef READ_H
#define READ_H

#include <fstream>
#include "graph2.h"

/**
 * Clase de ayuda para leer el grafo desde un archivo,
 * no es necesario que la utilicen, podrían implementar su lector
 * desde su grafo o algún otro lado
 **/
template <typename G>
class Read {
	typedef typename G::N N;
	typedef typename G::E E;

	public:
		graph2 ngraph;
		Read(string file) {
			ifstream read;
			read.open("input.txt");
			int numNodos;
			int nodo1;
			int nodo2;
			bool dir;
			int peso;
			char nodo;
			double x,y;
			bool coordenadas;
			read >> numNodos >> coordenadas >> dir;
			if (coordenadas){
				for(int i = 0;i < numNodos ; i++){
						read >> nodo >> x >> y;
						ngraph.insertNode(nodo, x, y);
				}
			}
			else{
				for(int i = 0;i < numNodos ; i++){
						read >> nodo;
						ngraph.insertNode(nodo);
				}
			}
			if (dir){
				for(int j = 0; j < numNodos; j++){
					read >> nodo1 >> nodo2 >> peso;
					ngraph.insertEdge(nodo1,nodo2,peso,1);
				}
			}
			else{
				for(int j = 0; j < numNodos; j++){
					read >> nodo1 >> nodo2 >> peso;
					ngraph.insertEdge(nodo1,nodo2,peso,0);
				}
			}
    }

		graph2 getGraph() {
			return ngraph;
    }
};

typedef Read<Traits2> read;

#endif
