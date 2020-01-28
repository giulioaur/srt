#include "rendering/Camera.hpp"

#include "utility/Randomizer.hpp"

namespace srt::rendering
{

//Camera::Camera(const geometry::Vector4& lookFrom, const geometry::Vector4& lookAt, 
//	const geometry::Vector4& up, const float vfov, const float aspect, const float aperture, 
//	const float focusDist, const float t0, const float t1) :
//	origin(lookFrom), aperture(aperture / 2), t0(t0 > 0 ? t0 : 0), t1(t1 > t0 ? t1 : t0) 
//{
//	geometry::Vector4 w = (lookFrom - lookAt).normalize();
//	this->u = w.cross(up).normalize();
//	this->v = this->u.cross(w).normalize();
//	float theta = vfov * M_PI / 180.;
//	float half_height = tan(theta / 2);
//	float half_width = aspect * half_height;
//
//	this->lower_left_corner = this->origin - half_width * focusDist * this->u -
//		half_height * focusDist * this->v - w * focusDist;
//	this->horizontal = 2 * half_width * focusDist * this->u;
//	this->vertical = 2 * half_height * focusDist * this->v;
//}

Camera::Camera(const geometry::Vector4& lookFrom, const geometry::Vector4& horizontal, const geometry::Vector4& vertical,
    const geometry::Vector4& llc)
    : m_origin(lookFrom)
    , m_horizontal(horizontal)
    , m_vertical(vertical)
    , m_lower_left_corner(llc)
{

}

/**
 * @brief Returns the ray from the camera to the scene.
 *
 * @param s - The horizontal offset.
 * @param t - The vertical offset.
 * @return Ray - The ray from the camera to the scene.
 */
geometry::Ray Camera::getRay(const float s, const float t) const
{
	/*geometry::Vector4 start = this->aperture * utility::Randomizer::randomInUnitSphere();
	geometry::Vector4 offset = this->u * start.x() + this->v * start.y();
	float time = utility::Randomizer::randomRange(this->t0, this->t1);
	return { this->origin + offset, this->lower_left_corner + s * this->horizontal + t * this->vertical - origin - offset, time };*/
    return geometry::Ray{ m_origin, m_lower_left_corner + s * m_horizontal + t * m_vertical - m_origin };
}

/**
 * @brief Set the new camera time. If t0 is negative, it will not be changed.
 *        If t1 is less than t0, it will not be changed.
 *
 * @param t0 - The start time.
 * @param t1 - The end time.
 */
void Camera::setTime(const float t0, const float t1) 
{
	if (t0 >= 0)   this->m_t0 = t0;
	if (t1 >= 1)   this->m_t1 = t1;
}

}