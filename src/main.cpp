#include <iostream>
#include <fstream>
#include "graph.h"

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

  graph.print_weight();
  graph.print_edge();
}