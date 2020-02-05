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
	Ray(const Vector4& origin, const Vector4& direction, const float time = 1) 
		: m_origin(origin)
		, m_direction(direction.normalize())
		, m_time(time)
		, m_invD({ 1/ direction[0], 1 / direction[1], 1 / direction[2], 0}) {}

	/**
	 * @brief Creates a new ray equal to an old one.
	 *
	 * @param old - The old ray.
	 */
	Ray(const Ray &old) 
		: m_origin(old.m_origin)
		, m_direction(old.m_direction)
		, m_invD(old.m_invD)
		, m_time(old.m_time){}

	const Vector4& getOrigin() const { return this->m_origin;	}
	const Vector4& getDirection() const { return this->m_direction; }
	const Vector4& getInvD() const { return this->m_invD; }
	float getTime() const { return this->m_time;	}

	/**
	 * @brief Gets the point of the vector at distance d.
	 *
	 * @param distance - The distance of the point from the origin.
	 * @return geometry::Vector4 getPosition - The position of the point at distance d.
	 */
	INLINE Vector4 getPoint(const float distance) const;


	Ray operator=(const Ray& rhs) noexcept;
	Ray operator=(Ray&& rhs) noexcept;

private:

	Vector4 m_origin;
	Vector4 m_direction;
	Vector4 m_invD;			// Used with AABB collisions.
	float m_time;

public:

	friend void swap(Ray& a, Ray& b)
	{
		srt::swap(a.m_origin, b.m_origin);
		srt::swap(a.m_direction, b.m_direction);
		srt::swap(a.m_invD, b.m_invD);
		srt::swap(a.m_time, b.m_time);
	}

};


INLINE Vector4 Ray::getPoint(const float distance) const
{
	return m_origin + (m_direction * distance);
}

INLINE Ray Ray::operator=(const Ray& rhs) noexcept
{
	Ray ray{ rhs };
	srt::swap(*this, ray);
	return *this;
}

INLINE Ray Ray::operator=(Ray&& rhs) noexcept
{
	srt::swap(*this, rhs);
	return *this;
}

}