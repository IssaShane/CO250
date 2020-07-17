#include "graph.h"

using namespace std;

Graph::~Graph() {
  for (unsigned int i = 0; i < this->nodes.size(); i++) {
    delete this->nodes[i];
  }
}

// addNode(n) adds the pointer n to the list of Node pointers of this graph
// requires: n is not a nullptr
// effects: mutates this->nodes
// efficiency: O(1)
void Graph::addNode(Node *n) {
  this->nodes.emplace_back(n);
}

// removeNode(name) removes the node of the given name from this graph. as well
//   as from the neighbours of all of the other nodes
// effects: mutates this->nodes
// efficiency: O(n²)
void Graph::removeNode(const string &name) {
  // remove node from the outflow of all of its in-neighbours
  for (unsigned int i = 0; i < this->nodes.size(); i++) {
    // if "name" is not in nodes[i]'s outflow, it does nothing
    this->nodes[i]->removeNeighbour(name);
  }

  for (unsigned int i = 0; i < this->nodes.size(); i++) {
    if (this->nodes[i]->getName() == name) {
      Node * backup = this->nodes[i];
      this->nodes.erase(this->nodes.begin()+i);
      delete backup;
    }
  }
}

// addEdge(start, dest) adds an edge from the node start to the node dest to
//   this graph
// requires: neither start nor dest is nullptr, start is in this graph
// effects: mutates data
// efficiency: O(n)
void Graph::addEdge(Node *start, Node *dest) {
  for (unsigned int i = 0; i < this->nodes.size(); i++) {
    if (this->nodes[i] == start) {
      Edge * newedge = new Edge{start,dest,0};
      this->nodes[i]->addNeighbour(newedge);
    }
  }
}

// addEdge(start, dest) adds an edge from the node of name start to the node
//   of name dest to this graph
// requires: this graph contains a node of name start
// effects: mutates data
// efficiency: O(n)
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

// setWeight(start, dest, weight) sets the weight of the edge from start to 
//   dest to the value weight
// requires: neither start nor dest is nullptr, there exists an edge from start
//           to dest in this graph
// effects: mutates data
// efficiency: O(n²)
void Graph::setWeight(Node *start, Node *dest, const Fraction &weight) {
  for (unsigned int i = 0; i < this->nodes.size(); i++) {
    if (this->nodes[i] == start) {
      this->nodes[i]->setWeight(dest, weight);
    }
  }
}

// setWeight(start, dest, weight) sets the weight of the edge from the node
//   of name start to the node of the name dest to the value weight
// requires: neither start nor dest is nullptr, there exists an edge from start
//           to dest in this graph
// effects: mutates data
// efficiency: O(n²)
void Graph::setWeight(const string &start, const string &dest, 
  const Fraction &weight) {
  for (unsigned int i = 0; i < this->nodes.size(); i++) {
    if (this->nodes[i]->getName() == start) {
      this->nodes[i]->setWeight(dest, weight);
    }
  }
}

// removeEdge(start, dest) removes the edge from the node of name start to the
//   node of name dest
// requires: there is a node from start to dest in this graph
// effects: mutates data
// efficiency: O(n²)
void Graph::removeEdge(const string &start, const string &dest) {
  for (unsigned int i = 0; i < this->nodes.size(); i++) {
    if (this->nodes[i]->getName() == start) {
      this->nodes[i]->removeNeighbour(dest);
    }
  }
}

// incidence() gives the incidence matrix for this graph, where each row 
//   represents a node, and each column represents an arc
// requires: none
// effects: creates data
// efficiency: O(n²)
matrix Graph::incidence() const {
  matrix retval;
  vector<Edge*> arcs;
  for (unsigned int i = 0; i < this->nodes.size(); i++) {
    for (unsigned int j = 0; j < this->nodes[i]->neighbours.size(); j++) {
      arcs.emplace_back(this->nodes[i]->neighbours[j]);
    }
  }
  for (unsigned int i = 0; i < this->nodes.size(); i++) {
    vector<Fraction> row;
    for (unsigned int j = 0; j < arcs.size(); j++) {
      if (this->nodes[i] == arcs[j]->start) row.emplace_back(-1);
      else if (this->nodes[i] == arcs[j]->dest) row.emplace_back(1);
      else row.emplace_back(0);
    }
    retval.emplace_back(row);
  }
  return retval;
}

// stdipathLP(start, dest) gives an LP in SEF for the shortest directed path
//   from the node of name start to the node of name dest
// requires: this graph contains a directed path from start to dest
// effects: creates data
// efficiency: O(n²)
LP Graph::stdipathLP(const string &start, const string &dest) const {
  LP retval;
  retval.A = this->incidence();
  
  vector<Edge*> arcs;
  for (unsigned int i = 0; i < this->nodes.size(); i++) {
    //cout << "|outflow(" << this->nodes[i]->getName() << ")|: " << this->nodes[i]->neighbours.size() << endl;
    for (unsigned int j = 0; j < this->nodes[i]->neighbours.size(); j++) {
      arcs.emplace_back(this->nodes[i]->neighbours[j]);
    }
  }
  //cout << "arcs.size(): " << arcs.size() << endl;
  vector<Fraction> weights;
  for (unsigned int i = 0; i < arcs.size(); i++) {
    weights.emplace_back((-1)*arcs[i]->weight);
  }
  retval.obj = weights;
  retval.A = this->incidence();
  vector<Fraction> soln_set;
  /*
  vector<Fraction> slack_vars;
  for (unsigned int i = 0; i < retval.A.size(); i++) {
    if (this->nodes[i]->name == start) soln_set.emplace_back(-1);
    else if (this->nodes[i]->name == dest) soln_set.emplace_back(1);
    else {
      soln_set.emplace_back(0);
      slack_vars.emplace_back(0);
      vector<Fraction> newcol;
      for (unsigned int j = 0; j < this->nodes.size(); j++) {
        if (j == i) newcol.emplace_back(1);
        else newcol.emplace_back(0);
      }
      add_column(retval.A,newcol);
    }
  }*/
  for (unsigned int i = 0; i < this->nodes.size(); i++) {
    if (this->nodes[i]->getName() == start) soln_set.emplace_back(-1);
    else if (this->nodes[i]->getName() == dest) soln_set.emplace_back(1);
    else soln_set.emplace_back(0);
  }
  retval.b = soln_set;
  // add slack variables to obj function
  /*for (unsigned int i = 0; i < slack_vars.size(); i++) {
    retval.obj.emplace_back(slack_vars[i]);
  }*/
  return retval;
}

ostream &operator<<(ostream &out, const Graph &g) {
  for (unsigned int i = 0; i < g.nodes.size(); i++) {
    out << *g.nodes[i];
    if (i < g.nodes.size()-1) out << endl;
  }
  return out;
}