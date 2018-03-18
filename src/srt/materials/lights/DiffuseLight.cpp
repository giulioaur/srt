/*******************************************************
 *                                                     *
 *  srt: Sushi RayTracer                               *
 *                                                     *
 *  DIFFUSE LIGHT HEADER FILE                          *
 *                                                     *
 *  Giulio Auriemma                                    *
 *                                                     *
 *******************************************************/
#include "DiffuseLight.hpp"

namespace srt{
namespace materials{
namespace lights{

    /**
     * @brief Creates a new lambertian material.
     * 
     * @param albedo - The fraction of light refracted.
     */
    DiffuseLight::DiffuseLight(const std::shared_ptr<textures::Texture> &albedo) : albedo(albedo) { }

    /**
     * @brief Constructs a new Diffuse Light object with the same texture as the passed one.
     * 
     * @param old - The light to duplicate.
     */
    DiffuseLight::DiffuseLight(const DiffuseLight &old) : albedo(old.albedo) { }

    /**
     * @brief Returns the quantity of light refracted by the lambertian.
     * 
     * @return const float& - The quantity of light refracted by the lambertian.
     */
    const std::shared_ptr<textures::Texture> DiffuseLight::getAlbedo(){ 
        return this->albedo;
    }

    /**
     * @brief 
     * 
     * @param ray 
     * @param attenuation 
     * @param hitPoint 
     * @param normal 
     * @param textureCoords 
     * @return true 
     * @return false 
     */
    bool DiffuseLight::scatter(Ray &ray, geometry::Vec3 &attenuation, const geometry::Vec3 &hitPoint, 
        const geometry::Vec3 &normal, const geometry::Vec3 &textureCoords) const{ return false; }

    /**
     * @brief Returns true and change emittedColor to the light color.
     * 
     * @param hitPoint - The point hit by the ray on which compute the color emission.
     * @param textureCoords - The texture coordinates.
     * @param emittedColor - The variable in which stores the light color.
     * @return true - If the material is an emitter.
     * @return false - If the material is not an emitter.
     */
    bool DiffuseLight::emit(const geometry::Vec3 &hitPoint, const geometry::Vec3 &textureCoords, geometry::Vec3 &emittedColor) const{
        emittedColor = this->albedo->value(textureCoords.x(), textureCoords.y(), hitPoint);
        return true;
    }

}
}
}