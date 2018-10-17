
#include <iostream>

#include "graph.h"

using namespace std;

int main(int argc, char *argv[]) {

  graph Graph;

  Graph.insertNode('A');
  Graph.insertNode('B');
  Graph.insertNode('C');
  Graph.insertNode('D');
  Graph.insertNode('E');
  Graph.insertNode('N');
  Graph.imprimeNodes();
  Graph.insertEdge('A', 'B', 1, 1);
  Graph.insertEdge('A', 'C', 1, 1);
  Graph.insertEdge('C', 'E', 1, 1);
  Graph.insertEdge('D', 'E', 1, 1);

  Graph.print();
  cout << Graph.denso(0.6)<< endl;
  Graph.BFS('C');
  cout << Graph.findNode('C') << endl;
  cout << Graph.findEdge('A', 'M') << endl;


  return EXIT_SUCCESS;
}
