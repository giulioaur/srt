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

    /**
     * @brief It stores the info about the collision with a ray.
     * 
     */
    typedef struct hr{
        bool hitted;
        float t;
        Hitable const* object;
        
        hr(bool h, float t, Hitable const *obj) : hitted(h), t(t), object(obj) {}
    } hit_record;

    // The record for no hit situation.
    static const hit_record NO_HIT;

    // METHODS
 
    /**
     * @brief Computes the intersection between the emitted ray and the hitable object.
     * 
     * @param ray - The ray.
     * @param tmin - The min t to consider.
     * @param tmax - The max t to consider.
     * @return Hitable::hit_record - The record that stores hit info.
     */
    virtual Hitable::hit_record intersection(const Ray &ray, const float tmin, const float tmax) const = 0;

    /**
     * @brief Gets the normal of the object in a given point.
     * 
     * @param pos - The position from which computes the normal.
     * @return geometry::Vec3 - The normal in that point.
     */
    virtual geometry::Vec3 getNormal(const srt::geometry::Vec3 &pos) const = 0;

    /**
     * @brief Get the Material of the object.
     * 
     * @return const Material& - The material of the object.
     */
    virtual const std::shared_ptr<materials::Material> getMaterial() const{
        return nullptr;
    }

    /**
     * @brief Returns the axis aligned bounded box boxes.
     * 
     * @param t0 - The first instant of time to consider.
     * @param t1 - The last instant of time to consider.
     * @return std::unique_ptr<geometry::AABB> The axis aligned bounded box that surrounds the object.
     */
    virtual std::unique_ptr<geometry::AABB> getAABB(const float t0, const float t1) const = 0;
    
    /**
     * @brief Get the Texture Coords of the object  in a given point.
     * 
     * @param p - The hit point on the object.
     * @return geometry::Vec3 - The texture coords.
     */
    virtual geometry::Vec3 getTextureCoords(const srt::geometry::Vec3 &p) const {
        return p;
    }

    // OPERATORS

    // virtual bool operator == (const Hitable &hitable) const = 0;
    // virtual bool operator != (const Hitable &hitable) const = 0;
};

}

#endif