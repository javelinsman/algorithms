#include <cstdio>

/*
 * Parametric Search : Integer
 * - let f : N -> {0, 1} where f(x) < f(y) => x < y
 * - find minimum x s.t. f(x) = 1 using binary search
 * - [lo, hi] represents the range of interest 
 * - since lo <= (lo + hi) / 2 < hi
 *      lo = mid + 1 when f(mid) = 0 since mid is worthless
 * - if mid := (lo + hi + 1) / 2, then it should be implemented vice versa
 */

const int MIN = 1, MAX = 99999; // f(MIN) = 0, f(MAX) = 1

bool valid(int l){
    return l >= 100;
}

int para_search(){
    int lo = MIN, hi = MAX;
    while(lo < hi){
        int mid = (lo + hi) / 2;
        if(valid(mid)) hi = mid;
        else lo = mid + 1;
    }
    return lo;
}

int main(){
    printf("%d\n", para_search()); // 100
    return 0;
}
