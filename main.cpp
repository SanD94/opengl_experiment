#include "sand.h"

int main() {
    vec<5> s(10,20,10,20,50);
    vec<2> t(10);
    vec<2> q(t);
    std::cout << s << std::endl;
    t[1] = 0;
    std::cout << t << std::endl;
    std::cout << q << std::endl;
    mat<2> a(20);
    mat<2> tt(10, 20, 40, 30);
    std::cout << a << std::endl;
    
    tt[0][1] = 10;
    float* ss = tt;
    for(int i=0;i<4;i++) { std::cout << *ss << std::endl; ss++;}

    return 0;
}