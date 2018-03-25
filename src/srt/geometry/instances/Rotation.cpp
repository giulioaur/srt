/*******************************************************
 *                                                     *
 *  srt: Sushi RayTracer                               *
 *                                                     *
 *  TRANSLATE CLASS FILE                               *
 *                                                     *
 *  Giulio Auriemma                                    *
 *                                                     *
 *******************************************************/
#include "Rotation.hpp"

// Other system includes.
#include <cmath>
#include <limits>


const float MAX_FLOAT = std::numeric_limits<float>::max();
const float MIN_FLOAT = std::numeric_limits<float>::min();

namespace srt{
namespace geometry{
namespace instances{

    /**
     * @brief Construct a new Rotation:: Rotation object
     * 
     * @param type 
     * @param object 
     * @param degree 
     */
    Rotation::Rotation(const Type type, const std::shared_ptr<Hitable> object, const float degree) : 
        object(object){
        float radians = (M_PI / 180) * degree,
              sinT = sin(radians),
              cosT = cos(radians);

        switch(type){
            case Rotation::roll:
                this->rotationMat = {1,    0,     0,
                                     0, cosT, -sinT,
                                     0, sinT, cosT};
                this->inverseMat = {1,    0,     0,
                                    0, cosT,  sinT,
                                    0, -sinT, cosT};
                break;
            case Rotation::pitch:
                this->rotationMat = {cosT, 0, -sinT,
                                     0,    1,    0,
                                     sinT, 0, cosT};
                this->inverseMat = {cosT,  0, sinT,
                                    0,     1,    0,
                                    -sinT, 0, cosT};
                break;
            case Rotation::yaw:
                this->rotationMat = {cosT, -sinT, 0,
                                     sinT, cosT,  0,
                                     0,    0,     1};
                this->inverseMat = {cosT,  sinT,  0,
                                    -sinT, cosT,  0,
                                    0,     0,     1};
                break;
        }
    }

    /**
     * @brief Construct a new Rotation:: Rotation object
     * 
     * @param old 
     */
    Rotation::Rotation(const Rotation &old) : object(old.object), rotationMat(old.rotationMat) { }

    /**
     * @brief Computes the intersection between the emitted ray and the rotated object.
     * 
     * @param ray - The ray.
     * @param tmin - The min t to consider.
     * @param tmax - The max t to consider.
     * @return Hitable::hit_record - The record that stores hit info.
     */
    Hitable::hit_record Rotation::intersection(const Ray &ray, const float tmin, const float tmax) const{
        // Rotate the ray and then computes intersection.
        Ray rotatedRay{this->rotationMat * ray.getOrigin(), this->rotationMat * ray.getDirection(), ray.getTime()};
        auto record = this->object->intersection(rotatedRay, tmin, tmax);

        // Rotate the point.
        if(record.hit){
            record.point = this->inverseMat * record.point;
            record.normal = this->inverseMat * record.normal;
        }

        return record;
    }

    /**
     * @brief Returns the axis aligned bounded box boxes.
     * 
     * @param t0 - The first instant of time to consider.
     * @param t1 - The last instant of time to consider.
     * @return std::unique_ptr<geometry::AABB> The axis aligned bounded box that surrounds the object.
     */
    std::unique_ptr<AABB> Rotation::getAABB(const float t0, const float t1) const{
        std::vector<float> min{MAX_FLOAT, MAX_FLOAT, MAX_FLOAT}, max = {MIN_FLOAT, MIN_FLOAT, MIN_FLOAT};
        auto box = this->object->getAABB(t0, t1);

        // Find min and max of the rotated bounding box.
        for(uint8_t i = 0; box && i < 2; ++i){
            for(uint8_t j = 0; j < 2; ++j){
                for(uint8_t k = 0; k < 2; ++k){
                    Vec3 newCoord{ i * box->getMax().x() + (1 - i) * box->getMin().x(),
                                   j * box->getMax().y() + (1 - j) * box->getMin().y(),
                                   k * box->getMax().z() + (1 - k) * box->getMin().z() };
                    Vec3 toTest = this->inverseMat * newCoord;

                    for(uint8_t c = 0; c < 3; ++c){
                        if(toTest[c] < min[c]) min[c] = toTest[c];
                        if(toTest[c] > max[c]) max[c] = toTest[c];
                    }
                }
            }
        }

        return box ? std::make_unique<AABB>(Vec3{min}, Vec3{max}) : nullptr;
    }

    /**
     * @brief Get the Material of the rotated object.
     * 
     * @return const Material& - The material of the rotated object.
     */
    const std::shared_ptr<materials::Material>& Rotation::getMaterial() const{
        return this->object->getMaterial();
    }

    /**
     * @brief Get the Texture Coords of the rotated object in a given point.
     * 
     * @param p - The hit point on the rotated object.
     * @return geometry::Vec3 - The texture coords.
     */
    geometry::Vec3 Rotation::getTextureCoords(const geometry::Vec3 &p) const{
        return this->object->getTextureCoords(this->rotationMat * p);
    }

}
}
}