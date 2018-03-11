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
    // CONSTRUCTORS
    
    Ray(const geometry::Vec3 &origin, const geometry::Vec3 &direction, const float time = 0);
    Ray(const Ray &old);

    // METHODS

    const geometry::Vec3& getOrigin() const;
    const geometry::Vec3& getDirection() const;
    float getTime() const;
    geometry::Vec3 getPoint(const float distance) const;
};
}

#endif