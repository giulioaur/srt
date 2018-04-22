/*******************************************************
 *                                                     *
 *  srt: Sushi RayTracer                               *
 *                                                     *
 *  BVH CLASS FILE                                     *
 *                                                     *
 *  Giulio Auriemma                                    *
 *                                                     *
 *******************************************************/
#include "BVH.hpp"

// Other system includes
#include <algorithm>
#include <queue>

// My other includes
#include "../utility/Randomizer.hpp"
#include "../geometry/shapes/AABox.hpp"
#include "../materials/Dielectric.hpp"

static uint32_t maxLevel;

#define MAX_LEVEL 3

namespace srt{
namespace ds{

    /**
     * @brief Cretes an empty Bounding Volume Hierarchy.
     * 
     */
    BVH::BVH(){ }

    /**
     * @brief Creates a BVH with the hitable passed as parameters.
     * 
     * @param hitables - The hitable on which construct the BVH.
     * @param t0 - The first time instant to consider.
     * @param t1 - The last time instant to consider.
     */
    BVH::BVH(std::vector<std::shared_ptr<Hitable>> &hitables, const float t0, const float t1) : 
        BVH(hitables, 0, hitables.size() - 1, t0, t1){ }

    struct axis_comparator
    {        
        inline bool operator() (const std::shared_ptr<Hitable>& hit0, const std::shared_ptr<Hitable>& hit1)
        {
            short axis = static_cast<short>(2.99*drand48());
            auto box0 = hit0->getAABB(0, 0), box1 = hit0->getAABB(0, 0);

            if(box0 == nullptr || box1 == nullptr)
                throw std::invalid_argument("One of the hitable object has no bounding box");
            
            return box0->getMin()[axis] > box1->getMin()[axis] ? true : false;
        }
    };

    /**
     * @brief Construct a new BVH::BVH object.
     * 
     * @param hitables 
     * @param start 
     * @param end 
     * @param t0 
     * @param t1 
     */
    BVH::BVH(std::vector<std::shared_ptr<Hitable>> &hitables, size_t start, size_t end, const float t0, const float t1){
        // Set left and right son.
        if(start == end){
            this->left = this->right = hitables[start]; 
            this->depth = 0;
        }
        else if(end - start == 1){
            this->left = hitables[start];
            this->right = hitables[end];
            this->depth = 0;
        }
        else{
            std::sort(hitables.begin() + start, hitables.begin() + end, axis_comparator());
            size_t middle = start + (end - start) / 2;
            this->left = std::make_shared<BVH>(BVH(hitables, start, middle, t0, t1));
            this->right = std::make_shared<BVH>(BVH(hitables, middle + 1, end, t0, t1));
            this->depth = max(static_cast<BVH *>(this->left.get())->depth, static_cast<BVH *>(this->right.get())->depth) + 1;
        }
        
        // Get boundig box and compute the current one.
        const auto &leftBox = this->left->getAABB(t0, t1),
                   &rightBox = this->right->getAABB(t0, t1);

        if(leftBox == nullptr || rightBox == nullptr)
            throw std::invalid_argument("One of the hitable object has no bounding box");

        this->box = leftBox->surroundingBox(*rightBox);
    }

    /**
     * @brief Gets the depth of the tree rooted at this.
     * 
     * @return const size_t& - The depth of the tree.
     */
    const size_t& BVH::getDepth() const{
        return this->depth;
    }

    /**
     * @brief Computes if the ray intersect one of the leaves of the tree.
     * 
     * @param ray - The ray.
     * @param tmin - The minumum t.
     * @param tmax - The maximum t.
     * @return Hitable::hit_record - The record with the info about the hit object, if one.
     */
    Hitable::hit_record BVH::intersection(const Ray &ray, const float tmin, const float tmax) const{
        if(box.hit(ray, tmin, tmax)){
            Hitable::hit_record leftHit = this->left->intersection(ray, tmin, tmax),
                                rightHit = this->right->intersection(ray, tmin, tmax);

            // If both sons are hit, return the closer one.
            if(leftHit.hit && rightHit.hit)
                return leftHit.t < rightHit.t ? leftHit : rightHit;

            // Otherwise return the one hit or an empty record.
            return leftHit.hit ? leftHit : 
                    rightHit.hit ? rightHit : Hitable::NO_HIT;
        }

        return Hitable::NO_HIT;
    }

    /**
     * @brief Returns the boundig box that surrounds all the leaves.
     * 
     * @param t0 - The first time instant to consider.
     * @param t1 - The last time instant to consider.
     * @return std::unique_ptr<geometry::AABB> - The axis aligned bounding box.
     */
    std::unique_ptr<geometry::AABB> BVH::getAABB(const float t0, const float t1) const{
        return std::make_unique<geometry::AABB>(this->box);
    }

    std::shared_ptr<Hitable> getShapeFromBox(const geometry::AABB &box, const int level){
        const float green = 1 - level / MAX_LEVEL * 0.3, red = 1 - (MAX_LEVEL - level) / MAX_LEVEL * 0.3;
        const std::shared_ptr<materials::Material> mat = std::make_shared<materials::Dielectric>(1, geometry::Vec3{0.89, 0.89, 0.89});
        
        // Use front face.
        // using rectangle = geometry::shapes::AARectangle;
        // const geometry::Vec3 min = box.getMin(), max = box.getMax();
        // return std::make_shared<rectangle>(rectangle::XY, min.x(), max.x(), min.y(), max.y(), min.z() - 2, mat);

        // Use box.
        return std::make_shared<geometry::shapes::AABox>(box.getMin(), box.getMax(), mat);
    }

    /**
     * @brief Used to build squares vector with recursion.
     */
    void BVH::draw_slave(std::vector<std::shared_ptr<Hitable>> &squares, const int level) const{

        // Add rectangle.
        squares.push_back(getShapeFromBox(this->box, level));

        // Check if the function need to be recalled on children.
        if (const BVH* leftSon = dynamic_cast<BVH*>(&*this->left))
            leftSon->draw_slave(squares, level + 1);
        else
            squares.push_back(getShapeFromBox(*this->left->getAABB(0, 1), level + 1));

        if (const BVH* rightSon = dynamic_cast<BVH*>(&*this->right))
            rightSon->draw_slave(squares, level + 1);
        else
            squares.push_back(getShapeFromBox(*this->right->getAABB(0, 1), level + 1));
    }

    /**
     * @brief Returns a vector of hitable to draw the BVH as transparent square. 
     *        The square used is the front face of the box. The color of the square depends on the depth of the box it represents.
     * 
     * @return std::vector<std::shared_ptr<Hitable>> 
     */
    std::vector<std::shared_ptr<Hitable>> BVH::draw() const{
        std::vector<std::shared_ptr<Hitable>> squares;
        draw_slave(squares, 0);
        return squares;
    }   
}
}