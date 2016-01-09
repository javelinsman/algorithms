#include <queue>
#include <vector>
#include <functional>
using namespace std;

typedef vector<int> vi;
typedef vector<vi> vvi;
typedef pair<int, int> pii;

/*
 * Dijkstra Algorithm
 * - compute the minimum distance from "ini" to "fin"
 * - the graph is implemented as vvi type
 * - though the number of iteration of major loop can be small as V, the critical part is inserting to pq, which should occur at least E times. 
 * - time complexity : O(ElogV)
 */
int dijkstra(vvi& graph, int ini, int fin){
    int n = graph.size();
    priority_queue<pii, vector<pii>, greater<pii> > pq;
    vi dp(n, -1);
    pq.emplace(0, ini); dp[ini] = 0;
    while(!pq.empty()){
        int dist = pq.top().first, here = pq.top().second; pq.pop();
        if(dist != dp[here]) continue;
        for(int there : graph[here]){
            if(dp[there] == -1 || dp[there] > dp[here] + graph[here][there]){
                dp[there] = dp[here] + graph[here][there];
                pq.emplace(dp[there], there);
            }
        }
    }
    return dp[fin];
}

/*
 * TODO : add test data and verify the implementation
 */
int main(){
    return 0;
}
