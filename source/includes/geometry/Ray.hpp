#pragma once

#include "srt.h"

#include <memory>

#include "geometry/Vector4.hpp"

namespace srt::geometry 
{

class Ray 
{

public:
	/**
	 * @brief Creates a new ray.
	 *
	 * @param o - The origin of the ray.
	 * @param dir - The direction of the ray.
	 * @param time - The time the ray is shot.
	 */
	Ray(const Vector4& origin, const Vector4& direction, const float time = 1) : origin(origin),
		direction(direction.normalize()), time(time) {}

	/**
	 * @brief Creates a new ray equal to an old one.
	 *
	 * @param old - The old ray.
	 */
	Ray(const Ray &old) : origin(old.origin), direction(old.direction), time(old.time) {}

	/**
	 * @brief Returns a copy of the vector that indicates the origin of the ray.
	 *
	 * @return geometry::Vector4 - The origin of the ray.
	 */
	INLINE const geometry::Vector4& getOrigin() const 
	{
		return this->origin;
	}

	/**
	 * @brief Returns a copy of the vector that indicates the direction of the ray.
	 *
	 * @return unique_ptr<Vector4> - The direction of the ray.
	 */
	INLINE const geometry::Vector4& getDirection() const 
	{
		return this->direction;
	}

	/**
	 * @brief Returns the time on which the ray was shot.
	 *
	 * @return float - The time the ray was shot.
	 */
	INLINE float getTime() const 
	{
		return this->time;
	}

	/**
	 * @brief Gets the point of the vector at distance d.
	 *
	 * @param distance - The distance of the point from the origin.
	 * @return geometry::Vector4 getPosition - The position of the point at distance d.
	 */
	INLINE geometry::Vector4 getPoint(const float distance) const 
	{
		return this->origin + (this->direction * distance);
	}


private:

	// ATTRIBUTES
	const Vector4 origin;
	const Vector4 direction;

	float time;

};
}