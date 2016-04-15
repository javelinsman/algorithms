#include <cstdio>
#include <vector>
using namespace std;


struct SegmentTree{
    typedef long long ll;
    typedef vector<ll> vl;

    vl tree;
    ll offset;
    ll defval;
    ll (*op)(ll a, ll b);

    SegmentTree(ll _size, ll _defval, ll (*_op)(ll a, ll b)): op(_op), defval(_defval) {
        for(offset = 1;offset < _size;offset *= 2);
        printf("offset = %lld\n", offset);
        tree = vl(offset * 2, _defval);
    }

    void push(ll ind, ll val){
        ind += offset;
        tree[ind] = val;
        while(ind > 0){
            ind /= 2;
            tree[ind] = op(tree[2*ind], tree[2*ind+1]);
        }
    }

    ll query(ll ini, ll fin){
        ll ans = defval;
        ini += offset;
        fin += offset;
        while(ini <= fin){
            if(ini % 2 == 1){
                ans = op(ans, tree[ini++]);
            }
            if(fin % 2 == 0){
                ans = op(ans, tree[fin--]);
            }
            ini /= 2;
            fin /= 2;
        }
        return ans;
    }
};

typedef long long ll;

int main(){
    SegmentTree mytree(10, 0, [](ll a, ll b){return a + b;});
    for(int i=0;i<10;i++){
        mytree.push(i, i);
    }
    int n; scanf("%d", &n);
    while(n--){
        int a, b, c; scanf("%d%d%d", &a, &b, &c);
        if(a == 1) mytree.push(b, c);
        else printf("%lld\n", mytree.query(b, c));
    }
    return 0;
}
