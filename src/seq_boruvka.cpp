#include "seq_boruvka.h"
#include "dsu.h"

#include <iostream>
graph<edge> boruvka_mst_seq(const graph<edge>& g, int n)
{
    graph<edge> mst;
    make_set(n);

    while(components_num() > 1)
    {
        std::vector<int> min(g.size(),-1);
        for(int i=0;i<g.size();++i)
        {
            auto [v,w, weight] = g[i];
            int cmp1 = find_set(v);
            int cmp2 = find_set(w);

            if(cmp1==cmp2)
                continue;
            
            if(min[cmp1] == -1 || std::get<2>(g[min[cmp1]]) > weight)
                min[cmp1] = i;
            if(min[cmp2] == -1 || std::get<2>(g[min[cmp2]]) > weight)
                min[cmp2] = i;
        }
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