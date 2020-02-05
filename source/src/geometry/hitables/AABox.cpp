#include "geometry/hitables/AABox.hpp"

namespace srt::geometry::hitables
{

AABox::AABox(const Vector4& min, const Vector4& max, const std::shared_ptr<srt::rendering::Material> material)
	: m_min(min)
    , m_max(max)
    , m_material(material)
{
}

bool AABox::intersect(const Ray& ray, float tmin, float tmax, s_hit_record& hit_record) const
{
    const Vector4 invD = ray.getInvD();
    for (uint8_t i = 0; i < 3; ++i)
    {
        // Compute intersection point.
        float t0 = (m_min[i] - ray.getOrigin()[i]) * invD[i];
        float t1 = (m_max[i] - ray.getOrigin()[i]) * invD[i];

        if (invD[i] < 0)
        {
            srt::swap(t0, t1);
        }

        // Compute the greater min and lower max.
        tmin = t0 > tmin ? t0 : tmin;
        tmax = t1 < tmax ? t1 : tmax;

        // Return false if the intervals does not intersect.
        if (tmax <= tmin)    return false;
    }

    const Vector4 point = ray.getPoint(tmin);
    hit_record = { true, tmin, this, point, getNormal(point), m_material, getTextureCoords(point) };
    return true;
}

const AABB AABox::getAABB(const float t0, const float t1) const noexcept
{
    return AABB{ m_min, m_max };
}

Vector4 AABox::getNormal(const Vector4& p) const noexcept
{
    if (p.z() == m_min.z())       // FRONT FACE
        return { 0, 0, -1, 0 };
    else if (p.z() == m_max.z())  // BACK FACE
        return { 0, 0, 1, 0 };
    else if (p.x() == m_min.x())  // LEFT FACE
        return { -1, 0, 0, 0 };
    else if (p.x() == m_max.x())  // RIGHT FACE
        return { 1, 0, -1, 0 };
    else if (p.y() == m_min.y())  // BOTTOM FACE
        return { 0, 0, -1, 0 };
    else                            // UPPER FACE
        return { 0, 0, 1, 0 };
}

TextureCoords AABox::getTextureCoords(const Vector4& p) const noexcept
{
    const Vector4 coords = (p - m_min) / (m_max - m_min);

    if (p.z() == m_min.z() || p.z() == m_max.z())       // FRONT / BACK FACE
        return { coords[0], coords[1] };
    else if (p.x() == m_min.x() || p.x() == m_max.x())  // LEFT / RIGHT FACE
        return { coords[1], coords[2] };
    else                                            // BOTTOM / UPPER FACE
        return { coords[0], coords[2] };
}

}