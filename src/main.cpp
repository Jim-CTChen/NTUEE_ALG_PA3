#include <iostream>
#include <fstream>
#include <algorithm>
#include "graph.h"
#include "my_utility.h"

using namespace std;

char graph_type = ' ';
int V = 0;
int E = 0;
Graph graph;


int main(int argc, char* argv[])
{
  string in_file = argv[1];
  string out_file = argv[2];
  ifstream infile(in_file);
  ofstream outfile(out_file);

  infile >> graph_type;
  infile >> V;
  infile >> E;
  
  graph.init(graph_type, V, E);
  int s, d, w;
  for (int i = 0; i < E; ++i) {
    infile >> s >> d >> w;
    graph.add_edge(s, d, w);
  }

  switch (graph_type)
  {
    case 'u':
      graph.FAS_u();
      break;
    case 'd':
      graph.FAS_d();
      break;
    default:
      break;
  }

  int total_weight = 0;
  // graph.sort_edge_by_source();
  for (auto &edge : graph.edges) {
    total_weight += edge.w;
  }
  outfile << total_weight << endl;
  for (auto &edge : graph.edges) {
    outfile << edge.s << " " << edge.t << " " << edge.w;
    outfile << endl;
  }

}