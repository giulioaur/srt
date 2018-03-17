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

    // METHODS

    geometry::Vec3 getUVCoords(const geometry::Vec3 &p) const;
    
public:
    // CONSTRUCTORS

    Sphere(const srt::geometry::Vec3 &center, const float radius, const std::shared_ptr<materials::Material> material);
    Sphere(const Sphere &old);

    // OPERATORS

    bool operator == (const Hitable &hitable) const;
    bool operator != (const Hitable &hitable) const; 

    // METHODS

    float getRay() const; 
    const srt::geometry::Vec3& getCenter() const;
    virtual srt::geometry::Vec3 getNormal(const srt::geometry::Vec3 &pos) const;
    virtual Hitable::hit_record intersection(const srt::Ray &ray, const float tmin, const float tmax) const;
    virtual bool scatter(srt::Ray &ray, srt::geometry::Vec3 &attenuation, const geometry::Vec3 &hitPoint) const;
    virtual std::unique_ptr<geometry::AABB> getAABB(const float t0, const float t1) const;
};

}
}
}

#endif