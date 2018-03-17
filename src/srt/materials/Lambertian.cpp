/*******************************************************
 *                                                     *
 *  srt: Sushi RayTracer                               *
 *                                                     *
 *  LAMBERTIAN HEADER FILE                             *
 *                                                     *
 *  Giulio Auriemma                                    *
 *                                                     *
 *******************************************************/
#include "Lambertian.hpp"

// My other includes
#include "../utility/Randomizer.hpp"

using namespace srt;
using namespace srt::geometry;
using namespace srt::utility;
using namespace srt::textures;

namespace srt{
namespace materials{

    /**
     * @brief Creates a new lambertian material.
     * 
     * @param albedo - The fraction of light refracted.
     */
    Lambertian::Lambertian(const std::shared_ptr<Texture> &albedo) : albedo(albedo) { }

    /**
     * @brief Returns the quantity of light refracted by the lambertian.
     * 
     * @return const float& - The quantity of light refracted by the lambertian.
     */
    const std::shared_ptr<Texture> Lambertian::getAlbedo(){ 
        return this->albedo;
    }


    bool Lambertian::scatter(Ray &ray, Vec3 &attenuation, const Vec3 &hitPoint, const Vec3 &normal, const Vec3 &textureCoords) const{
        Vec3 target = hitPoint + normal + Randomizer::randomInUnitSphere();
        ray = {hitPoint, target - hitPoint, ray.getTime()};
        attenuation = this->albedo->value(textureCoords.x(), textureCoords.y(), hitPoint);
        return true;
    }

}
}