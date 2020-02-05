/*******************************************************
 *                                                     *
 *  srt: Sushi RayTracer                               *
 *                                                     *
 *  AABB HEADER FILE                                   *
 *                                                     *
 *  Giulio Auriemma                                    *
 *                                                     *
 *******************************************************/
#pragma once

#include <array>

#include "Vector4.hpp"
#include "Ray.hpp"

namespace srt::geometry 
{

/// This class represents a axis aligned bounding box. It is used to make faster
/// the computation of the ray-shape intersection. 
/// It is build using the upper left corner and lower right corner that represent
/// respectively the intersection of the planes with the greater x, y, z and the 
/// intersection of the ones with the lower x, y, z. 
/// NB: since we are considering axis aligned planes, one coordinate is sufficient.
class AABB 
{
public:

    AABB();
    AABB(const Vector4& min, const Vector4& max);
    AABB(Vector4&& min, Vector4&& max);

    const Vector4& getMin() const noexcept { return m_min; };
	const Vector4& getMax() const noexcept { return m_max; };
	Vector4 getSize() const noexcept { return m_max - m_min; };

    bool intersect(const Ray& ray, float tmin, float tmax) const;

    /**
     * @brief Returns the box containing the current aabb and the passed one.
     *
     * @param box - The other box to contain.
     * @return AABB - The aabb containing the two boxes.
     */
	AABB getSurroundingBox(const AABB& box) const;

	bool collide(const AABB& box) const;
	std::array<float, 2> getCollisionPoints(const Ray& ray, float tmin, float tmax) const;

private:

    Vector4 m_min;
    Vector4 m_max;
};
}
