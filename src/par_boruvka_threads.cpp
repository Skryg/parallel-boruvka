#include "par_boruvka_threads.h"
#include "dsu.h"
#include <thread>
#include <mutex> 
#include <algorithm>
#include <climits>
#include <iostream>
void join(std::vector<std::thread> &threads)
{
    for(int i=0;i<THREADS_NUM;++i){
        // if(threads[i].joinable())
            threads[i].join();
    }

}

graph<edge> boruvka_mst_par_threads(const graph<edge>&g, int n)
{

    graph<edge> mst;
    mst.resize(n-1);
    make_set(n);

    int bignum = n;
    const int VERT_NUM = n;

    int vert_thread = (n+THREADS_NUM-1)/THREADS_NUM;
    int edge_thread = (g.size()+THREADS_NUM-1)/THREADS_NUM;

    std::vector<std::thread> threads;
    threads.reserve(THREADS_NUM);
    
    std::vector<int> min(n+1,-1);
    std::vector<int> processed(n+1);                   
    int iters = 0;
    while(components_num()>1)
    {

        for(int i=0;i<THREADS_NUM;++i){
            std::thread t = std::thread([&](int x, int y){for(int j=x;j<y;++j) {min[j]=-1; processed[j]=0;}},
                i*vert_thread+1, std::min((i+1)*vert_thread,(int)n)+1);
            threads.push_back(std::move(t));
        }
        join(threads);
        threads.clear();

        for(int i=0;i<THREADS_NUM;++i)
        {   
        
            std::thread t = std::thread([&processed, &g, &n, &min]()
            {
                for(int i=1;i<=n;++i)
                {
                    int com = atomic_find_set(i);
                    if(!__sync_bool_compare_and_swap(&processed[com],0,1)) 
                        continue;
                    
                    int minimal = INT_MAX;
                    int min_id = -1;

                    for(int j=0;j<g.size();++j)
                    {   
                        auto [v,u,weight] = g[j];
                        v=atomic_find_set(v);
                        u=atomic_find_set(u);
                        if(v==u) continue;
                        if(v==com || u == com)

                        if(weight < minimal)
                        {
                            min_id = j;
                            minimal = weight;
                        }

                    }                   
                    min[com] = min_id;

                }
            });
            threads.push_back(std::move(t));
        }
        join(threads);
        threads.clear();
        for(int i=1; i<=n; ++i)
        {
            if(min[i] != -1)
            {
                auto [v,w,weight] = g[min[i]];
                int cmp1 = find_set(v);
                int cmp2 = find_set(w);
                if(cmp1 != cmp2)
                {
                    union_sets(cmp1, cmp2);
                    // std::cerr<<"UNION! "<< components_num()<<std::endl;
                    mst.push_back(g[min[i]]);
                }
            }
        }
    }
    
    return mst;
        
}