#ifndef GRAPH_H
#define GRAPH_H

#include "./node.h"

class Graph {
  private:
    std::vector<Node*> nodes;

  public:
    ~Graph();
    void addNode(Node*);
    void removeNode(const std::string&);
    void addEdge(Node*,Node*);
    void addEdge(const std::string&, const std::string&);
    void setWeight(Node*,Node*,const Fraction&);
    void setWeight(const std::string&, const std::string&, const Fraction&);
    void removeEdge(const std::string&, const std::string&);

    friend std::ostream& operator<<(std::ostream&,const Graph&);
};

std::ostream& operator<<(std::ostream&,const Graph&);

#endif