#pragma once

#include "srt.h"

#include <vector>

#include "ds/Scene.hpp"
#include "geometry/Vector4.hpp"
#include "rendering/Color.hpp"

typedef std::vector<srt::rendering::Color> pixel_vector;

namespace srt
{

pixel_vector raytracing(const ds::Scene& scene, const geometry::Vector4& origin);
void draw(const ds::Scene& scene, const pixel_vector& pixels);

}
