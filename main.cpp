#include "sand.h"

int main() {
    vec<2> s(20, 10);
    vec<2> v(10, 1000);
    mat<2> x(s,v);
    mat<2> yy(10.0, 20, 30, 40);
    mat<2> qq(yy);
    
    std::cout << x << std::endl;
    std::cout << yy << std::endl;
    //
    std::cout << qq[0][0] << std::endl;

    return 0;
}