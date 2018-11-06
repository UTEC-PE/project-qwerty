
#include <iostream>

#include "graph.h"
#include "graph2.h"

using namespace std;

int main(int argc, char *argv[]) {

  graph2 Graph;

  Graph.insertNode('A');
  Graph.insertNode('B');
  Graph.insertNode('C');
  Graph.insertNode('D');
  Graph.insertNode('E');

  Graph.insertEdge('A', 'C', 6, 1);
  Graph.insertEdge('B', 'A', 3, 1);
  Graph.insertEdge('A', 'D', 3, 1);
  Graph.insertEdge('C', 'D', 2, 1);
  Graph.insertEdge('D', 'C', 1, 1);
  Graph.insertEdge('D', 'B', 1, 1);
  Graph.insertEdge('E', 'B', 4, 1);
  Graph.insertEdge('E', '4', 2, 1);

  Graph.floydWarshall();

  Graph.pqq();


  return EXIT_SUCCESS;
}
