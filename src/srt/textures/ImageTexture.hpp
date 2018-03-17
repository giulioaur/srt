/*******************************************************
 *                                                     *
 *  srt: Sushi RayTracer                               *
 *                                                     *
 *  IMAGE TEXTURE HEADER FILE                          *
 *                                                     *
 *  Giulio Auriemma                                    *
 *                                                     *
 *******************************************************/
#ifndef S_TEXTURES_IMAGETEXTURE_S
#define S_TEXTURES_IMAGETEXTURE_S

// System includes.
#include <string>
#include <vector>

// My includes.
#include "Texture.hpp"

namespace srt{
namespace textures{

/// This represents a monochromatic texture (basically a color).
class ImageTexture : public Texture{
private:
    std::vector<unsigned char> data;
    size_t h, w;
public:
    // CONSTRUCTORS

    ImageTexture(const std::string &imagePath);
    ImageTexture(const ImageTexture &old);
    ImageTexture(const ImageTexture &&old);

    // METHODS

    virtual geometry::Vec3 value(const float u, const float v, const geometry::Vec3 &p) const;
};

}
}

#endif