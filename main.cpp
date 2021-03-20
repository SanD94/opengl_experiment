#include <iostream>
#include "vec.h"
#include "mats.h"
// #include "exp.h"

using namespace std;

int main() {
    vec<2> s(float(20), float(10));
    vec<2> v(float(10), float(1000));
    mat<2> x(s,v);
    mat<2> yy(float(10), float(20), float(30), float(40));
    mat<2> qq(yy);
    
    //

    return 0;
}