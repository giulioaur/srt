/*******************************************************
 *                                                     *
 *  srt: Sushi RayTracer                               *
 *                                                     *
 *  CHECKER TEXTURE CLASS FILE                         *
 *                                                     *
 *  Giulio Auriemma                                    *
 *                                                     *
 *******************************************************/
#include "CheckerTexture.hpp"

// Other system includes
#include <cmath>

// My other includes.
#include "StaticTexture.hpp"

namespace srt{
namespace textures{

    /**
     * @brief Constructs a new black and white Checker Texture.
     * 
     */
    CheckerTexture::CheckerTexture() : c0(std::make_unique<StaticTexture>(geometry::Vec3{0, 0, 0})), 
        c1(std::make_unique<StaticTexture>(geometry::Vec3{1, 1, 1})) {} 

    /**
     * @brief Constructs a new Checker Texture.
     * 
     * @param c0 - The first color.
     * @param c1 - The second color.
     */
    CheckerTexture::CheckerTexture(const std::shared_ptr<Texture> c0, const std::shared_ptr<Texture> c1) : 
        c0(c0), c1(c1) {} 

    /**
     * @brief Constructs a new Checker Texture with the same colors of the passed one.
     * 
     * @param old - The texture from which copy the colors.
     */
    CheckerTexture::CheckerTexture(const CheckerTexture &old) : c0(old.c0), c1(old.c1) {}

    /**
     * @brief Return an RGB value that represents the color of the texture in that point.
     * 
     * @param u - The x texture coord. Ranged from 0 to 1.
     * @param v - The y texture coord. Ranged from 0 to 1.
     * @param p - The point hit on the object.
     * @return geometry::Vec3 - The color of the texture.
     */
    geometry::Vec3 CheckerTexture::value(const float u, const float v, const geometry::Vec3 &p) const{
        float sines = sin(10 * p.x()) * sin(10 * p.y()) * sin(10 * p.z());
        return sines > 0 ? this->c0->value(u, v, p) : this->c1->value(u, v, p);
    }

}
}