#include "node.h"

using namespace std;

Node::Node(string name) {
  this->name = name;
}

Node::Node(string name, Edge* e) {
  this->name = name;
  this->neighbours.emplace_back(e);
}

Node::~Node() { 
  for (unsigned int i = 0; i < this->neighbours.size(); i++)
    delete this->neighbours[i];
}

// addNeighbour(n) adds a pointer to an edge from this node to n 
//   with a weight of zero to this->neighbours, which represents
//   the outflow of this node
// requires: n is not nullptr
// effects: mutates data, creates data
// efficiency: O(1)
void Node::addNeighbour(Node* n) {
  Edge* newedge = new Edge{this,n,0};
  this->neighbours.emplace_back(newedge);
}

// addNeighbour(n, isdest) adds a pointer to an edge to this->neighbours,
//   where n is in the outflow of this node iff isdest == true
// requires: n is not nullptr
// effects: mutates data, creates data
// efficiency: O(1)
void Node::addNeighbour(Node *n, bool isdest) {
  Edge* newedge;
  if (isdest) newedge = new Edge{this,n,0};
  else newedge = new Edge{n,this,0};
  this->neighbours.emplace_back(newedge);
}

// addNeighbour(e) adds the edge pointer e to this->neighbours
// requires: e is not nullptr
// effects: mutates data
// efficiency: O(1)
void Node::addNeighbour(Edge *e) {
  this->neighbours.emplace_back(e);
}

// addNeighbour(name) adds a new node with the given name as a neighbour to
//   this node
// effects: creates and mutates data
// efficiency: O(1)
void Node::addNeighbour(const string &name) {
  Node *new_node = new Node{name};
  this->addNeighbour(new_node);
}

// removeNeighbour(n) removes n from the outflow of this node
// requires: n is not nullptr, n is in the outflow of this node
// effects: mutates data
// efficiency: O(n)
void Node::removeNeighbour(Node *n) {
  for (unsigned int i = 0; i < this->neighbours.size(); i++) {
    if (this->neighbours[i]->dest == n) {
      this->neighbours.erase(this->neighbours.begin()+i);
    }
  }
}

// removeNeighbour(n) removes the node of name from the outflow of this node
// requires: the node of name is in the outflow of this node
// effects: mutates data
// efficiency: O(n)
void Node::removeNeighbour(const string &name) {
  for (unsigned int i = 0; i < this->neighbours.size(); i++) {
    if (this->neighbours[i]->dest->getName() == name) {
      Edge *backup = this->neighbours[i];
      this->neighbours.erase(this->neighbours.begin()+i);
      delete backup;
    }
  }
}

// setWeight(n, weight) sets the weight of the edge from this node to n to weight
// requires: n is not nullptr, weight is a valid fraction
// effects: mutates data
// efficiency: O(n)
void Node::setWeight(Node *n, const Fraction &weight) {
  for (unsigned int i = 0; i < this->neighbours.size(); i++) {
    if (this->neighbours[i]->dest == n) {
      this->neighbours[i]->weight = weight;
    }
  }
}

// setWeight(name, weight) sets the weight of the edge from this node to the 
//   node of the given name to weight
// requires: weight is a valid fraction
// effects: mutates data
// efficiency: O(n)
void Node::setWeight(const string &name, const Fraction &weight) {
  for (unsigned int i = 0; i < this->neighbours.size(); i++) {
    if (this->neighbours[i]->dest->getName() == name) {
      this->neighbours[i]->weight = weight;
    }
  }
}

string Node::getName() const { return this->name; }

ostream & operator<<(ostream &out, const Node &n) {
  out << n.name << ":";
  if (n.neighbours.empty()) out << " no outflow";
  else out << endl;
  for (unsigned int i = 0; i < n.neighbours.size(); i++) {
    out << n.neighbours[i]->start->name << "-"; 
    out << n.neighbours[i]->weight << "->";
    out << n.neighbours[i]->dest->name;
    if (i < n.neighbours.size()-1) out << endl;
  }
  return out;
}