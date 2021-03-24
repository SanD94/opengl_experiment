#include <iostream>
#include "vec.h"
#include "mat.h"

using namespace std;

int main() {
    vec<2> s(20, 10);
    vec<2> v(10, 1000);
    mat<2> x(s,v);
    mat<2> yy(10.0, 20, 30, 40);
    mat<2> qq(yy);
    
    cout << x << endl;
    cout << yy << endl;
    //
    cout << qq[0][0] << endl;

    return 0;
}