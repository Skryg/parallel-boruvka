#pragma once

#include "graph_types.h"

constexpr int DEFAULT_N = 128;
constexpr int DEFAULT_M = 1024;
constexpr int DEF_WEIGHT_MIN = 0;
constexpr int DEF_WEIGHT_MAX = 1024;

bool is_connected(const graph<edge>&);

class Generator 
{
    int weight_min = DEF_WEIGHT_MIN;
    int weight_max = DEF_WEIGHT_MAX;
    int n = DEFAULT_N;
    int m = DEFAULT_M;
public:
    Generator();
    Generator(int,int);
    Generator(int,int,int,int);
    graph<edge> generate_graph();
    void set_weight_min(int);
    void set_weight_max(int);
    void set_vertices(int);
    void set_edges(int);
};