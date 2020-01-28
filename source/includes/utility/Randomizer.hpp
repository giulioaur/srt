/*******************************************************
 *                                                     *
 *  srt: Sushi RayTracer                               *
 *                                                     *
 *  RANDOMIZER CLASS HEADER                            *
 *                                                     *
 *  Dr.Sushi                                           *
 *                                                     *
 *******************************************************/
#pragma once

#include "geometry/Vector4.hpp"

namespace srt::utility
{

/*
 * This class offers only static methods for random calculations.
 */
class Randomizer
{
public:

    /**
     * @brief Returns a random number in a given interval.
     * 
     * @param min - The lower bound of the interval.
     * @param max - The upper bound of the interval.
     * @return float - The random number.
     */
    static float randomRange(const float min, const float max);

    /**
     * @brief Returns a random float between 0 and 1.
     */
    static float randomFloat();

    /**
     * @brief Returns a random point in the unit sphere.
     * 
     * @return Vec3 - A random point in unit sphere.
     */
    static geometry::Vector4 randomInUnitSphere();
};

}