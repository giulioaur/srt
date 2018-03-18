/*******************************************************
 *                                                     *
 *  srt: Sushi RayTracer                               *
 *                                                     *
 *  HITABLE CLASS FILE                                 *
 *                                                     *
 *  Giulio Auriemma                                    *
 *                                                     *
 *******************************************************/
#include "Hitable.hpp"

namespace srt{
    const Hitable::hit_record Hitable::NO_HIT = {false, -1, nullptr};
}