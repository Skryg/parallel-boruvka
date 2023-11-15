#pragma once

#include "graph_types.h"

constexpr int DEFAULT_N = 100;
constexpr int DEFAULT_M = 1000;

bool is_connected(graph<list_el>& g);

struct generator 
{
    int seed;
    graph<list_el> generate_graph(int n, int m);
};