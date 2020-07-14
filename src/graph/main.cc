#include "graph.h"
#include <string>

using namespace std;

int main() {
  string cmd;
  vector<Graph*> graphs;
  for (unsigned int i = 0; i < 4; i++) graphs.emplace_back(nullptr);
  while (true) {
    cin >> cmd;
    if (cmd == "q" || cmd == "quit") {
      break;
    }
    else if (cmd == "new") {
      char c;
      cin >> c;
      graphs[c-'a'] = new Graph();
    }
    else if (cmd == "addnode") {
      char c;
      cin >> c;
      string name;
      cin >> name;
      graphs[c-'a']->addNode(new Node{name});
    }
    else if (cmd == "addarc") {
      char c;
      string startnode;
      string destnode;
      cin >> c;
      cin >> startnode;
      cin >> destnode;
      graphs[c-'a']->addEdge(startnode,destnode);
    }
    else if (cmd == "setweight") {
      char c;
      string startnode;
      string destnode;
      Fraction weight;
      cin >> c;
      cin >> startnode;
      cin >> destnode;
      cin >> weight;
      graphs[c-'a']->setWeight(startnode,destnode,weight);
    }
    else if (cmd == "print") {
      char c;
      cin >> c;
      cout << *graphs[c-'a'] << endl;
    }
    else if (cmd == "removearc") {
      char c;
      string startnode;
      string destnode;
      cin >> c;
      cin >> startnode;
      cin >> destnode;
      graphs[c-'a']->removeEdge(startnode,destnode);
    }
    else if (cmd == "removenode") {
      char c;
      string name;
      cin >> c;
      cin >> name;
      graphs[c-'a']->removeNode(name);
    }
    else if (cmd == "incidence") {
      char c;
      matrix inc;
      cin >> c;
      inc = graphs[c-'a']->incidence();
      cout << inc << endl;
    }
    else if (cmd == "dipathLP") {
      char c;
      LP lp;
      cin >> c;
      string s, t;
      cin >> s;
      cin >> t;
      lp = graphs[c-'a']->stdipathLP(s,t);
      LP_simplify(lp);
      cout << lp << endl;
    }
  }
  for (unsigned int i = 0; i < 4; i++) delete graphs[i];
  return 0;
}