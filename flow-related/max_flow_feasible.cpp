#include <cstdio>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

/*
 * Feasible Maximum Flow (Flow with lower bounds)
 * O(V^2 E)
 * verification : http://codeforces.com/contest/704/problem/D
 */

struct MaxFlow{
    typedef int flow_t;
    struct edge{int next, inv; flow_t cap, orig;};
    int n;
    vector<vector<edge>> g;
    vector<int> cur, l;
    const flow_t INF = numeric_limits<flow_t>::max();
    MaxFlow(int _n) : n(_n) {g.resize(n); l.resize(n); cur.resize(n);}
    MaxFlow(){}
    void init(int _n){ n = _n; g.resize(n); l.resize(n); cur.resize(n);}
    int add_edge(int u, int v, flow_t w, flow_t wr=0){
        edge a = {v, (int)g[v].size(), w, w};
        edge b = {u, (int)g[u].size(), wr, wr};
        g[u].push_back(a); g[v].push_back(b);
        return b.inv;
    }
    bool con(int src, int dst){
        fill(l.begin(), l.end(), -1);
        fill(cur.begin(), cur.end(), 0);
        queue<int> q; q.push(src); l[src] = 0;
        while(!q.empty()){
            int here = q.front(); q.pop();
            for(auto& e : g[here]) if(e.cap > 0 && l[e.next] == -1){
                l[e.next] = l[here] + 1;
                q.push(e.next);
            }
        }
        return l[dst] != -1;
    }
    flow_t dfs(int here, int dst, flow_t flow){
        if(here == dst) return flow;
        for(int& i=cur[here];i<g[here].size();i++){
            auto& e = g[here][i];
            if(e.cap > 0 && l[here]+1==l[e.next]){
                flow_t f = dfs(e.next, dst, min(e.cap, flow));
                if(f > 0){
                    e.cap -= f; g[e.next][e.inv].cap += f;
                    return f;
                }
            }
        }
        return 0;
    }
    flow_t solve(int src, int dst){
        flow_t total_flow = 0;
        while(con(src, dst)){
            while(true){
                flow_t f = dfs(src, dst, INF);
                if(f == 0) break;
                total_flow += f;
            }
        }
        return total_flow;
    }
};

struct MaxFlowFeasible{
    typedef MaxFlow::flow_t flow_t;
    struct edge{ int next; flow_t lo, hi; int x, y; };
    int n; vector<vector<edge>> g;
    MaxFlow mf1, mf2; flow_t circulation;
    MaxFlowFeasible(int _n) : n(_n) { g.resize(n); mf1.init(n+2); mf2.init(n); }
    int add_edge(int u, int v, flow_t lo, flow_t hi){
        g[u].push_back({v, lo, hi, -1, -1});
        return (int)g[u].size() - 1;
    }
    /* remove or optimize this function to enhance performance */
    bool has_invalid_edge(){
        for(int i=0;i<n;i++) for(auto& e : g[i]) if(e.lo > e.hi) return true;
        return false;
    }
    bool feasible_flow(int src, int dst){
        if(has_invalid_edge()) return false;
        vector<flow_t> inflow(n, 0);
        for(int i=0;i<n;i++) for(auto& e : g[i]){
            e.x = mf1.add_edge(i, e.next, e.hi - e.lo);
            inflow[e.next] += e.lo; inflow[i] -= e.lo;
        }
        int circ_ind = mf1.add_edge(dst, src, mf1.INF);
        int new_src = n, new_dst = n+1;
        flow_t supply = 0;
        for(int i=0;i<n;i++){
            if(inflow[i] > 0){
                mf1.add_edge(new_src, i, inflow[i]);
                supply += inflow[i];
            }
            else if(inflow[i] < 0) mf1.add_edge(i, new_dst, -inflow[i]);
        }
        bool ret = mf1.solve(new_src, new_dst) == supply;
        circulation = mf1.g[dst][circ_ind].orig - mf1.g[dst][circ_ind].cap;
        return ret;
    }
    flow_t maximum_flow(int src, int dst){
        for(int i=0;i<n;i++) for(auto& e : g[i]){
            flow_t f = e.lo + mf1.g[i][e.x].orig - mf1.g[i][e.x].cap;
            e.y = mf2.add_edge(i, e.next, e.hi - f, f - e.lo);
        }
        return circulation + mf2.solve(src, dst);
    }
    int arc_flow(int u, int ind){
        auto& e = g[u][ind];
        return e.lo + (mf1.g[u][e.x].orig - mf1.g[u][e.x].cap)
            + (mf2.g[u][e.y].orig - mf2.g[u][e.y].cap);
    }
};

int main(){
    int n, m; scanf("%d%d", &n, &m);
    MaxFlowFeasible mff(n);
    vector<pair<int,int>> edge_ind(m);
    for(int i=0;i<m;i++){
        int u, v, l, r; scanf("%d%d%d%d", &u, &v, &l, &r);
        edge_ind[i] = {u, mff.add_edge(u, v, l, r)};
    }
    int s, t; scanf("%d%d", &s, &t);
    if(mff.feasible_flow(s, t)){
        printf("%d\n", mff.maximum_flow(s, t));
        for(auto ij : edge_ind){
            auto& e = mff.g[ij.first][ij.second];
            printf("edge %d -> %d with capacity (%d...%d) is sending flow %d\n",
                    ij.first, e.next, e.lo, e.hi, mff.arc_flow(ij.first, ij.second));
        }
    }
    else printf("-1\n");
}
