/*******************************************************
 *                                                     *
 *  srt: Sushi RayTracer                               *
 *                                                     *
 *  MOVING SPHERE CLASS FILE                           *
 *                                                     *
 *  Giulio Auriemma                                    *
 *                                                     *
 *******************************************************/
#include "MovingSphere.hpp"

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
     * @param ray - The ray of the sphere.
     * @param plane - The normal vector of the plane containing the sphere
     * @param color - The color of the sphere.
     */
    MovingSphere::MovingSphere(const Vec3 &c0, const Vec3 &c1, const float t0, const float t1, 
        const float ray, const shared_ptr<Material> material) : Sphere({0, 0, 0}, ray, material),
        c0(c0), c1(c1), t0(t0), t1(t1) { }

    /**
     * @brief Creates a new sphere with the same center and ray of an old one.
     * 
     * @param old - The old sphere.
     */
    MovingSphere::MovingSphere(const MovingSphere &old) : Sphere(old), c0(old.c0), c1(old.c1),
        t0(old.t0), t1(old.t1) { }

    /**
     * @brief Returns the distance t in which a ray eventually intersect the sphere. 
     *        If the ray does not intersect the sphere, it returns -1
     * 
     * @param ray - The ray.
     * @param tmin - The lower t to consider.
     * @param tmax - The greater t to consider.
     * @return float - The distance from the ray origin, -1 if there is no intersection.
     */
    Hitable::hit_record MovingSphere::intersection(const Ray &ray, const float tmin, const float tmax) const{
        Vec3 currCenter = this->c0 + ((ray.getTime() - this->t0) / (this->t1 - this->t0)) * (this->c1 - this->c0);
        float currRay = this->getRay();
        const Vec3 dist = ray.getOrigin() - currCenter;
        const float a = ray.getDirection() ^ 2;
        const float b = 2. * (ray.getDirection() * dist);
        const float c = (dist ^ 2) - currRay * currRay;
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

        if(t >= tmin && t <= tmax)  return {true, t, this};
        return {false, -1, nullptr}; 
    }

    /**
     * @brief Returns the box that contains all the space that the sphere cover from t0 to t1.
     * 
     * @param t0 - The first time instant.
     * @param t1 - The last time instant.
     * @return std::unique_ptr<geometry::AABB> - The AABB.
     */
    std::unique_ptr<geometry::AABB> MovingSphere::getAABB(const float t0, const float t1) const{
        const Vec3 radVec{this->getRay(), this->getRay(), this->getRay()};
        AABB aabb0{this->c0 - radVec, this->c0 + radVec}, 
             aabb1{this->c1 - radVec, this->c1 + radVec};

        return make_unique<AABB>(aabb0.surroundingBox(aabb1));
    }
}
}
}