#include "Raytracer.h"

#include <cmath>

#include "ds/Scene.hpp"
#include "utility/FileManager.hpp"
#include "utility/Randomizer.hpp"

namespace srt
{

rendering::Color compute_color(const geometry::Ray& ray, const ds::Scene& scene)
{
	return rendering::Color();
}

pixel_vector raytracing(const ds::Scene& scene, const rendering::Camera camera,
	const s_rt_parameter& parameters)
{
	using random = utility::Randomizer;

	pixel_vector pixels;
	const float height = scene.getHeight();
	const float width = scene.getWidth();

	pixels.resize(height * width);

	for (size_t j = height; j > 0; --j) {
		for (size_t i = 0; i < width; ++i) {
			rendering::Color finalColor;

			// Anti aliasing.
			for (size_t k = 0; k < parameters.antialiasing_samples; ++k) {
				float u = ((float)i + random::randomFloat()) / width;
				float v = ((float)j + random::randomFloat()) / height;

				finalColor += compute_color(camera.getRay(u, v), scene);
			}

			finalColor /= parameters.antialiasing_samples;

			pixels[(height - j) * width + i] = rendering::Color(
				sqrt(finalColor.x()) * 255.99f,
				sqrt(finalColor.y()) * 255.99f,
				sqrt(finalColor.z()) * 255.99f
			);
			// pixels.push_back(finalColor.x()); pixels.push_back(finalColor.y()); pixels.push_back(finalColor.z());
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

