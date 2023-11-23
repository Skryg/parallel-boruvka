#include "par_boruvka_threads.h"
#include "dsu.h"
#include <thread>
#include <mutex> 
#include <algorithm>
#include <iostream>
void join(std::thread *threads)
{
    for(int i=0;i<THREADS_NUM;++i){
        if(threads[i].joinable())
            threads[i].join();
    }

}

graph<edge> boruvka_mst_par_threads(const graph<edge>&g, int n)
{
    graph<edge> mst;
    mst.resize(n-1);
    make_set(n);

    int bignum = n;


    int vert_thread = (n+THREADS_NUM-1)/THREADS_NUM;
    int edge_thread = (g.size()+THREADS_NUM-1)/THREADS_NUM;

    std::thread threads[THREADS_NUM];
    
    std::vector<int> min(n+1,-1);
    std::vector<std::mutex> mutex(n+1);
                    

    while(bignum>1)
    {

        for(int i=0;i<THREADS_NUM;++i){
            threads[i]=std::thread([&](int x, int y){for(int j=x;j<y;++j) min[j]=-1;},
                i*vert_thread+1, std::min((i+1)*vert_thread,(int)n)+1);
        }
        join(threads);
    
        for(int i=0;i<THREADS_NUM;++i)
        {   
            threads[i] = std::thread([&](int x,int y)
            {
            for(int j=x;j<y;++j)
            {
                auto [v,w, weight] = g[j];
                int cmp1 = find_set(v);
                int cmp2 = find_set(w);
                
                if(cmp1==cmp2)
                    continue;
                if(cmp1 > cmp2) std::swap(cmp1,cmp2);

                {

                    const std::lock_guard lock1(mutex[cmp1]);
                    const std::lock_guard lock2(mutex[cmp2]);

                    if(min[cmp1] == -1 || std::get<2>(g[min[cmp1]]) > weight)
                        min[cmp1] =j;
                    if(min[cmp2] == -1 || std::get<2>(g[min[cmp2]]) > weight)
                        min[cmp2] =j;

                }
            }
            },i*edge_thread, std::min((i+1)*edge_thread, (int)g.size()));
            

        }
        join(threads);
        int ans[THREADS_NUM];
        for(int i=0;i<THREADS_NUM;++i)
        {
            threads[i] = std::thread([&](int x,int y, int i){
                int unions = 0;
                for(int j=x; j<y; ++j)
                {
                    if(min[j] != -1)
                    {
                        auto [v,w,weight] = g[min[j]];        
                        int cmp1 = find_set(v);
                
                        int cmp2 = find_set(w);
                        if(cmp1 == cmp2) continue;
                        if(cmp1 > cmp2) std::swap(cmp1,cmp2);
                        {
                            const std::lock_guard lock1(mutex[cmp1]);
                            const std::lock_guard lock2(mutex[cmp2]);
                            if(find_set(cmp1) == find_set(cmp2)) continue;
                            union_sets(cmp1, cmp2);
                            unions++;
                            // std::cerr<<"UNION! "<< components_num()<<std::endl;
                            mst.push_back(g[min[j]]);
                        
                        }
                        
                    }
                }
                ans[i] = unions;
            },i*vert_thread+1,std::min((i+1)*vert_thread, n)+1,i);
           
        }
        join(threads);
        int x = 0;
        for(int i=0;i<THREADS_NUM;++i) x+=ans[i]; 
        bignum-=x;
    }
    
    return mst;
        
}