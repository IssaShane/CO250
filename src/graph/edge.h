#include "../lib_vector/fraction.h"

class Node;

struct Edge {
  Node *start;
  Node *dest;
  Fraction weight;
};