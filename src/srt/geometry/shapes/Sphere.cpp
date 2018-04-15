/*******************************************************
 *                                                     *
 *  srt: Sushi RayTracer                               *
 *                                                     *
 *  SPHERE CLASS FILE                                  *
 *                                                     *
 *  Giulio Auriemma                                    *
 *                                                     *
 *******************************************************/
#include "Sphere.hpp"

// System includes.
#include <cmath>

using namespace std;
using namespace srt::geometry;
using namespace srt::materials;

namespace srt{
namespace geometry{
namespace shapes{

    /**
     * @brief Creates a new sphere.
     * 
     * @param center - The center of the sphere.
     * @param radius - The radius of the sphere.
     * @param plane - The normal vector of the plane containing the sphere
     * @param color - The color of the sphere.
     */
    Sphere::Sphere(const Vec3 &center, const float radius, const shared_ptr<Material> material) : 
        center(center), radius(radius), material(material) { }
    
    /**
     * @brief Sphere equality.
     * 
     */
    bool Sphere::operator == (const Hitable &hitable) const{
        if(const Sphere *sphere = dynamic_cast<Sphere const*>(&hitable))
            return this->center == sphere->center && this->radius == sphere->radius;
        return false;
    }

    /**
     * @brief Sphere inequality.
     * 
     */
    bool Sphere::operator != (const Hitable &hitable) const{
        if(const Sphere *sphere = dynamic_cast<Sphere const*>(&hitable))
            return this->center != sphere->center || this->radius != sphere->radius;
        return false;
    }

    /**
     * @brief Returns the ray of the sphere.
     * 
     * @return float - The ray.
     */
    float Sphere::getRay() const{
        return this->radius;
    }
    
    /**
     * @brief Returns the center of the sphere.
     * 
     * @return float - The center of the sphere.
     */
    const Vec3& Sphere::getCenter() const{
        return this->center;
    }

    /**
     * @brief Returns the distance t in which a ray eventually intersect the sphere. 
     *        If the ray does not intersect the sphere, it returns -1
     * 
     * @param ray - The ray.
     * @param tmin - The lower t to consider.
     * @param tmax - The greater t to consider.
     * @return float - The distance from the ray origin, -1 if there is no intersection.
     */
    Hitable::hit_record Sphere::intersection(const Ray &ray, const float tmin, const float tmax) const{
        const Vec3 dist = ray.getOrigin() - this->center;
        const float a = ray.getDirection() ^ 2;
        const float b = 2. * (ray.getDirection() * dist);
        const float c = (dist ^ 2) - this->radius * this->radius;
        const float delta = b * b - 4 * a * c;
        float t = -1;

        // If the solution is only one, use it to return the point, else return the positive one.
        // if(delta == 0)  t = -0.5 * b / a;
        if(delta > 0){
            const float q = b < 0 ? -0.5 * (b - sqrt(delta)) : -0.5 * (b + sqrt(delta));
            const float t0 = q / a, t1 = c / q;
            if(t0 > 0 && t1 > 0)        t = min(t0, t1);
            else                        t = max(t0, t1);
        }

        if(t >= tmin && t <= tmax)  return {true, t, this, ray.getPoint(t), this->getNormal(ray.getPoint(t))}; 
        return Hitable::NO_HIT; 
    }

    /**
     * @brief Returns the normal to the circle of a given point.
     * 
     * @param pos - The position on which compute the normal.
     * @return srt::geometry::Vec3 getNormal - The normal to the circle at given point. 
     */
    Vec3 Sphere::getNormal(const Vec3 &pos) const{
        return (pos - this->center) / this->radius;
    }

    /**
     * @brief Returns the material of the sphere.
     * 
     * @return const Material& - The material of the spheres.
     */
    const std::shared_ptr<materials::Material>& Sphere::getMaterial() const{
        return this->material;
    }

    /**
     * @brief Returns the surrounding axis aligned bounding box. 
     * 
     * @return std::unique_ptr<geometry::AABB> The surrounding axis aligned boundig box, nullptr
     *                                          if it does not exist.
     */
    std::unique_ptr<geometry::AABB> Sphere::getAABB(const float t0, const float t1) const{
        return make_unique<AABB>(this->center - Vec3{radius}, this->center + Vec3{radius});
    }
    
    /**
     * @brief Returns the u/v coords of a texture sphere in a given point.
     * 
     * @param p - The point hit in the sphere.
     * @return geometry::Vec3 - The vector in which x = u, y = v and z = 0.
     */
    Vec3 Sphere::getTextureCoords(const Vec3 &p) const{
        // Compute the phi and theta angle.
        float phi = atan2(p.z(), p.x()), theta = asin(p.y());
        // Compute the u and v coords.
        float u = 1 - (phi + M_PI) / (2 * M_PI),
              v = (theta + M_PI / 2) / M_PI;

        return{u, v, 0};
    }
}
}
}