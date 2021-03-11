#include <iostream>
#include "vec.h"

using namespace std;

int main() {
    vec<6> s(20, 10, 2, 5, 10, 2);
    vec<6> v(float(10));
    
    cout << cross(s,v) << endl;

    return 0;
}