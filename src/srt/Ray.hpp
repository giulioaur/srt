#ifndef S_RAY_S
#define S_RAY_S

// System includes.
#include <memory>

// My includes.
#include "geometry/Vec3.hpp"

namespace srt{
class Ray{
private:
    // ATTRIBUTES

    geometry::Vec3 origin, direction;
    float time;

public:
    /**
     * @brief Creates a new ray.
     * 
     * @param o - The origin of the ray.
     * @param dir - The direction of the ray.
     * @param time - The time the ray is shot.
     */
    Ray(const geometry::Vec3 &origin, const geometry::Vec3 &direction, const float time = 1) : origin(origin), 
        direction(direction.normalize()), time(time) {}

    /**
     * @brief Creates a new ray equal to an old one.
     * 
     * @param old - The old ray.
     */
    Ray(const Ray &old) : origin(old.origin), direction(old.direction), time(old.time) {}

    /**
     * @brief Returns a copy of the vector that indicates the origin of the ray.
     * 
     * @return geometry::Vec3 - The origin of the ray.
     */
    VM_INLINE const geometry::Vec3& getOrigin() const{
        return this->origin;
    }

    /**
     * @brief Returns a copy of the vector that indicates the direction of the ray.
     * 
     * @return unique_ptr<Vec3> - The direction of the ray.
     */
    VM_INLINE const geometry::Vec3& getDirection() const{
        return this->direction;
    }

    /**
     * @brief Returns the time on which the ray was shot.
     * 
     * @return float - The time the ray was shot.
     */
    VM_INLINE float getTime() const{
        return this->time;
    }

    /**
     * @brief Gets the point of the vector at distance d.
     * 
     * @param distance - The distance of the point from the origin. 
     * @return geometry::Vec3 getPosition - The position of the point at distance d.
     */
    VM_INLINE geometry::Vec3 getPoint(const float distance) const{
        return this->origin + (this->direction * distance);
    }
};
}

#endif