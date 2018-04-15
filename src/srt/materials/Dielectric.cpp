/*******************************************************
 *                                                     *
 *  srt: Sushi RayTracer                               *
 *                                                     *
 *  DIELETRIC CLASS FILE                               *
 *                                                     *
 *  Giulio Auriemma                                    *
 *                                                     *
 *******************************************************/
#include "Dielectric.hpp"

// Other system include
#include <cmath>

// #todelete
#include <iostream>

using namespace srt;
using namespace srt::geometry;

namespace srt{
namespace materials{

    /**
     * @brief Creates a new dieletric material.
     * 
     * @param refractivity - The refractivity index.
     */
    Dielectric::Dielectric(const float refractivity, const Vec3 &attenuation) : 
        refractivity(refractivity), attenuation(attenuation) { }

    float Dielectric::schlick(const float cos, const float refractivity) const{
        float r0 = (1 - refractivity) / (1 + refractivity);
        r0 *= r0;
        return r0 + (1 - r0) * pow(1 - cos, 5);
    }

    /**
     * @brief Returns a vector reflected by given normal.
     * 
     * @param vec - The vector to reflect.
     * @param normal - The normal.
     * @return Vec3 Metal::reflect - The reflected vector 
     */
    Vec3 Dielectric::reflect(const geometry::Vec3 &vec, const geometry::Vec3 &normal) const{
        return vec - 2 * (vec * normal) * normal;
    }

    /**
     * @brief Computes a refracted ray.
     * 
     * @param ray - The ray to refract.
     * @param normal - The normal of the hit point.
     * @param refractivity - The refractivity factor.
     * @return true - If the ray could be refract.
     * @return false - If the ray could not be refract.
     */
    bool Dielectric::refract(const Vec3 &v, const Vec3 normal, const float refractivity, Vec3 &refracted) const{
        float dt = v * normal;
        float delta = 1.f - refractivity * refractivity * (1 - dt * dt);
        if(delta > 0) {
            refracted = refractivity * (v - normal * dt) - normal * sqrt(delta);
            return true;
        }
        return false;
    }

    bool Dielectric::scatter(Ray &ray, Vec3 &attenuation, const Vec3 &hitPoint, const Vec3 &normal, const Vec3 &textureCoords) const{
        Vec3 reflected = this->reflect(ray.getDirection(), normal),
             outNormal = -normal,
             refracted;
        float dot = ray.getDirection() * normal,
              refractivity = this->refractivity,
              cosine = this->refractivity * dot / ray.getDirection().length();

        attenuation = this->attenuation;
        
        // Check if the ray come from inside.
        if(dot <= 0){
            outNormal = normal;
            refractivity = 1 / this->refractivity;
            cosine = - dot / ray.getDirection().length();
        }

        if(this->refract(ray.getDirection(), outNormal, refractivity, refracted)){
            if(drand48() >= this->schlick(cosine, refractivity)){
                ray = {hitPoint, refracted};
                return true;
            }
        }
        
        ray = {hitPoint, reflected};
        return true;
    }

}
}