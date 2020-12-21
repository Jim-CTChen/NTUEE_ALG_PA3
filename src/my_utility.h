#ifndef MY_UTILITY_H
#define MY_UTILITY_H

#include <utility>

using namespace std;

struct Edge;

int max(int, int);
int min(int, int);

bool my_compare(const Edge&, const Edge&);
bool my_compare_2(const Edge&, const Edge&);

void print_pair(pair<int, int>);
void print_edge(pair<pair<int, int>, int>);



#endif // MY_UTILITY_H