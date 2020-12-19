#include <iostream>
# include "graph.h"

using namespace std;

int Node::count = 0;

void Node::print_adj() {
  cout << "index: " << index << endl;
  for (auto &it : adj) {
    cout << *it << " ";
  }
  cout << endl;
}

void Node::print_fanin() {
  cout << "index: " << index << endl;
  for (auto &it : fanin) {
    cout << *it << " ";
  }
  cout << endl;
}

void Node::print_fanout() {
  cout << "index: " << index << endl;
  for (auto &it : fanout) {
    cout << *it << " ";
  }
  cout << endl;
}

ostream& operator<<(ostream& os, const Node& node) {
  os << node.index;
}




void Graph::init(char type, int v, int e) {
  graph_type = type;
  V = v;
  E = e;
  nodes = new Node[e];
  weight = new int16_t*[v];
  for (int i = 0; i < v; i++) {
    weight[i] = new int16_t[v];
    for (int j = 0; j < v; j++) {
      weight[i][j] = 101;
    }
  }
}

void Graph::add_edge(int s, int t, int w) {
  switch (graph_type) {
    case 'u':
      nodes[s].adj.push_back(&nodes[t]);
      nodes[t].adj.push_back(&nodes[s]);
      weight[s][t] = int8_t(w);
      weight[t][s] = int8_t(w);
      break;
    case 'd':
      nodes[s].fanin.push_back(&nodes[t]);
      nodes[t].fanout.push_back(&nodes[s]);
      weight[s][t] = w;
      break;
    default:
      cerr << "sth wrong!" << endl;
  }
}

void Graph::print_weight() {
  cout << "weight: " << endl;
  for (int i = 0; i < V; ++i) {
    for (int j = 0; j < V; ++j) {
      cout << " " << weight[i][j];
    }
    cout << endl;
  }
}

void Graph::print_edge() {
  cout << "edge: " << endl;
  for (int i = 0; i < V; ++i) {
    switch(graph_type) {
      case 'u':
        nodes[i].print_adj();
        break;
      case 'd':
        nodes[i].print_fanin();
        nodes[i].print_fanout();
    }
  }
}