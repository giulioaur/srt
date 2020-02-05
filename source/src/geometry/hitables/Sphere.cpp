#include "geometry/hitables/Sphere.hpp"

#include <algorithm>
#include <cmath>

namespace srt::geometry::hitables
{

Sphere::Sphere(const Vector4& center, const float radius, const std::shared_ptr<rendering::Material> material) 
	: m_center(center)
	, m_radius(radius)
	, m_material(material) { }

bool Sphere::intersect(const Ray& ray, const float tmin, const float tmax,
    Hitable::s_hit_record& hit_record) const 
{
    const Vector4 dist = ray.getOrigin() - m_center;
    const float a = ray.getDirection().squaredMagnitude();
    const float b = 2.f * (ray.getDirection() * dist);
    const float c = dist.squaredMagnitude() - m_radius * m_radius;
    const float delta = b * b - 4 * a * c;
    float t = -1;

    // If the solution is only one, use it to return the point, else return the positive one.
    // if(delta == 0)  t = -0.5 * b / a;
    if (delta > 0) {
        const float q = b < 0 ? -0.5f * (b - sqrt(delta)) : -0.5f * (b + sqrt(delta));
        const float t0 = q / a, t1 = c / q;
        if (t0 > 0 && t1 > 0)        t = std::min(t0, t1);
        else                         t = std::max(t0, t1);
    }

    if (t >= tmin && t <= tmax)
    {
		const Vector4 hitPoint = ray.getPoint(t);
        hit_record = { 
			true, 
			t, 
			this, 
			hitPoint,
			this->getNormal(ray.getPoint(t)), 
			m_material, 
			getTextureCoordsOnPoint(hitPoint)
		};
        return true;
    }
    return false;
}

/**
 * @brief Returns the normal to the circle of a given point.
 *
 * @param pos - The position on which compute the normal.
 * @return srt::geometry::Vector4 getNormal - The normal to the circle at given point.
 */
Vector4 Sphere::getNormal(const Vector4& pos) const 
{
    return (pos - m_center) / m_radius;
}

const geometry::AABB Sphere::getAABB(const float t0, const float t1) const noexcept
{
    return AABB{ m_center - Vector4{ m_radius }, m_center + Vector4{ m_radius } };
}

srt::geometry::hitables::TextureCoords Sphere::getTextureCoordsOnPoint(const Vector4& p) const
{
	// Compute the phi and theta angle.
    float phi = atan2(p.z(), p.x()), theta = asin(p.y());

    // Compute the u and v coords.
    float u = 1 - (phi + M_PI) / (2 * M_PI),
          v = (theta + M_PI / 2) / M_PI;

    return{ u, v };
}

}