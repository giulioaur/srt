/*******************************************************
 *                                                     *
 *  srt: Sushi RayTracer                               *
 *                                                     *
 *  PLANE HEADER FILE                                  *
 *                                                     *
 *  Giulio Auriemma                                    *
 *                                                     *
 *******************************************************/
#include "Plane.hpp"

// System includes
#include <cmath>

using namespace std;

namespace srt{
namespace geometry{
    /**
     * @brief Creates a new plane containing a point P and orthogonal to a vector n.
     * 
     * @param norm - The orthogonal vector.
     * @param point - The inside point.
     */
    Plane::Plane(const Vec3 &norm, const Vec3 &point) : normal((Vec3{norm}).normalize()), point(point) {}

    /**
     * @brief Creates a new plane with the same normal and containing the same points of an old one.
     * 
     * @param old - The old planes.
     */
    Plane::Plane(const Plane &old) : normal(old.normal), point(old.point) {}

    /**
     * @brief Returns the normal of the plane.
     * 
     * @return const Vec3& - The normal of the plane.
     */
    const Vec3& Plane::getNormal() const{
        return this->normal;
    }

    /**
     * @brief Returns the point in which a ray intersect the plane containg the circle. If no intersection is
     *        found, nullptr is returned.
     * 
     * @param ray - The ray.
     * @return Vec3 - The intersection point.
     */
    float Plane::intersect(const Ray &ray, const float tmin, const float tmax) const{
        const float angle = this->normal * ray.getDirection();
        if(std::abs(angle) > 1e-5){
            const float t = ((this->point - ray.getOrigin()) * this->normal) / angle;
            if (t >= tmin && t <= tmax) return t;
        }
        return -1;
    }

    /**
     * @brief Returns true if a point lies on the plane, false otherwise.
     * 
     * @param point - The point.
     * @return true - If the point lies on the plane.
     * @return false - If the point does not lie on the plane.
     */
    bool Plane::contain(const Vec3 &point) const{
        return (point - this->point) * normal < 1e-14 ? true : false;
    }
}
}