#include <iostream>
#include <cstring>
#include <chrono>

#include "graph_types.h"
#include "graph_generator.h"
#include "seq_boruvka.h"
#include "par_boruvka_threads.h"
#include "par_boruvka_openmp.h"


typedef std::chrono::milliseconds time_type;

graph<edge> graph_input(int N, int M)
{
    graph<edge> g;
    // N vertices, M edges
    // insert M edges 
    for(int i=0;i<M;++i)
    {   
        int v, u, weight;
        std::cin >> v >> u >> weight;
        g.push_back({v,u,weight});
    }
    return g;
}

int main(int argc, char* argv[])
{
    
    int N, M;
    std::cin >> N >> M;
    graph<edge> g = graph_input(N,M);

    // tests
    /*
    for(int i=1;i<g.size();++i){
        auto [a,b,weight] = g[i];
        std::cerr << a<< ' ' << b << ' ' << weight << '\n';
    }
    */
    
    auto start = std::chrono::high_resolution_clock::now();
    graph<edge> gg = boruvka_mst_seq(g,N);
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<time_type>(stop - start);
    std::cout << " --- Sequential Boruvka MST --- " << std::endl;
    long long ans = 0;
    for(auto  [a,b,w] : gg){
        ans+=w;
    }
    std::cout << "TOTAL WEIGHT: " << ans<<std::endl;
    std::cout <<"Sequential Boruvka MST algorithm time: " << duration.count() << " ms"<< std::endl;

    start = std::chrono::high_resolution_clock::now();
    direct_flat_graph dfg(g, N);
    stop = std::chrono::high_resolution_clock::now();
    std::cout<< "GRAPH TRANSFORM:"<<  std::chrono::duration_cast<time_type>(stop-start).count()<< " ms"<<std::endl;

    std::cout << " --- Parallel Boruvka MST (thread) --- " << std::endl;


    start = std::chrono::high_resolution_clock::now();
    graph<edge> gd = boruvka_mst_par_threads(dfg,N);
    stop = std::chrono::high_resolution_clock::now();

    

    duration = std::chrono::duration_cast<time_type>(stop - start);
    ans=0;
    for(auto  [a,b,w] : gd){
        ans+=w;
    }
    std::cout<< "TOTAL WEIGHT: " << ans<< std::endl;

    std::cout <<"Parallel Boruvka MST algorithm with Threads library time: " << duration.count() << " ms"<< std::endl;
    

    std::cout << " --- Parallel Boruvka MST (OpenMP) --- " << std::endl;


    start = std::chrono::high_resolution_clock::now();
    graph<edge> go = boruvka_mst_par_openmp(dfg,N);
    stop = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<time_type>(stop - start);
    ans=0;
    for(auto  [a,b,w] : go){
        ans+=w;
    }
    std::cout << "TOTAL WEIGHT: " << ans<<'\n';

    std::cout <<"Parallel Boruvka MST algorithm with OpenM library time: " << duration.count() << " ms" << std::endl;

    return 0;
}