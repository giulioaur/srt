#pragma once

#include "geometry/hitables/Hitable.hpp"
#include "geometry/AABB.hpp"

#include <vector>

namespace srt::ds 
{

/// This class represents a bounding volume hierarchy composed by a tree structure in which every
/// node is a AABB and the leaves are the true hitable objects.

//#TODO_OPTIMIZATION Use array to construct a binary tree, make it does not inherit from hitable
// and add a hitable ptr to understand if it is a leaf or not.
// intersect method becomes an if, use a template argument to get rid of the exec time if.
class BVH : public geometry::hitables::Hitable 
{
public:

    BVH();
    BVH(std::vector<std::shared_ptr<Hitable>>& hitables, const float t0, const float t1);

    bool intersect(const geometry::Ray& ray, const float tmin, const float tmax,
        geometry::hitables::Hitable::s_hit_record& hit_record) const override;
    const geometry::AABB getAABB(const float t0, const float t1) const noexcept override { return m_box; };

    /**
     * @brief Returns a vector of hitable to draw the BVH as transparent square.
     *        The square used is the front face of the box. The color of the square depends on the depth of the box it represents.
     *
     * @return std::vector<std::shared_ptr<Hitable>>
     */
    std::vector<std::shared_ptr<geometry::hitables::Hitable>> draw() const;

private:

    BVH(std::vector<std::shared_ptr<Hitable>>& hitables, size_t start, size_t end, 
        const float t0, const float t1);

    /**
     * @brief Used to build squares vector with recursion.
     */
    std::shared_ptr<geometry::hitables::Hitable> getShapeFromBox(const geometry::AABB& box, const int level) const;
    void draw_slave(std::vector<std::shared_ptr<Hitable>>& squares, const int level) const;
    
    std::shared_ptr<Hitable> m_left;
    std::shared_ptr<Hitable> m_right;
    geometry::AABB m_box;
};

}