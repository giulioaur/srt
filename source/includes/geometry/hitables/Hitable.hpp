#pragma once

#include "srt.h"

#include <array>

#include "geometry/AABB.hpp"
#include "geometry/Ray.hpp"
#include "geometry/Vector4.hpp"

namespace srt::rendering
{
	class Material;
}

namespace srt::geometry::hitables 
{

using TextureCoords = std::array<float, 2>;

class Hitable 
{
public:
	// STRUCTURES

	/**
	 * @brief It stores the info about the collision with a ray.
	 *
	 */
	typedef struct hr {
		bool hit = false;
		float t = FLOAT_MAX;
		const Hitable* object = nullptr;
		Vector4 point;
		Vector4 normal;
		std::shared_ptr<rendering::Material> material = nullptr;
		TextureCoords textureCoords;
	} s_hit_record;

	// The record for no hit situation.
	static const s_hit_record NO_HIT;

public:

	/**
	 * @brief Computes the intersection between the emitted ray and the hitable object.
	 *
	 * @param ray - The ray.
	 * @param tmin - The min t to consider.
	 * @param tmax - The max t to consider.
	 * @return Hitable::s_hit_record - The record that stores hit info.
	 */
	virtual bool intersect(const Ray &ray, const float tmin, const float tmax, 
		s_hit_record& hit_record) const = 0;

	/**
	 * @brief Returns the axis aligned bounded box boxes.
	 *
	 * @param t0 - The first instant of time to consider.
	 * @param t1 - The last instant of time to consider.
	 * @return std::unique_ptr<geometry::AABB> The axis aligned bounded box that surrounds the object.
	 */
	virtual const geometry::AABB getAABB(const float t0, const float t1) const noexcept = 0;
};

}