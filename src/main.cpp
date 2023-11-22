#include <iostream>
#include <cstring>
#include <chrono>

#include "graph_types.h"
#include "graph_generator.h"
#include "seq_boruvka.h"
#include "par_boruvka_threads.h"
#include "par_boruvka_openmp.h"
#include "program_options.h"



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
    program_options::parse(argc,argv);
    
    // Neighbourhood lists, for vertex v there are elements (w, weight), 
    // i.e. v is connected by an enge with w specified weight
    graph<edge> g;
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
    /*
    for(int i=1;i<g.size();++i){
        auto [a,b,weight] = g[i];
        std::cerr << a<< ' ' << b << ' ' << weight << '\n';
    }
    */
    
    auto start = std::chrono::high_resolution_clock::now();
    graph<edge> gg = boruvka_mst_seq(g,N);
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    std::cerr << "SEQ" << '\n';
    for(auto  [a,b,w] : gg){
        std::cerr << a<< ' ' << b << ' ' << w << '\n';
    }
    std::cout <<"Sequential Boruvka MST algorithm time: " << duration.count() << std::endl;

    start = std::chrono::high_resolution_clock::now();
    boruvka_mst_par_threads(g,N);
    stop = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);

    std::cout <<"Parallel Boruvka MST algorithm with Threads library time: " << duration.count() << std::endl;
    
    start = std::chrono::high_resolution_clock::now();
    boruvka_mst_par_openmp(g,N);
    stop = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);

    std::cout <<"Parallel Boruvka MST algorithm with Threads library time: " << duration.count() << std::endl;

    return 0;
}