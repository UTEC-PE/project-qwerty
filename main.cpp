
#include <iostream>

#include "graph.h"

using namespace std;

int main(int argc, char *argv[]) {

  graph Graph;

  Graph.insertNode('A');
  Graph.insertNode('B');
  Graph.insertNode('C');
  Graph.imprimeNodes();
  Graph.insertEdge('A', 'B', 1, 0);
  Graph.insertEdge('A', 'C', 1, 0);
  Graph.print();
  Graph.denso(0.6);
  Graph.fuente_hundido();
  Graph.BFS('B');
  Graph.findNode('A');
  cout << Graph.findNode('C');
  cout << Graph.findEdge('A', 'M');


  return EXIT_SUCCESS;
}
