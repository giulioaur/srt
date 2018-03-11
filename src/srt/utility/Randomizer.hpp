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

    static float randomRange(const float min, const float max);
    static geometry::Vec3 randomInUnitSphere();
};

}
}


#endif