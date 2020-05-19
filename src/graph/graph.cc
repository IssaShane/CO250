#include "graph.h"

using namespace std;

void Graph::addNode(Node *n) {
  this->nodes.emplace_back(n);
}

void Graph::addEdge(Node *start, Node *dest) {
  for (unsigned int i = 0; i < this->nodes.size(); i++) {
    if (this->nodes[i] == start) {
      Edge * newedge = new Edge{start,dest,0};
      this->nodes[i]->addNeighbour(newedge);
    }
  }
}

void Graph::addEdge(const string &start, const string &dest) {
  Node *destnode;
  for (unsigned int i = 0; i < this->nodes.size(); i++) {
    if (this->nodes[i]->getName() == dest) destnode = this->nodes[i];
  }

  for (unsigned int i = 0; i < this->nodes.size(); i++) {
    if (this->nodes[i]->getName() == start) {
      this->nodes[i]->addNeighbour(destnode);
    }
  }
}

void Graph::setWeight(Node *start, Node *dest, const Fraction &weight) {
  for (unsigned int i = 0; i < this->nodes.size(); i++) {
    if (this->nodes[i] == start) {
      this->nodes[i]->setWeight(dest, weight);
    }
  }
}

void Graph::setWeight(const string &start, const string &dest, 
  const Fraction &weight) {
  for (unsigned int i = 0; i < this->nodes.size(); i++) {
    if (this->nodes[i]->getName() == start) {
      this->nodes[i]->setWeight(dest, weight);
    }
  }
}

ostream &operator<<(ostream &out, const Graph &g) {
  for (unsigned int i = 0; i < g.nodes.size(); i++) {
    out << *g.nodes[i] << endl;
  }
  return out;
}