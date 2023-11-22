#include <iostream>
#include <cstring>
#include <chrono>

#include "graph_types.h"
#include "graph_generator.h"
#include "seq_boruvka.h"
#include "par_boruvka.h"
#include "program_options.h"



graph<list_el> graph_input(int N, int M)
{
    graph<list_el> g;
    // N vertices, M edges
    g.assign(N+1, list_el());
    // insert M edges 
    for(int i=0;i<M;++i)
    {   
        int v, u, weight;
        std::cin >> v >> u >> weight;
        g[v].push_back({u,weight});
        g[u].push_back({v,weight});
    }
    return g;
}

int main(int argc, char* argv[])
{
    program_options::parse(argc,argv);
    
    // Neighbourhood lists, for vertex v there are elements (w, weight), 
    // i.e. v is connected by an enge with w specified weight
    graph<list_el> g;
    int N = DEFAULT_N;
    int M = DEFAULT_M;


    if(program_options::has_arg("n")) N = program_options::get_arg("n");
    if(program_options::has_arg("m")) M = program_options::get_arg("m");


    // If flag --input is provided, load graph from stdin
    if(program_options::has_arg("input"))
    {
        graph_input(N,M);
    }
    else
    {
        //Generate graph
        Generator gen(N,M);
        g = gen.generate_graph();

    } 

    // tests
    for(int i=1;i<g.size();++i){
        std::cerr<<i<<": ";
        for(auto pair : g[i]){
            std::cerr<<pair.first<<' ';
        }
        std::cerr<< '\n';
    }
    
    
    auto start = std::chrono::high_resolution_clock::now();
    boruvka_mst_seq(g);
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);

    std::cout <<"Sequential Boruvka MST algorithm time: " << duration.count() << std::endl;

    start = std::chrono::high_resolution_clock::now();
    boruvka_mst_par(g);
    stop = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);

    std::cout <<"Parallel Boruvka MST algorithm time: " << duration.count() << std::endl;
    return 0;
}