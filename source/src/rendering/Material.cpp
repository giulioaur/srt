#include "rendering/Material.hpp"

#include "utility/Randomizer.hpp"

namespace srt::rendering
{

Diffuse::Diffuse(const rendering::Color& albedo)
	: m_albedo(albedo)
{
}

bool Diffuse::hit(const geometry::Ray& ray, const geometry::hitables::Hitable::s_hit_record& hit_record, 
	geometry::Ray& newRay, rendering::Color& attenuation) const
{
	attenuation = m_albedo;
	newRay = { hit_record.point, 
		hit_record.point + hit_record.normal + utility::Randomizer::randomInUnitSphere() };
	return true;
}





Metal::Metal(const rendering::Color& albedo, const float blurriness)
	: m_albedo(albedo)
	, m_blurriness(blurriness)
{
}

bool Metal::hit(const geometry::Ray& ray, const geometry::hitables::Hitable::s_hit_record& hit_record, 
	geometry::Ray& newRay, rendering::Color& attenuation) const
{
	const geometry::Vector4 reflected = reflect(ray.getDirection().normalize(), hit_record.normal);
	attenuation = m_albedo;
	newRay = { hit_record.point, reflected + m_blurriness * utility::Randomizer::randomInUnitSphere() };
	return newRay.getDirection().dot(hit_record.normal) > 0;
}

geometry::Vector4 Metal::reflect(const geometry::Vector4& direction, const geometry::Vector4& normal) const
{
	return direction - 2 * direction.dot(normal) * normal;
}

}

