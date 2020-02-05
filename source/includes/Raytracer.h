#pragma once

#include "srt.h"

#include <vector>

#include "ds/Scene.hpp"
#include "geometry/Vector4.hpp"
#include "rendering/Camera.hpp"
#include "rendering/Color.hpp"

typedef std::vector<srt::rendering::Color> pixel_vector;

namespace srt
{

typedef struct rtp
{
	int16_t antialiasing_samples;
	int16_t max_bounces;
	rendering::Color backgroundColor;
} s_rt_parameter;


pixel_vector raytracing(const ds::Scene& scene, const rendering::Camera& camera,
	const s_rt_parameter& parameters);


void draw(const ds::Scene& scene, const pixel_vector& pixels);

}
