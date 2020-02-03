#pragma once

#include "Hitable.hpp"
#include "rendering/Material.hpp"

namespace srt::geometry::hitables
{

/// This class represents an axis aligned rectangle.
class AARectangle : public Hitable {
public:
	/// The type of the axis aligned rectangle.
	enum e_type { XY, XZ, YZ };

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
	AARectangle(const AARectangle::e_type type, const float a0_0, const float a0_1, const float a1_0, const float a1_1,
		const float k, const std::shared_ptr<rendering::Material> material, bool flipNormal = false);

	virtual Vector4 getNormal(const Vector4& pos) const;
	virtual bool intersect(const Ray &ray, const float tmin, const float tmax,
		s_hit_record& hit_record) const override;
	virtual const AABB getAABB(const float t0, const float t1) const noexcept override;

private:

	TextureCoords getTextureCoords(const Vector4 &p) const;

	e_type m_type;
	bool m_isNormalFlipped;
	std::shared_ptr<rendering::Material> m_material;
	float m_axis0_0;
	float m_axis0_1;
	float m_axis1_0; 
	float m_axis1_1;
	float m_k;
};

}