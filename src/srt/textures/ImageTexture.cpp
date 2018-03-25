/*******************************************************
 *                                                     *
 *  srt: Sushi RayTracer                               *
 *                                                     *
 *  IMAGE TEXTURE CLASS FILE                           *
 *                                                     *
 *  Giulio Auriemma                                    *
 *                                                     *
 *******************************************************/
#include "ImageTexture.hpp"

// Images library.
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

namespace srt{
namespace textures{

    /**
     * @brief Constructs a new Image Texture from a given image.
     * 
     * @param imagePath - The path in which find the image.
     */
    ImageTexture::ImageTexture(const std::string &imagePath){
        int nx, ny, nc;
        unsigned char *rawData = stbi_load(imagePath.c_str(), &nx, &ny, &nc, 0);
        this->data = {rawData, rawData + (nx * ny * 3)};
        this->w = nx;
        this->h = ny;
    }

    /**
     * @brief Constructs a new Image Texture object equal to an old one.
     * 
     * @param old - The Image texture to copy.
     */
    ImageTexture::ImageTexture(const ImageTexture &old) : data(old.data), w(old.w), h(old.h) { }

    /**
     * @brief Constructs a new Image Texture object using move semantics.
     * 
     * @param old - The Image texture to move.
     */
    ImageTexture::ImageTexture(const ImageTexture &&old) : data(std::move(old.data)), w(old.w), h(old.h) { }

    /**
     * @brief Returns an RGB value that represents the color of the image in that point.
     * 
     * @param u - The x texture coord. Ranged from 0 to 1.
     * @param v - The y texture coord. Ranged from 0 to 1.
     * @param p - The point hit on the object.
     * @return geometry::Vec3 - The color of the image.
     */
    geometry::Vec3 ImageTexture::value(const float u, const float v, const geometry::Vec3 &p) const{
        // The u/v coords are computed from bottom-left angle, we have it as upper left angle as origin.
        int x = u * w, y = (1 - v) * h - 0.0001;

        // Be sure that they are in the right range.
        x = x >= 0 && x <= w ? x : (x < 0 ? 0 : w-1);
        y = y >= 0 && y <= w ? y : (y < 0 ? 0 : h-1);

        // Return the color in a range from 0 to 1.
        auto it = data.begin() + (3 * x + 3 * y * w);
        return {it[0] / 255.f, it[1] / 255.f, it[2] / 255.f};
    }

}
}