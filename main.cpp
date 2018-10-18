
#include <iostream>

#include "graph.h"

using namespace std;

int main(int argc, char *argv[]) {

  graph Graph;

  Graph.insertNode('A');
  Graph.insertNode('C');
  Graph.insertNode('D');
  Graph.insertNode('E');
  Graph.insertEdge('A', 'C', 3, 1);
  Graph.insertEdge('C', 'E', 2, 1);
  Graph.insertEdge('D', 'E', 9, 1);
  Graph.insertEdge('E', 'A', 5, 1);
  Graph.insertEdge('A', 'D', 5, 1);
  Graph.print();

  cout << "--------------" << endl;
  //cout << Graph.DFS('A');
  cout << Graph.fuerteConexo();



  return EXIT_SUCCESS;
}
