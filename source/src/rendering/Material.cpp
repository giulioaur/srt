#include "rendering/Material.hpp"

#include "utility/Randomizer.hpp"

namespace srt::rendering
{

Diffuse::Diffuse(const rendering::Color& albedo)
	: m_albedo(albedo)
{
}

bool Diffuse::hit(const geometry::Ray& ray, const geometry::hitables::Hitable::s_hit_record& hitRecord, 
	geometry::Ray& newRay, rendering::Color& attenuation) const
{
	attenuation = m_albedo;
	newRay = { hitRecord.point, 
		hitRecord.point + hitRecord.normal + utility::Randomizer::randomInUnitSphere() };
	return true;
}





Metal::Metal(const rendering::Color& albedo, const float blurriness)
	: m_albedo(albedo)
	, m_blurriness(blurriness)
{
}

bool Metal::hit(const geometry::Ray& ray, const geometry::hitables::Hitable::s_hit_record& hitRecord, 
	geometry::Ray& newRay, rendering::Color& attenuation) const
{
	const geometry::Vector4 reflected = reflect(ray.getDirection().normalize(), hitRecord.normal);
	attenuation = m_albedo;
	newRay = { hitRecord.point, reflected + m_blurriness * utility::Randomizer::randomInUnitSphere() };
	return newRay.getDirection().dot(hitRecord.normal) > 0;
}

geometry::Vector4 Metal::reflect(const geometry::Vector4& direction, const geometry::Vector4& normal) const
{
	return direction - 2 * direction.dot(normal) * normal;
}

}

