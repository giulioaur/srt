#include "ds/Scene.hpp"


namespace srt::ds
{

Scene::Scene(const int32_t width, const int32_t height, const std::string &name,
	const float t0 /*= 0*/, const float t1 /*= 1*/)
	: m_width(width)
	, m_height(height)
	, m_name(name)
	, m_t0(t0)
	, m_t1(t1)
{

}

void Scene::addHitables(const std::vector<std::shared_ptr<geometry::hitables::Hitable>>& newHitables) 
{
	this->m_hitables.insert(this->m_hitables.end(), newHitables.begin(), newHitables.end());
}

const bool Scene::intersection(const geometry::Ray& ray, const float tmin, const float tmax, 
	geometry::hitables::Hitable::s_hit_record& hit_record) const
{
	for (const auto& hitable : m_hitables)
	{
		if (hitable->intersection(ray, tmin, tmax, hit_record))
		{
			return true;
		}
	}

	return false;
}

}

