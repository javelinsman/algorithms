#include <cstdio>
#include <vector>
using namespace std;

typedef vector<int> vi;
typedef long long ll;
typedef vector<ll> vl;

/*
 * Compute Partial Sum
 * - It is easy thing but the way should be normalized
 * - given the sequence of n integers
 * - compute the partial sum defined as
 *   psum[n] = partial sum of integers in range [0, n)
 *
 * To get range sum
 * - sum[a, b) = psum[b] - psum[a]
 * - sum[a, b] = psum[b+1] - psum[a]
 * - sum(a, b) = psum[b] - psum[a+1]
 */

vl partial_sum(vi& seq){
    int n = seq.size();
    vl psum(n+1, 0);
    for(int i=0;i<n;i++){
        psum[i+1] = psum[i] + seq[i];
    }
    return psum;
}
