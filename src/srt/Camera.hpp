/*******************************************************
 *                                                     *
 *  srt: Sushi RayTracer                               *
 *                                                     *
 *  CAMERA HEADER FILE                                 *
 *                                                     *
 *  Giulio Auriemma                                    *
 *                                                     *
 *******************************************************/
#ifndef S_CAMERA_S
#define S_CAMERA_S

// My includes.
#include "geometry/Vec3.hpp"
#include "Ray.hpp"

namespace srt{

/// This class represents the camera from which see the scene.
class Camera{
private:
    // ATTRIBUTES

    geometry::Vec3 origin, lower_left_corner, horizontal, vertical, u, v;
    float aperture, t0, t1;
public:
    // CONSTRUCTORS

    Camera(const geometry::Vec3 &lookFrom, const geometry::Vec3 &lookAt, const geometry::Vec3 &up, 
            const float vfov, const float aspect, const float aperture, const float focusDist, 
            const float t0 = 0, const float t1 = 0);

    // METHODS

    Ray get_ray(const float u, const float v);
    void setTime(const float t0, const float t1);
};

}

#endif