#include <stdexcept>
#include <set>
#include <numeric>
#include <random>
#include <algorithm>


#include "graph_generator.h"

void dfs(int v, const graph<list_el> &g, std::vector<bool> &vis, int &cnt){
    vis[v] = true;
    ++cnt;
    for(auto w : g[v])
    {
        if(!vis[w.first]) dfs(w.first,g,vis,cnt);
    }
}

bool is_connected(const graph<list_el>& g)
{
    std::vector<bool> vis(g.size());
    int cnt=0;
    dfs(1,g,vis,cnt);
    return cnt == g.size()-1;
}

Generator::Generator(){}
Generator::Generator(int n, int m)
{
    this->n = n;
    this->m = m;
}
Generator::Generator(int n, int m, int wmin, int wmax)
{
    this->n = n;
    this->m = m;
    this->weight_min = wmin;
    this->weight_max = wmax;
}

graph<list_el> Generator::generate_graph()
{
    if(m<n-1) throw std::invalid_argument("Number of edges shouldn't be less than number of vertices-1.");
    if((long long)n*(n-1)/2 < (long long)m) throw std::invalid_argument("Number of edges is too big");
    if(weight_max<weight_min) throw std::invalid_argument("Weight max cannot be less than weight min");
    graph<list_el> g(n+1);
    std::set<std::pair<int,int>> edges;
    std::vector<int> nums(n);
    std::iota(nums.begin(),nums.end(),1);
    std::random_device r;
    std::default_random_engine rng(r()); 
    std::shuffle(std::begin(nums), std::end(nums), rng);
    std::uniform_int_distribution<> one_dst(0,1);
    std::uniform_int_distribution<> weight_dst(weight_min,weight_max);
    while(nums.size()>1)
    {
        int v1 = nums.back();
        nums.pop_back();
        int v2 = nums.back();
        nums.pop_back();
        int weight = weight_dst(rng);
        g[v1].push_back({v2, weight});
        g[v2].push_back({v1, weight});
        edges.insert({std::min(v1,v2), std::max(v1,v2)});
        if(one_dst(rng)) 
            nums.push_back(v1);
        else 
            nums.push_back(v2);
    }
    std::uniform_int_distribution<> vertices_dst(1,n);

    int toadd = m - (n-1);
    while(toadd)
    {
        int v1 = vertices_dst(rng);
        int v2 = vertices_dst(rng);
        if(v1 == v2) continue;
        if(v1 > v2) std::swap(v1, v2);
        if(edges.find({v1,v2}) == edges.end())
        {
            int weight = weight_dst(rng);
            g[v1].push_back({v2,weight});
            g[v2].push_back({v1,weight});
            edges.insert({v1,v2});
            --toadd;
        }
    }
    return g;
}

void Generator::set_weight_min(int w)
{
    weight_min=w;
}
void Generator::set_weight_max(int w)
{
    weight_max = w;
}
void Generator::set_vertices(int n)
{
    this->n = n;
}
void Generator::set_edges(int m)
{
    this->m = m;
}