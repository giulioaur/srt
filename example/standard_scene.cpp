#include "Raytracer.h"

#include <iostream>

#include "geometry/hitables/Sphere.hpp"
#include "geometry/hitables/AABox.hpp"
#include "geometry/hitables/AARectangle.hpp"
#include "rendering/Material.hpp"
#include "utility/Stopwatch.hpp"

#include <array>

void draw_and_render(const srt::ds::Scene& scene, const srt::rendering::Camera& camera,
	const srt::s_rt_parameter& parameters);

void base_scene();
void random_scene();
void cornell_box();

//#define BENCHMARK

/**************************************** MAIN ****************************************/

int main(int argc, char** argv)
{
#ifdef BENCHMARK
	base_scene();
	random_scene();
	cornell_box();
#else
	base_scene();
#endif // BENCHMARK

	return 0;
}


/**************************************** FUNCTIONS ****************************************/

void draw_and_render(const srt::ds::Scene& scene, const srt::rendering::Camera& camera,
	const srt::s_rt_parameter& parameters)
{
	srt::utility::Stopwatch sw;

	std::cout << "-------------------------------- START DRAWING --------------------------------" << std::endl;
	sw.start();
	const auto pixels = srt::raytracing(scene, camera, parameters);
	std::cout << "-------------------------------- END DRAWING (" << sw.endms() << " ms) --------------------------------" << std::endl << std::endl;

	std::cout << "-------------------------------- START RENDERING --------------------------------" << std::endl;
	sw.start();
	srt::draw(scene, pixels);
	std::cout << "-------------------------------- END RENDERING (" << sw.endms() << " ms) --------------------------------" << std::endl << std::endl;
}

void base_scene()
{
	srt::utility::Stopwatch sw;

	std::cout << "-------------------------------- TEST SCENE --------------------------------" << std::endl << std::endl;
	std::cout << "-------------------------------- START BUILDING --------------------------------" << std::endl;
	sw.start();
	std::vector<std::shared_ptr<srt::geometry::hitables::Hitable>> objects{
		std::make_shared<srt::geometry::hitables::Sphere>(
			srt::geometry::Vector4{ 0.f, 0.f, -1.f, 0.f },
			0.5f,
			std::make_shared<srt::rendering::Diffuse>(
				std::make_shared<srt::rendering::Texture>(srt::rendering::Texture{ srt::rendering::Color{ 1, 0, 0} }))
		),
		std::make_shared<srt::geometry::hitables::Sphere>(
			srt::geometry::Vector4{ 0.f, -100.5f, -1.f, 0.f },
			100.f,
			std::make_shared<srt::rendering::Diffuse>(
				std::make_shared<srt::rendering::Texture>(srt::rendering::Texture{ srt::rendering::Color{ 0.2f, 1, 0.2f} }))
		),
		std::make_shared<srt::geometry::hitables::Sphere>(
			srt::geometry::Vector4{ 1.f, 0.f, -1.f, 0.f },
			0.5f,
			std::make_shared<srt::rendering::Metal>(
				std::make_shared<srt::rendering::Texture>(srt::rendering::Texture{ srt::rendering::Color{ 0.8f, 0.6f, 0.2f} }), 0.5f)
		),
		std::make_shared<srt::geometry::hitables::Sphere>(
			srt::geometry::Vector4{ -1.f, 0.f, -1.f, 0.f },
			0.5f,
			std::make_shared<srt::rendering::Metal>(
				std::make_shared<srt::rendering::Texture>(srt::rendering::Texture{ srt::rendering::Color{ 0.8f, 0.8f, 0.8f} }), 0.f)
		),
		std::make_shared<srt::geometry::hitables::Sphere>(
			srt::geometry::Vector4{ 0.f, 1.5f, -1.f, 0.f },
			0.5f,
			std::make_shared<srt::rendering::DiffuseLight>(srt::rendering::Color{ 1.f, 1.f, 1.f})
		)
	};
	srt::ds::Scene scene{
		200,
		100,
		"Test",
		objects
	};
	const srt::rendering::Camera camera{
		srt::geometry::Vector4{ 0.f, 0.f, 0.f, 0.f },
		srt::geometry::Vector4{ 0.f, 0.f, -1.f, 0.f },
		srt::geometry::Vector4{ 0.f, 1.f, 0.f, 0.f },
		95,
		static_cast<float>(scene.getWidth()) / scene.getHeight(),
		0,
		1
	};
	const srt::s_rt_parameter parameters{ 100, 50, { 0.7f, 0.94f, 1 } };
	std::cout << "-------------------------------- END BUILDING (" << sw.endms() << " ms) --------------------------------" << std::endl << std::endl;

	draw_and_render(scene, camera, parameters);
}

void random_scene()
{
	srt::utility::Stopwatch sw;

	std::cout << "-------------------------------- RANDOM SCENE --------------------------------" << std::endl << std::endl;
	std::cout << "-------------------------------- START BUILDING --------------------------------" << std::endl;
	size_t length = 1250, side = sqrt(1000);
	float radius = length / (side * 2.f), dradius = radius * 2.f;
	float angularFrequency = 2 * static_cast<float>(M_PI) * 0.1f;
	std::vector<std::shared_ptr<srt::geometry::hitables::Hitable>> objects;
	objects.reserve(1000);

	for (size_t i = 0; i < 1000; ++i)
	{
		// Choose an x to be sure the circles are not intersected.
		float x = static_cast<float>(i / side), z = static_cast<float>(i % side);
		srt::geometry::Vector4 pos{ x * dradius, sin(x * angularFrequency) * radius, z * dradius, 0 };
		std::shared_ptr<srt::rendering::Material> material = 
			std::make_shared<srt::rendering::Diffuse>(
				std::make_shared<srt::rendering::Texture>(srt::rendering::Color{ 1.f - (x / side), 0, 0 + (z / side) }));
		objects.push_back(std::make_shared<srt::geometry::hitables::Sphere>(pos, radius, material));
	}

	// End scene.
	srt::ds::Scene scene{ 512, 384, "my_random_scene", objects };
	const srt::rendering::Camera camera{
		srt::geometry::Vector4{ 560, 850, -1050, 0.f },
		srt::geometry::Vector4{ 560, 250, 0, 0.f },
		srt::geometry::Vector4{ 0.f, 1.f, 0.f, 0.f },
		40,
		static_cast<float>(scene.getWidth()) / scene.getHeight(),
		0,
		1
	};
	const srt::s_rt_parameter parameters{ 100, 50, { 0.7f, 0.94f, 1 } };

	std::cout << "-------------------------------- END BUILDING (" << sw.endms() << " ms) --------------------------------" << std::endl << std::endl;

	draw_and_render(scene, camera, parameters);
}

void cornell_box()
{
	using e_rect_type = srt::geometry::hitables::e_rect_type;
	srt::utility::Stopwatch sw;

	std::cout << "-------------------------------- CORNELL BOX --------------------------------" << std::endl << std::endl;
	std::cout << "-------------------------------- START BUILDING --------------------------------" << std::endl;
	sw.start();
	const auto whiteMaterial = std::make_shared<srt::rendering::Diffuse>(
		std::make_shared<srt::rendering::Texture>(srt::rendering::Color{ 0.73f, 0.73f, 0.73f })
		);
	std::vector<std::shared_ptr<srt::geometry::hitables::Hitable>> objects{
		// RIGHT WALL
		std::make_shared<srt::geometry::hitables::AARectangle<e_rect_type::YZ>>(
			0, 555,
			0, 555,
			555,
			std::make_shared<srt::rendering::Diffuse>(
				std::make_shared<srt::rendering::Texture>(
					srt::rendering::Texture{ srt::rendering::Color{ 0.65f, 0.05f, 0.05f} })),
			true
		),
		// LEFT WALL
		std::make_shared<srt::geometry::hitables::AARectangle<e_rect_type::YZ>>(
			0, 555,
			0, 555,
			0,
			std::make_shared<srt::rendering::Diffuse>(
				std::make_shared<srt::rendering::Texture>(
					srt::rendering::Texture{ srt::rendering::Color{ 0.12f, 0.45f, 0.15f} }))
		),
		// FRONT WALL
		std::make_shared<srt::geometry::hitables::AARectangle<e_rect_type::XY>>(
			0, 555,
			0, 555,
			555,
			whiteMaterial,
			true
		),
		// ROOF
		std::make_shared<srt::geometry::hitables::AARectangle<e_rect_type::XZ>>(
			0, 555,
			0, 555,
			555,
			whiteMaterial,
			true
		),
		// FLOOR
		std::make_shared<srt::geometry::hitables::AARectangle<e_rect_type::XZ>>(
			0, 555,
			0, 555,
			0,
			whiteMaterial
		),
		// LIGHT
		std::make_shared<srt::geometry::hitables::AARectangle<e_rect_type::XZ>>(
			213, 343,
			227, 332,
			554,
			std::make_shared<srt::rendering::DiffuseLight>(
				srt::rendering::Color{ 15, 15, 15})
		),
		// CUBE 1
		std::make_shared<srt::geometry::hitables::AABox>(
			srt::geometry::Vector4{ 130, 0, 65, 0 },
			srt::geometry::Vector4{ 295, 165, 230, 0 },
			whiteMaterial
		),
		// CUBE 2
		std::make_shared<srt::geometry::hitables::AABox>(
			srt::geometry::Vector4{ 265, 0, 295, 0 },
			srt::geometry::Vector4{ 430, 330, 460, 0 },
			whiteMaterial
		)
	};
	srt::ds::Scene scene{
		580,
		720,
		"Cornell_Box",
		objects
	};
	const srt::rendering::Camera camera{
		srt::geometry::Vector4{ 278, 278, -800, 0.f },
		srt::geometry::Vector4{ 278.f, 278.f, 0, 0.f },
		srt::geometry::Vector4{ 0.f, 1.f, 0.f, 0.f },
		40,
		static_cast<float>(scene.getWidth()) / scene.getHeight(),
		0,
		1
	};
	//const srt::s_rt_parameter parameters{ 100, 50, { 0.7f, 0.94f, 1 } };
	const srt::s_rt_parameter parameters{ 100, 50, { 0, 0, 0 } };
	std::cout << "-------------------------------- END BUILDING (" << sw.endms() << " ms) --------------------------------" << std::endl << std::endl;

	draw_and_render(scene, camera, parameters);
}