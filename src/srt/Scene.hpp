/*******************************************************
 *                                                     *
 *  srt: Sushi RayTracer                               *
 *                                                     *
 *  SCENE HEADER FILE                                  *
 *                                                     *
 *  Giulio Auriemma                                    *
 *                                                     *
 *******************************************************/
#ifndef S_SCENE_S
#define S_SCENE_S

// System includes.
#include <memory>
#include <vector>
#include <string>

// My includes.
#include "Ray.hpp"
#include "Hitable.hpp"
#include "ds/BVH.hpp"

namespace srt{

class Scene{
private:
    // ATTRIBUTES

    float height, width, t0, t1;
    std::string name;
    ds::BVH hitablesTree;
    std::vector<std::shared_ptr<Hitable>> hitables = {};

public:

    // CONSTRUCTORS
    
    Scene(const float width, const float height, const std::string &name, 
            const float t0 = 0, const float t1 = 1);
    
    // METHODS

    const float& getHeight() const;
    const float& getWidth() const;
    const std::string& getName() const;
    const size_t &getHierarchyDepth() const;
    void buildBVH();
    void addHitables(const std::vector<std::shared_ptr<Hitable>> &newHitables);
    const Hitable::hit_record intersection(const Ray &ray, const float tmin, const float tmax) const;
};
}

#endif
