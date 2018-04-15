/*******************************************************
 *                                                     *
 *  srt: Sushi RayTracer                               *
 *                                                     *
 *  DIELETRIC HEADER FILE                              *
 *                                                     *
 *  Giulio Auriemma                                    *
 *                                                     *
 *******************************************************/
#ifndef S_MATERIALS_DIELETRIC_S
#define S_MATERIALS_DIELETRIC_S

// My includes
#include "Material.hpp"

namespace srt{
namespace materials{

/// The abstract material class.
class Dielectric : public Material{
private:
    // ATTRIBUTES

    float refractivity;
    geometry::Vec3 attenuation;

    // METHODS
    float schlick(const float cos, const float refractivity) const;
    geometry::Vec3 reflect(const geometry::Vec3 &vec, const geometry::Vec3 &normal) const;
    bool refract(const geometry::Vec3 &v, const geometry::Vec3 normal, const float refractivity, geometry::Vec3 &refracted) const;
public:
    //CONSTRUCTORS

    Dielectric(const float refractivity, const geometry::Vec3 &attenuation = {1, 1, 1});

    // METHODS
    bool scatter(Ray &ray, geometry::Vec3 &attenuation, const geometry::Vec3 &hitPoint, 
                    const geometry::Vec3 &normal, const geometry::Vec3 &textureCoords = {0, 0, 0}) const;
};
}
}

#endif