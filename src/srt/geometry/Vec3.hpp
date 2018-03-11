/*******************************************************
 *                                                     *
 *  srt: Sushi RayTracer                               *
 *                                                     *
 *  VECTOR HEADER FILE                                 *
 *                                                     *
 *  Giulio Auriemma                                    *
 *                                                     *
 *******************************************************/
#ifndef S_GEOMETRY_VEC3_S
#define S_GEOMETRY_VEC3_S

// System includes
#include <iostream>
#include <vector>
#include <functional>

namespace srt{
namespace geometry{

/// This class represents a classic 3D vector.
class Vec3{
private:
    // ATTRIBUTES

    float _x, _y, _z, _length;
    
public:

    // CONSTRUCTORS
    Vec3();
    Vec3(const float x, const float y, const float z);
    Vec3(const std::vector<float> &vec);
    Vec3(const Vec3 &old);

    // OPERATION

    Vec3 operator + (const Vec3& v) const;
    Vec3 operator += (const Vec3& v);
    Vec3 operator - (const Vec3& v) const;
    Vec3 operator - () const;
    Vec3 operator * (const float d) const;
    friend Vec3 operator * (const float d, const Vec3 &vec);
    Vec3 operator *= (const float d);
    float operator * (const Vec3& v) const;
    Vec3 operator / (const float d) const;
    Vec3 operator /= (const float d);
    float operator ^ (const short &n) const;
    bool operator == (const Vec3 &v) const;
    bool operator != (const Vec3 &v) const;
    float operator [] (const int i) const;
    friend std::ostream& operator << (std::ostream &os, const Vec3 &vec);

    // METHOD

    const float& x() const;
    const float& y() const;
    const float& z() const;
    const float& length() const;
    Vec3 normalize() const;
    Vec3 multiplication(const Vec3 &vec) const;
    Vec3 cross(const Vec3 &vec) const;
    float distance(const Vec3 &vec) const;
    Vec3 projection(const Vec3 &vec) const;
    void clamp(const float min, const float max);
    void makeInteger(const bool useFloor = true);
    Vec3 map(std::function<float(float)> func);
};

Vec3 operator * (const float d, const Vec3 &vec);
}
}
#endif