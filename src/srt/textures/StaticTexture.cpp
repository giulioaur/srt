/*******************************************************
 *                                                     *
 *  srt: Sushi RayTracer                               *
 *                                                     *
 *  STATIC TEXTURE CLASS FILE                          *
 *                                                     *
 *  Giulio Auriemma                                    *
 *                                                     *
 *******************************************************/
#include "StaticTexture.hpp"

namespace srt{
namespace textures{

    /**
     * @brief Constructs a new black Static Texture.
     * 
     */
    StaticTexture::StaticTexture() : color(geometry::Vec3{0, 0, 0}) {} 

    /**
     * @brief Constructs a new Static Texture object.
     * 
     * @param color - The color of the whole texture.
     */
    StaticTexture::StaticTexture(const geometry::Vec3 &color) : color(color) {} 

    /**
     * @brief Constructs a new Static Texture with the same color of the passed one.
     * 
     * @param old - The texture from which copy the color.
     */
    StaticTexture::StaticTexture(const StaticTexture &old) : color(old.color) {}

    /**
     * @brief Return an RGB value that represents the color of the texture (it is always the same).
     * 
     * @param u - The x texture coord. Ranged from 0 to 1.
     * @param v - The y texture coord. Ranged from 0 to 1.
     * @param p - The point hit on the object.
     * @return geometry::Vec3 - The color of the texture.
     */
    geometry::Vec3 StaticTexture::value(const float u, const float v, const geometry::Vec3 &p) const{
        return this->color;
    }

}
}