#pragma once

#include "geometry/hitables/Hitable.hpp"

namespace srt::geometry::hitables {

/// This class represents a sphere shape.
class Sphere : public Hitable {

public:

    /**
     * @brief Creates a new sphere.
     *
     * @param center - The center of the sphere.
     * @param radius - The radius of the sphere.
     * @param plane - The normal vector of the plane containing the sphere
     * @param color - The color of the sphere.
     */
    Sphere(const Vector4& center, const float radius);
    //Sphere(const Vector4& center, const float radius, const std::shared_ptr<materials::Material> material);

    // OPERATORS

    bool operator == (const Hitable& hitable) const;
    bool operator != (const Hitable& hitable) const;

    // METHODS

    float getRadius() const { return radius; };
    const Vector4& getCenter() const { return center; };
    virtual Vector4 getNormal(const Vector4& pos) const;
    virtual bool intersection(const Ray& ray, const float tmin, const float tmax,
        Hitable::s_hit_record& hit_record) const;
    //virtual const std::shared_ptr<materials::Material>& getMaterial() const;
    //virtual std::unique_ptr<AABB> getAABB(const float t0, const float t1) const;
    //virtual Vector4 getTextureCoords(const Vector4& p) const;


private:

    const Vector4 center;
    float radius;
    //std::shared_ptr<materials::Material> material;

};

}