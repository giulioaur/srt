/*******************************************************
 *                                                     *
 *  srt: Sushi RayTracer                               *
 *                                                     *
 *  CHECKER TEXTURE HEADER FILE                        *
 *                                                     *
 *  Giulio Auriemma                                    *
 *                                                     *
 *******************************************************/
#ifndef S_TEXTURES_CHECKERTEXTURE_S
#define S_TEXTURES_CHECKERTEXTURE_S

// System includes.
#include <memory>

// My includes.
#include "Texture.hpp"

namespace srt{
namespace textures{

/// This represents a monochromatic texture (basically a color).
class CheckerTexture : public Texture{
private:
    std::shared_ptr<Texture> c0, c1;
public:
    // CONSTRUCTORS
    CheckerTexture();
    CheckerTexture(const std::shared_ptr<Texture> c0, const std::shared_ptr<Texture> c1);

    virtual geometry::Vec3 value(const float u, const float v, const geometry::Vec3 &p) const;
};

}
}

#endif