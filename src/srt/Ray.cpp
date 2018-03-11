/*******************************************************
 *                                                     *
 *  srt: Sushi RayTracer                               *
 *                                                     *
 *  RAY CLASS FILE                                     *
 *                                                     *
 *  Giulio Auriemma                                    *
 *                                                     *
 *******************************************************/
#include "Ray.hpp"

using namespace std;
using namespace srt::geometry;

namespace srt{
    /**
     * @brief Creates a new ray.
     * 
     * @param o - The origin of the ray.
     * @param dir - The direction of the ray.
     * @param time - The time the ray is shot.
     */
    Ray::Ray(const Vec3 &origin, const Vec3 &direction, const float time) : origin(origin), 
        direction(direction.normalize()), time(time) {}

    /**
     * @brief Creates a new ray equal to an old one.
     * 
     * @param old - The old ray.
     */
    Ray::Ray(const Ray &old) : origin(old.origin), direction(old.direction), time(old.time) {}

    /**
     * @brief Returns a copy of the vector that indicates the origin of the ray.
     * 
     * @return Vec3 - The origin of the ray.
     */
    const Vec3& Ray::getOrigin() const{
        return this->origin;
    }

    /**
     * @brief Returns a copy of the vector that indicates the direction of the ray.
     * 
     * @return unique_ptr<Vec3> - The direction of the ray.
     */
    const Vec3& Ray::getDirection() const{
        return this->direction;
    }

    /**
     * @brief Returns the time on which the ray was shot.
     * 
     * @return float - The time the ray was shot.
     */
    float Ray::getTime() const{
        return this->time;
    }

    /**
     * @brief Gets the point of the vector at distance d.
     * 
     * @param distance - The distance of the point from the origin. 
     * @return geometry::Vec3 getPosition - The position of the point at distance d.
     */
    Vec3 Ray::getPoint(const float distance) const{
        return this->origin + (this->direction * distance);
    }
}