#include <vector>
#include "graph_types.h"

// returns vector of edges type (from, to, weight)
std::vector<std::tuple<int,int,int>> boruvka_mst_par(const graph<list_el>&);