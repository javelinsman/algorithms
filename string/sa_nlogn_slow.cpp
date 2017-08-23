#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;

struct node {
    int ind, r1, r2;
    node(){}
    node(int _ind, int _r1, int _r2) : ind(_ind), r1(_r1), r2(_r2) {}
    bool operator<(const node& rhs) const{
        if(r1 != rhs.r1) return r1 < rhs.r1;
        if(r2 == -1) return true;
        else if(rhs.r2 == -1) return false;
        else return r2 < rhs.r2;
    }
    
    bool operator==(const node& rhs) const{
        return r1 == rhs.r1 && r2 == rhs.r2;
    }
};

string s;

void print(vector<node>& sa){
    for(auto& n : sa){
        printf("[%s_%d_%d] ", s.c_str() + n.ind, n.r1, n.r2);
    }
    printf("\n");
}

void radix_sort(vector<node>& sa){
    int n = sa.size();
    vector<vector<node>> v(n+1);

    for(int i=0;i<n;i++){
        v[sa[i].r2+1].push_back(sa[i]);
    }

    sa.clear();
    for(int i=0;i<=n;i++){
        for(auto& nd : v[i]) sa.push_back(nd);
    }

    v.clear(); v.resize(n+1);

    for(int i=0;i<n;i++){
        v[sa[i].r1+1].push_back(sa[i]);
    }

    sa.clear();
    for(int i=0;i<=n;i++){
        for(auto& nd : v[i]) sa.push_back(nd);
    }
}

void rearrange_rank(vector<node>& sa, int k){
    int n = sa.size();
    vector<int> new_rank(n); int p = 0;
    for(int i=0;i<n;i++){
        if(i == 0 || sa[i-1] == sa[i]){
            new_rank[sa[i].ind] = p;
        }
        else{
            new_rank[sa[i].ind] = ++p;
        }
    }
    for(int i=0;i<n;i++){
        sa[i].r1 = new_rank[sa[i].ind];
        sa[i].r2 = sa[i].ind + k < n ? new_rank[sa[i].ind + k] : -1;
    }
}

vector<int> suffix_array(string& s){
    int n = s.size();

    vector<node> sa(n);
    for(int i=0;i<n;i++){
        sa[i].ind = i;
        sa[i].r1 = s[i] - 'a';
        sa[i].r2 = i+1 < n ? s[i+1] - 'a' : -1;
    }
    sort(sa.begin(), sa.end());

    int sz = 1;
    while(1){
        sz *= 2;
        rearrange_rank(sa, sz);
        radix_sort(sa);
        if(sz > n) break;
    }

    vector<int> ret(n);
    for(int i=0;i<n;i++) ret[i] = sa[i].ind;
    return ret;
}

vector<int> longest_common_prefix(string& s, vector<int>& sa){
    int n = sa.size();
    vector<int> lcp(n);
    vector<int> rank(n);
    for(int i=0;i<n;i++) rank[sa[i]] = i;
    int h = 0;
    for(int i=0;i<n;i++){
        if(h > 0) h--;
        if(rank[i] == n-1) continue;
        int j = sa[rank[i]+1];
        while(s[i+h] == s[j+h]) h++;
        lcp[rank[j]] = h;
    }
    return lcp;
}

int main(){
    cin >> s;
    vector<int> sa = suffix_array(s);
    vector<int> lcp = longest_common_prefix(s, sa);
    for(int d : sa) printf("%d ", d + 1); printf("\n");
    printf("x "); for(int i=1;i<lcp.size();i++) printf("%d ", lcp[i]);
    printf("\n");
    return 0;
}
