#include <cstdio>
#include <vector>
using namespace std;

/*
 * Segment Tree
 * supports point-wise update and range query
 *
 * Usage
 *
 * SegmentTree<T> st(size, default value, op);
 *      - size is the number of elements, 0 to size-1
 *      - op is the operator which satisfies associative property
 *      - default value is the identity elemend of op
 *      - ex. SegmentTree<int> st(100, 1, [](int a, int b){return a * b;});
 * st.push(int i, T t);
 * st.query(int i, int j);
 */

template <typename T>
struct SegmentTree{
    vector<T> tree;
    int offset;
    T defval;
    T (*op)(T a, T b);

    SegmentTree(T _size, T _defval, T (*_op)(T a, T b)): op(_op), defval(_defval) {
        for(offset = 1;offset < _size;offset *= 2);
        tree = vector<T>(offset * 2, _defval);
    }

    void push(int ind, T val){
        ind += offset;
        tree[ind] = val;
        while(ind > 0){
            ind /= 2;
            tree[ind] = op(tree[2*ind], tree[2*ind+1]);
        }
    }

    T query(int ini, int fin){
        T ans = defval;
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
