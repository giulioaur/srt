/*******************************************************
 *                                                     *
 *  srt: Sushi RayTracer                               *
 *                                                     *
 *  RANDOMIZER CLASS FILE                              *
 *                                                     *
 *  Giulio Auriemma                                    *
 *                                                     *
 *******************************************************/
#include "Randomizer.hpp"

using namespace srt::geometry;

namespace srt{
namespace utility{

    /**
     * @brief Returns a random number in a given interval.
     * 
     * @param min - The lower bound of the interval.
     * @param max - The upper bound of the interval.
     * @return float - The random number.
     */
    float Randomizer::randomRange(const float min, const float max){
        double value = (double)rand() / RAND_MAX;
        return min + value * (max - min);
    }

    /**
     * @brief Returns a random point in the unit sphere.
     * 
     * @return Vec3 - A random point in unit sphere.
     */
    Vec3 Randomizer::randomInUnitSphere(){
        Vec3 p;
        p = 2. * Vec3{drand48(), drand48(), drand48()} - Vec3{1, 1, 1};
        return p.normalize();
    }
}
}