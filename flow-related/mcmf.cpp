#include <cstdio>
#include <vector>
#include <algorithm>
#include <queue>
#include <memory.h>
using namespace std;

struct MinCostFlow{
    typedef long long cost_t;
    typedef int flow_t;
    struct edge{
        int next, inv;
        cost_t cost;
        flow_t cap, orig;
    };
    int n; vector<vector<edge>> g; vector<cost_t> pi;
    MinCostFlow(int _n) : n(_n) { g.resize(n); pi.resize(n); }
    const cost_t infinite_cost = numeric_limits<cost_t>::max()/2;
    const flow_t infinite_flow = numeric_limits<flow_t>::max()/2;
    void add_edge(int u, int v, cost_t c, flow_t w){
        edge a = {v, (int)g[v].size(), c, w, w};
        edge b = {u, (int)g[u].size(), -c, 0, 0};
        g[u].push_back(a); g[v].push_back(b);
    }
    void init_potential(int src){
        fill(pi.begin(), pi.end(), infinite_cost); pi[src] = 0;
        queue<int> q; q.push(src);
        while(!q.empty()){
            int here = q.front(); q.pop();
            for(auto& e : g[here]) if(e.cap > 0){
                if(pi[here] + e.cost < pi[e.next]){
                    pi[e.next] = pi[here] + e.cost;
                    q.push(e.next);
                }
            }
        }
    }
    pair<cost_t, flow_t> augment_shortest(int src, int dst){
        typedef pair<cost_t, int> pqt;
        priority_queue<pqt,vector<pqt>,greater<pqt>> pq;
        pq.emplace(0, src);
        vector<cost_t> d(n, infinite_cost); d[src] = 0;
        vector<flow_t> f(n, infinite_flow);
        vector<pair<int,edge*>> prev(n);
        while(!pq.empty()){
            cost_t dist = pq.top().first;
            int here = pq.top().second; pq.pop();
            if(dist != d[here]) continue;
            for(auto& e : g[here]) if(e.cap > 0){
                cost_t reduced_cost = e.cost + pi[here] - pi[e.next];
                if(d[e.next] > dist + reduced_cost){
                    d[e.next] = dist + reduced_cost;
                    f[e.next] = min(f[here], e.cap);
                    prev[e.next] = {here, &e};
                    pq.emplace(d[e.next], e.next);
                }
            }
        }
        if(d[dst] == infinite_cost) return {0, 0};
        cost_t cost = d[dst] + pi[dst];
        flow_t flow = f[dst];
        int cur = dst;
        for(int i=0;i<n;i++) pi[i] += d[i];
        while(cur != src){
            auto& e = *prev[cur].second;
            e.cap -= flow; g[e.next][e.inv].cap += flow;
            cur = prev[cur].first;
        }
        return {cost * flow, flow};
    }
    pair<cost_t, flow_t> solve(int src, int dst){
        init_potential(src);
        cost_t total_cost = 0;
        flow_t total_flow = 0;
        while(true){
            auto r = augment_shortest(src, dst);
            if(!r.second) break;
            // if(r.first >= 0) break; add this to get min cost flow
            total_cost += r.first;
            total_flow += r.second;
        }
        return {total_cost, total_flow};
    }
};

const long long M = -1000000000LL;

int main(){
    int n, k; scanf("%d%d", &n, &k);
    MinCostFlow mcf(2*(n+1)+2); int src = 2*(n+1), dst = 2*(n+1)+1;
    for(int i=0;i<=n;i++) mcf.add_edge(2*i, 2*i+1, M, 1);
    for(int i=0;i<n;i++){
        for(int j=i+1;j<=n;j++){
            int t; scanf("%d", &t);
            mcf.add_edge(2*i+1, 2*j, t, 1);
        }
    }
    mcf.add_edge(src, 2*0+1, 0, k);
    for(int i=0;i<=n;i++) mcf.add_edge(2*i+1, dst, 0, 1);
    printf("%lld\n", -n*M + mcf.solve(src, dst).first);
    return 0;
}
