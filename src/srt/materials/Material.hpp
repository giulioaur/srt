/*******************************************************
 *                                                     *
 *  srt: Sushi RayTracer                               *
 *                                                     *
 *  MATERIAL HEADER FILE                               *
 *                                                     *
 *  Giulio Auriemma                                    *
 *                                                     *
 *******************************************************/
#ifndef S_MATERIALS_MATERIAL_S
#define S_MATERIALS_MATERIAL_S

// My includes
#include "../geometry/Vec3.hpp"
#include "../Ray.hpp"

namespace srt{
namespace materials{

/// The abstract material class.
class Material{
private:
    // ATTRIBUTES

public:
    // METHODS
    virtual bool scatter(Ray &ray, geometry::Vec3 &attenuation, const geometry::Vec3 &hitPoint, 
                            const geometry::Vec3 &normal) const = 0;
};
}
}

#endif