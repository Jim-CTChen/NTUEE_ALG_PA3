#ifndef GRAPH_H
#define GRAPH_H

#include <vector>

using namespace std;

class Node {
  public:
    Node() {
      index = count;
      count++;
    };
    ~Node() {};
    static int count;
    void print_fanin();
    void print_fanout();
    void print_adj();
    vector<Node*> fanin;
    vector<Node*> fanout;
    vector<Node*> adj;
    int index;
    friend ostream& operator << (ostream&, const Node&);
  private:
};

class Graph {
  public:
    Graph() {};
    ~Graph() {};
    int V;
    int E;
    char graph_type = ' ';
    Node* nodes;
    int16_t** weight;
    void init(char, int, int);
    void add_edge(int, int, int);
    void print_weight();
    void print_edge();
};

#endif // GRAPH_H