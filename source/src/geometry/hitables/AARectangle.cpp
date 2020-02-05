#include "geometry/hitables/AARectangle.hpp"

namespace srt::geometry::hitables
{

template<>
Vector4 AARectangle<e_rect_type::XY>::getNormal() const
{
	return{ 0, 0, m_isNormalFlipped ? -1.f : 1.f, 0 };
}

template<>
bool AARectangle<e_rect_type::XY>::intersect(const Ray& ray, const float tmin, const float tmax,
	s_hit_record& hit_record) const
{
	return intersectHelper(ray, tmin, tmax, hit_record, 0, 1, 2);
}

template <>
const geometry::AABB AARectangle<e_rect_type::XY>::getAABB(const float t0, const float t1) const noexcept
{
	return geometry::AABB{
		Vector4{ m_axis0_0, m_axis1_0, m_k - 0.0001f, 0 },
		Vector4{ m_axis0_1, m_axis1_1, m_k + 0.0001f, 0 }
	};
}

template<>
TextureCoords AARectangle<e_rect_type::XY>::getTextureCoords(const Vector4 &p) const
{
	return { (p.x() - m_axis0_0) / (m_axis0_1 - m_axis0_0),
			 (p.y() - m_axis1_0) / (m_axis1_1 - m_axis1_0)};
}

template<>
Vector4 AARectangle<e_rect_type::XZ>::getNormal() const
{
	return{ 0, m_isNormalFlipped ? -1.f : 1.f, 0, 0 };
}

template<>
bool AARectangle<e_rect_type::XZ>::intersect(const Ray& ray, const float tmin, const float tmax,
	s_hit_record& hit_record) const
{
	return intersectHelper(ray, tmin, tmax, hit_record, 0, 2, 1);
}

template <>
const geometry::AABB AARectangle<e_rect_type::XZ>::getAABB(const float t0, const float t1) const noexcept
{
	return geometry::AABB{
		Vector4{ m_axis0_0, m_k - 0.0001f, m_axis1_0, 0 },
		Vector4{ m_axis0_1, m_k + 0.0001f, m_axis1_1, 0 }
	};
}

template<>
TextureCoords AARectangle<e_rect_type::XZ>::getTextureCoords(const Vector4& p) const
{
	return { (p.x() - m_axis0_0) / (m_axis0_1 - m_axis0_0),
			 (p.z() - m_axis1_0) / (m_axis1_1 - m_axis1_0) };
}

template<>
Vector4 AARectangle<e_rect_type::YZ>::getNormal() const
{
	return{ m_isNormalFlipped ? -1.f : 1.f, 0, 0, 0 };
}

template<>
bool AARectangle<e_rect_type::YZ>::intersect(const Ray& ray, const float tmin, const float tmax,
	s_hit_record& hit_record) const
{
	return intersectHelper(ray, tmin, tmax, hit_record, 1, 2, 0);
}

template <>
const geometry::AABB AARectangle<e_rect_type::YZ>::getAABB(const float t0, const float t1) const noexcept
{
	return geometry::AABB{
		Vector4{ m_k - 0.0001f, m_axis0_0, m_axis1_0, 0 },
		Vector4{ m_k + 0.0001f, m_axis0_1, m_axis1_1, 0 }
	};
}

template<>
TextureCoords AARectangle<e_rect_type::YZ>::getTextureCoords(const Vector4& p) const
{
	return { (p.y() - m_axis0_0) / (m_axis0_1 - m_axis0_0),
			 (p.z() - m_axis1_0) / (m_axis1_1 - m_axis1_0) };
}

}