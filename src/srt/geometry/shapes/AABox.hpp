/*******************************************************
 *                                                     *
 *  srt: Sushi RayTracer                               *
 *                                                     *
 *  AABOX HEADER FILE                                  *
 *                                                     *
 *  Giulio Auriemma                                    *
 *                                                     *
 *******************************************************/
#ifndef S_SHAPES_AABOX_S
#define S_SHAPES_AABOX_S

// System includes.
#include <array>

// My includes.
#include "AARectangle.hpp"

namespace srt{
namespace geometry{
namespace shapes{

/// This class represents an axis aligned box.
class AABox : public Hitable{
private:
    // ATTRIBUTES

    std::array<AARectangle, 6> sides;
    Vec3 min, max;

public:
    // CONSTRUCTORS

    AABox(const Vec3 &min, const Vec3 &max, const std::shared_ptr<materials::Material> material);
    AABox(const AABox &old);

    // METHODS

    virtual Hitable::hit_record intersection(const srt::Ray &ray, const float tmin, const float tmax) const;
    virtual std::unique_ptr<geometry::AABB> getAABB(const float t0, const float t1) const;
    virtual geometry::Vec3 getTextureCoords(const geometry::Vec3 &p) const;
};

}
}
}

#endif