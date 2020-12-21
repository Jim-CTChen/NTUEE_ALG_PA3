#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <utility>

#define white 0
#define grey  1
#define black 2

using namespace std;

class Node {
  public:
    Node() {
      index = count;
      p = count;
      count++;
    };
    ~Node() {};
    static int count;
    int index;
    vector<int> fanout;
    void print_fanout();

    // for dfs

    int color = white;

    // Kruskal's

    int p = -1;
    int rank = 0;
    
    // ostream operator

    friend ostream& operator << (ostream&, const Node&);

};


struct Edge {
  public:
    Edge(int _s, int _t, int _w):s(_s), t(_t), w(_w) {};
    ~Edge() {};
    void print() {
      cout << s << " " << t << " " << w << endl;
    }
    int s = 0; // source
    int t = 0; // target
    int w = 0; // weight
};

class Graph {
  public:
    Graph() {};
    ~Graph() {};

    // graph spec

    int V;
    int E;
    char graph_type = ' ';

    // E & V set

    vector<Edge> edges;
    Node* nodes = 0;

    // external function

    void FAS_u();
    void FAS_d();
    void init(char, int, int);
    void add_edge(int, int, int);

    // Kruskal's

    int  find_set(int);
    void link(int, int);
    void MST_Kruskal();

    // for directed graph

    void reset_color();
    void reconstruct_graph();
    void add_back_edges();
    bool find_cycle_by_edge(const Edge&);
    bool dfs_has_cycle(int);

    // util

    void sort_edge_by_source();
    void traversal_test();
    bool find_cycle();

};


#endif // GRAPH_H