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

// My other includes
#include "../utility/Randomizer.hpp"

namespace srt{
namespace ds{

    /**
     * @brief Cretes an empty Bounding Volume Hierarchy.
     * 
     */
    BVH::BVH(){}

    /**
     * @brief Creates a BVH with the hitable passed as parameters.
     * 
     * @param hitables - The hitable on which construct the BVH.
     * @param t0 - The first time instant to consider.
     * @param t1 - The last time instant to consider.
     */
    BVH::BVH(std::vector<std::shared_ptr<Hitable>> &hitables, const float t0, const float t1) : 
        BVH(hitables, 0, hitables.size() - 1, t0, t1){ }

    /**
     * @brief Construct a new BVH object equal to a passed one. The new tree is build coping the
     *        pointers, so no new object is build.
     * 
     * @param old - The BVH to copy.
     */ 
    BVH::BVH(const BVH &old) : left(old.left), right(old.right), box(old.box){ }

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
     * @brief 
     * 
     * @param hitables 
     * @param start 
     * @param end 
     * @param t0 - 
     * @param t1 
     */
    BVH::BVH(std::vector<std::shared_ptr<Hitable>> &hitables, size_t start, size_t end, const float t0, const float t1){
        if(start == end){
            this->left = this->right = hitables[start];
        }
        else if(end - start == 1){
            this->left = hitables[start];
            this->right = hitables[end];
        }
        else{
            std::sort(hitables.begin() + start, hitables.begin() + end, axis_comparator());
            size_t middle = start + (end - start) / 2;
            this->left = std::make_shared<BVH>(BVH(hitables, start, middle, t0, t1));
            this->right = std::make_shared<BVH>(BVH(hitables, middle + 1, end, t0, t1));
        }
        
        auto leftBox = this->left->getAABB(t0, t1),
             rightBox = this->right->getAABB(t0, t1);

        if(leftBox == nullptr || rightBox == nullptr)
            throw std::invalid_argument("One of the hitable object has no bounding box");

        this->box = leftBox->surroundingBox(*rightBox);
    }

    /**
     * @brief Computes if the ray intersect one of the leaves of the tree.
     * 
     * @param ray - The ray.
     * @param tmin - The minumum t.
     * @param tmax - The maximum t.
     * @return Hitable::hit_record - The record with the info about the hitted object, if one.
     */
    Hitable::hit_record BVH::intersection(const Ray &ray, const float tmin, const float tmax) const{
        if(box.hit(ray, tmin, tmax)){
            Hitable::hit_record leftHit = this->left->intersection(ray, tmin, tmax),
                                rightHit = this->right->intersection(ray, tmin, tmax);

            // If both sons are hitted, return the closer one.
            if(leftHit.hitted && rightHit.hitted)
                return leftHit.t < rightHit.t ? leftHit : rightHit;

            // Otherwise return the one hitted or an empty record.
            return leftHit.hitted ? leftHit : 
                    (rightHit.hitted ? rightHit : Hitable::hit_record{false, -1, nullptr});
        }
        return Hitable::hit_record{false, -1, nullptr};
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

}
}