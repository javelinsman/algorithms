#include <cstdio>
#include <cstdlib>
#include <vector>
#include <algorithm>
using namespace std;

typedef vector<int> vi;
typedef vector<vi> vvi;

const int INF = 987654321;
const int START_POINT = 0;

int n;
vvi dist;
vi visited;

bool visited_all_city(){
    for(int i=0;i<n;i++) if(!visited[i]) return false;
    return true;
}

/*
 * This implementation is apperantly O(n!)
 * However, this approach is more closer to dp
 * instead of exaustive search
 * f(visited, here) -> min length of remaining city
 */
int tsp(int here){
    visited[here] = true;
    int ret = INF;
    if(visited_all_city()) ret = dist[here][START_POINT];
    else{
        for(int there=0;there<n;there++){
            if(!visited[there]){
                ret = min(ret, dist[here][there] + tsp(there));
            }
        }
    }
    visited[here] = false;
    return ret;
}

int main(){
    scanf("%d", &n);
    visited = vi(n, false);
    dist = vvi(n, vi(n));
    for(int i=0;i<n;i++) for(int j=0;j<n;j++) dist[i][j] = dist[j][i] = rand()%100;
    printf("Randomly generated distances are\n");
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++) printf("%d ", dist[i][j]);
        printf("\n");
    }
    printf("minimum length by tsp_nfac is : %d\n", tsp(START_POINT));
    return 0;
}
