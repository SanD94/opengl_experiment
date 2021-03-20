//////////////////////////////////////////////////////////////////////////////
//
//  --- mat.h ---
//
//////////////////////////////////////////////////////////////////////////////

#ifndef __MAT_H__
#define __MAT_H__

#include "vec.h"
#include <vector>
#include <cstdio>
#include <type_traits>
#include <tuple>

    

template<int N>
class mat {

    std::vector<vec<N>> m;

private:
    // vector generator init for float
    template<int curm, int curv, typename T>
    void vec_generate(std::vector<T> &v) {
        m[curm] = vec<N>(v);
        return;
    }
    
    // vector generator recursion for float
    template<int curm, int curv, typename... T, typename U>
    void vec_generate(std::vector<U> &v, U first, T... rest) {
        if constexpr (curv == N) {
            m[curm] = vec<N>(v);
            vec_generate<curm+1, 0>(v, first, rest...);
            return;
        }
        v[curv] = first;
        vec_generate<curm, curv+1>(v, rest...);
    }



    template<typename... T>
    void mat_float(T... vals) {
        static_assert(N * N == sizeof...(vals),
             "The number of parameters should be N square.");
        m = std::vector<vec<N>>(N);
        auto v = std::vector<float>(N);
        vec_generate<0, 0>(v, vals...); 
    }

    // N vectors
    template<typename... T> // requires is_same_v<T, vec<N>> c++20 // for vector
    void mat_vec(T&&... vals) {
        static_assert(N == sizeof...(vals), 
            "The number of parameters should be N");
        m = std::vector<vec<N>>{vals...};
    }
    
    
    


public:
    //
    //  --- Constructors and Destructors ---
    //

    mat(const float d = float(1.0))  { // Diagonal
        m = std::vector<vec<N>>(N);
        for(int i = 0; i < N; i++)
            m[i][i] = d;
    }
    
    
    template<typename... Ts>
    mat(const Ts&... vals) {
        if constexpr (std::conjunction_v<std::is_floating_point<Ts>...>)
            mat_float(vals...);
        else if constexpr (std::conjunction_v<std::is_same<vec<N>, Ts>...>)
            mat_vec(vals...);
    }
    
    void print() {
        std::cout << m.size() << std::endl;
        for(int i=0;i<m.size();i++) {
            std::cout << m[i] << std::endl;
        }
    }
    

    


    // mat2(GLfloat m00, GLfloat m10, GLfloat m01, GLfloat m11)
    // {
    //     _m[0] = vec2(m00, m10);
    //     _m[1] = vec2(m01, m11);
    // }
};
#endif // __MAT_H__
