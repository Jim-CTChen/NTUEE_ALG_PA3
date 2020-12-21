#include <iostream>
#include "my_utility.h"
#include "graph.h"

int max(int x, int y) {
  return (x >= y) ? x : y;
}

int min(int x, int y) {
  return (x >= y) ? y : x;
}

/**
 * Comparison function used in algorithm/soriting 
 * Sort Edges in descending weight order 
 * @param i (Edge) target edge
 * @param j (Edge) comparison opponent
 */ 
bool my_compare(const Edge& i, const Edge& j) {
  return i.w > j.w;
}

/**
 * Comparison function used in <algorithm/soriting> 
 * Sort Edges in ascending source-index order 
 * @param i (Edge) target edge
 * @param j (Edge) comparison opponent
 */ 
bool my_compare_2(const Edge& i, const Edge& j) {
  return i.s < j.s;
}

void print_pair(pair<int, int> p) {
  cout << "(" << p.first << ", " << p.second << ")";
}

void print_edge(Edge& edge) {
  cout << edge.s << " " << edge.w << " " << edge.t;
}