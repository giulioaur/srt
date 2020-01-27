#include "geometry/hitables/Hitable.hpp"

namespace srt::geometry::hitables 
{

const Hitable::s_hit_record Hitable::NO_HIT = { false, -1, nullptr, {}, {} };
//const std::shared_ptr<materials::Material> Hitable::NO_MATERIAL = { };

}