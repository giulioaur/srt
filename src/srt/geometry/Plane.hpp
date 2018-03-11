/*******************************************************
 *                                                     *
 *  srt: Sushi RayTracer                               *
 *                                                     *
 *  PLANE HEADER FILE                                  *
 *                                                     *
 *  Giulio Auriemma                                    *
 *                                                     *
 *******************************************************/
#ifndef S_GEOMETRY_PLANE_S
#define S_GEOMETRY_PLANE_S

// System includes.
#include <memory>

// My includes.
#include "Vec3.hpp"
#include "../Ray.hpp"

namespace srt{
namespace geometry{

/// This class represents a 2D plane.
class Plane{
private:
    // ATTRIBUTES

    Vec3 normal, point;  
public:
    // CONSTRUCTORS

    Plane(const Vec3 &norm, const Vec3 &point);
    Plane(const Plane &old);

    // METHODS

    const Vec3& getNormal() const;
    float intersect(const Ray &ray, const float tmin, const float tmax) const;
    bool contain(const Vec3 &point) const;
};

}
}
#endif