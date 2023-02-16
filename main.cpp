/*
  Copyright (c) 2021
  Swarthmore College Computer Science Department, Swarthmore PA
  J. Brody, S. Caplan, A. Danner, L. Meeden, Z. Palmer, A. Soni, M. Wehar
  Distributed as course material for Fall 2021
  CPSC 035: Data Structures and Algorithms
*/
#include <string>
#include <iostream>
#include "adjacencyListUndirectedGraph.h"
#include "adts/graph.h"
#include "adjacencyListGraph.h"
#include "graphAlgorithms.h"
#include "adts/stlHashTable.h"
#include "adts/stlStack.h"
#include "adts/stlQueue.h"
using namespace std;


void addvertices(AdjacencyListUndirectedGraph<string,string,int>* map);
void addedges(AdjacencyListUndirectedGraph<string,string,int>* map);
void printmessage();
int main() {
  // TO DO: implement the main program here
  AdjacencyListUndirectedGraph<string,string,int>* map = new AdjacencyListUndirectedGraph<string,string,int>();
  addvertices(map);
  addedges(map);
  printmessage();
  int choice;
  cin >> choice;
  if (!(choice >= 0 && choice <= 3)) {
    throw runtime_error("not valid");
  } else if (choice == 1){
      string src;
      cout << "Enter a starting point: ";
      cin >> src;
      string dest;
      cout << "Enter a destination: ";
      cin >> dest;
      bool result = reachableDFS(src, dest, map);
      if (result == true){
        cout << dest << " is reachable from " << src << endl;
      } else {
      cout << "not reachable" << endl;
      }
    } else if (choice == 2){
        string src;
        cout << "Enter a starting point: ";
        cin >> src;
        string dest;
        cout << "Enter a destination: ";
        cin >> dest;
        vector<string> path = shortestLengthPathBFS(src, dest, map);
        if (!(path.size() == 0)){
          cout << "The path is as follows: ";
          for (int i = path.size(); i > 0; i--) {
            cout << path[i-1] << " ";
          }
        cout << endl;
        }
    } else if (choice == 3) {
        string src;
        cout << "Enter a starting point: ";
        cin >> src;
        Dictionary<string,int>* costs = singleSourceShortestPath(src, map);
        vector<pair<string,int>> lst = costs->getItems();
        for (int i = 0; i<lst.size(); i++) {
          cout << lst[i].first << ":" << lst[i].second << " " << endl;
        }
    }
}

void addvertices(AdjacencyListUndirectedGraph<string,string,int>* map) {
  map->insertVertex("SCI");
  map->insertVertex("SING");
  map->insertVertex("TROT");
  map->insertVertex("BER");
  map->insertVertex("KOHL");
  map->insertVertex("PAR");
  map->insertVertex("LPAC");
  map->insertVertex("MAR");
  map->insertVertex("SHAR");
  map->insertVertex("CLOT");
  map->insertVertex("WHAR");
}
void addedges(AdjacencyListUndirectedGraph<string,string,int>* map) {
  map->insertEdge("SCI", "SING", "p1", 3);
  map->insertEdge("SING", "TROT", "p2", 5);
  map->insertEdge("SCI", "BER", "p3", 4);
  map->insertEdge("SING", "BER", "p4", 2);
  map->insertEdge("SCI", "MAR", "p5", 6);
  map->insertEdge("MAR", "LPAC", "p6", 3);
  map->insertEdge("LPAC", "KOHL", "p7", 2);
  map->insertEdge("BER", "KOHL", "p8", 2);
  map->insertEdge("PAR", "KOHL", "p9", 4);
  map->insertEdge("TROT", "KOHL", "p10", 3);
  map->insertEdge("SHAR", "CLOT", "p11", 4);
  map->insertEdge("WHAR", "SHAR", "p12", 5);
  map->insertEdge("CLOT", "WHAR", "p13", 4);
}
void printmessage() {
  cout << "Let's explore Swarthmore's campus" << endl;
  cout << "1. Reachability from one building to another" << endl;
  cout << "2. Shortest length path from one building to another" << endl;
  cout << "3. Distances from one building to all other reachable buildings" << endl;
  cout << "4. Quit" << endl;
  cout << "Choice: ";
}
