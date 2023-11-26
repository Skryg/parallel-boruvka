#pragma once

#include <vector>
#include "graph_types.h"

constexpr int THREADS_NUM = 8;
// returns vector of edges type (from, to, weight)
graph<edge> boruvka_mst_par_threads(const graph<edge>&, int);