#pragma once

#include "geometry/hitables/Hitable.hpp"

#include <memory>
#include <string>
#include <vector>

namespace srt::ds
{

class Scene
{
public:

	// CONSTRUCTORS

	Scene(const int32_t width, const int32_t height, const std::string &name,
		const float t0 = 0, const float t1 = 1);

	// METHODS

	const int32_t& getHeight() const	{ return m_height; };
	const int32_t& getWidth() const		{ return m_width; };
	const std::string& getName() const	{ return m_name; }
	//const size_t &getHierarchyDepth() const;
	//void buildBVH();
	void addHitables(const std::vector<std::shared_ptr<geometry::hitables::Hitable>> &newHitables);
	const bool intersection(const geometry::Ray& ray, const float tmin, const float tmax,
		geometry::hitables::Hitable::s_hit_record& hitRecord) const;

private:

	const std::string m_name;
	const int32_t m_height;
	const int32_t m_width;
	const float m_t0;
	const float m_t1;
	//ds::BVH hitablesTree;
	std::vector<std::shared_ptr<geometry::hitables::Hitable>> m_hitables;
};

}