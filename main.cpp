#include <iostream>

#include "graph2.h"

using namespace std;

int main(int argc, char *argv[]) {

  graph2 Graph;

  Graph.insertNode('A');
  Graph.insertNode('B');
  Graph.insertNode('C');
  Graph.insertNode('D');
  Graph.insertNode('S');

  Graph.insertEdge('S', 'A', 6, 1);
  Graph.insertEdge('S', 'C', 7, 1);
  Graph.insertEdge('A', 'B', 5, 1);
  Graph.insertEdge('A', 'D', -4, 1);
  Graph.insertEdge('A', 'C', 8, 1);
  Graph.insertEdge('B', 'A', -2, 1);
  Graph.insertEdge('C', 'B', -3, 1);
  Graph.insertEdge('C', 'D', 9, 1);
  Graph.insertEdge('D', 'S', 8, 1);
  Graph.insertEdge('D', 'B', 7, 1);

  // auto mymatrices = Graph.floydWarshall();
  // for (int i = 0; i < 5; i++){
  //     for (int j = 0; j < 5; j++){
  //         if (mymatrices.first[i][j] == INF)
  //             cout << setw(5) << "INF";
  //         else
  //             cout << setw(5) << mymatrices.first[i][j];
  //     }
  //     cout <<  endl;
  // }
  // cout << endl;
  // for (int i = 0; i < 5; i++){
  //     for (int j = 0; j < 5; j++){
  //           cout << setw(5) << mymatrices.second[i][j];
  //     }
  //     cout <<  endl;
  // }
  auto bellman = Graph.bellMan('S');
  for (auto& t : bellman){
  	cout << t.first << " "<< t.second << "\n";
  }



  return EXIT_SUCCESS;
}
