/*******************************************************
 *                                                     *
 *  srt: Sushi RayTracer                               *
 *                                                     *
 *  MOVING SPHERE HEADER FILE                          *
 *                                                     *
 *  Giulio Auriemma                                    *
 *                                                     *
 *******************************************************/
#ifndef S_SHAPES_MOVINGSPHERE_S
#define S_SHAPES_MOVINGSPHERE_S

// My includes.
#include "Sphere.hpp"

namespace srt{
namespace geometry{
namespace shapes{

/// This class represents a sphere moving in time.
class MovingSphere : public Sphere{
private:
    // ATTRIBUTES

    srt::geometry::Vec3 c0, c1;
    float t0, t1;
    
public:
    // CONSTRUCTORS

    MovingSphere(const srt::geometry::Vec3 &c0, const srt::geometry::Vec3 &c1, const float t0,
        const float t1, const float ray, const std::shared_ptr<materials::Material> material);

    // OPERATORS

    // bool operator == (const MovingSphere &shape) const;
    // bool operator != (const MovingSphere &shape) const; 

    // METHODS 

    virtual Hitable::hit_record intersection(const srt::Ray &ray, const float tmin, const float tmax) const;
    virtual std::unique_ptr<geometry::AABB> getAABB(const float t0, const float t1) const;
};

}
}
}

#endif