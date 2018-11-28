#include <iostream>
#include <thread>
#include "graph2.h"

using namespace std;

int main(int argc, char *argv[]) {

  graph2 Graph;

  Graph.insertNode('A', 0, 0);
  Graph.insertNode('B', 1, 2);
  Graph.insertNode('C', 1, 0);
  Graph.insertNode('D', 1, -2);
  Graph.insertNode('E', 3, 2);
  Graph.insertNode('F', 3, 0);
  Graph.insertNode('G', 3, -2);
  Graph.insertNode('H', 5, -2);
  Graph.insertNode('I', 5, 0);

  Graph.insertEdge('A', 'B', 5, 1);
  Graph.insertEdge('A', 'C', 25, 1);
  Graph.insertEdge('B', 'E', 11, 1);
  Graph.insertEdge('B', 'F', 33, 1);
  Graph.insertEdge('C', 'D', 17, 1);
  Graph.insertEdge('C', 'F', 38, 1);
  Graph.insertEdge('D', 'G', 12, 1);
  Graph.insertEdge('E', 'F', 21, 1);
  Graph.insertEdge('E', 'I', 1, 1);
  Graph.insertEdge('F', 'D', 4, 1);
  Graph.insertEdge('F', 'G', 3, 1);
  Graph.insertEdge('G', 'H', 50, 1);
  Graph.insertEdge('H', 'F', 41, 1);
  Graph.insertEdge('I', 'F', 2, 1);
  Graph.insertEdge('I', 'H', 14, 1);

  cout << "Floi" << endl;
  auto mymatrices = Graph.floydWarshall();
  for (int i = 0; i < 9; i++){
      for (int j = 0; j < 9; j++){
          if (mymatrices.first[i][j] == INF)
              cout << setw(5) << "INF";
          else
              cout << setw(5) << mymatrices.first[i][j];
      }
      cout <<  endl;
  }
  cout << endl;
  for (int i = 0; i < 9; i++){
      for (int j = 0; j < 9; j++){
            cout << setw(5) << mymatrices.second[i][j];
      }
      cout <<  endl;
  }
  cout << " ========================================================" << endl;
  cout << "Boiman" << endl;

  auto bellman = Graph.bellMan('A');
  for (auto& t : bellman){
  	cout << t.first << " "<< t.second << "\n";
  }
  cout << " ========================================================" << endl;
  cout << "Guriido" << endl;

  auto greedy = Graph.greedyBFS('A', 'I');
  for (auto g : greedy){
    cout << g.first << " " << g.second << endl;
  }

  cout << " ========================================================" << endl;
  cout << "BigD" << endl;

  map<char, int> Dijkstra = Graph.Dijkstra('A');
  for (auto g : Dijkstra){
    if (g.second==INF){
      cout << g.first << " " << "INF" << endl;
    }
    else{
      cout << g.first << " " << g.second << endl;
    }

  }

  cout << " ========================================================" << endl;
  cout << "Esther" << endl;

  

  list<char> path = Graph.Astar('A','H').second;
  for(list<char>::iterator it = path.begin(); it != path.end(); ++it)
    cout << (*it) << " ";
  cout << Graph.Astar('A','H').first;


  return EXIT_SUCCESS;
}
