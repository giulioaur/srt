#include "geometry/hitables/AARectangle.hpp"

namespace srt::geometry::hitables
{
AARectangle::AARectangle(const AARectangle::e_type type, const float a0_0, const float a0_1, const float a1_0, const float a1_1,
	const float k, const std::shared_ptr<rendering::Material> material, bool flipNormal) 
	: m_type(type)
	, m_axis0_0(a0_0)
	, m_axis0_1(a0_1)
	, m_axis1_0(a1_0)
	, m_axis1_1(a1_1)
	, m_k(k)
	, m_material(material)
	, m_isNormalFlipped(flipNormal)
{
}

Vector4 AARectangle::getNormal(const Vector4 &pos) const 
{
	switch (m_type) 
	{
	case AARectangle::XY:	return{ 0, 0, m_isNormalFlipped ? -1.f : 1.f, 0 };
	case AARectangle::XZ:	return{ 0, m_isNormalFlipped ? -1.f : 1.f, 0, 0 };
	case AARectangle::YZ:	return{ m_isNormalFlipped ? -1.f : 1.f, 0, 0, 0 };
	default:				return{ 0, 0, 0, 0 };
	}
}

bool AARectangle::intersect(const Ray &ray, const float tmin, const float tmax,
	s_hit_record& hit_record) const 
{
	uint8_t a0, a1, a2;
	const Vector4 ro = ray.getOrigin(), rd = ray.getDirection();

	// Set the index of the coords for the three axis.
	switch (m_type) {
	case AARectangle::XY:
		// First axis = x, second axis = y, last axis = z.
		a0 = 0; a1 = 1; a2 = 2; break;
	case AARectangle::XZ:
		// First axis = x, second axis = z, last axis = y.
		a0 = 0; a1 = 2; a2 = 1; break;
	case AARectangle::YZ:
	default:
		// First axis = y, second axis = z, last axis = x.
		a0 = 1; a1 = 2; a2 = 0; break;
	}

	// Compute t.
	float t = (m_k - ro[a2]) / rd[a2];
	if (t < tmin || t > tmax)   return false;

	// Compute the hit point.
	Vector4 hitPoint = ray.getPoint(t);
	if (hitPoint[a0] < m_axis0_0 || hitPoint[a0] > m_axis0_1 ||
		hitPoint[a1] < m_axis1_0 || hitPoint[a1] > m_axis1_1)
	{
		return false;
	}

	hit_record = { true, t, this, hitPoint, getNormal(hitPoint), m_material, getTextureCoords(hitPoint) };
	return true;
}


const geometry::AABB AARectangle::getAABB(const float t0, const float t1) const noexcept
{
	switch (m_type) {
	case AARectangle::XY:
		return geometry::AABB{ 
			Vector4{ m_axis0_0, m_axis1_0, m_k - 0.0001f, 0 },
			Vector4{ m_axis0_1, m_axis1_1, m_k + 0.0001f, 0 }
		};
	case AARectangle::XZ:
		return geometry::AABB{
			Vector4{ m_axis0_0, m_k - 0.0001f, m_axis1_0, 0 },
			Vector4{ m_axis0_1, m_k + 0.0001f, m_axis1_1, 0 }
		};
	case AARectangle::YZ:
		return geometry::AABB{
			Vector4{ m_k - 0.0001f, m_axis0_0, m_axis1_0, 0 },
			Vector4{ m_k + 0.0001f, m_axis0_1, m_axis1_1, 0 }
		};
	default:
		return geometry::AABB{
			Vector4{ 0, 0, 0, 0 },
			Vector4{ 0, 0, 0, 0 }
		};
	}
}

TextureCoords AARectangle::getTextureCoords(const Vector4 &p) const
{
	switch (m_type) {
	case AARectangle::XY:
		return { (p.x() - m_axis0_0) / (m_axis0_1 - m_axis0_0),
				(p.y() - m_axis1_0) / (m_axis1_1 - m_axis1_0)};
	case AARectangle::XZ:
		return { (p.x() - m_axis0_0) / (m_axis0_1 - m_axis0_0),
				(p.z() - m_axis1_0) / (m_axis1_1 - m_axis1_0) };
	case AARectangle::YZ:
		return { (p.y() - m_axis0_0) / (m_axis0_1 - m_axis0_0),
				(p.z() - m_axis1_0) / (m_axis1_1 - m_axis1_0)};
	default:
		return { 0, 0 };
	}
}

//
//Vector4 AARectangle::getTextureCoords(const geometry::Vector4 &p) const 
//{
//	switch (m_type) {
//	case AARectangle::XY:
//		return { (p.x() - m_axis0_0) / (m_axis0_1 - m_axis0_0),
//				(p.y() - m_axis1_0) / (m_axis1_1 - m_axis1_0),
//				0 };
//	case AARectangle::XZ:
//		return { (p.x() - m_axis0_0) / (m_axis0_1 - m_axis0_0),
//				(p.z() - m_axis1_0) / (m_axis1_1 - m_axis1_0),
//				0 };
//	case AARectangle::YZ:
//		return { (p.y() - m_axis0_0) / (m_axis0_1 - m_axis0_0),
//				(p.z() - m_axis1_0) / (m_axis1_1 - m_axis1_0),
//				0 };
//	}
//}
}