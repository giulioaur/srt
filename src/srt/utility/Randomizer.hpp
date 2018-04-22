/*******************************************************
 *                                                     *
 *  srt: Sushi RayTracer                               *
 *                                                     *
 *  RANDOMIZER CLASS HEADER                            *
 *                                                     *
 *  Giulio Auriemma                                    *
 *                                                     *
 *******************************************************/
#ifndef S_UTILITY_RANDOM_S
#define S_UTILITY_RANDOM_S

// My includes
#include "../geometry/Vec3.hpp"

namespace srt{
namespace utility{

/// This class offers only static methods for random calculations.

class Randomizer{
private:
    static int initSeed;
public:
    // METHODS

    /**
     * @brief Returns a random number in a given interval.
     * 
     * @param min - The lower bound of the interval.
     * @param max - The upper bound of the interval.
     * @return float - The random number.
     */
    static inline float randomRange(const float min, const float max){
        double value = (double)rand() / RAND_MAX;
        return min + value * (max - min);
    }


    /**
     * @brief Returns a random point in the unit sphere.
     * 
     * @return Vec3 - A random point in unit sphere.
     */
    static inline geometry::Vec3 randomInUnitSphere(){
        // Marsiglia's formula
        float x1, x2, sos = 2;
        while(sos >= 1){
            x1 = drand48() * 2 - 1;
            x2 = drand48() * 2 - 1;
            sos = x1 * x1 + x2 * x2;
        }

        float ssos = sqrt(1 - sos);
        return {2 * x1 * ssos, 2 * x2 * ssos, 1 - 2 * sos};
    }
};

}
}


#endif