#include "geometry/hitables/Sphere.hpp"

#include <algorithm>

namespace srt::geometry::hitables
{

Sphere::Sphere(const Vector4& center, const float radius/*, const shared_ptr<Material> material*/) :
    center(center), radius(radius)/*, material(material)*/ { }

    
bool Sphere::operator == (const Hitable& hitable) const {
    if (const Sphere* sphere = dynamic_cast<Sphere const*>(&hitable))
        return this->center == sphere->center && this->radius == sphere->radius;
    return false;
}

bool Sphere::operator != (const Hitable& hitable) const {
    if (const Sphere* sphere = dynamic_cast<Sphere const*>(&hitable))
        return this->center != sphere->center || this->radius != sphere->radius;
    return false;
}

bool Sphere::intersection(const Ray& ray, const float tmin, const float tmax,
    Hitable::s_hit_record& hit_record) const 
{
    const Vector4 dist = ray.getOrigin() - this->center;
    const float a = ray.getDirection().squaredMagnitude();
    const float b = 2. * (ray.getDirection() * dist);
    const float c = dist.squaredMagnitude() - this->radius * this->radius;
    const float delta = b * b - 4 * a * c;
    float t = -1;

    // If the solution is only one, use it to return the point, else return the positive one.
    // if(delta == 0)  t = -0.5 * b / a;
    if (delta > 0) {
        const float q = b < 0 ? -0.5f * (b - sqrt(delta)) : -0.5f * (b + sqrt(delta));
        const float t0 = q / a, t1 = c / q;
        if (t0 > 0 && t1 > 0)        t = std::min(t0, t1);
        else                         t = std::max(t0, t1);
    }

    if (t >= tmin && t <= tmax)
    {
        hit_record = { true, t, this, ray.getPoint(t), this->getNormal(ray.getPoint(t)) };
        return true;
    }
    return false;
}

/**
    * @brief Returns the normal to the circle of a given point.
    *
    * @param pos - The position on which compute the normal.
    * @return srt::geometry::Vector4 getNormal - The normal to the circle at given point.
    */
Vector4 Sphere::getNormal(const Vector4& pos) const {
    return (pos - this->center) / this->radius;
}

///**
//    * @brief Returns the material of the sphere.
//    *
//    * @return const Material& - The material of the spheres.
//    */
//const std::shared_ptr<materials::Material>& Sphere::getMaterial() const {
//    return this->material;
//}

///**
//    * @brief Returns the surrounding axis aligned bounding box.
//    *
//    * @return std::unique_ptr<geometry::AABB> The surrounding axis aligned boundig box, nullptr
//    *                                          if it does not exist.
//    */
//std::unique_ptr<geometry::AABB> Sphere::getAABB(const float t0, const float t1) const {
//    return make_unique<AABB>(this->center - Vector4{ radius }, this->center + Vector4{ radius });
//}

///**
//    * @brief Returns the u/v coords of a texture sphere in a given point.
//    *
//    * @param p - The point hit in the sphere.
//    * @return geometry::Vector4 - The vector in which x = u, y = v and z = 0.
//    */
//Vector4 Sphere::getTextureCoords(const Vector4& p) const {
//    // Compute the phi and theta angle.
//    float phi = atan2(p.z(), p.x()), theta = asin(p.y());
//    // Compute the u and v coords.
//    float u = 1 - (phi + M_PI) / (2 * M_PI),
//        v = (theta + M_PI / 2) / M_PI;

//    return{ u, v, 0 };
//}

}