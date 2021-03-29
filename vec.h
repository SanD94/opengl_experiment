#ifndef __VEC_H__
#define __VEC_H__

#include "sand.h"

namespace Sand {

template<typename T>
std::ostream& operator << (std::ostream& os, const std::vector<T> v) {
    std::copy(v.begin(), v.end()-1, std::ostream_iterator<T>(os, ", "));
    os << *(v.end() - 1);
    return os; 
}

template <int N>
struct vec {
    std::vector<float> v;

    vec(float s = float(0.0)) {
        v = std::vector<float>(N, s);
    }

    template<typename... T>
    vec(T... vals) {
        static_assert(N == sizeof...(vals), "[vec] : Parameter size should be N");
        v = std::vector<float>{static_cast<float>(vals)...};
    }
    

    vec(const vec& v) : v(v.v) {}
    vec(const std::vector<float>& _v) : v(_v) {}
    
    template<int I, typename... T>
    vec(const vec<I>& _v, T... vals) {
        static_assert(N == I + sizeof...(vals), "[vec]: Total parameter size should be N");
        auto rest = std::vector<float>{static_cast<float>(vals)...};
        v = std::vector<float>(N);
        std::copy(_v.v.begin(), _v.v.end(), v.begin());
        std::copy(rest.begin(), rest.end(), v.begin() + I);
    }


    float &operator[](int i) { return v[i]; } // lvalue
    const float operator[](int i) const { return v[i]; } // rvalue

    vec operator-() const {
        std::vector<float> res(N);
        std::transform(v.begin(), v.end(), res.begin(), 
            [](float x) -> float { return -x; });
        return vec(res);
    }
    
    vec operator+ (const vec& _v) const { 
        std::vector<float> res(N);
        std::transform(v.begin(), v.end(), _v.v.begin(), res.begin(), std::plus<>{});
        return vec(res);
    }
    
    vec operator- (const vec& _v) const {
        std::vector<float> res(N);
        std::transform(v.begin(), v.end(), _v.v.begin(), res.begin(), std::minus<>{});
        return vec(res);
    }
    
    vec operator * (const float s) const { 
        std::vector<float> res(N);
        std::transform(v.begin(), v.end(), res.begin(), 
            [s](float x) -> float { return s * x; });
        return vec(res);
    }

    vec operator * (const vec& _v) const { 
        std::vector<float> res(N);
        std::transform(v.begin(), v.end(), _v.v.begin(), res.begin(), std::multiplies<>{});
        return vec(res);
    }
    
    friend vec operator * (const float s, const vec& v)
    { return v * s; }
    
    vec operator / (const float s) const {
        float r = 1.0 / s;
        return *this * r;
    }
    
    vec& operator += (const vec& _v) {
        std::transform(v.begin(), v.end(), _v.v.begin(), v.begin(), std::plus<>{});
        return *this;
    }
    
    vec& operator -= (const vec& _v) {
        std::transform(v.begin(), v.end(), _v.v.begin(), v.begin(), std::minus<>{});
        return *this;
    }
    
    vec& operator *= (const vec& _v) {
        std::transform(v.begin(), v.end(), _v.v.begin(), v.begin(), std::multiplies<>{});
        return *this;
    }
    
    vec& operator *= (const float s) {
        std::transform(v.begin(), v.end(), v.begin(),
                [s](float x) -> float {return s * x;});
        return *this;
    }
    
    vec& operator /= (const float s) {
        float r = 1.0 / s;
        *this *= r;
        return *this;
    }
    
    friend std::ostream& operator << (std::ostream& os, const vec& v) {
         return os << "(" << v.v << ")";
    }
    
    friend std::istream& operator >> (std::istream& is, vec& v) {
        std::copy_n(std::istream_iterator<float>(is), 
            N,
            v.v.begin());
        return is;
    }
    

    // Conversion
    operator const float* () const {
        return static_cast<const float*>(&v[0]);
    }
    
    operator float* () {
        return static_cast<float*>(&v[0]);
    }
    
};

template <int N>
inline float dot (const vec<N>& u, const vec<N>& v) {
    return std::inner_product(u.v.begin(), u.v.end(), v.v.begin(), 0);
}

template <int N>
inline float length (const vec<N>& v) {
    return std::sqrt(dot(v, v));
}

template <int N>
inline vec<N> normalize (const vec<N>& v) {
    return v / length(v);
}

template <int N>
inline vec<3> cross(const vec<N>&u, const vec<N>&v) {
    static_assert(2 < N && N < 5);
    return vec<3>(
        u[1] * v[2] - u[2] * v[1],
        u[2] * v[0] - u[0] * v[2],
        u[0] * v[1] - u[1] * v[0] 
    );
}


} // namespace Sand

#endif  // __VEC_H__
