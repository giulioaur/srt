#pragma once

#include "srt.h"

#include "geometry/Ray.hpp"
#include "geometry/Vector4.hpp"

namespace srt::rendering
{
	class Material;
}

namespace srt::geometry::hitables 
{

class Hitable 
{
public:
	// STRUCTURES

	/**
	 * @brief It stores the info about the collision with a ray.
	 *
	 */
	typedef struct hr {
		bool hit;
		float t;
		const Hitable* object;
		Vector4 point;
		Vector4 normal;
		std::shared_ptr<rendering::Material> material;

		hr() : hit(false), t(-1), object(nullptr), point(), normal() { };

		hr(bool h, float t, Hitable const *obj, const Vector4& point, const Vector4& normal, 
			const std::shared_ptr<rendering::Material> material) 
			: hit(h), t(t), object(obj), point(point), normal(normal), material(material) {}

		struct hr& operator=(struct hr&& rhs)
		{
			hit = rhs.hit;
			t = rhs.t;
			object = rhs.object;
			point = std::move(rhs.point);
			normal = std::move(rhs.normal);
			material = std::move(rhs.material);
			return *this;
		}
	} s_hit_record;

	// The record for no hit situation.
	static const s_hit_record NO_HIT;
	//static const std::shared_ptr<materials::Material> NO_MATERIAL;

public:

	/**
	 * @brief Computes the intersection between the emitted ray and the hitable object.
	 *
	 * @param ray - The ray.
	 * @param tmin - The min t to consider.
	 * @param tmax - The max t to consider.
	 * @return Hitable::s_hit_record - The record that stores hit info.
	 */
	virtual bool intersection(const Ray &ray, const float tmin, const float tmax, 
		s_hit_record& hit_record) const = 0;

	///**
	//	* @brief Get the Material of the object.
	//	*
	//	* @return const Material& - The material of the object.
	//	*/
	//virtual const std::shared_ptr<materials::Material> &getMaterial() const {
	//	return NO_MATERIAL;
	//}

	///**
	//	* @brief Returns the axis aligned bounded box boxes.
	//	*
	//	* @param t0 - The first instant of time to consider.
	//	* @param t1 - The last instant of time to consider.
	//	* @return std::unique_ptr<geometry::AABB> The axis aligned bounded box that surrounds the object.
	//	*/
	//virtual std::unique_ptr<geometry::AABB> getAABB(const float t0, const float t1) const = 0;

	/**
	 * @brief Get the Texture Coords of the object  in a given point.
	 *
	 * @param p - The hit point on the object.
	 * @return Vector4 - The texture coords.
	 */
	virtual Vector4 getTextureCoords(const Vector4& p) const 
	{
		return p;
	}
};

}