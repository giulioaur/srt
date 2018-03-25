/*******************************************************
 *                                                     *
 *  srt: Sushi RayTracer                               *
 *                                                     *
 *  AABOX CLASS FILE                                   *
 *                                                     *
 *  Giulio Auriemma                                    *
 *                                                     *
 *******************************************************/
#include "AABox.hpp"

using namespace std;
using namespace srt::geometry;

namespace srt{
namespace geometry{
namespace shapes{

    /**
     * @brief Construct a new AABox::AABox object.
     * 
     * @param min - The lowest value for the three axis.
     * @param max - The highest value for the three axis.
     * @param material - The material of the box.
     */
    AABox::AABox(const Vec3 &min, const Vec3 &max, const std::shared_ptr<materials::Material> material) :
        sides {{AARectangle(AARectangle::XY, min.x(), max.x(), min.y(), max.y(), max.z(), material),
                 AARectangle(AARectangle::XY, min.x(), max.x(), min.y(), max.y(), min.z(), material, true),
                 AARectangle(AARectangle::XZ, min.x(), max.x(), min.z(), max.z(), max.y(), material),
                 AARectangle(AARectangle::XZ, min.x(), max.x(), min.z(), max.z(), min.y(), material, true),
                 AARectangle(AARectangle::YZ, min.y(), max.y(), min.z(), max.z(), min.x(), material, true),
                 AARectangle(AARectangle::YZ, min.y(), max.y(), min.z(), max.z(), max.x(), material)}}, 
        min(min), max(max) { } 
    
    
    /**
     * @brief Construct a new AABox object equal to an old one.
     * 
     * @param old - The rectangle to copy.
     */
    AABox::AABox(const AABox &old) : sides(old.sides), min(old.min), max(old.max) { }

    /**
     * @brief Computes the intersection between the emitted ray and the box.
     * 
     * @param ray - The ray.
     * @param tmin - The min t to consider.
     * @param tmax - The max t to consider.
     * @return Hitable::hit_record - The record that stores hit info.
     */
    Hitable::hit_record AABox::intersection(const srt::Ray &ray, const float tmin, const float tmax) const{
        Hitable::hit_record bestRecord = {false, tmax, nullptr, {}, {}};

        // Check which side is hit.
        for(const auto &side : sides){
            Hitable::hit_record currRecord = side.intersection(ray, tmin, bestRecord.t);
            if(currRecord.hit){
                bestRecord = currRecord;
            }
        }
            
        return bestRecord;
    }

    /**
     * @brief Returns the axis aligned bounded box boxes.
     * 
     * @param t0 - The first instant of time to consider.
     * @param t1 - The last instant of time to consider.
     * @return std::unique_ptr<geometry::AABB> The axis aligned bounded box that surrounds the box.
     */
    std::unique_ptr<AABB> AABox::getAABB(const float t0, const float t1) const{
        return std::make_unique<AABB>(min, max);
    }

    /**
     * @brief Get the Texture Coords of the box in a given point.
     * 
     * @param p - The point hit on the box.
     * @return geometry::Vec3 - The texture coords.
     */
    geometry::Vec3 AABox::getTextureCoords(const geometry::Vec3 &p) const{
        return p.z() == max.z() ? sides[0].getTextureCoords(p) :
               p.z() == min.z() ? sides[1].getTextureCoords(p) :
               p.y() == max.y() ? sides[2].getTextureCoords(p) :
               p.y() == min.y() ? sides[3].getTextureCoords(p) :
               p.x() == max.x() ? sides[4].getTextureCoords(p) :
               sides[5].getTextureCoords(p) ;
    }

}
}
}