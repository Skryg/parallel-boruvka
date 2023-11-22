#pragma once

#include <vector>
#include "graph_types.h"

// returns vector of edges type (from, to, weight)
graph<edge> boruvka_mst_par_threads(const graph<edge>&, int);