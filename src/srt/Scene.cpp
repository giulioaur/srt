/*******************************************************
 *                                                     *
 *  srt: Sushi RayTracer                               *
 *                                                     *
 *  SCENE CLASS FILE                                   *
 *                                                     *
 *  Giulio Auriemma                                    *
 *                                                     *
 *******************************************************/
#include "Scene.hpp"

// System includes.
#include <cmath>
#include <queue> 

// My includes.
#include "geometry/Plane.hpp"
#include "geometry/shapes/Circle.hpp"
#include "geometry/shapes/Sphere.hpp"

using namespace std;
using namespace srt::geometry;
using namespace srt::geometry::shapes;
using namespace srt::illumination::lights;

const float DISTANCE_TRESHOLD = 10e-2;

namespace srt{
    // Black color.
    const Vec3 BLACK{0, 0, 0}, WHITE{255, 255, 255};

    /**
     * @brief Constructs a new empty Scene object.
     * 
     * @param height - The height in pixel of the scene.
     * @param width - The width in pixel of the scene.
     * @param name - The name of the scene.
     * @param t0 - The first instant of time considered in the scene. 0 by default.
     * @param t1 - The last instant of time considered in the scene. 1 by default.
     */
    Scene::Scene(const float width, const float height, const string &name, const float t0, const float t1) :
        height(height), width(width), name(name), t0(t0), t1(t1) { }

    /**
     * @brief Creates a scene equal to a given one.
     * 
     * @param scene - The scene to copy.
     */
    Scene::Scene(const Scene &scene) : height(scene.height), width(scene.width), name(scene.name),
        t0(t0), t1(t1), hitables(scene.hitables), hitablesTree(scene.hitablesTree) {}

    /**
     * @brief Returns the height of the scene.
     * 
     * @return short - The height of the scene.
     */
    const float& Scene::getHeight() const{
        return this->height;
    }

    /**
     * @brief Returns the width of the scene.
     * 
     * @return short - The width of the scene.
     */
    const float& Scene::getWidth() const{
        return this->width;
    }

    /**
     * @brief Returns the name of the scene.
     * 
     * @return const string& getName - The name of the scene.
     */
    const string& Scene::getName() const{
        return this->name;
    }

    /**
     * @brief Builds a new tree for the BVH. This function should be called every time
     *        the user want to update the bvh after inserting new object.
     * 
     */
    void Scene::buildBVH(){
        this->hitablesTree = {this->hitables, this->t0, this->t1};
    }

    /**
     * @brief Adds new Hitables to the scene.
     * 
     * @param newHitables - The Hitables to add to the scene.
     */
    void Scene::addHitables(const vector<shared_ptr<Hitable>> &newHitables){
        this->hitables.insert(this->hitables.end(), newHitables.begin(), newHitables.end());
    }

    /**
     * @brief Returns the object intersected by the ray, if one. If no object has been intersected,
     *        returns nullptr.
     * 
     * @param ray - The ray.
     * @param ligthPos - Could be any value. When method returns, it is setted to -1 if the Hitable is not a
     *                  light, otherwise it is the position of the light in the lights vector.
     * @param light - The light emmiting the ray, nullptr if no light is emitting this ray.
     * @param minDist - The minimum distance for the intersection.
     * @return std::shared_ptr<Hitable> - The closer Hitable intersected.
     */
    const Hitable::hit_record Scene::intersection(const Ray &ray, const float tmin, const float tmax) const{
        return this->hitablesTree.intersection(ray, tmin, tmax);
    }
}