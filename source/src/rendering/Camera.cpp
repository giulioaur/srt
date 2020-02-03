#include "rendering/Camera.hpp"

#include "utility/Randomizer.hpp"

namespace srt::rendering
{

Camera::Camera(const geometry::Vector4& lookFrom, const geometry::Vector4& lookAt, 
	const geometry::Vector4& up, const float vfov, const float aspect, const float aperture, 
	const float focusDist, const float t0, const float t1) 
	: m_origin(lookFrom)
	, m_aperture(aperture / 2)
	, m_t0(t0 > 0 ? t0 : 0)
	, m_t1(t1 > t0 ? t1 : t0)
{
	geometry::Vector4 w = (lookFrom - lookAt).normalize();
	m_u = w.cross(up).normalize();
	m_v = m_u.cross(w).normalize();
	float theta = vfov * M_PI / 180.f;
	float half_height = tan(theta / 2);
	float half_width = aspect * half_height;

	m_lower_left_corner = m_origin - half_width * focusDist * m_u -
		half_height * focusDist * m_v - w * focusDist;
	m_horizontal = 2 * half_width * focusDist * m_u;
	m_vertical = 2 * half_height * focusDist * m_v;
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
	geometry::Vector4 start = m_aperture * utility::Randomizer::randomInUnitSphere();
	geometry::Vector4 offset = m_u * start.x() + m_v * start.y();
	float time = utility::Randomizer::randomRange(m_t0, m_t1);
	return { m_origin + offset, m_lower_left_corner + s * m_horizontal + t * m_vertical - m_origin - offset, time };
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
	if (t0 >= 0)   m_t0 = t0;
	if (t1 >= 1)   m_t1 = t1;
}

}