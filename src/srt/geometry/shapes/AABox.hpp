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
public:
    // ENUMERATIONS

    /// The type of the box face.
    /// The directions refer to the viewpoint of a spectator that face the XY faces with negative normal.
    enum Face {BACK_FACE, FRONT_FACE, UP_FACE, BOT_FACE, RIGHT_FACE, LEFT_FACE};

private:
    // ATTRIBUTES

    std::array<AARectangle, 6> sides;
    Vec3 min, max;

public:
    // CONSTRUCTORS

    AABox(const Vec3 &min, const Vec3 &max, const std::shared_ptr<materials::Material> material);

    // METHODS

    virtual Hitable::hit_record intersection(const srt::Ray &ray, const float tmin, const float tmax) const;
    virtual std::unique_ptr<AABB> getAABB(const float t0, const float t1) const;
    virtual Vec3 getTextureCoords(const Vec3 &p) const;
    const AARectangle &getFace(Face face);
};

}
}
}

#endif