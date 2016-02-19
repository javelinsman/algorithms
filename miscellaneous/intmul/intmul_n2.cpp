#include <iostream>
#include <string>
#include <vector>
using namespace std;

typedef vector<int> vi;

void normalize(vi& v){
    int n = v.size();
    v.push_back(0);
    for(int i=0;i<n;i++){
        if(v[i] >= 0){
            v[i+1] += v[i] / 10;
            v[i] %= 10;
        }
        else{
            int borrow = (-v[i] - 1) / 10 + 1;
            v[i] += borrow * 10;
            v[i+1] -= borrow;
        }
    }
    while(v.size() > 1 && v.back() == 0) v.pop_back();
}

void pprint(const vi& v){
    int n = v.size();
    bool det = true;
    for(int i=n-1;i>=0;i--){
        if(det && v[i] == 0) continue;
        else det = false;
        cout << v[i];
    }
    if(det) cout << 0;
    cout << endl;
}

vi multiply(const vi& a, const vi& b){
    int n_a = a.size(), n_b = b.size();
    vi c(n_a + n_b, 0);
    for(int i=0;i<n_a;i++){
        for(int j=0;j<n_b;j++){
            c[i+j] += a[i] * b[j];
        }
    }
    normalize(c);
    return c;
}

int main(){
    string s_a, s_b; cin >> s_a >> s_b;
    int n_a = s_a.size(), n_b = s_b.size();
    vi a(n_a), b(n_b);
    for(int i=0;i<n_a;i++) a[i] = s_a[n_a - i - 1] - '0';
    for(int i=0;i<n_b;i++) b[i] = s_b[n_b - i - 1] - '0';
    pprint(multiply(a, b));
    return 0;
}
