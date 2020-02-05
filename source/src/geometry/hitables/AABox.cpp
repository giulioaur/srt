#include "..\..\..\includes\geometry\hitables\AABox.hpp"

namespace srt::geometry::hitables
{

AABox::AABox(const Vector4& min, const Vector4& max, const std::shared_ptr<srt::rendering::Material> material)
	: m_sides{ { AARectangle(AARectangle::e_type::XY, min.x(), max.x(), min.y(), max.y(), max.z(), material),
                 AARectangle(AARectangle::e_type::XY, min.x(), max.x(), min.y(), max.y(), min.z(), material, true),
                 AARectangle(AARectangle::e_type::XZ, min.x(), max.x(), min.z(), max.z(), max.y(), material),
                 AARectangle(AARectangle::e_type::XZ, min.x(), max.x(), min.z(), max.z(), min.y(), material, true),
                 AARectangle(AARectangle::e_type::YZ, min.y(), max.y(), min.z(), max.z(), max.x(), material),
                 AARectangle(AARectangle::e_type::YZ, min.y(), max.y(), min.z(), max.z(), min.x(), material, true)} }
{
}

bool AABox::intersect(const Ray& ray, const float tmin, const float tmax, s_hit_record& hit_record) const
{
    Hitable::s_hit_record bestRecord;
    bestRecord.t = tmax;

    for (const auto& side : m_sides) 
    {
        side.intersect(ray, tmin, bestRecord.t, bestRecord);
    }

    if (bestRecord.hit)
    {
        hit_record = bestRecord;
        return true;
    }

    return false;
}

const AABB AABox::getAABB(const float t0, const float t1) const noexcept
{
    return AABB{
        { m_sides[5].m_k, m_sides[3].m_k, m_sides[1].m_k, 0 },
        { m_sides[4].m_k, m_sides[2].m_k, m_sides[0].m_k, 0 }
    };
}

const AARectangle& AABox::getFace(const e_face face) const noexcept
{
    return m_sides[static_cast<size_t>(face)];
}

}