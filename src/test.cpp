#include <iostream>

#include "graph_types.h"
#include "graph_generator.h"
#include "program_options.h"


int main(int argc, char* argv[])
{
    std::ios_base::sync_with_stdio(0);

    program_options::parse(argc,argv);
    
    // Neighbourhood lists, for vertex v there are elements (w, weight), 
    // i.e. v is connected by an enge with w specified weight
    graph<edge> g;
    int N = DEFAULT_N;
    int M = DEFAULT_M;

    if(program_options::has_arg("n")) N = program_options::get_arg("n");
    if(program_options::has_arg("m")) M = program_options::get_arg("m");
    Generator gen(N,M); 
    if(program_options::has_arg("max-weight")) gen.set_weight_max(program_options::get_arg("max-weight"));
    if(program_options::has_arg("min-weight")) gen.set_weight_min(program_options::get_arg("min-weight"));


    if(program_options::has_arg("clique"))
    {
        g = gen.generate_clique();
        M = (long long)N*(N-1)/2;
    }
    else
    {
        g = gen.generate_graph();
    }

    
    std::cout<<N<<' '<<M<<'\n';
    for(auto [v,w, weight] : g)
        std::cout<<v<<' '<<w<<' '<<weight<<'\n';
    return 0;
}