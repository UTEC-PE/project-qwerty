#include <iostream>

#include "read.h"

using namespace std;

int main(int argc, char *argv[]) {

  read readGraph("input.txt");
  graph2 Graph = readGraph.getGraph();

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
  // auto bellman = Graph.bellMan('S');
  // for (auto& t : bellman){
  // 	cout << t.first << " "<< t.second << "\n";
  // }



  return EXIT_SUCCESS;
}
