#pragma once

#include <string>

namespace srt::ds
{

class Scene
{
public:

	// CONSTRUCTORS

	Scene(const float width, const float height, const std::string &name,
		const float t0 = 0, const float t1 = 1);

	// METHODS

	const float& getHeight() const { return height; };
	const float& getWidth() const { return width; };
	const std::string& getName() const { return name; }
	//const size_t &getHierarchyDepth() const;
	//void buildBVH();
	//void addHitables(const std::vector<std::shared_ptr<Hitable>> &newHitables);
	//const Hitable::hit_record intersection(const Ray &ray, const float tmin, const float tmax) const;

private:

	const std::string name;
	const float height;
	const float width;
	const float t0;
	const float t1;
	//ds::BVH hitablesTree;
	//std::vector<std::shared_ptr<Hitable>> hitables = {};
};

}