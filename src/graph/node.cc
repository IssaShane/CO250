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

void Node::addNeighbour(Node* n) {
  Edge* newedge = new Edge{this,n,0};
  this->neighbours.emplace_back(newedge);
}

void Node::addNeighbour(Node *n, bool isdest) {
  Edge* newedge;
  if (isdest) newedge = new Edge{this,n,0};
  else newedge = new Edge{n,this,0};
  this->neighbours.emplace_back(newedge);
}

void Node::addNeighbour(Edge *e) {
  this->neighbours.emplace_back(e);
}

void Node::addNeighbour(const string &name) {
  
}

void Node::removeNeighbour(Node *n) {
  for (unsigned int i = 0; i < this->neighbours.size(); i++) {
    if (this->neighbours[i]->dest == n) {
      this->neighbours.erase(this->neighbours.begin()+i);
    }
  }
}

void Node::removeNeighbour(const string &name) {
  for (unsigned int i = 0; i < this->neighbours.size(); i++) {
    if (this->neighbours[i]->dest->getName() == name) {
      Edge *backup = this->neighbours[i];
      this->neighbours.erase(this->neighbours.begin()+i);
      delete backup;
    }
  }
}

void Node::setWeight(Node *n, const Fraction &weight) {
  for (unsigned int i = 0; i < this->neighbours.size(); i++) {
    if (this->neighbours[i]->dest == n) {
      this->neighbours[i]->weight = weight;
    }
  }
}

void Node::setWeight(const string &name, const Fraction &weight) {
  for (unsigned int i = 0; i < this->neighbours.size(); i++) {
    if (this->neighbours[i]->dest->getName() == name) {
      this->neighbours[i]->weight = weight;
    }
  }
}

string Node::getName() const { return this->name; }

ostream & operator<<(ostream &out, const Node &n) {
  out << n.name << ":" << endl;
  for (unsigned int i = 0; i < n.neighbours.size(); i++) {
    out << n.neighbours[i]->start->name << "-"; 
    out << n.neighbours[i]->weight << "->";
    out << n.neighbours[i]->dest->name;
    if (i < n.neighbours.size()-1) out << endl;
  }
  return out;
}