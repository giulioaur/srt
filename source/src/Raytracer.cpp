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
	const s_rt_parameter& parameters)
{
	int32_t depth = 0;
	s_hit_record hit_record;
	
	if (scene.intersection(ray, 0.0001f, FLOAT_MAX, hit_record))
	{
		rendering::Color attenuation;
		geometry::Ray newRay{ ray };
		geometry::Vector4 target = hit_record.point + hit_record.normal +
			utility::Randomizer::randomInUnitSphere();

		if (hit_record.material->hit(ray, hit_record, newRay, attenuation))
		{
			return attenuation * compute_color(geometry::Ray{ hit_record.point, target - hit_record.point }, scene, parameters);
		}
	}

	float t = 0.5f * (ray.getDirection().normalize().y() + 1);
	return (1.f - t) * rendering::Color(1.f, 1.f, 1.f) + t * rendering::Color(0.5f, 0.7f, 1.f);
}

pixel_vector raytracing(const ds::Scene& scene, const rendering::Camera camera,
	const s_rt_parameter& parameters)
{
	using random = utility::Randomizer;

	pixel_vector pixels;
	const int32_t height = scene.getHeight();
	const int32_t width = scene.getWidth();

	pixels.resize(height * width);

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
			pixels[(height - j) * width + i] = rendering::Color(
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

