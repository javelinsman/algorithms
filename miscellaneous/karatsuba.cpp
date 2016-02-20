#include <iostream>
#include <cstdio>
#include <cstdlib>
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

void add_to(vi& a, const vi& b, int k = 0){
    if(a.size() < b.size() + k) a.resize(b.size() + k);
    for(int i=0;i<b.size();i++){
        a[i+k] += b[i];
    }
    normalize(a);
}

void sub_from(vi& a, const vi& b){
    if(a.size() < b.size()) a.resize(b.size());
    for(int i=0;i<b.size();i++){
        a[i] -= b[i];
    }
    normalize(a);
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
        add_to(a0, a1); add_to(b0, b1);
        vi z1 = multiply(a0, b0);
        sub_from(z1, z0); sub_from(z1, z2);
        vi ret;
        add_to(ret, z0);
        add_to(ret, z1, k);
        add_to(ret, z2, 2*k);
        return ret;
    }
}

int main(){
    printf("Do you want to test automatically(y/n) ? ");
    char flag; scanf("%c", &flag);
    if(flag == 'n'){
        string s_a, s_b; cin >> s_a >> s_b;
        int n_a = s_a.size(), n_b = s_b.size();
        vi a(n_a), b(n_b);
        for(int i=0;i<n_a;i++) a[i] = s_a[n_a - i - 1] - '0';
        for(int i=0;i<n_b;i++) b[i] = s_b[n_b - i - 1] - '0';
        pprint(multiply_raw(a, b));
        pprint(multiply(a, b));
    }
    else{
        printf("Enter the maximum problem size : ");
        int n; scanf("%d", &n);
        printf("Start testing 100 cases\n");
        for(int ti=0;ti<100;ti++){
            int l1 = 1 + rand()%(n-1);
            int l2 = 1 + rand()%(n-1);
            vi a(l1), b(l2);
            for(int i=0;i<l1;i++) a[i] = rand()%10;
            for(int i=0;i<l2;i++) b[i] = rand()%10;
            clock_t t1 = clock();
            vi c1 = multiply(a, b);
            clock_t t2 = clock();
            vi c2 = multiply_raw(a, b);
            clock_t t3 = clock();
            double d1 = (double)(t2 - t1) / CLOCKS_PER_SEC;
            double d2 = (double)(t3 - t2) / CLOCKS_PER_SEC;
            if(equal(c1.begin(), c1.end(), c2.begin())){
                printf("[Success : %d] Two outputs are equal.\n", ti+1);
                printf("\tproblem size %d x %d, karatsuba : %.3f sec(s) %s raw : %.3f sec(s)\n", l1, l2, d1, d1>d2?">":"<", d2);
            }
            else{
                printf("[Fail : %d] Two outputs are different.\n", ti+1);
                printf("a : "); pprint(a);
                printf("b : "); pprint(b);
                printf("c1 : "); pprint(c1);
                printf("c2 : "); pprint(c2);
            }
        }
    }
    return 0;
}
