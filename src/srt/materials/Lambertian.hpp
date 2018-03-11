/*******************************************************
 *                                                     *
 *  srt: Sushi RayTracer                               *
 *                                                     *
 *  LAMBERTIAN HEADER FILE                             *
 *                                                     *
 *  Giulio Auriemma                                    *
 *                                                     *
 *******************************************************/
#ifndef S_MATERIALS_LAMBERTIAN_S
#define S_MATERIALS_LAMBERTIAN_S

// My includes
#include "Material.hpp"

namespace srt{
namespace materials{

/// The abstract material class.
class Lambertian : public Material{
private:
    // ATTRIBUTES

    geometry::Vec3 albedo;
public:
    //CONSTRUCTORS

    Lambertian(const geometry::Vec3 &albedo);

    // METHODS
    const geometry::Vec3& getAlbedo();
    bool scatter(Ray &ray, geometry::Vec3 &attenuation, const geometry::Vec3 &hitPoint, 
                    const geometry::Vec3 &normal) const;
};
}
}

#endif