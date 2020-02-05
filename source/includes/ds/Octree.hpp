#pragma once

#include <array>
#include <memory>
#include <vector>

#include "geometry/hitables/Hitable.hpp"

namespace srt::ds
{

class Octree
{
private:

	struct s_node
	{
		const geometry::AABB box;
		std::array<s_node, 8> children;
		std::vector<std::shared_ptr<geometry::hitables::Hitable>> containedObjs;
		bool isLeaf;
	
		s_node(const std::vector<std::shared_ptr<geometry::hitables::Hitable>>& objects,
			geometry::AABB&& box, const size_t minLeafObjs, const float minCubeSize, 
			const float t0, const float t1);

		bool hit(const geometry::Ray& ray, const float tmin, const float tmax,
			geometry::hitables::Hitable::s_hit_record& hit_record, float& outT) const;

		bool hitContent(const geometry::Ray& ray, const float tmin, const float tmax,
			geometry::hitables::Hitable::s_hit_record& hit_record) const;
	};


public:

	Octree(const std::vector<std::shared_ptr<geometry::hitables::Hitable>>& objects,
		const size_t minLeafObjs, const float minCubeSize, const float t0, const float t1);

	bool intersect(const geometry::Ray& ray, const float tmin, const float tmax,
		geometry::hitables::Hitable::s_hit_record& hit_record) const;

private:

	geometry::AABB getContainerBox(const std::vector<std::shared_ptr<geometry::hitables::Hitable>>& objects,
		const float t0, const float t1);

	const s_node m_root;

};

}