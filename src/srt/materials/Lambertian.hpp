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
#include "../textures/Texture.hpp"

namespace srt{
namespace materials{

/// The abstract material class.
class Lambertian : public Material{
private:
    // ATTRIBUTES

    std::shared_ptr<textures::Texture> albedo;
public:
    //CONSTRUCTORS

    Lambertian(const std::shared_ptr<textures::Texture> &albedo);

    // METHODS
    const std::shared_ptr<textures::Texture> getAlbedo();
    bool scatter(Ray &ray, geometry::Vec3 &attenuation, const geometry::Vec3 &hitPoint, 
                    const geometry::Vec3 &normal, const geometry::Vec3 &textureCoords) const;
};
}
}

#endif