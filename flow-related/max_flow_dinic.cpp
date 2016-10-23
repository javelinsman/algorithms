#include <cstdio>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

// Max Flow : Dinic's algorithm
// runs in
//     * O(V^2 E) time in general graph
//     * O(min(V^(2/3), E^(1/2)) * E) time in unit capacity network
//     * O(V^(1/2) * E) time in unit capacity simple network

// verification
// https://www.acmicpc.net/problem/13161
// https://www.acmicpc.net/problem/3736

struct MaxFlow{
    struct edge{ int next, inv, cap, orig; };
    int n;
    vector<vector<edge>> g;
    vector<int> l, cur;
    const int INF = 987654321;
    void add_edge(int u, int v, int w, int wr = 0){
        edge forward = {v, (int)g[v].size(), w, w};
        edge backward = {u, (int)g[u].size(), wr, wr};
        g[u].push_back(forward); g[v].push_back(backward);
    }
    MaxFlow(int _n) : n(_n) {g.resize(n); l.resize(n); cur.resize(n);}
    bool construct_level_graph(int src, int dst){
        fill(l.begin(), l.end(), -1);
        fill(cur.begin(), cur.end(), 0);
        l[src] = 0; queue<int> q; q.push(src);
        while(!q.empty()){
            int here = q.front(); q.pop();
            for(auto& e : g[here]) if(e.cap > 0 && l[e.next] == -1){
                l[e.next] = l[here] + 1;
                q.push(e.next);
            }
        }
        return l[dst] != -1;
    }
    int dfs(int here, int dst, int flow){
        if(here == dst) return flow;
        for(int& i=cur[here];i<g[here].size();i++){
            auto& e = g[here][i];
            if(e.cap > 0 && l[here] + 1 == l[e.next]){
                int f = dfs(e.next, dst, min(flow, e.cap));
                if(f > 0){
                    e.cap -= f;
                    g[e.next][e.inv].cap += f;
                    return f;
                }
            }
        }
        return 0;
    }
    int solve(int src, int dst){
        int total_flow = 0;
        while(construct_level_graph(src, dst)){
            while(true){
                int f = dfs(src, dst, INF);
                if(f == 0) break;
                total_flow += f;
            }
        }
        return total_flow;
    }
};

int main(){
    int n;
    MaxFlow mf(2*n+2); int src = 2*n, dst = 2*n+1;
    while(scanf("%d", &n) > 0){
        for(int i=0;i<n;i++){
            int u, nr;
            scanf(" %d : ( %d )", &u, &nr);
            while(nr--){
                int v; scanf("%d", &v);
                mf.add_edge(u, v, 1);
            }
            mf.add_edge(src, i, 1);
            mf.add_edge(n+i, dst, 1);
        }
        printf("%d\n", mf.solve(src, dst));
    }
    return 0;
}
