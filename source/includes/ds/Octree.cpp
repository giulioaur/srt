#include "Octree.hpp"


namespace srt::ds
{

std::array<geometry::AABB, 8> split(const geometry::AABB& box)
{
	const geometry::Vector4 min = box.getMin();
	const geometry::Vector4 max = box.getMax();
	const geometry::Vector4 center = min + box.getSize() / 2;

	return {
		// LEFT - BOTTOM - FRONT
		geometry::AABB{ min, center },
		// RIGHT - BOTTOM - FRONT
		geometry::AABB{ {center[0], min[1],    min[2],    0}, {max[0],    center[1], center[2], 0} },
		// LEFT - UPPER - FRONT						      
		geometry::AABB{ {min[0],    center[1], min[2],    0}, {center[0], max[1],    center[2], 0} },
		// RIGHT - UPPER - FRONT					      
		geometry::AABB{ {center[0], center[1], min[2],    0}, {max[0],    max[1],    center[2], 0} },
		// LEFT - BOTTOM - BACK
		geometry::AABB{ {min[0],    min[1],    center[2], 0}, {center[0], center[1], max[2],    0} },
		// RIGHT - BOTTOM - BACK
		geometry::AABB{ {center[0], min[1],    center[2], 0}, {max[0],    center[1], max[2],    0} },
		// LEFT - UPPER - BACK
		geometry::AABB{ {min[0],    center[1], center[2], 0}, {center[0], max[1],    max[2],    0} },
		// RIGHT - UPPER - BACK
		geometry::AABB{center, max }
	};
}


Octree::s_node::s_node(const std::vector<std::shared_ptr<geometry::hitables::Hitable>>& objects,
	geometry::AABB&& box, const size_t minLeafObjs, const float minCubeSize, const float t0, const float t1)
	: box(box)
	, isLeaf(false)
{
	// Be sure the child can be further divided, if not this become a leaf node.
	if (objects.size() > minLeafObjs)
	{
		std::array<geometry::AABB, 8> childBoxes = split(box);

		for (size_t i = 0; i < 8; ++i)
		{
			std::vector<std::shared_ptr<geometry::hitables::Hitable>> containedObj;
			containedObj.reserve(objects.size());

			// Find the objects contained by each child and construct the child with them.
			std::copy_if(objects.begin(), objects.end(), std::back_inserter(containedObj), 
				[&currentBox = childBoxes[i], t0, t1](const std::shared_ptr<geometry::hitables::Hitable>& obj) {
					return currentBox.collide(obj->getAABB(t0, t1)); 
				}
			);

			children[i] = s_node{ containedObj, std::move(childBoxes[i]), minLeafObjs, minCubeSize, t0, t1 };
		}
	}
	else
	{
		containedObjs = objects;
		isLeaf = true;
	}
}

bool Octree::s_node::hit(const geometry::Ray& ray, const float tmin, const float tmax, 
	geometry::hitables::Hitable::s_hit_record& hit_record, float& outT) const
{
	if (isLeaf)
	{
		// If an object inside is hit, stop the search, otherwise return exit point.
		if (hitContent(ray, tmin, tmax, hit_record))
		{
			return true;
		}

		const auto collisionPoints = box.getCollisionPoints(ray, tmin, tmax);
		outT = collisionPoints[1];
		return false;
	}
	else
	{
		// Check if the origin is contained in a child?

	}

	return hit_record.hit;
}

bool Octree::s_node::hitContent(const geometry::Ray& ray, const float tmin, const float tmax,
	geometry::hitables::Hitable::s_hit_record& hit_record) const
{
	// Check all the contained object the first hit.
	hit_record.t = tmin;
	hit_record.hit = false;

	for (const auto obj : containedObjs)
	{
		obj->intersect(ray, hit_record.t, tmax, hit_record);
	}

	return hit_record.hit;
}

Octree::Octree(const std::vector<std::shared_ptr<geometry::hitables::Hitable>>& objects, 
	const size_t minLeafObjs, const float minCubeSize, const float t0, const float t1)
	: m_root(objects, getContainerBox(objects, t0, t1), minLeafObjs, minCubeSize, t0, t1)
{

}

geometry::AABB Octree::getContainerBox(
	const std::vector<std::shared_ptr<geometry::hitables::Hitable>>& objects, const float t0, const float t1)
{
	geometry::AABB container{};

	for (const auto hitable : objects)
	{
		container = hitable->getAABB(t0, t1).getSurroundingBox(container);
	}

	// Create a square container that is a power of two?

	return container;
}

bool Octree::intersect(const geometry::Ray& ray, const float tmin, const float tmax, 
	geometry::hitables::Hitable::s_hit_record& hit_record) const
{
	return m_root.hit(ray, tmin, tmax, hit_record);
}

}

