/*******************************************************
 *                                                     *
 *  srt: Sushi RayTracer                               *
 *                                                     *
 *  DIFFUSE LIGHT HEADER FILE                          *
 *                                                     *
 *  Giulio Auriemma                                    *
 *                                                     *
 *******************************************************/
#ifndef S_MATERIALS_LIGHTS_DIFFUSE_S
#define S_MATERIALS_LIGHTS_DIFFUSE_S

// My includes
#include "../Material.hpp"
#include "../../textures/Texture.hpp"

namespace srt{
namespace materials{
namespace lights{

/// A diffuse light.
class DiffuseLight : public Material{
private:
    // ATTRIBUTES

    std::shared_ptr<textures::Texture> albedo;
public:
    //CONSTRUCTORS

    DiffuseLight(const std::shared_ptr<textures::Texture> &albedo);

    // METHODS
    const std::shared_ptr<textures::Texture> getAlbedo();
    virtual bool scatter(Ray &ray, geometry::Vec3 &attenuation, const geometry::Vec3 &hitPoint, 
                    const geometry::Vec3 &normal, const geometry::Vec3 &textureCoords) const;
    virtual bool emit(const geometry::Vec3 &hitPoint, const geometry::Vec3 &textureCoords, geometry::Vec3 &emittedColor) const;
};
}
}
}

#endif