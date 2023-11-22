#pragma once

#include <vector>
#include "graph_types.h"

// returns graph of edges type (from, to, weight)
graph<edge> boruvka_mst_seq(const graph<edge>&, int);