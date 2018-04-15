/*******************************************************
 *                                                     *
 *  srt: Sushi RayTracer                               *
 *                                                     *
 *  METAL CLASS FILE                                   *
 *                                                     *
 *  Giulio Auriemma                                    *
 *                                                     *
 *******************************************************/
#include "Metal.hpp"

// My other includes
#include "../utility/Randomizer.hpp"

using namespace srt;
using namespace srt::geometry;
using namespace srt::utility;

namespace srt{
namespace materials{

    /**
     * @brief Creates a new lambertian material.
     * 
     * @param albedo - The fraction of light refracted.
     */
    Metal::Metal(const geometry::Vec3 &albedo, const float fuziness) : albedo(albedo),
        fuziness(fuziness >= 0 ? fuziness <= 1 ? fuziness : 1 : 0 ) { }

    /**
     * @brief Returns a vector reflected by given normal.
     * 
     * @param vec - The vector to reflect.
     * @param normal - The normal.
     * @return Vec3 Metal::reflect - The reflected vector 
     */
    Vec3 Metal::reflect(const geometry::Vec3 &vec, const geometry::Vec3 &normal) const{
        return vec - 2 * (vec * normal) * normal;
    }

    /**
     * @brief 
     * 
     * @param ray 
     * @param attenuation 
     * @param hitPoint 
     * @param normal 
     * @return true 
     * @return false 
     */
    bool Metal::scatter(Ray &ray, Vec3 &attenuation, const Vec3 &hitPoint, const Vec3 &normal, const Vec3 &textureCoords) const{
        Vec3 reflected = reflect(ray.getDirection(), normal);
        if(reflected * normal > 0){
            ray = {hitPoint, reflected + this->fuziness * Randomizer::randomInUnitSphere()};
            attenuation = this->albedo;
            return true;
        }
        return false; 
    }

}
}