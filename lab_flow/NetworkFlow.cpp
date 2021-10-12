/**
 * @file NetworkFlow.cpp
 * CS 225: Data Structures
 */

#include <vector>
#include <algorithm>
#include <set>

#include "graph.h"
#include "edge.h"

#include "NetworkFlow.h"

int min(int a, int b) {
  if (a<b)
    return a;
  else return b;
}



const Graph & NetworkFlow::calculateFlow() {
  // YOUR CODE HERE
  vector<Vertex> vertex_;
  while (findAugmentingPath(source_, sink_, vertex_)) 
  {
    int temp = pathCapacity(vertex_);
    for (unsigned x = 1; x < vertex_.size(); x++) 
    {
      if (flow_.edgeExists(vertex_[x - 1], vertex_[x]) == false) 
      {
        flow_.setEdgeWeight(vertex_[x], vertex_[x - 1], flow_.getEdgeWeight(vertex_[x], vertex_[x - 1]) - temp);
      }
      else 
      {
        flow_.setEdgeWeight(vertex_[x - 1], vertex_[x], flow_.getEdgeWeight(vertex_[x - 1], vertex_[x]) + temp);
      }
      residual_.setEdgeWeight(vertex_[x - 1], vertex_[x], residual_.getEdgeWeight(vertex_[x - 1], vertex_[x]) - temp);
      residual_.setEdgeWeight(vertex_[x], vertex_[x - 1], residual_.getEdgeWeight(vertex_[x], vertex_[x - 1]) + temp);
    }
  }
  int best = 0;
  vector<Edge> edg_ = flow_.getEdges();
  for (Edge edge : edg_) 
  {
    if (edge.source == source_) 
    {
      best = best+edge.getWeight();
    }
  }
  maxFlow_ = best;
  return flow_;
}



NetworkFlow::NetworkFlow(Graph & startingGraph, Vertex source, Vertex sink) :
  g_(startingGraph), residual_(Graph(true,true)), flow_(Graph(true,true)), source_(source), sink_(sink) {

  // YOUR CODE HERE
    vector<Vertex> vex_ = g_.getVertices();
    for (Vertex vertex : vex_) 
    {
      flow_.insertVertex(vertex);
      residual_.insertVertex(vertex);
    }

    vector<Edge> edg_ = g_.getEdges();
    for (Edge edge : edg_) 
    {
      flow_.insertEdge(edge.source, edge.dest);
      residual_.insertEdge(edge.dest, edge.source);
      residual_.insertEdge(edge.source, edge.dest);
      residual_.setEdgeWeight(edge.source, edge.dest, edge.getWeight());
      residual_.setEdgeWeight(edge.dest, edge.source, 0);
      flow_.setEdgeWeight(edge.source, edge.dest, 0);
    }

}

  /**
   * findAugmentingPath - use DFS to find a path in the residual graph with leftover capacity.
   *  This version is the helper function.
   *
   * @param source  The starting (current) vertex
   * @param sink    The destination vertex
   * @param path    The vertices in the path
   * @param visited A set of vertices we have visited
   */

bool NetworkFlow::findAugmentingPath(Vertex source, Vertex sink, 
  std::vector<Vertex> &path, std::set<Vertex> &visited) {

  if (visited.count(source) != 0)
    return false;
  visited.insert(source);

  if (source == sink) {
    return true;
  }

  vector<Vertex> adjs = residual_.getAdjacent(source);
  for(auto it = adjs.begin(); it != adjs.end(); it++) {
    if (visited.count(*it) == 0 && residual_.getEdgeWeight(source,*it) > 0) {
      path.push_back(*it);
      if (findAugmentingPath(*it,sink,path,visited))
        return true;
      else {
        path.pop_back();
      }
    }
  }

  return false;
}

  /**
   * findAugmentingPath - use DFS to find a path in the residual graph with leftover capacity.
   *  This version is the main function.  It initializes a set to keep track of visited vertices.
   *
   * @param source The starting (current) vertex
   * @param sink   The destination vertex
   * @param path   The vertices in the path
   */

bool NetworkFlow::findAugmentingPath(Vertex source, Vertex sink, std::vector<Vertex> &path) {
   std::set<Vertex> visited;
   path.clear();
   path.push_back(source);
   return findAugmentingPath(source,sink,path,visited);
}

  /**
   * pathCapacity - Determine the capacity of a path in the residual graph.
   *
   * @param path   The vertices in the path
   */

int NetworkFlow::pathCapacity(const std::vector<Vertex> & path) const {
  // YOUR CODE HERE
  int capacity_ = residual_.getEdgeWeight(path[0], path[1]);
  for (unsigned i = 1; i < path.size() - 1; i++) 
  {
    if (capacity_ > residual_.getEdgeWeight(path[i], path[i + 1])) 
    {
      capacity_ = residual_.getEdgeWeight(path[i], path[i + 1]);
    }
  }
  return capacity_;

}

  /**
   * calculuateFlow - Determine the capacity of a path in the residual graph.
   * Sets the member function `maxFlow_` to be the flow, and updates the
   * residual graph and flow graph according to the algorithm.
   *
   * @return The network flow graph.
   */

int NetworkFlow::getMaxFlow() const {
  return maxFlow_;
}

const Graph & NetworkFlow::getGraph() const {
  return g_;
}

const Graph & NetworkFlow::getFlowGraph() const {
  return flow_;
}

const Graph & NetworkFlow::getResidualGraph() const {
  return residual_;
}

