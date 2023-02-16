/*
  Copyright (c) 2021
  Swarthmore College Computer Science Department, Swarthmore PA
  J. Brody, S. Caplan, A. Danner, L. Meeden, Z. Palmer, A. Soni, M. Wehar
  Distributed as course material for Fall 2021
  CPSC 035: Data Structures and Algorithms
*/

#include "adts/stlStack.h"
#include "adts/stlQueue.h"
#include "adts/stlHashTable.h"
#include "adts/stlMinPriorityQueue.h"
#include <stdexcept>

template <typename V, typename E, typename W>
bool reachableDFS(V src, V dest, Graph<V, E, W>* g) {
    STLStack<V>* frontier = new STLStack<V>();
    STLHashTable<V,int>* visited = new STLHashTable<V,int>();
    frontier->push(src);
    visited->insert(src, 0);
    while (!frontier->isEmpty()){
      V current = frontier->pop();
      if (current == dest){
        return true;
      }
      vector<V> neb = g->getNeighbors(current);
      for (int i = 0; i < neb.size(); i++){
        if (!visited->contains(neb[i])){
          frontier->push(neb[i]);
          visited->insert(neb[i], 0);
        }
      }
    }
    return false;
    //throw runtime_error("Not yet implemented: reachableDFS");
}

template <typename V, typename E, typename W>
vector<V> shortestLengthPathBFS(V src, V dest, Graph<V, E, W>* g) {
    STLQueue<V>* frontier = new STLQueue<V>();
    STLHashTable<V, V>* prev = new STLHashTable<V, V>();
    frontier->enqueue(src);
    prev->insert(src, src);
    while (!frontier->isEmpty()){
      V current = frontier->dequeue();
      if (current == dest){
        vector<V> path;
        path.push_back(current);
        V cur = prev->get(current);
        while (!(cur == src)){
          path.push_back(cur);
          cur = prev->get(cur);
        }
        path.push_back(cur);
        return path;
      }
      vector<V> neb = g->getNeighbors(current);
      for (int i = 0; i < neb.size(); i++) {
        if (!prev->contains(neb[i])){
          prev->insert(neb[i], current);
          frontier->enqueue(neb[i]);
        }
      }
    }
    vector<V> nopath;
    return nopath;
    //throw runtime_error("Not yet implemented: shortestLengthPathBFS");
}

template <typename V, typename E, typename W>
Dictionary<V, W>* singleSourceShortestPath(V src, Graph<V, E, W>* g) {
  STLMinPriorityQueue<W, V>* frontier = new STLMinPriorityQueue<W, V>();
  Dictionary<V, int>* costs = new STLHashTable<V, int>();
  frontier->insert(0, src);
  costs->insert(src, 0);
  while (!frontier->isEmpty()){
    V current = frontier->remove();
    vector<Edge<V, E, W>> outedge = g->getOutgoingEdges(src);
    for (int i = 0; i < outedge.size(); i++){
      V neighbor = outedge[i].getDestination();
      W stepCost = outedge[i].getWeight();
      W newCost = costs->get(current) + stepCost;
      if (!(costs->contains(neighbor))){
        frontier->insert(newCost, neighbor);
        costs->insert(neighbor, newCost);
      }else if (costs->get(neighbor) > newCost){
        frontier->insert(newCost, neighbor);
        costs->update(neighbor, newCost);
      }
    }
  }
  return costs;
    //throw runtime_error("Not yet implemented: singleSourceShortestPath");
}
