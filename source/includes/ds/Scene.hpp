#pragma once

#include <memory>
#include <string>
#include <vector>

#include "ds/BVH.hpp"
#include "geometry/hitables/Hitable.hpp"

namespace srt::ds
{

class Scene
{
public:

	// CONSTRUCTORS

	Scene(const int32_t width, const int32_t height, const std::string &name,
		std::vector<std::shared_ptr<geometry::hitables::Hitable>>& objects,
		const float time0 = 0, const float time1 = 1);

	// METHODS

	const int32_t& getHeight() const	{ return m_height; };
	const int32_t& getWidth() const		{ return m_width; };
	const std::string& getName() const  { return m_name; };
	const bool intersect(const geometry::Ray& ray, const float tmin, const float tmax,
		geometry::hitables::Hitable::s_hit_record& hit_record) const;

private:

	const std::string m_name;
	const int32_t m_height;
	const int32_t m_width;
	const float m_time0;
	const float m_time1;
	ds::BVH m_hitablesTree;
	const std::vector<std::shared_ptr<geometry::hitables::Hitable>>& m_objects;
};

}