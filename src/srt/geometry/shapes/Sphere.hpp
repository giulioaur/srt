/*******************************************************
 *                                                     *
 *  srt: Sushi RayTracer                               *
 *                                                     *
 *  SPHERE HEADER FILE                                 *
 *                                                     *
 *  Giulio Auriemma                                    *
 *                                                     *
 *******************************************************/
#ifndef S_SHAPES_SPHERE_S
#define S_SHAPES_SPHERE_S

// My includes.
#include "../../Hitable.hpp"
#include "../Plane.hpp"
#include "../../materials/Material.hpp"

namespace srt{
namespace geometry{
namespace shapes{

/// This class represents a sphere shape.
class Sphere : public Hitable{
private:
    // ATTRIBUTES

    srt::geometry::Vec3 center;
    float radius;
    std::shared_ptr<materials::Material> material;

public:
    // CONSTRUCTORS

    Sphere(const Vec3 &center, const float radius, const std::shared_ptr<materials::Material> material);

    // OPERATORS

    bool operator == (const Hitable &hitable) const;
    bool operator != (const Hitable &hitable) const; 

    // METHODS

    float getRay() const; 
    const Vec3& getCenter() const;
    virtual Vec3 getNormal(const Vec3 &pos) const;
    virtual Hitable::hit_record intersection(const Ray &ray, const float tmin, const float tmax) const;
    virtual const std::shared_ptr<materials::Material> &getMaterial() const;
    virtual std::unique_ptr<AABB> getAABB(const float t0, const float t1) const;
    virtual Vec3 getTextureCoords(const Vec3 &p) const;
};

}
}
}

#endif