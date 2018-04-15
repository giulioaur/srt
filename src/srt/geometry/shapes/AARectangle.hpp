/*******************************************************
 *                                                     *
 *  srt: Sushi RayTracer                               *
 *                                                     *
 *  AARECTANGLE HEADER FILE                            *
 *                                                     *
 *  Giulio Auriemma                                    *
 *                                                     *
 *******************************************************/
#ifndef S_SHAPES_AARECTANGLE_S
#define S_SHAPES_AARECTANGLE_S

// My includes.
#include "../../Hitable.hpp"

namespace srt{
namespace geometry{
namespace shapes{

/// This class represents an axis aligned rectangle.
class AARectangle : public Hitable{
public:
    // ENUMERATIONS

    /// The type of the axis aligned rectangle.
    enum Type {XY, XZ, YZ};

private:
    // ATTRIBUTES

    Type type;
    float axis0_0, axis0_1, axis1_0, axis1_1, k;
    std::shared_ptr<materials::Material> material;
    bool isNormalFlipped;

public:
    // CONSTRUCTORS

    AARectangle(const AARectangle::Type type, const float a0_0, const float a0_1, const float a1_0, const float a1_1, 
                const float k, const std::shared_ptr<materials::Material> material, bool flipNormal = false);

    // METHODS

    virtual Vec3 getNormal(const Vec3 &pos) const;
    virtual Hitable::hit_record intersection(const Ray &ray, const float tmin, const float tmax) const;
    virtual const std::shared_ptr<materials::Material> &getMaterial() const;
    virtual std::unique_ptr<AABB> getAABB(const float t0, const float t1) const;
    virtual Vec3 getTextureCoords(const Vec3 &p) const;
};

}
}
}

#endif