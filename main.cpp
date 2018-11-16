#include <iostream>

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

  auto mymatrices = Graph.floydWarshall();
  for (int i = 0; i < 5; i++){
      for (int j = 0; j < 5; j++){
          if (mymatrices.first[i][j] == INF)
              cout << setw(5) << "INF";
          else
              cout << setw(5) << mymatrices.first[i][j];
      }
      cout <<  endl;
  }
  cout << endl;
  for (int i = 0; i < 5; i++){
      for (int j = 0; j < 5; j++){
            cout << setw(5) << mymatrices.second[i][j];
      }
      cout <<  endl;
  }


  return EXIT_SUCCESS;
}
