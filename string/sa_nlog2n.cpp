#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct node{
    int ind, r1, r2;
    node(){}
    bool operator<(const node& rhs) const {
        if(r1 != rhs.r1) return r1 < rhs.r1;
        else return r2 < rhs.r2;
    }
    bool operator==(const node& rhs) const {
        return r1 == rhs.r1 && r2 == rhs.r2;
    }
};

bool rearrange_rank(vector<node>& v, int sz){
    int n = v.size();
    node last; last.r1 = -1; last.r2 = -1;
    int cnt = -1;
    vector<int> rnk(n);
    for(int i=0;i<v.size();i++){
        if(!(last == v[i])) last = v[i], cnt++;
        rnk[v[i].ind] = cnt;
    }
    for(int i=0;i<v.size();i++){
        v[i].r1 = rnk[v[i].ind];
        v[i].r2 = v[i].ind + sz < n ? rnk[v[i].ind + sz] : -1;
    }
    return cnt == n-1;
}

vector<int> suffix_array(string& s){
    int n = s.size();
    vector<node> v(n);
    for(int i=0;i<n;i++){
        v[i].ind = i;
        v[i].r1 = s[i] - 'a';
        v[i].r2 = i+1 < n ? s[i+1] - 'a' : -1;
    }
    sort(v.begin(), v.end());
    int sz = 1;
    while(sz < n){
        sz *= 2;
        if(rearrange_rank(v, sz)) break;
        sort(v.begin(), v.end());
    }
    vector<int> ret(n);
    for(int i=0;i<n;i++) ret[i] = v[i].ind;
    return ret;
}

int main(){
    string s; cin >> s;
    vector<int> sa = suffix_array(s);
    for(int d : sa) printf("%d\n", d);
    return 0;
}
