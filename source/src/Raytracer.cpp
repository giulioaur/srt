#include "Raytracer.h"

#include <cmath>

#include "ds/Scene.hpp"
#include "rendering/Material.hpp"
#include "utility/FileManager.hpp"
#include "utility/Randomizer.hpp"

namespace srt
{

using s_hit_record = geometry::hitables::Hitable::s_hit_record;

rendering::Color compute_color(const geometry::Ray& ray, const ds::Scene& scene,
	const s_rt_parameter& parameters, const int16_t inDepth = 0)
{
	//s_hit_record hit_record;
	//
	//if (depth < parameters.max_bounces && scene.intersect(ray, 0.0001f, FLOAT_MAX, hit_record))
	//{
	//	rendering::Color attenuation;
	//	geometry::Ray newRay{ ray };
	//	geometry::Vector4 target = hit_record.point + hit_record.normal +
	//		utility::Randomizer::randomInUnitSphere();

	//	if (hit_record.material->bounce(ray, hit_record, newRay, attenuation))
	//	{
	//		return attenuation * compute_color(newRay, scene, parameters, depth + 1);
	//	}
	//	else
	//	{
	//		return attenuation;
	//	}
	//}
	//
	//return parameters.backgroundColor;

	int16_t depth = inDepth;
	s_hit_record hit_record;
	rendering::Color currentColor{ 1 };
	rendering::Color attenuation;
	geometry::Ray oldRay{ ray };
	geometry::Ray newRay{ ray };

	while (depth < parameters.max_bounces && scene.intersect(oldRay, 0.0001f, FLOAT_MAX, hit_record))
	{
		geometry::Vector4 target = hit_record.point + hit_record.normal +
			utility::Randomizer::randomInUnitSphere();
		++depth;

		if (!hit_record.material->bounce(ray, hit_record, newRay, attenuation))
		{
			return currentColor * attenuation;
		}

		currentColor *= attenuation;
		oldRay = std::move(newRay);
	}

	return depth < parameters.max_bounces ? currentColor * parameters.backgroundColor : currentColor;
}

pixel_vector raytracing(const ds::Scene& scene, const rendering::Camera camera,
	const s_rt_parameter& parameters)
{
	using random = utility::Randomizer;

	pixel_vector pixels;
	const int32_t height = scene.getHeight();
	const int32_t width = scene.getWidth();

	pixels.reserve(height * width);

	for (size_t j = height; j > 0; --j) {
		for (size_t i = 0; i < width; ++i) {
			rendering::Color finalColor;

			// Anti aliasing.
			for (size_t k = 0; k < parameters.antialiasing_samples; ++k) {
				float u = ((float)i + random::randomFloat()) / width;
				float v = ((float)j + random::randomFloat()) / height;

				finalColor += compute_color(camera.getRay(u, v), scene, parameters);
			}

			finalColor /= parameters.antialiasing_samples;

			// #TODO_OPTIMIZATION Use a simple gamma correction.
			pixels.emplace_back(
				sqrt(finalColor.x()) * 255.99f,
				sqrt(finalColor.y()) * 255.99f,
				sqrt(finalColor.z()) * 255.99f
			);
		}
	}

	return pixels;
}

void draw(const ds::Scene& scene, const pixel_vector& pixels)
{
	// Write on the file.
	std::ostringstream imageStream;
	imageStream << "P3\n" << scene.getWidth() << ' ' << scene.getHeight() << ' ' << "255\n";

	// image.write(pixels.data(), pixels.size());
	for (const auto& pix : pixels)
		imageStream << short(pix.x()) << ' ' << short(pix.y()) << ' ' << short(pix.z()) << '\n';
	
	utility::FileManager::writeFile(FILES_DIR + scene.getName() + ".ppm", imageStream.str(), false);
}

}

