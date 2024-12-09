#ifndef VECTOR_H
#define VECTOR_H

#include <cmath>
#include <vector>

template <size_t DIM , typename T> 
class vec {
    protected:
      T components[DIM];
      int len = DIM;
      
    public:
      T operator[](int i) const {return components[i]; } //non-mutable
      T& operator[](int i) {return components[i]; } //mutable

      vec& operator+=(const vec& v) {
        for (int i = 0; i < len; i++) {
            components[i] += v[i];
        }

        return *this;
      }

      vec& operator-=(const vec& v) {
        for (int i = 0; i < len; i++) {
            components[i] -= v[i];
        }
        return *this;
      }

      vec& operator*=(auto scalar) {
        for (int i = 0; i < len; i++)
        {
            components[i] *= scalar;
        }

        return *this;
      }

      vec& operator/=(auto scalar) {
        return *this *= 1/scalar;
      }

      float length_squared() const {
        float length = 0;
        for (int i = 0; i < len; i++)
        {
            length += components[i]*components[i];
        }

        return length;
      }

      float length() {return std::sqrt(length_squared()); }

};

template <typename T>
class vec2 : public vec<2, T> {
    public:

      vec2() {
        vec<2,T>::components[0] = 0; 
        vec<2,T>::components[1] = 0;
      }

      vec2(T x, T y) { 
        vec<2,T>::components[0] = x; 
        vec<2,T>::components[1] = y;}
      vec2 operator-() const { return {vec<2,T>::components[0] * -1, vec<2,T>::components[1] * -1}; }
      vec2 operator+(const vec2& v) { return {vec<2,T>::components[0] + v[0], vec<2,T>::components[1] + v[1]}; }
      vec2 operator-(const vec2& v) { return {vec<2,T>::components[0] - v[0], vec<2,T>::components[1] - v[1]}; }
      vec2 operator*(const vec2& v) { return {vec<2,T>::components[0] * v[0], vec<2,T>::components[1] * v[1]}; }
      vec2 operator/(const vec2& v) { return {vec<2,T>::components[0] / v[0], vec<2,T>::components[1] / v[1]}; }
      vec2 operator/(auto t) { return {vec<2,T>::components[0] / t, vec<2,T>::components[1] / t}; }
      vec2 operator*(auto t) { return {vec<2,T>::components[0] * t, vec<2,T>::components[1] * t}; }
      vec2 normalized() { return *this / vec<2,T>::length(); }
};

template <typename T>
class vec3 : public vec<3,T> {
    public:
      vec3() {
        vec<3,T>::components[0] = 0; 
        vec<3,T>::components[1] = 0;
        vec<3,T>::components[2] = 0;
      }

      vec3(T x, T y, T z) { 
        vec<3,T>::components[0] = x; 
        vec<3,T>::components[1] = y;
        vec<3,T>::components[2] = z;}
      vec3 operator-() const { return {vec<3,T>::components[0] * -1, vec<3,T>::components[1] * -1, vec<3,T>::components[2] * -1}; }
      vec3 operator+(const vec3& v) const { return {vec<3,T>::components[0] + v[0], vec<3,T>::components[1] + v[1], vec<3,T>::components[2] + v[2]}; }
      vec3 operator-(const vec3& v) const { return {vec<3,T>::components[0] - v[0], vec<3,T>::components[1] - v[1], vec<3,T>::components[2] - v[2]}; }
      vec3 operator*(const vec3& v) const { return {vec<3,T>::components[0] * v[0], vec<3,T>::components[1] * v[1], vec<3,T>::components[2] * v[2]}; }
      vec3 operator/(const vec3& v) const { return {vec<3,T>::components[0] / v[0], vec<3,T>::components[1] / v[1], vec<3,T>::components[2] / v[2]}; }
      vec3 operator/(auto t) const { return {vec<3,T>::components[0] / t, vec<3,T>::components[1] / t, vec<3,T>::components[2] / t}; }
      vec3 operator*(auto t) const { return {vec<3,T>::components[0] * t, vec<3,T>::components[1] * t, vec<3,T>::components[2] * t}; }
      vec3 normalized() { return *this / vec<3,T>::length(); }
};

template <typename T>
class vec4 : public vec<4, T> {
    public:

     vec4() {
        vec<4,T>::components[0] = 0; 
        vec<4,T>::components[1] = 0;
        vec<4,T>::components[2] = 0;
        vec<4,T>::components[3] = 0;
      }
      
      vec4(T x, T y, T z, T w) { 
        vec<4,T>::components[0] = x; 
        vec<4,T>::components[1] = y;
        vec<4,T>::components[2] = z;
        vec<4,T>::components[3] = w; }

      vec4 operator-() const { return {vec<4,T>::components[0] * -1, vec<4,T>::components[1] * -1, vec<4,T>::components[2] * -1, vec<4,T>::components[3] * -1}; }
      vec4 operator+(const vec4& v) { return {vec<3,T>::components[0] + v[0], vec<4,T>::components[1] + v[1], vec<4,T>::components[2] + v[2], vec<4,T>::components[3] + v[3]}; }
      vec4 operator-(const vec4& v) { return {vec<3,T>::components[0] - v[0], vec<4,T>::components[1] - v[1], vec<4,T>::components[2] - v[2], vec<4,T>::components[3] - v[3]}; }
      vec4 operator*(const vec4& v) { return {vec<3,T>::components[0] * v[0], vec<4,T>::components[1] * v[1], vec<4,T>::components[2] * v[2], vec<4,T>::components[3] * v[3]}; }
      vec4 operator/(const vec4& v) { return {vec<3,T>::components[0] / v[0], vec<4,T>::components[1] / v[1], vec<4,T>::components[2] / v[2], vec<4,T>::components[3] / v[3]}; }
      vec4 operator/(auto t) { return {vec<4,T>::components[0] / t, vec<4,T>::components[1] / t, vec<4,T>::components[2] / t, vec<4,T>::components[2] / t}; }
      vec4 operator*(auto t) { return {vec<4,T>::components[0] * t, vec<4,T>::components[1] * t, vec<4,T>::components[2] * t, vec<4,T>::components[2] * t}; }
      vec4 normalized() { return *this / vec<4,T>::length(); }
};

//for the sake of simplicity i ve implemented type definitions 
//of each vector length and type we are gonna need
//as well the point definition for extra clarity.

typedef vec2<float> vec2f;
typedef vec2<int> vec2i;
using point2f = vec2f;
using point2i = vec2i;

typedef vec3<float> vec3f;
typedef vec3<int> vec3i;
using point3f = vec3f;
using point3i = vec3i;

typedef vec4<float> vec4f;
typedef vec4<int> vec4i;

//standard operator implementations for our vector class

template <size_t DIM, typename T> std::ostream& operator<<(std::ostream& out, const vec<DIM, T>& v) {
    for(size_t i=0; i<DIM; i++) {
        out << v[i] << " " ;
    }
    return out ;
}

template <typename T> vec2<T> operator*(auto t, vec2<T>& v) {
    return v * t;
}

template <typename T> vec3<T> operator*(auto t, vec3<T>& v) {
    return v * t;
}

template <typename T> vec4<T> operator*(auto t, vec4<T>& v) {
    return v * t;
}

template <size_t DIM, typename T> float dot(const vec<DIM, T>& v, const vec<DIM, T>& u) {
    float total = 0;
    for(size_t i=0; i<DIM; i++) {
        total += v[i] * u[i];
    } 

    return total;
}

template <typename T> vec3<T> cross(const vec3<T>& v, const vec3<T>& u) {
    return vec3<T>(v[1] * u[2] - v[2] * u[1],
                   v[2] * u[0] - v[0] * u[2],
                   v[0] * u[1] - v[1] * u[0]);
}

#endif /* VECTOR_H */