#include "ds/Scene.hpp"


namespace srt::ds
{

Scene::Scene(const int32_t width, const int32_t height, const std::string &name,
	std::vector<std::shared_ptr<geometry::hitables::Hitable>>& objects,
	const float t0 /*= 0*/, const float t1 /*= 1*/)
	: m_name(name)
	, m_height(height)
	, m_width(width)
	, m_time0(t0)
	, m_time1(t1)
	, m_hitablesTree(objects, t0, t1)
	, m_hitablesOctree(objects, 1, 0, t0, t1)
	, m_objects(objects)
{

}

const bool Scene::intersect(const geometry::Ray& ray, const float tmin, const float tmax,
	geometry::hitables::Hitable::s_hit_record& hit_record) const
{
	//geometry::hitables::Hitable::s_hit_record tmpRecord;
	//geometry::hitables::Hitable::s_hit_record maxRecord;

	//for (const auto& hitable : m_objects)
	//{
	//	if (hitable->intersect(ray, tmin, tmax, tmpRecord))
	//	{
	//		if (tmpRecord.t < maxRecord.t)
	//		{
	//			maxRecord = tmpRecord;
	//		}
	//	}
	//}

	//if (maxRecord.hit)
	//{
	//	hit_record = maxRecord;
	//	return true;
	//}
	//return false;
	//return m_hitablesTree.intersect(ray, tmin, tmax, hit_record);
	return m_hitablesOctree.intersect(ray, tmin, tmax, hit_record);
}

}

