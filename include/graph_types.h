#pragma once 

#include <vector> 
#include <tuple>
#include <iostream>

template <typename T>
using graph = std::vector<T>;

typedef std::tuple<int,int,int> edge;

template <typename T>
using directed_graph = std::vector<std::vector<T>>;

typedef std::pair<int,int> edge_map;


struct direct_flat_graph
{
    std::vector<int> nums;
    graph<edge> gr;
    direct_flat_graph(const graph<edge> &g, int n)
    {
        nums.assign(n+1,0);
        for(auto [v,w,weight] : g)
        {
            ++nums[v];
            ++nums[w];
        }
        for(int i=1;i<=n;++i)
        {
            nums[i] = nums[i]+nums[i-1];
        }


        std::vector<int> positions = nums;
        gr.resize(nums.back());
        for(auto [v,w,weight] : g)
        {
            gr[positions[v-1]++]={v,w,weight};
            gr[positions[w-1]++]={w,v,weight};
        }
    }

    //neighbourhood lists
    int first_id(int v) const
    {
        return nums[v-1];
    }

    int last_id(int v) const
    {
        return nums[v]-1;
    }


};

