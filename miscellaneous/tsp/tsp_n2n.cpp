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

/*
 * This implementation is O(n 2^n)
 * using bitmask memoization
 * f(visited, here) -> min length of remaining city
 */
vvi cache;
int tsp(int visited, int here){
    int &ret = cache[visited][here];
    if(ret != -1) return ret;
    else ret = INF;
    visited |= 1 << here;
    if(visited == (1 << n) - 1) ret = dist[here][START_POINT];
    else{
        for(int there=0;there<n;there++){
            bool v = (visited >> there) & 1;
            if(!v){
                ret = min(ret, dist[here][there] + tsp(visited, there));
            }
        }
    }
    visited &= ~(1 << here);
    return ret;
}

int main(){
    scanf("%d", &n);
    dist = vvi(n, vi(n));
    cache = vvi(1<<n, vi(n, -1));
    for(int i=0;i<n;i++) for(int j=0;j<n;j++) dist[i][j] = dist[j][i] = rand()%100;
    printf("Randomly generated distances are\n");
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++) printf("%d ", dist[i][j]);
        printf("\n");
    }
    printf("minimum length by tsp_n2n is : %d\n", tsp(0, START_POINT));
    return 0;
}
