/*******************************************************
 *                                                     *
 *  srt: Sushi RayTracer                               *
 *                                                     *
 *  HITABLE HEADER FILE                                *
 *                                                     *
 *  Giulio Auriemma                                    *
 *                                                     *
 *******************************************************/
#ifndef S_HITABLE_S
#define S_HITABLE_S

// System includes.
#include <memory>

// My includes.
#include "structs.h"
#include "Ray.hpp"
#include "materials/Material.hpp"
#include "geometry/AABB.hpp"

namespace srt{

class Hitable{
private:
public:
    // STRUCTURES
    typedef struct hr{
        bool hitted;
        float t;
        Hitable const* object;
        
        hr(bool h, float t, Hitable const *obj) : hitted(h), t(t), object(obj) {}
    } hit_record;


    // METHODS
 
    virtual Hitable::hit_record intersection(const Ray &ray, const float tmin, const float tmax) const = 0;
    virtual geometry::Vec3 getNormal(const srt::geometry::Vec3 &pos) const = 0;
    virtual bool scatter(Ray &ray, geometry::Vec3 &attenuation, const geometry::Vec3 &hitPoint) const = 0;
    virtual std::unique_ptr<geometry::AABB> getAABB(const float t0, const float t1) const = 0;

    // OPERATORS

    // virtual bool operator == (const Hitable &hitable) const = 0;
    // virtual bool operator != (const Hitable &hitable) const = 0;
};

}

#endif