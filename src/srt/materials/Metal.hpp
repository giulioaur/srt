/*******************************************************
 *                                                     *
 *  srt: Sushi RayTracer                               *
 *                                                     *
 *  METAL HEADER FILE                                  *
 *                                                     *
 *  Giulio Auriemma                                    *
 *                                                     *
 *******************************************************/
#ifndef S_MATERIALS_METAL_S
#define S_MATERIALS_METAL_S

// My includes
#include "Material.hpp"

namespace srt{
namespace materials{

/// The abstract material class.
class Metal : public Material{
private:
    // ATTRIBUTES

    geometry::Vec3 albedo;
    float fuziness;

    // METHODS
    geometry::Vec3 reflect(const geometry::Vec3 &vec, const geometry::Vec3 &normal) const;
public:
    //CONSTRUCTORS

    Metal(const geometry::Vec3 &albedo, const float fuziness);
    Metal(const Metal &old);

    // METHODS
    bool scatter(Ray &ray, geometry::Vec3 &attenuation, const geometry::Vec3 &hitPoint, 
                    const geometry::Vec3 &normal) const;
};
}
}

#endif