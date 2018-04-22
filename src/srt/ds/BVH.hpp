/*******************************************************
 *                                                     *
 *  srt: Sushi RayTracer                               *
 *                                                     *
 *  BVH HEADER FILE                                    *
 *                                                     *
 *  Giulio Auriemma                                    *
 *                                                     *
 *******************************************************/
#ifndef S_DS_BVH_S
#define S_DS_BVH_S

// My includes
#include "../Hitable.hpp"
#include "../geometry/AABB.hpp"

namespace srt{
namespace ds{

/// This class represents a bounding volume hierarchy composed by a tree structure in which every
/// node is a AABB and the leaves are the true hitable objects.
class BVH : public Hitable{
private:
    // ATTRIBUTES

    std::shared_ptr<Hitable> left, right;
    geometry::AABB box;
    size_t depth;
 
    // METHODS
    BVH(std::vector<std::shared_ptr<Hitable>> &hitables, size_t start, size_t end, const float t0, const float t1);
    void draw_slave(std::vector<std::shared_ptr<Hitable>> &squares, const int level) const;
public:
    // CONSTRUCTORS

    BVH();
    BVH(std::vector<std::shared_ptr<Hitable>> &hitables, const float t0, const float t1);

    // METHODS

    const size_t &getDepth() const;
    Hitable::hit_record intersection(const Ray &ray, const float tmin, const float tmax) const;
    std::unique_ptr<geometry::AABB> getAABB(const float t0, const float t1) const;
    std::vector<std::shared_ptr<Hitable>> draw() const;
};

}
}

#endif