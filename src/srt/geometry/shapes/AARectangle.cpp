/*******************************************************
 *                                                     *
 *  srt: Sushi RayTracer                               *
 *                                                     *
 *  AARECTANGLE CLASS FILE                             *
 *                                                     *
 *  Giulio Auriemma                                    *
 *                                                     *
 *******************************************************/
#include "AARectangle.hpp"

using namespace std;
using namespace srt::geometry;

namespace srt{
namespace geometry{
namespace shapes{

    /**
     * @brief Construct a new AARectangle object.
     * 
     * @param type - The type of the rectangle.
     * @param a0_0 - The lower bound of the first axis.
     * @param a0_1 - The upper bound of the first axis.
     * @param a1_0 - The lower bound of the second axis.
     * @param a1_1 - The upper bound of the second axis.
     * @param t - The distance from the last axis.
     * @param material - The material of the rectangle.
     */
    AARectangle::AARectangle(const AARectangle::Type type, const float a0_0, const float a0_1, const float a1_0, const float a1_1, 
        const float k, const std::shared_ptr<materials::Material> material, bool flipNormal) :
        type(type), axis0_0(a0_0), axis0_1(a0_1), axis1_0(a1_0), axis1_1(a1_1), k(k), material(material), isNormalFlipped(flipNormal){ }
    
    
    /**
     * @brief Construct a new AARectangle object equal to an old one.
     * 
     * @param old - The rectangle to copy.
     */
    AARectangle::AARectangle(const AARectangle &old) : type(old.type), axis0_0(old.axis0_0), axis0_1(old.axis0_1), axis1_0(old.axis1_0), 
        axis1_1(old.axis1_1), k(old.k), material(old.material) { }

    /**
     * @brief Return the normal of the rectangle.
     * 
     * @param pos - The hit point. It is irrelevant.
     * @return srt::geometry::Vec3 - The normal of the plane.
     */
    srt::geometry::Vec3 AARectangle::getNormal(const srt::geometry::Vec3 &pos) const{
        switch(this->type){
            case AARectangle::XY: return{0, 0, this->isNormalFlipped ? -1.f : 1.f};
            case AARectangle::XZ: return{0, this->isNormalFlipped ? -1.f : 1.f, 0};
            case AARectangle::YZ: return{this->isNormalFlipped ? -1.f : 1.f, 0, 0};
        }
    }

    /**
     * @brief Computes the intersection between the emitted ray and the rectangle.
     * 
     * @param ray - The ray.
     * @param tmin - The min t to consider.
     * @param tmax - The max t to consider.
     * @return Hitable::hit_record - The record that stores hit info.
     */
    Hitable::hit_record AARectangle::intersection(const srt::Ray &ray, const float tmin, const float tmax) const{
        size_t a0, a1, a2;
        const Vec3 ro = ray.getOrigin(), rd = ray.getDirection();

        // Set the index of the coords for the three axis.
        switch(this->type){
            case AARectangle::XY: 
                // First axis = x, second axis = y, last axis = z.
                a0 = 0; a1 = 1; a2 = 2; break;
            case AARectangle::XZ: 
                // First axis = x, second axis = z, last axis = y.
                a0 = 0; a1 = 2; a2 = 1; break;
            case AARectangle::YZ: 
                // First axis = y, second axis = z, last axis = x.
                a0 = 1; a1 = 2; a2 = 0; break;
        }

        // Compute t.
        float t = (this->k - ro[a2]) / rd[a2];
        if (t < tmin || t > tmax)   return Hitable::NO_HIT;

        // Compute the hit point.
        Vec3 hitPoint = ray.getPoint(t);
        if(hitPoint[a0] < this->axis0_0 || hitPoint[a0] > this->axis0_1 ||
            hitPoint[a1] < this->axis1_0 || hitPoint[a1] > this->axis1_1)
            return Hitable::NO_HIT;
        
        return {true, t, this, ray.getPoint(t), this->getNormal(ray.getPoint(t))};
    }

    /**
     * @brief Get the Material of the rectangle.
     * 
     * @return const Material& - The material of the rectangle.
     */
    const std::shared_ptr<materials::Material>& AARectangle::getMaterial() const{
        return this->material;
    }

    /**
     * @brief Returns the axis aligned bounded box boxes.
     * 
     * @param t0 - The first instant of time to consider.
     * @param t1 - The last instant of time to consider.
     * @return std::unique_ptr<geometry::AABB> The axis aligned bounded box that surrounds the rectangle.
     */
    std::unique_ptr<geometry::AABB> AARectangle::getAABB(const float t0, const float t1) const{
        switch(this->type){
            case AARectangle::XY: 
                return std::make_unique<geometry::AABB>(Vec3{this->axis0_0, this->axis1_0, k - 0.0001f}, 
                                                        Vec3{this->axis0_1, this->axis1_1, k + 0.0001f});
            case AARectangle::XZ: 
                return std::make_unique<geometry::AABB>(Vec3{this->axis0_0, k - 0.0001f, this->axis1_0}, 
                                                        Vec3{this->axis0_1, k + 0.0001f, this->axis1_1});
            case AARectangle::YZ: 
                return std::make_unique<geometry::AABB>(Vec3{k - 0.0001f, this->axis0_0, this->axis1_0}, 
                                                        Vec3{k + 0.0001f, this->axis0_1, this->axis1_1});
        }
    }

    /**
     * @brief Get the Texture Coords of the rectangle in a given point.
     * 
     * @param p - The point on the rectangle hit.
     * @return geometry::Vec3 - The texture coords.
     */
    geometry::Vec3 AARectangle::getTextureCoords(const geometry::Vec3 &p) const{
        switch(this->type){
            case AARectangle::XY: 
                return {(p.x() - this->axis0_0) / (this->axis0_1 - this->axis0_0),
                        (p.y() - this->axis1_0) / (this->axis1_1 - this->axis1_0), 
                        0};
            case AARectangle::XZ: 
                return {(p.x() - this->axis0_0) / (this->axis0_1 - this->axis0_0),
                        (p.z() - this->axis1_0) / (this->axis1_1 - this->axis1_0), 
                        0};
            case AARectangle::YZ: 
                return {(p.y() - this->axis0_0) / (this->axis0_1 - this->axis0_0),
                        (p.z() - this->axis1_0) / (this->axis1_1 - this->axis1_0), 
                        0};
        }
    }

}
}
}