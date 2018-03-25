/*******************************************************
 *                                                     *
 *  srt: Sushi RayTracer                               *
 *                                                     *
 *  ROTATION HEADER FILE                               *
 *                                                     *
 *  Giulio Auriemma                                    *
 *                                                     *
 *******************************************************/
#ifndef S_INSTANCES_ROTATION_S
#define S_INSTANCES_ROTATION_S

// System includes.
#include <array>

// My includes.
#include "../../Hitable.hpp"
#include "../../geometry/Mat3.hpp"

namespace srt{
namespace geometry{
namespace instances{

/// This class is used to translate the wrapped hitable object.
class Rotation : public Hitable{
public: 
    // ENUMARATION

    /// The type of the rotation.
    enum Type {roll, pitch, yaw};

private:
    // ATTRIBUTES

    std::shared_ptr<Hitable> object;
    Mat3 rotationMat, inverseMat;  

public:
    // CONSTRUCTORS

    Rotation(const Type type, const std::shared_ptr<Hitable> object, const float degree);
    Rotation(const Rotation &old);

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