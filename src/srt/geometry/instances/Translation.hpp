/*******************************************************
 *                                                     *
 *  srt: Sushi RayTracer                               *
 *                                                     *
 *  TRANSLATION HEADER FILE                            *
 *                                                     *
 *  Giulio Auriemma                                    *
 *                                                     *
 *******************************************************/
#ifndef S_INSTANCES_TRASLATE_S
#define S_INSTANCES_TRASLATE_S

// My includes.
#include "../../Hitable.hpp"

namespace srt{
namespace geometry{
namespace instances{

/// This class is used to translate the wrapped hitable object.
class Translation : public Hitable{
private:
    // ATTRIBUTES

    std::shared_ptr<Hitable> object;
    Vec3 offset;  

public:
    // CONSTRUCTORS

    Translation(const std::shared_ptr<Hitable> object, const Vec3 &offset);
    Translation(const Translation &old);

    // METHODS

    virtual Hitable::hit_record intersection(const srt::Ray &ray, const float tmin, const float tmax) const;
    virtual const std::shared_ptr<materials::Material> &getMaterial() const;
    virtual std::unique_ptr<geometry::AABB> getAABB(const float t0, const float t1) const;
    virtual geometry::Vec3 getTextureCoords(const geometry::Vec3 &p) const;
};

}
}
}

#endif