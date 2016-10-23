#include <cstdio>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

// Max Flow : Shortest Augmenting Path Algorithm
// * runs in O(V^2 E) time, the same as dinic
// * a little modification needed to assure advantage in unit capacity graph (or in unit capacity simple graph)
// * you are recommended to use Dinic's algorithm

// verification
// * https://www.acmicpc.net/problem/13161
// * https://www.acmicpc.net/problem/3736

struct MaxFlow{
    struct edge{
        int next, inv, cap, orig;
    };
    int n;
    vector<vector<edge>> g;
    vector<int> d, cur, numb;
    const int INF = 987654321;
    MaxFlow(int _n) : n(_n) { g.resize(n); }
    void add_edge(int u, int v, int w, int wr = 0){
        edge forward = {v, (int)g[v].size(), w, w};
        edge reverse = {u, (int)g[u].size(), wr, wr};
        g[u].push_back(forward); g[v].push_back(reverse);
    }
    void init_distance_label(int ind){
        d.clear(); d.resize(n, INF);
        d[ind] = 0;
        queue<int> q; q.push(ind);
        while(!q.empty()){
            int here = q.front(); q.pop();
            for(auto &e : g[here]) if(d[e.next] == INF){
                d[e.next] = d[here] + 1;
                q.push(e.next);
            }
        }
        numb.clear(); numb.resize(n+1, 0);
        for(int i=0;i<n;i++) if(d[i] < INF) numb[d[i]]++;
    }
    int dfs(int here, int dst, int flow){
        if(here == dst) return flow;
        if(d[here] == INF) return 0;
        for(int& i=cur[here];i<g[here].size();i++){
            auto& e = g[here][i];
            if(e.cap == 0 || d[e.next] + 1 != d[here]) continue;
            int f = dfs(e.next, dst, min(flow, e.cap));
            if(f > 0){
                e.cap -= f;
                g[e.next][e.inv].cap += f;
                return f;
            }
            if(f < 0) return -1;
        }
        numb[d[here]]--; if(numb[d[here]] == 0) return -1;
        cur[here] = 0; d[here] = INF;
        for(auto& e : g[here]) if(e.cap > 0){
            d[here] = min(d[here], d[e.next] + 1);
        }
        if(d[here] < INF) numb[d[here]]++;
        return 0;
    }
    int solve(int src, int dst){
        init_distance_label(dst);
        if(d[src] == INF) return 0;
        int total_flow = 0;
        cur.clear(); cur.resize(n, 0);
        while(d[src] < n){
            int f = dfs(src, dst, INF);
            if(f < 0) break;
            total_flow += f;
        }
        return total_flow;
    }
    void min_cut(int here, vector<int>& vis){
        vis[here] = true;
        for(auto& e : g[here]) if(e.cap > 0 && !vis[e.next]){
            min_cut(e.next, vis);
        }
    }
    void clear(){
        for(int i=0;i<n;i++) for(auto& e : g[i]) e.cap = e.orig;
    }
};
