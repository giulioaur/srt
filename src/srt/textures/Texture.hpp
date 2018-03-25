/*******************************************************
 *                                                     *
 *  srt: Sushi RayTracer                               *
 *                                                     *
 *  TEXTURE HEADER FILE                                *
 *                                                     *
 *  Giulio Auriemma                                    *
 *                                                     *
 *******************************************************/
#ifndef S_TEXTURES_TEXTURE_S
#define S_TEXTURES_TEXTURE_S

// My includes.
#include "../geometry/Vec3.hpp"

namespace srt{
namespace textures{

/// This is the interface for the textures.
class Texture{
public:
    /**
     * @brief Returns an RGB value that represents the color of the texture in that point.
     * 
     * @param u - The x texture coord. Ranged from 0 to 1.
     * @param v - The y texture coord. Ranged from 0 to 1.
     * @param p - The point hit on the object.
     * @return geometry::Vec3 - The color of the texture.
     */
    virtual geometry::Vec3 value(const float u, const float v, const geometry::Vec3 &p) const = 0;
};

}
}


#endif