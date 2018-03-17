/*******************************************************
 *                                                     *
 *  srt: Sushi RayTracer                               *
 *                                                     *
 *  STATIC TEXTURE HEADER FILE                         *
 *                                                     *
 *  Giulio Auriemma                                    *
 *                                                     *
 *******************************************************/
#ifndef S_TEXTURES_STATICTEXTURE_S
#define S_TEXTURES_STATICTEXTURE_S

// My includes.
#include "Texture.hpp"

namespace srt{
namespace textures{

/// This represents a monochromatic texture (basically a color).
class StaticTexture : public Texture{
private:
    geometry::Vec3 color;
public:
    // CONSTRUCTORS
    StaticTexture();
    StaticTexture(const geometry::Vec3 &color);
    StaticTexture(const StaticTexture &old);

    virtual geometry::Vec3 value(const float u, const float v, const geometry::Vec3 &p) const;
};

}
}


#endif