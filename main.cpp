
#include <iostream>

#include "graph.h"

using namespace std;

int main(int argc, char *argv[]) {

  graph Graph;

  Graph.insertNode('A');
  Graph.insertNode('B');
  Graph.insertNode('C');
  Graph.imprimeNodes();
  Graph.insertEdge('A', 'B', 3, 1);
  Graph.imprimeEdges('A');
  //Graph.removeEdge('A', 'B');
  Graph.removeNode('C');
  Graph.imprimeNodes();
  // Graph.imprimeEdges('A');


  return EXIT_SUCCESS;
}
