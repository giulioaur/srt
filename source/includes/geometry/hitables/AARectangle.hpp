#pragma once

#include "Hitable.hpp"
#include "rendering/Material.hpp"

namespace srt::geometry::hitables
{

/// The type of the axis aligned rectangle.
enum class e_rect_type : uint8_t { XY, XZ, YZ };

/// This class represents an axis aligned rectangle.
template <e_rect_type TYPE>
class AARectangle : public Hitable 
{
public:

public:

	/**
	 * @brief Construct a new AARectangle object.
	 *
	 * @param type - The type of the rectangle.
	 * @param a0_0 - The lower bound of the first axis.
	 * @param a0_1 - The upper bound of the first axis.
	 * @param a1_0 - The lower bound of the second axis.
	 * @param a1_1 - The upper bound of the second axis.
	 * @param t - The distance from the last axis.
	 * @param material - The material of the rectangle.
	 */
	AARectangle(const float a0_0, const float a0_1, const float a1_0, const float a1_1,
		const float k, const std::shared_ptr<rendering::Material> material, bool flipNormal = false);
	virtual bool intersect(const Ray &ray, const float tmin, const float tmax,
		s_hit_record& hit_record) const override;
	virtual const AABB getAABB(const float t0, const float t1) const noexcept override;

private:

	bool intersectHelper(const Ray& ray, const float tmin, const float tmax,
		s_hit_record& hit_record, const uint8_t a0, const uint8_t a1, const uint8_t a2) const;
	Vector4 getNormal() const;
	TextureCoords getTextureCoords(const Vector4 &p) const;

	bool m_isNormalFlipped;
	float m_axis0_0;
	float m_axis0_1;
	float m_axis1_0; 
	float m_axis1_1;
	float m_k;
	std::shared_ptr<rendering::Material> m_material;
	Vector4 m_normal;

	friend class AABox;
};


template<e_rect_type TYPE>
AARectangle<TYPE>::AARectangle(const float a0_0, const float a0_1, const float a1_0, 
	const float a1_1, const float k, const std::shared_ptr<rendering::Material> material, bool flipNormal)
	: m_axis0_0(a0_0)
	, m_axis0_1(a0_1)
	, m_axis1_0(a1_0)
	, m_axis1_1(a1_1)
	, m_k(k)
	, m_material(material)
	, m_isNormalFlipped(flipNormal)
	, m_normal(getNormal())
{
}

template<e_rect_type TYPE>
bool AARectangle<TYPE>::intersectHelper(const Ray& ray, const float tmin, const float tmax, 
	s_hit_record& hit_record, const uint8_t a0, const uint8_t a1, const uint8_t a2) const
{
	const Vector4 ro = ray.getOrigin(), rd = ray.getDirection();

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

	hit_record = { true, t, this, hitPoint, m_normal, m_material, getTextureCoords(hitPoint) };
	return true;
}


}