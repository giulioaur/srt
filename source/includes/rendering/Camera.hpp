#pragma once

#include "geometry/Ray.hpp"
#include "geometry/Vector4.hpp"

namespace srt::rendering
{

/// This class represents the camera from which see the scene.
class Camera 
{
public:

	/**
	 * @brief Builds a camera.
	 *
	 * @param lookFrom - The origin of the camera.
	 * @param lookAt - The point the camera is pointing.
	 * @param up - The world up vector.
	 * @param vfov - The focal distance.
	 * @param aspect - The aspect ratio (width / height).
	 * @param aperture - The lens ray from which shot the ray.
	 * @param focusDist - The distance of the focus.
	 * @param t0 - The time the camera starts to "record". It must be greater than 0, otherwise it will be set to 0.
	 * @parma t1 - The time the camera stops to "record". It must be greater than t1, otherwise it will be set to t1.
	 */
	Camera(const geometry::Vector4 &lookFrom, const geometry::Vector4 &lookAt, const geometry::Vector4 &up,
		const float vfov, const float aspect, const float aperture, const float focusDist,
		const float t0 = 0, const float t1 = 0);

	/**
	 * @brief Returns the ray from the camera to the scene.
	 *
	 * @param s - The horizontal offset.
	 * @param t - The vertical offset.
	 * @return Ray - The ray from the camera to the scene.
	 */
	geometry::Ray getRay(const float u, const float v) const;

	/**
	 * @brief Set the new camera time. If t0 is negative, it will not be changed.
	 *        If t1 is less than t0, it will not be changed.
	 *
	 * @param t0 - The start time.
	 * @param t1 - The end time.
	 */
	void setTime(const float t0, const float t1);


private: 

	geometry::Vector4 origin;
	geometry::Vector4 lower_left_corner;
	geometry::Vector4 horizontal;
	geometry::Vector4 vertical;
	geometry::Vector4 u; 
	geometry::Vector4 v;
	float aperture;
	float t0;
	float t1;
};

}