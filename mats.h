#ifndef __MAT_H__
#define __MAT_H__

#include "vec.h"
#include <vector>
#include <cstdio>
#include <type_traits>
#include <tuple>
#include <cmath>

const float DegreesToRadians = M_PI / 180.0;

    

template<int N>
class mat {

    std::vector<vec<N>> m;

private:
    // vector generator init for float
    template<int curm, int curv, typename T>
    void vec_generate(std::vector<T> &v) {
        m[curm] = vec<N>(v);
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


    mat(const mat<N>& m) : m(m.m) {}
    mat(const std::vector<vec<N>>& _m) : m(_m) {}

    vec<N>& operator [] (int i) { return m[i]; }
    const vec<N>& operator [] (int i) const { return m[i]; }

    mat operator-() const {
        std::vector<vec<N>> res(N);
        std::transform(m.begin(), m.end(), res.begin(),
            [](vec<N> v) -> vec<N> { return -v; });
        return mat(res);
    }

    mat operator + (const mat& _m) const {
        std::vector<vec<N>> res(N);
        std::transform(m.begin(), m.end(), _m.m.begin(), res.begin(), std::plus<>{}); 
        return mat(res);
    }

    mat operator - (const mat& _m) const {
        std::vector<vec<N>> res(N);
        std::transform(m.begin(), m.end(), _m.m.begin(), res.begin(), std::minus<>{});
        return mat(res);
    }

    mat operator * (const float s) const {
        std::vector<vec<N>> res(N);
        std::transform(m.begin(), m.end(), res.begin(),
                [s](vec<N> v) -> vec<N> { return s * v; });
        return mat(res);
    }

    friend mat operator * (const float s, const mat m)
    { return m * s; }

    mat operator * (const mat& _m) const {
        std::vector<vec<N>> res(N);
        for (int i = 0; i < N; i++)
            for(int j = 0; j < N; j++)
                for (int k = 0; k < N; k++)
                    res[i][j] += m[i][k] * _m[k][j];
        return mat(res);
    }

    vec<N> operator * (const vec<N>& v) const {
        std::vector<float> res(N);
        std::transform(m.m.begin(), m.m.end(), res.begin(),
                [v](vec<N> _v) -> float { return dot(v, _v); });
        return vec(res);
    }

    mat operator / (const float s) const {
        float r  = float(1.0) / s;
        return *this * r;
    }


    mat& operator += (const mat& _m) {
        std::transform(m.begin(), m.end(), _m.m.begin(), std::plus<>{});
        return *this;
    }

    mat& operator -= (const mat& _m) {
        std::transform(m.begin(), m.end(), _m.m.begin(), std::minus<>{});
        return *this;
    }

    mat& operator *= (const float s) {
        std::transform(m.begin(), m.end(), m.begin(),
                [s](vec<N> v) -> vec<N> { return s * v; });
        return *this;
    }

    mat& operator /= (const float s) {
        float r = float(1.0) / s;
        return *this *= r;
    }

    friend std::ostream& operator << (std::ostream& os, const mat& m) {
        std::copy(m.m.begin(), m.m.end(), std::ostream_iterator<vec<N>>(os, "\n"));
        return os;
    }

    friend std::istream& operator >> (std::istream& is, mat& m) {
        std::copy_n(std::istream_iterator<vec<N>>(is),
                N,
                m.m.begin());
        return is;
    }
    
    // Conversion operators

    operator const float* () const {
        return static_cast<const float*>(&m[0][0]);
    }

    operator float* () const {
        return static_cast<float*>(&m[0][0]);
    }
};


// Non-class matrix methods

template<int N>
inline mat<N> matrixCompMult(const mat<N>& A, const mat<N>& B) {
    std::vector<vec<N>> res(N);
    std::transform(A.begin(), A.end(), B.begin(), res.begin(), std::multiplies<>{});
    return mat(res);
}

template<int N>
inline mat<N> transpose(const mat<N>& A) {
    std::vector<vec<N>> res(N, vec<N>(0));
    for(int i=0;i<N;i++) for(int j=0;j<N;j++) res[j][i] = A[i][j];
    return mat(res);
}


// Matrix Methods

#define Error(str) std::cerr << "[" __FILE__ ":" << __LINE__ << "] " \
    << str << std::endl

inline mat<4> RotateX(const float theta) {
    float angle = DegreesToRadians * theta;
    mat<4> c;
    c[2][2] = c[1][1] = cos(angle);
    c[2][1] = sin(angle);
    c[1][2] = -c[2][1];
    return c;
}

inline mat<4> RotateY(const float theta) {
    float angle = DegreesToRadians * theta;

    mat<4> c;
    c[2][2] = c[0][0] = cos(angle);
    c[0][2] = sin(angle);
    c[2][0] = -c[0][2];
    return c;
}

inline mat<4> RotateZ(const float theta) {
    float angle = DegreesToRadians * theta;
    mat<4> c;
    c[0][0] = c[1][1] = cos(angle);
    c[1][0] = sin(angle);
    c[0][1] = -c[1][0];
    return c;
}

inline mat<4> Translate(const float x, const float y, const float z) {
    mat<4> c;
    c[0][3] = x; c[1][3] = y; c[2][3] = z;
    return c;
}

inline mat<4> Translate(const vec<3>& v) {
    return Translate(v[0], v[1], v[2]);
}

inline mat<4> Translate(const vec<4>& v) {
    return Translate(v[0], v[1], v[2]);
}


inline mat<4> Scale(const float x, const float y, const float z) {
    mat<4> c;
    c[0][0] = x;
    c[1][1] = y;
    c[2][2] = z;
    return c;
}

inline mat<4> Scale(const vec<3>& v) {
    return Scale(v[0], v[1], v[2]);
}


// Projection Transformations



inline mat<4> Ortho( const float left, const float right,
           const float bottom, const float top,
           const float zNear, const float zFar ) {
    mat<4> c;
    c[0][0] = 2.0/(right - left);
    c[1][1] = 2.0/(top - bottom);
    c[2][2] = 2.0/(zNear - zFar);
    c[3][3] = 1.0;
    c[0][3] = -(right + left)/(right - left);
    c[1][3] = -(top + bottom)/(top - bottom);
    c[2][3] = -(zFar + zNear)/(zFar - zNear);
    return c;
}

inline mat<4> Ortho2D( const float left, const float right,
             const float bottom, const float top ) {
    return Ortho( left, right, bottom, top, -1.0, 1.0 );
}

inline mat<4> Frustum( const float left, const float right,
             const float bottom, const float top,
             const float zNear, const float zFar ) {
    mat<4> c;
    c[0][0] = 2.0*zNear/(right - left);
    c[0][2] = (right + left)/(right - left);
    c[1][1] = 2.0*zNear/(top - bottom);
    c[1][2] = (top + bottom)/(top - bottom);
    c[2][2] = -(zFar + zNear)/(zFar - zNear);
    c[2][3] = -2.0*zFar*zNear/(zFar - zNear);
    c[3][2] = -1.0;
    c[3][3] = 0.0;
    return c;
}

inline mat<4> Perspective( const float fovy, const float aspect,
                 const float zNear, const float zFar) {
    float top   = tan(fovy*DegreesToRadians/2) * zNear;
    float right = top * aspect;
    
    mat<4> c;
    c[0][0] = zNear/right;
    c[1][1] = zNear/top;
    c[2][2] = -(zFar + zNear)/(zFar - zNear);
    c[2][3] = -2.0*zFar*zNear/(zFar - zNear);
    c[3][2] = -1.0;
    c[3][3] = 0.0;
    return c;
}

//----------------------------------------------------------------------------
//
//  Viewing transformation matrix generation
//

inline mat<4> LookAt( const vec<4>& eye, const vec<4>& at, const vec<4>& up ) {
    vec<4> n = normalize(eye - at);
    vec<4> u = vec<4>(normalize(cross(up,n)), 0.0);
    vec<4> v = vec<4>(normalize(cross(n,u)), 0.0);
    vec<4> t = vec<4>(0.0, 0.0, 0.0, 1.0);
    mat<4> c = mat<4>(u, v, n, t);
    return c * Translate( -eye );
}

//----------------------------------------------------------------------------
//
// Generates a Normal Matrix
//
inline mat<3> Normal( const mat<4>& c) {
    mat<3> d;
    float det;
    
    det = c[0][0]*c[1][1]*c[2][2]+c[0][1]*c[1][2]*c[2][1]+c[0][2]*c[1][0]*c[2][1]
    -c[2][0]*c[1][1]*c[0][2]-c[1][0]*c[0][1]*c[2][2]-c[0][0]*c[1][2]*c[2][1];
    
    d[0][0] = (c[1][1]*c[2][2]-c[1][2]*c[2][1])/det;
    d[0][1] = -(c[1][0]*c[2][2]-c[1][2]*c[2][0])/det;
    d[0][2] =  (c[1][0]*c[2][1]-c[1][1]*c[2][0])/det;
    d[1][0] = -(c[0][1]*c[2][2]-c[0][2]*c[2][1])/det;
    d[1][1] = (c[0][0]*c[2][2]-c[0][2]*c[2][0])/det;
    d[1][2] = -(c[0][0]*c[2][1]-c[0][1]*c[2][0])/det;
    d[2][0] =  (c[0][1]*c[1][2]-c[0][2]*c[1][1])/det;
    d[2][1] = -(c[0][0]*c[1][2]-c[0][2]*c[1][0])/det;
    d[2][2] = (c[0][0]*c[1][1]-c[1][0]*c[0][1])/det;
    
    return d;
}


#endif // __MAT_H__
