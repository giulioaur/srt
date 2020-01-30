#pragma once

#include "geometry/hitables/Hitable.hpp"
#include "geometry/Ray.hpp"
#include "geometry/Vector4.hpp"
#include "rendering/Color.hpp"

namespace srt::rendering
{

class Material
{
public: 

	virtual bool hit(const geometry::Ray& ray, const geometry::hitables::Hitable::s_hit_record& hitRecord,
		geometry::Ray& newRay, rendering::Color& attenuation) const = 0;

};


class Diffuse : public Material
{
public:

	Diffuse(const rendering::Color& albedo);

	virtual bool hit(const geometry::Ray& ray, const geometry::hitables::Hitable::s_hit_record& hitRecord,
		geometry::Ray& newRay, rendering::Color& attenuation) const;

private:

	const rendering::Color m_albedo;
};

class Metal : public Material
{
public:

	Metal(const rendering::Color& albedo, const float blurriness);

	virtual bool hit(const geometry::Ray& ray, const geometry::hitables::Hitable::s_hit_record& hitRecord,
		geometry::Ray& newRay, rendering::Color& attenuation) const;

private:

	geometry::Vector4 reflect(const geometry::Vector4& direction, const geometry::Vector4& normal) const;

	const rendering::Color m_albedo;
	const float m_blurriness;
};

}