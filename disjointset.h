#ifndef DISJOINTSET_H
#define DISJOINTSET_H

#include "node.h"
#include <vector>
using namespace std;

template <typename G>
struct DisjointSet {

    typedef typename G::node node;
    typedef typename G::NodeSeq NodeSeq;

    NodeSeq parent;
    int *rank;
    int size;


    DisjointSet(NodeSeq nodes):size(nodes.size()){
        rank = new int[size];
        parent = nodes;
        *rank = {0};
    };

    int getPosition(node* nodo) {
        for (int i = 0; i < size; i++) {
            if (nodo == parent[i])
                return i;
        }
    }

    node* findParent(node* nodo) {
        if (nodo != parent[getPosition(nodo)])
            parent[getPosition(nodo)] = findParent(parent[getPosition(nodo)]);
        return parent[getPosition(nodo)];
    }

    void mergeSet(node* nodo1, node* nodo2) {
        nodo1 = findParent(nodo1);
        nodo2 = findParent(nodo2);
        if (rank[getPosition(nodo1)] > rank[getPosition(nodo2)])
            parent[getPosition(nodo2)] = nodo1;
        else
            parent[getPosition(nodo1)] = nodo2;
        if (rank[getPosition(nodo1)] == rank[getPosition(nodo2)])
            rank[getPosition(nodo2)]++;
    }
};

#endif
