#include <cstdio>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

struct MinCostFlow{
    struct edge{int next, inv, cost, cap, orig;};
    const int INF = 987654321;
    int n;
    vector<vector<edge>> g;
    MinCostFlow(int _n) : n(_n) {g.resize(n);}
    void add_edge(int u, int v, int c, int w){
        edge a = {v, (int)g[v].size(), c, w, w};
        edge b = {u, (int)g[u].size(), -c, 0, 0};
        g[u].push_back(a); g[v].push_back(b);
    }
    pair<int,int> augment_shortest(int src, int dst){
        vector<int> d(n, INF), f(n, INF); d[src] = 0;
        vector<pair<int,edge*>> prev(n);
        for(int it=0;it<n-1;it++){
            for(int here=0;here<n;here++) for(auto& e: g[here]) if(e.cap > 0){
                if(d[here] + e.cost < d[e.next]){
                    d[e.next] = d[here] + e.cost;
                    f[e.next] = min(f[here], e.cap);
                    prev[e.next] = {here, &e};
                }
            }
        }

        if(d[dst] == INF) return {0, 0};

        int cost = d[dst], flow = f[dst], cur = dst;
        while(cur != src){
            auto& e = *(prev[cur].second);
            e.cap -= flow; g[e.next][e.inv].cap += flow;
            cur = prev[cur].first;
        }
        return {cost * flow, flow};
    }
    pair<int,int> solve(int src, int dst){
        int total_flow = 0, total_cost = 0;
        while(true){
            auto r = augment_shortest(src, dst);
            if(!r.second) break;
            total_cost += r.first;
            total_flow += r.second;
        }
        return {total_cost, total_flow};
    }
};

int main(){
    int n, m; scanf("%d%d", &n, &m);
    MinCostFlow mcmf(n+2);
    for(int i=0;i<m;i++){
        int u, v, w; scanf("%d%d%d", &u, &v, &w);
        mcmf.add_edge(u, v, w, 1);
        mcmf.add_edge(v, u, w, 1);
    }
    mcmf.add_edge(0, 1, 0, 2);
    mcmf.add_edge(n, n+1, 0, 2);
    auto r = mcmf.solve(0, n+1);
    //printf("%d %d\n", r.first, r.second);
    if(r.second < 2) printf("-1\n");
    else printf("%d\n", r.first);
    return 0;
}
