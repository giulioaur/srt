/*******************************************************
 *                                                     *
 *  srt: Sushi RayTracer                               *
 *                                                     *
 *  MATERIAL HEADER FILE                               *
 *                                                     *
 *  Giulio Auriemma                                    *
 *                                                     *
 *******************************************************/
#ifndef S_MATERIALS_MATERIAL_S
#define S_MATERIALS_MATERIAL_S

// My includes
#include "../geometry/Vec3.hpp"
#include "../Ray.hpp"

namespace srt{
namespace materials{

/// The abstract material class.
class Material{
private:
    // ATTRIBUTES

public:
    // METHODS
    virtual bool scatter(Ray &ray, geometry::Vec3 &attenuation, const geometry::Vec3 &hitPoint, 
                            const geometry::Vec3 &normal, const geometry::Vec3 &textureCoords) const = 0;
    
    /**
     * @brief Returns true if the current one is an emitting material, then change emittedColor to the color emitted.
     * 
     * @param hitPoint - The point hit by the ray on which compute the color emission.
     * @param textureCoords - The texture coordinates.
     * @param emittedColor - The variable in which stores the emitted color, if one.
     * @return true - If the material is an emitter.
     * @return false - If the material is not an emitter.
     */
    virtual bool emit(const geometry::Vec3 &hitPoint, const geometry::Vec3 &textureCoords, geometry::Vec3 &emittedColor) const{
        return false;
    }
};
}
}

#endif