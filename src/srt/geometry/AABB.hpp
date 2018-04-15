/*******************************************************
 *                                                     *
 *  srt: Sushi RayTracer                               *
 *                                                     *
 *  AABB HEADER FILE                                   *
 *                                                     *
 *  Giulio Auriemma                                    *
 *                                                     *
 *******************************************************/
#ifndef S_GEOMETRY_AABB_S
#define S_GEOMETRY_AABB_S

#include "Vec3.hpp"
#include "../Ray.hpp"

namespace srt{
namespace geometry{

/// This class represents a axis aligned bounding box. It is used to make faster
/// the computation of the ray-shape intersection. 
/// It is build using the upper left corner and lower right corner that represent
/// respectively the intersection of the planes with the greater x, y, z and the 
/// intersection of the ones with the lower x, y, z. 
/// NB: since we are considering axis aligned planes, one coordinate is sufficient.
class AABB{
private:
    // ATTRIBUTES

    Vec3 min, max;

public:
    // CONSTRUCTORS

    AABB();
    AABB(const Vec3 &min, const Vec3 &max);

    // METHODS

    const Vec3 &getMin() const;
    const Vec3 &getMax() const;
    bool hit(const srt::Ray &ray, float tmin, float tmax) const;
    AABB surroundingBox(const AABB &box) const;
};

}
}

#endif