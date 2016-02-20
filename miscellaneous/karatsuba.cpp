#include <cstdio>
#include <iostream>
#include <string>
#include <algorithm>
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

/*
 * O(nm) straight forward integer multiplication
 */
vi multiply_raw(const vi& a, const vi& b){
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

vi add(const vi& a, const vi& b){
    int n_a = a.size(), n_b = b.size();
    int n = max(n_a, n_b);
    vi c(n);
    for(int i=0;i<n;i++){
        if(i < n_a) c[i] += a[i];
        if(i < n_b) c[i] += b[i];
    }
    normalize(c);
    return c;
}
vi sub(const vi& a, const vi& b){
    int n_a = a.size(), n_b = b.size();
    int n = max(n_a, n_b);
    vi c(n);
    for(int i=0;i<n;i++){
        if(i < n_a) c[i] += a[i];
        if(i < n_b) c[i] -= b[i];
    }
    normalize(c);
    return c;
}
vi shift(const vi& v, int k){
    int n = v.size();
    vi c(n+k);
    for(int i=0;i<n;i++) c[i+k] = v[i];
    normalize(c);
    return c;
}

/*
 * O(n^lg(3)) karatsuba integer multiplication
 */
vi multiply(const vi& a, const vi& b){
    int n_a = a.size(), n_b = b.size();
    int n = max(n_a, n_b);
    if(n < 50)
        return multiply_raw(a, b);
    else{
        int k = (n+1) / 2;
        vi a0, a1, b0, b1;
        for(int i=0;i<n_a;i++){
            if(i<k) a0.push_back(a[i]);
            else a1.push_back(a[i]);
        }
        for(int i=0;i<n_b;i++){
            if(i<k) b0.push_back(b[i]);
            else b1.push_back(b[i]);
        }
        vi z0 = multiply(a0, b0);
        vi z2 = multiply(a1, b1);
        vi z3 = multiply(add(a0, a1), add(b0, b1));
        vi z1 = sub(sub(z3, z0), z2);
        return add(add(
                    shift(z2, 2*k),
                    shift(z1, k)),
                z0);
    }
}

int main2(){
    string s_a, s_b; cin >> s_a >> s_b;
    int n_a = s_a.size(), n_b = s_b.size();
    vi a(n_a), b(n_b);
    for(int i=0;i<n_a;i++) a[i] = s_a[n_a - i - 1] - '0';
    for(int i=0;i<n_b;i++) b[i] = s_b[n_b - i - 1] - '0';
    pprint(multiply_raw(a, b));
    pprint(multiply(a, b));
    return 0;
}
