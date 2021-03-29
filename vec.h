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
    std::vector<GLfloat> v;

    vec(GLfloat s = GLfloat(0.0)) {
        v = std::vector<GLfloat>(N, s);
    }

    template<typename... T>
    vec(T... vals) {
        static_assert(N == sizeof...(vals), "[vec] : Parameter size should be N");
        v = std::vector<GLfloat>{static_cast<GLfloat>(vals)...};
    }
    

    vec(const vec& v) : v(v.v) {}
    vec(const std::vector<GLfloat>& _v) : v(_v) {}
    
    template<int I, typename... T>
    vec(const vec<I>& _v, T... vals) {
        static_assert(N == I + sizeof...(vals), "[vec]: Total parameter size should be N");
        auto rest = std::vector<GLfloat>{static_cast<GLfloat>(vals)...};
        v = std::vector<GLfloat>(N);
        std::copy(_v.v.begin(), _v.v.end(), v.begin());
        std::copy(rest.begin(), rest.end(), v.begin() + I);
    }


    GLfloat &operator[](int i) { return v[i]; } // lvalue
    const GLfloat operator[](int i) const { return v[i]; } // rvalue

    vec operator-() const {
        std::vector<GLfloat> res(N);
        std::transform(v.begin(), v.end(), res.begin(), 
            [](GLfloat x) -> GLfloat { return -x; });
        return vec(res);
    }
    
    vec operator+ (const vec& _v) const { 
        std::vector<GLfloat> res(N);
        std::transform(v.begin(), v.end(), _v.v.begin(), res.begin(), std::plus<>{});
        return vec(res);
    }
    
    vec operator- (const vec& _v) const {
        std::vector<GLfloat> res(N);
        std::transform(v.begin(), v.end(), _v.v.begin(), res.begin(), std::minus<>{});
        return vec(res);
    }
    
    vec operator * (const GLfloat s) const { 
        std::vector<GLfloat> res(N);
        std::transform(v.begin(), v.end(), res.begin(), 
            [s](GLfloat x) -> GLfloat { return s * x; });
        return vec(res);
    }

    vec operator * (const vec& _v) const { 
        std::vector<GLfloat> res(N);
        std::transform(v.begin(), v.end(), _v.v.begin(), res.begin(), std::multiplies<>{});
        return vec(res);
    }
    
    friend vec operator * (const GLfloat s, const vec& v)
    { return v * s; }
    
    vec operator / (const GLfloat s) const {
        GLfloat r = 1.0 / s;
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
    
    vec& operator *= (const GLfloat s) {
        std::transform(v.begin(), v.end(), v.begin(),
                [s](GLfloat x) -> GLfloat {return s * x;});
        return *this;
    }
    
    vec& operator /= (const GLfloat s) {
        GLfloat r = 1.0 / s;
        *this *= r;
        return *this;
    }
    
    friend std::ostream& operator << (std::ostream& os, const vec& v) {
         return os << "(" << v.v << ")";
    }
    
    friend std::istream& operator >> (std::istream& is, vec& v) {
        std::copy_n(std::istream_iterator<GLfloat>(is), 
            N,
            v.v.begin());
        return is;
    }
    

    // Conversion
    operator const GLfloat* () const {
        return static_cast<const GLfloat*>(&v[0]);
    }
    
    operator GLfloat* () {
        return static_cast<GLfloat*>(&v[0]);
    }
    
};

template <int N>
inline GLfloat dot (const vec<N>& u, const vec<N>& v) {
    return std::inner_product(u.v.begin(), u.v.end(), v.v.begin(), 0);
}

template <int N>
inline GLfloat length (const vec<N>& v) {
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
