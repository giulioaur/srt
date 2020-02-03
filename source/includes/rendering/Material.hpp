#pragma once

#include "geometry/hitables/Hitable.hpp"
#include "geometry/Ray.hpp"
#include "geometry/Vector4.hpp"
#include "rendering/Color.hpp"
#include "rendering/Texture.hpp"

namespace srt::rendering
{

class Material
{
public: 

	virtual bool bounce(const geometry::Ray& ray, const geometry::hitables::Hitable::s_hit_record& hit_record,
		geometry::Ray& newRay, rendering::Color& attenuation) const = 0;

};


class Diffuse : public Material
{
public:

	Diffuse(const std::shared_ptr<rendering::Texture>& albedo);

	virtual bool bounce(const geometry::Ray& ray, const geometry::hitables::Hitable::s_hit_record& hit_record,
		geometry::Ray& newRay, rendering::Color& attenuation) const;

private:

	const std::shared_ptr<rendering::Texture> m_albedo;
};

class Metal : public Material
{
public:

	Metal(const std::shared_ptr<rendering::Texture>& albedo, const float blurriness);

	virtual bool bounce(const geometry::Ray& ray, const geometry::hitables::Hitable::s_hit_record& hit_record,
		geometry::Ray& newRay, rendering::Color& attenuation) const;

private:

	geometry::Vector4 reflect(const geometry::Vector4& direction, const geometry::Vector4& normal) const;

	const std::shared_ptr<rendering::Texture> m_albedo;
	const float m_blurriness;
};

class DiffuseLight : public Material
{
public:

	DiffuseLight(const rendering::Color& lightColor);

	virtual bool bounce(const geometry::Ray& ray, const geometry::hitables::Hitable::s_hit_record& hit_record,
		geometry::Ray& newRay, rendering::Color& attenuation) const;

private:

	const rendering::Color m_albedo;
};

}