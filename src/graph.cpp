#include <iostream>
#include <algorithm>
#include <utility>
#include "graph.h"
#include "my_utility.h"

#define white 0
#define grey  1
#define black 2

using namespace std;

int Node::count = 0;

void Node::print_fanout() {
  cout << "index: " << index << endl;
  for (auto &out : fanout) {
    cout << out << " ";
  }
  cout << endl;
}

ostream& operator << (ostream& os, const Node& node) {
  os << node.index;
}

/**
 * Initialize graph
 * @param type 'u' for undirected, 'd' for directed
 * @param v |G.V|
 * @param e |G.E|
 */ 
void Graph::init(char _type, int _v, int _e) {
  graph_type = _type;
  V = _v;
  E = _e;
  edges.reserve(_e);
  nodes = new Node[_v];
}

/**
 * Specify edges of the graph
 * @param s edge's source
 * @param t edge's target
 * @param w edge's weight
 */ 
void Graph::add_edge(int _s, int _t, int _w) {
  edges.push_back(Edge(_s, _t, _w));
  nodes[_s].fanout.push_back(_t);
}

/**
 * For finding feedback arc set in undirected graph
 * 
 * Steps:
 * Simply run Kruskal in decreasing weight order
 * Return the unuse edges
 */ 
void Graph::FAS_u() {
  MST_Kruskal();
}

/**
 * For finding feedback arc set in directed graph
 * In directed graph, Kruskal might identify some cycle by mistake,
 * therefore we need to add back edges which don't cause cycle
 * 
 * Steps:
 * 1. Run Kruskal in decreasing weight order
 * 2. Reconstruct the intial graph using the result of Kruskal
 * 3. Try adding back every edge in decreasing weight order and check if it cause cycle
 * 4. Until no edges left or the weight < 0
 */
void Graph::FAS_d() {
  MST_Kruskal();
  reconstruct_graph();
  add_back_edges();
}

// Kruskal

int Graph::find_set(int x) {
  if (nodes[x].p != x) {
    nodes[x].p = find_set(nodes[x].p);
  }
  return nodes[x].p;
}

void Graph::link(int x, int y) {
  if (nodes[x].rank > nodes[y].rank) 
    nodes[y].p = x;
  else {
    nodes[x].p = y;
    if (nodes[x].rank == nodes[y].rank)
      nodes[y].rank++;
  }
}

/**
 * Run Kruskal
 * this->edges will return unuse edges
 */
void Graph::MST_Kruskal() {
  sort(edges.begin(), edges.end(), my_compare);
  vector<Edge> new_edges;
  for (size_t i = 0; i < edges.size(); ++i) {
    if (find_set(edges[i].s) != find_set(edges[i].t)) {
      link(find_set(edges[i].s), find_set(edges[i].t));
    }
    else  new_edges.push_back(edges[i]);
  }
  edges = new_edges;
}

// directed graph

/**
 * Reconstruct the graph by deleting unuse edges which are left after Kruskal
 */ 
void Graph::reconstruct_graph() {
  for (auto& edge : edges) {
    for (size_t i = 0; i < nodes[edge.s].fanout.size(); ++i) {
      vector<int>::iterator it = find(nodes[edge.s].fanout.begin(), nodes[edge.s].fanout.end(), edge.t);
      if (it != nodes[edge.s].fanout.end()) {
        nodes[edge.s].fanout.erase(it);
      }
    }
  }
}

void Graph::add_back_edges() {
  for (size_t i = 0; i < edges.size(); ++i) {
    if (edges[i].w <= 0) break;
    if (find_cycle_by_edge(edges[i])) continue;
    else {
      nodes[edges[i].s].fanout.push_back(edges[i].t);
      edges.erase(edges.begin()+i);
      i--;
    }
  }
}

// dfs

void Graph::reset_color() {
  for (int i = 0; i < V; ++i) {
    nodes[i].color = white;
  }
}

/**
 * Testing whether add this edge will cause cycle by DFS
 */ 
bool Graph::find_cycle_by_edge(const Edge& edge) {
  reset_color();
  nodes[edge.s].color = grey;
  return dfs_has_cycle(edge.t);
}

/**
 * Run DFS to check cycle from single source
 * @param u index of single source vertex
 */ 
bool Graph::dfs_has_cycle(int u) {
  nodes[u].color = grey;
  for (auto& out : nodes[u].fanout) {
    if (nodes[out].color == white) {
      if(dfs_has_cycle(nodes[out].index)) return true;
    }
    else if (nodes[out].color == grey) {
      return true;
    }
  }
  nodes[u].color = black;
  return false;
}

// testing

/**
 * Check whether there is any cycle in current graph by DFS
 */ 
bool Graph::find_cycle() {
  reset_color();
  
  for (int i = 0; i < V; ++i) {
    if (nodes[i].color == white) {
      if (dfs_has_cycle(i)) return true;
    }
  }
  return false;
}

/**
 * Check whether there is any cycle in current graph 
 * Or the graph is not weakly connected
 */ 
void Graph::traversal_test() {
  if(find_cycle()) {
    cerr << "sth wrong!!" << endl;
    cerr << "cycles existing!!" << endl;
  }
  for (int i = 0; i < V; ++i) {
    if (nodes[i].color == white) {
      cerr << "sth wrong!!" << endl;
      cerr << "traversal failed!!" << endl;
    }
  }
}

void Graph::sort_edge_by_source() {
  sort(edges.begin(), edges.end(), my_compare_2);
}