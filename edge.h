#ifndef EDGE_H
#define EDGE_H

#include "node.h"

template <typename G>
class Edge {
    public:
        typedef typename G::E E;
        typedef typename G::node node;

        node* nodes[2];

    private:
        E data;
        bool dir;

    public:
      Edge(node* nodo1, node* nodo2, E value, bool dir):data(value), dir(dir){
        nodes[0]=nodo1;
        nodes[1]=nodo2;
      };
};

#endif
