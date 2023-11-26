#pragma once 

#include <vector> 
#include <tuple>

template <typename T>
using graph = std::vector<T>;

typedef std::tuple<int,int,int> edge;

template <typename T>
using directed_graph = std::vector<std::vector<T>>;

typedef std::pair<int,int> edge_map;


inline directed_graph<edge_map> vertex_mapping(const graph<edge> &g, int n)
{
    directed_graph<edge_map> graph;
    graph.resize(n+1);
    for(int i=0;i<g.size();++i)
    {
        auto [v,w,weight] = g[i];
        graph[v].push_back({w,i});
        graph[w].push_back({v,i});
    }

    return graph;
}