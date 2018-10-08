
#include <iostream>

#include "graph.h"

using namespace std;

int main(int argc, char *argv[]) {

  graph Graph;

  Graph.insertNode('A');
  Graph.insertNode('B');
  Graph.insertNode('C');
  Graph.imprimeNodes();
  Graph.insertEdge('A', 'B', 1, 1);
  Graph.insertEdge('A', 'C', 1, 1);
  Graph.print();
  Graph.denso(0.6);


  return EXIT_SUCCESS;
}
