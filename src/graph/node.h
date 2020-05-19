#ifndef NODE_H
#define NODE_H

#include "../simplex/simplex.h"
#include <string>
#include "edge.h"

class Node {
  private:
    std::vector<Edge*> neighbours;
    std::string name;
  
  public:
    Node(std::string);
    Node(std::string, Edge*);
    ~Node();
    void addNeighbour(Node*);
    void addNeighbour(Node*,bool);
    void addNeighbour(Edge*);
    void addNeighbour(const std::string&);
    void removeNeighbour(Node*);
    void setWeight(Node*, const Fraction &);
    void setWeight(const string&, const Fraction &);
    friend std::ostream &operator<<(std::ostream&,const Node&);

    std::string getName() const;
};

std::ostream &operator<<(std::ostream&,const Node&);


#endif