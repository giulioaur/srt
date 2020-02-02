/*******************************************************
 *                                                     *
 *  srt: Sushi RayTracer                               *
 *                                                     *
 *  BVH CLASS FILE                                     *
 *                                                     *
 *  Giulio Auriemma                                    *
 *                                                     *
 *******************************************************/
#include "ds/BVH.hpp"

 // Other system includes
#include <algorithm>
#include <queue>

#include "utility/Randomizer.hpp"

namespace srt::ds 
{

BVH::BVH() 
{ 
}

/**
 * @brief Creates a BVH with the hitable passed as parameters.
 *
 * @param hitables - The hitable on which construct the BVH.
 * @param t0 - The first time instant to consider.
 * @param t1 - The last time instant to consider.
 */
BVH::BVH(std::vector<std::shared_ptr<Hitable>>& hitables, const float t0, const float t1)
    : BVH(hitables, 0, hitables.size() - 1, t0, t1) { }

struct axis_comparator
{
    inline bool operator() (const std::shared_ptr<geometry::hitables::Hitable>& hit0, 
        const std::shared_ptr<geometry::hitables::Hitable>& hit1) const
    {
        short axis = static_cast<short>(utility::Randomizer::randomRange(0, 2.99f));
        auto box0 = hit0->getAABB(0, 0), box1 = hit0->getAABB(0, 0);

        return box0.getMin()[axis] > box1.getMin()[axis];
    }
};

BVH::BVH(std::vector<std::shared_ptr<geometry::hitables::Hitable>>& hitables, size_t start,
    size_t end, const float t0, const float t1) 
{
    // Set left and right son.
    if (start == end) 
    {
        m_left = m_right = hitables[start];
    }
    else if (end - start == 1) 
    {
        m_left = hitables[start];
        m_right = hitables[end];
    }
    else 
    {
        std::sort(hitables.begin() + start, hitables.begin() + end, axis_comparator{ });
        size_t middle = start + (end - start) / 2;
        m_left = std::make_shared<BVH>(BVH(hitables, start, middle, t0, t1));
        m_right = std::make_shared<BVH>(BVH(hitables, middle + 1, end, t0, t1));
    }

    // Get boundig box and compute the current one.
    const geometry::AABB leftBox = m_left->getAABB(t0, t1),
                         rightBox = m_right->getAABB(t0, t1);

    m_box = leftBox.getSurroundingBox(rightBox);
}


bool BVH::intersect(const geometry::Ray& ray, const float tmin, const float tmax,
    geometry::hitables::Hitable::s_hit_record& hit_record) const 
{
    if (m_box.intersect(ray, tmin, tmax)) 
    {
        geometry::hitables::Hitable::s_hit_record leftHit, rightHit;

        m_left->intersect(ray, tmin, tmax, leftHit);
        m_right->intersect(ray, tmin, tmax, rightHit);

        if (leftHit.hit && rightHit.hit)
        {
            hit_record = leftHit.t < rightHit.t ? leftHit : rightHit;
            return true;
        }            

        // Otherwise return the one hit or an empty record.
        hit_record = leftHit.hit ? leftHit :
            rightHit.hit ? rightHit : Hitable::NO_HIT;
        return hit_record.hit;
    }

    return false;
}


std::vector<std::shared_ptr<geometry::hitables::Hitable>> BVH::draw() const
{
    std::vector<std::shared_ptr<Hitable>> squares;
    draw_slave(squares, 0);
    return squares;
}



void BVH::draw_slave(std::vector<std::shared_ptr<geometry::hitables::Hitable>>& squares, const int level) const 
{

    // Add rectangle.
    squares.push_back(getShapeFromBox(m_box, level));

    // Check if the function need to be recalled on children.
    if (const BVH* leftSon = dynamic_cast<BVH*>(&*m_left))
        leftSon->draw_slave(squares, level + 1);
    else
        squares.push_back(getShapeFromBox(m_left->getAABB(0, 1), level + 1));

    if (const BVH* rightSon = dynamic_cast<BVH*>(&*m_right))
        rightSon->draw_slave(squares, level + 1);
    else
        squares.push_back(getShapeFromBox(m_right->getAABB(0, 1), level + 1));
}

std::shared_ptr<geometry::hitables::Hitable> BVH::getShapeFromBox(const geometry::AABB& box, const int level) const
{
    //const float green = 1 - level / MAX_LEVEL * 0.3, red = 1 - (MAX_LEVEL - level) / MAX_LEVEL * 0.3;
    //const std::shared_ptr<materials::Material> mat = std::make_shared<materials::Dielectric>(1, geometry::Vec3{ 0.89, 0.89, 0.89 });

    //// Use front face.
    //// using rectangle = geometry::shapes::AARectangle;
    //// const geometry::Vec3 min = box.getMin(), max = box.getMax();
    //// return std::make_shared<rectangle>(rectangle::XY, min.x(), max.x(), min.y(), max.y(), min.z() - 2, mat);

    //// Use box.
    //return std::make_shared<geometry::AABox>(box.getMin(), box.getMax(), mat);
    return nullptr;
}

}
