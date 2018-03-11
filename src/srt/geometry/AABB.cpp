/*******************************************************
 *                                                     *
 *  srt: Sushi RayTracer                               *
 *                                                     *
 *  AABB CLASS FILE                                    *
 *                                                     *
 *  Giulio Auriemma                                    *
 *                                                     *
 *******************************************************/
#include "AABB.hpp"

// Other system includes.
#include <algorithm>

namespace srt{
namespace geometry{

    /**
     * @brief Creates an empty bounding box.
     * 
     */
    AABB::AABB() : min(Vec3{0, 0, 0}), max(Vec3{0, 0, 0}) {}

    /**
     * @brief Create a bounding box delimited by the upper left corner and the lower right one.
     * 
     * @param min - The lower right corner.
     * @param max - The upper left corner.
     */
    AABB::AABB(const Vec3 &min, const Vec3 &max) : min(min), max(max) {}

    /**
     * @brief Creates a new boundig box with the same size and position of an old one.
     * 
     * @param old - The bounding box to copy.
     */
    AABB::AABB(const AABB &old) : min(old.min), max(old.max) {}

    /**
     * @brief Returns the lower right corner.
     * 
     * @return const Vec3& - The lower right corner.
     */
    const Vec3& AABB::getMin() const{
        return this->min;
    }

    /**
     * @brief Returns the upper left corner.
     * 
     * @return const Vec3& - The upper left corner.
     */
    const Vec3& AABB::getMax() const{
        return this->max;
    }

    /**
     * @brief Computes if a ray hit the counding box using the slab methods.
     * 
     * @param ray - The ray.
     * @param tmin - The lower t to consider.
     * @param tmax - The greater t to consieder.
     * @return true - If the ray hit the aabb.
     * @return false - If the ray does not it the aabb.
     */
    bool AABB::hit(const srt::Ray &ray, float tmin, float tmax) const{
        for(size_t i = 0; i < 3; ++i){
            // Compute intersection point.
            const float invD = 1 / ray.getDirection()[i];
            float t0 = (this->min[i] - ray.getOrigin()[i]) * invD;
            float t1 = (this->max[i] - ray.getOrigin()[i]) * invD;

            if(invD < 0)    std::swap(t0, t1);

            // Compute the greater min and lower max.
            tmin = t0 > tmin ? t0 : tmin;
            tmax = t1 < tmax ? t1 : tmax;

            // Return false if the intervals does not intersect.
            if(tmax <= tmin)    return false;
        }
        return true;
    }

    /**
     * @brief Returns the box containing the current aabb and the passed one.
     * 
     * @param box - The other box to contain.
     * @return AABB - The aabb containing the two boxes.
     */
    AABB AABB::surroundingBox(const AABB &box) const{
        Vec3 lrc{std::min(this->min.x(), box.min.x()),
                 std::min(this->min.y(), box.min.y()),
                 std::min(this->min.z(), box.min.z())};
        Vec3 ulc{std::max(this->max.x(), box.max.x()),
                 std::max(this->max.y(), box.max.y()),
                 std::max(this->max.z(), box.max.z())};
        return AABB{lrc, ulc};
    }
}
}