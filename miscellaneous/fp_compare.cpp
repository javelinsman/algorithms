#include <cstdio>
#include <cmath>
#include <algorithm>
using namespace std;

/* 
 * compare two floating point numbers
 * using absolute and relative error
 */

bool double_equal(double x, double y){
    double diff = fabs(x - y);
    if(diff < 1e-10) return true;
    else return diff <= max(fabs(x), fabs(y)) * 1e-8;
}

bool double_greater(double x, double y){
    if(double_equal(x, y)) return false;
    return x < y;
}

int main(){
    double d = 3823123912391283971239.12312333212312123;
    printf("%d\n", 1.0 == 1.0 / d * d); // 0
    printf("%d\n", double_equal(1.0, 1.0 / d * d)); // 1
    return 0;
}
