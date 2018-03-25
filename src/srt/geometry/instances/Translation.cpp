/*******************************************************
 *                                                     *
 *  srt: Sushi RayTracer                               *
 *                                                     *
 *  TRANSLATION CLASS FILE                             *
 *                                                     *
 *  Giulio Auriemma                                    *
 *                                                     *
 *******************************************************/
#include "Translation.hpp"

namespace srt{
namespace geometry{
namespace instances{

    /**
     * @brief Construct a new Translation:: Translation object
     * 
     * @param object 
     * @param offset 
     */
    Translation::Translation(const std::shared_ptr<Hitable> object, const Vec3 &offset) : 
        object(object), offset(offset){ }

    /**
     * @brief Construct a new Translation:: Translation object
     * 
     * @param old 
     */
    Translation::Translation(const Translation &old) : object(old.object), offset(old.offset) { }

    /**
     * @brief Computes the intersection between the emitted ray and the hitable object.
     * 
     * @param ray - The ray.
     * @param tmin - The min t to consider.
     * @param tmax - The max t to consider.
     * @return Hitable::hit_record - The record that stores hit info.
     */
    Hitable::hit_record Translation::intersection(const Ray &ray, const float tmin, const float tmax) const{
        // Move the ray, then compute intersection.
        Ray movedRay{ray.getOrigin() - offset, ray.getDirection(), ray.getTime()};
        auto record = this->object->intersection(movedRay, tmin, tmax);
        
        // If a point has been hit, translate it.
        if(record.hit){
            record.point += offset;
            // record.object = this;
        }   

        return record;
    }

    /**
     * @brief Returns the axis aligned bounded box boxes.
     * 
     * @param t0 - The first instant of time to consider.
     * @param t1 - The last instant of time to consider.
     * @return std::unique_ptr<geometry::AABB> The axis aligned bounded box that surrounds the object.
     */
    std::unique_ptr<AABB> Translation::getAABB(const float t0, const float t1) const{
        auto bb = this->object->getAABB(t0, t1);

        return bb ? std::make_unique<AABB>(bb->getMin() + this->offset, bb->getMax() + this->offset) : nullptr; 
    }

    /**
     * @brief Get the Material of the tranlsated object.
     * 
     * @return const Material& - The material of the tranlsated object.
     */
    const std::shared_ptr<materials::Material>& Translation::getMaterial() const{
        return this->object->getMaterial();
    }

    /**
     * @brief Get the Texture Coords of the tranlsated object in a given point.
     * 
     * @param p - The hit point on the tranlsated object.
     * @return srt::geometry::Vec3 - The texture coords. 
     */
    Vec3 Translation::getTextureCoords(const Vec3 &p) const{
        return this->object->getTextureCoords(p - this->offset);
    }

}
}
}