#ifndef __EXP_H__
#define __EXP_H__

#include <vector>

// template<int N, int cur, typename...T, typename U>
// void vec_generate(std::vector<U> &v, T... args);

template<int N, int cur, typename U>
void vec_generate(std::vector<U> &v) {
    static_assert(N == cur, "Insufficient paramaters");
    return;
}

template<int N, int cur, typename... T, typename U>
void vec_generate(std::vector<U> &v, U first, T... rest) {
    if (cur == N) return;
    v[cur] = first;
    vec_generate<N, cur+1>(v, rest...);
}





#endif