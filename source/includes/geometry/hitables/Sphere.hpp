#pragma once

#include <memory>

#include "geometry/hitables/Hitable.hpp"

namespace srt::geometry::hitables 
{

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
    Sphere(const Vector4& center, const float radius, const std::shared_ptr<rendering::Material> material);

    float getRadius() const { return m_radius; };
    const Vector4& getCenter() const { return m_center; };
    virtual Vector4 getNormal(const Vector4& pos) const;
	virtual const std::shared_ptr<rendering::Material>& getMaterial() const { return m_material; };

    virtual bool intersection(const Ray& ray, const float tmin, const float tmax,
        Hitable::s_hit_record& hit_record) const;
    //virtual std::unique_ptr<AABB> getAABB(const float t0, const float t1) const;
	//virtual Vector4 getTextureCoords(const Vector4& p) const;

	// OPERATORS

	bool operator == (const Hitable& hitable) const;
	bool operator != (const Hitable& hitable) const;


private:

    const Vector4 m_center;
    float m_radius;
    const std::shared_ptr<rendering::Material> m_material;

};

}