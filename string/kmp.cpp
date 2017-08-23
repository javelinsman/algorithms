#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;

vector<int> get_pi(string& s){
    int n = s.size(), j = 0;
    vector<int> pi(n, 0);
    for(int i=1;i<n;i++){
        while(j > 0 && s[i] != s[j]){
            j = pi[j-1];
        }
        if(s[i] == s[j]){
            pi[i] = ++j;
        }
    }
    return pi;
}

vector<int> kmp(string& s, string& t){
    vector<int> pi = get_pi(t);
    vector<int> ans;
    int n = s.size(), m = t.size(), j = 0;
    for(int i=0;i<n;i++){
        while(j > 0 && s[i] != t[j]){
            j = pi[j-1];
        }
        if(s[i] == t[j]){
            if(j == m-1){
                ans.push_back(i);
                j = pi[j];
            }
            else{
                j++;
            }
        }
    }
    return ans;
}
