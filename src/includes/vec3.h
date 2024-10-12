#pragma once
#include <cmath>
#include <iostream>

//Vec3 class
class vec3 {
    public:
    //value container
    double vals[3];

    //constructor for 0 parameters just returns a 0 vector
    vec3() : vals{0,0,0} {}

    //constructor with 3 overloads, return the x,y,z vector
    vec3(double x, double y, double z) : vals{x, y, z} {}

    //getters for the x,y,z components of the vec3 object
    double x() const { return vals[0]; }
    double y() const { return vals[1]; }
    double z() const { return vals[2]; }

    //return the negative vector
    vec3 operator-() const { return vec3(-vals[0], -vals[1], -vals[2] ); }

    //return the i element of the vector
    double operator[](int i) const { return vals[i]; } //in this case, the vec3[i] element is constant, and used to get the value
    double& operator[](int i) { return vals[i]; } //here, since its not constant, and we get the reference to the i-th element, we can also change it, thus making it mutable

    vec3& operator+=(const vec3& v) { //we return the reference to the object added with a vector v
        vals[0] = v[0];
        vals[1] = v[1];
        vals[2] = v[2];
        return *this;
    }

    vec3& operator*=(double w) { //again we return the reference to the object multiplied by a value w
        vals[0] *= w;
        vals[1] *= w;
        vals[2] *= w;
        return *this;
    }

    vec3& operator/=(double w) { //division with a value w
        return *this *= 1/w;
    }

    double length() const {
        return std::sqrt(length_squared());
    }

    double length_squared() const {
        return vals[0]*vals[0] + vals[1]*vals[1] + vals[2]*vals[2];
    }
};

inline std::ostream& operator<<(std::ostream& out, const vec3& v) {
    return out << v.vals[0] << ' ' << v.vals[1] << ' ' << v.vals[2];
}

inline vec3 operator+(const vec3& u, const vec3& v) {
    return vec3(u.vals[0] + v.vals[0], u.vals[1] + v.vals[1], u.vals[2] + v.vals[2]);
}

inline vec3 operator-(const vec3& u, const vec3& v) {
    return vec3(u.vals[0] - v.vals[0], u.vals[1] - v.vals[1], u.vals[2] - v.vals[2]);
}

inline vec3 operator*(const vec3& u, const vec3& v) {
    return vec3(u.vals[0] * v.vals[0], u.vals[1] * v.vals[1], u.vals[2] * v.vals[2]);
}

inline vec3 operator*(double t, const vec3& v) {
    return vec3(t*v.vals[0], t*v.vals[1], t*v.vals[2]);
}

inline vec3 operator*(const vec3& v, double t) {
    return t * v;
}

inline vec3 operator/(const vec3& v, double t) {
    return (1/t) * v;
}

inline double dot(const vec3& u, const vec3& v) {
    return u.vals[0] * v.vals[0]
         + u.vals[1] * v.vals[1]
         + u.vals[2] * v.vals[2];
}

inline vec3 cross(const vec3& u, const vec3& v) {
    return vec3(u.vals[1] * v.vals[2] - u.vals[2] * v.vals[1],
                u.vals[2] * v.vals[0] - u.vals[0] * v.vals[2],
                u.vals[0] * v.vals[1] - u.vals[1] * v.vals[0]);
}

inline vec3 unit_vector(const vec3& v) {
    return v / v.length();
}