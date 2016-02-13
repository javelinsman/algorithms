#include <cstdio>
#include <vector>
using namespace std;

typedef vector<int> vi;
typedef vector<vi> vvi;
typedef vector<bool> vb;
typedef vector<vb> vvb;

/*
 * Depth-First Search on graph
 * - implemented with recursion
 * - vector "visited" need to be initialized
 * - time complexity : O(V+E)
 */

vvi g;
vb visited;

bool other_constrains(){ return true; }

void dfs(int here){
    visited[here] = true;
    for(int there : g[here]){
        bool valid = !visited[there] &&
            other_constrains();
        if(valid) dfs(there);
    }
}

/*
 * Depth-First Search on array
 * - implemented with recursion
 * - DFS on the 2D array with island - sea model
 * - time complexity : O(wh)
 */

int h, w;
vvi m;
vvb visited2;

const int di[4] = { 1, -1, 0, 0 };
const int dj[4] = { 0, 0, 1, -1 };

bool is_inside_interval(int x, int begin, int end){
    return begin <= x && x < end;
}

void dfs_array(int i, int j){
    visited2[i][j] = true;
    for(int k = 0; k < 4; k++){
        int ni = i + di[k], nj = j + dj[k];
        bool valid =
            is_inside_interval(ni, 0, h) &&
            is_inside_interval(nj, 0, w) &&
            m[ni][nj] && !visited2[ni][nj];
        if(valid) dfs_array(ni, nj);
    }
}
