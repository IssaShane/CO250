#ifndef GRAPH_H
#define GRAPH_H

#include "./node.h"

class Graph {
  private:
    std::vector<Node*> nodes;

  public:
    void addNode(Node*);
    void addEdge(Node*,Node*);
    void addEdge(const std::string&, const std::string&);
    void setWeight(Node*,Node*,const Fraction&);
    void setWeight(const std::string&, const std::string&, const Fraction&);

    friend std::ostream& operator<<(std::ostream&,const Graph&);
};

std::ostream& operator<<(std::ostream&,const Graph&);

#endif