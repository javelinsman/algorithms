#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

/*
 * Longest Increasing Subsequence
 * - given a sequence of n integers
 * - find the longest (strictly) increasing subsequence
 * - time complexity : O(nlogk) where k is the length of LIS
 */


/*
 * this is the crude implementation of LIS,
 * having time complexity of O(n2)
 * if there is a sequence S of generic type T
 * which satisfies S[i] < S[j] => i < j
 * but does NOT guarantee that for any i < j < k
 *  s[i] !<> s[j] and s[i] < s[k] => s[j] < s[k]
 * then this approach might be used
 */
vector<int> lis_n2(vector<int>& s){
    int n = s.size();
    vector<int> d(n), next(n, n);
    d[n-1] = 1;
    for(int i=n-2;i>=0;i--){
        d[i] = 1;
        for(int j=i+1;j<n;j++){
            if(s[i] < s[j] && d[i] < d[j] + 1){
                d[i] = d[j] + 1;
                next[i] = j;
            }
        }
    }
    auto it = max_element(d.begin(), d.end());
    vector<int> ret;
    for(int i=it-d.begin();i<n;i=next[i]){
        ret.push_back(s[i]);
    }
    return ret;
}

/*
 * This is the modest implementation of LIS
 * having time complexity of O(nlogk)
 * with much shorter and simpler code
 */
vector<int> lis(vector<int>& s){
    int n = s.size();
    vector<int> d;
    for(int i=0;i<n;i++){
        auto it = lower_bound(d.begin(), d.end(), s[i]);
        if(it == d.end()) d.push_back(s[i]);
        else *it = s[i];
    }
    return d;
}

int main(){
    int n; scanf("%d", &n);
    vector<int> s(n);
    for(int i=0;i<n;i++) scanf("%d", &s[i]);
    vector<int> l1 = lis(s);
    vector<int> l2 = lis_n2(s);
    return 0;
}
