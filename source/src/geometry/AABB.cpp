/*******************************************************
 *                                                     *
 *  srt: Sushi RayTracer                               *
 *                                                     *
 *  AABB CLASS FILE                                    *
 *                                                     *
 *  Giulio Auriemma                                    *
 *                                                     *
 *******************************************************/
#include "geometry/AABB.hpp"

#include <algorithm>

namespace srt::geometry 
{

AABB::AABB() 
    : m_min(Vector4{ 0, 0, 0, 0 })
    , m_max(Vector4{ 0, 0, 0, 0 }) 
{
}

AABB::AABB(const Vector4& min, const Vector4& max) 
    : m_min(min)
    , m_max(max) 
{
}

AABB::AABB(Vector4&& min, Vector4&& max)
    : m_min(min)
    , m_max(max)
{
}

bool AABB::intersect(const Ray& ray, float tmin, float tmax) const 
{
    const Vector4 invD = ray.getInvD();
    for (uint8_t i = 0; i < 3; ++i)
    {
        // Compute intersection point.
        float t0 = (m_min[i] - ray.getOrigin()[i]) * invD[i];
        float t1 = (m_max[i] - ray.getOrigin()[i]) * invD[i];

        if (invD[i] < 0)
        {
            srt::swap(t0, t1);
        }

        // Compute the greater min and lower max.
        tmin = t0 > tmin ? t0 : tmin;
        tmax = t1 < tmax ? t1 : tmax;

        // Return false if the intervals does not intersect.
        if (tmax <= tmin)    return false;
    }

    return true;
}

AABB AABB::getSurroundingBox(const AABB& box) const 
{
    Vector4 lrc{ std::min(m_min.x(), box.m_min.x()),
                 std::min(m_min.y(), box.m_min.y()),
                 std::min(m_min.z(), box.m_min.z()),
                 0 };
    Vector4 ulc{ std::max(m_max.x(), box.m_max.x()),
                 std::max(m_max.y(), box.m_max.y()),
                 std::max(m_max.z(), box.m_max.z()),
                 0 };
    return AABB{ lrc, ulc };
}

bool AABB::collide(const AABB& box) const
{
	// Two boxes collides only if all the three (min -> max) intervals overlap.
	// This way we check the sign of the multiplication between the two max - min differences.
	// If all of them have negative sign ( less than / greater than proportion are not respected)
	// or zero (they have the same coordinate) then all three axes overlap).
	const Vector4 diff = (m_min - box.getMin()).mul(m_max - box.getMax());

	return diff[0] <= 0 && diff[1] <= 0 && diff[2] <= 0;
}

std::array<float, 2> AABB::getCollisionPoints(const Ray& ray, float tmin, float tmax) const
{
	float currMin = tmin, currMax = tmax;
	for (uint8_t i = 0; i < 3; ++i)
	{
		// Compute intersection point.
		const float invD = 1 / ray.getDirection()[i];
		float t0 = (m_min[i] - ray.getOrigin()[i]) * invD;
		float t1 = (m_max[i] - ray.getOrigin()[i]) * invD;

		if (invD < 0)
		{
			srt::swap(t0, t1);
		}

		// Compute the greater min and lower max.
		currMin = t0 > currMin ? t0 : currMin;
		currMax = t1 < currMax ? t1 : currMax;

		// Return false if the intervals does not intersect.
		if (currMax <= currMin)    return { -1, -1 };
	}

	return { tmin, tmax };
}

}