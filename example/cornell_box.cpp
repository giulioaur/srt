#include "Raytracer.h"

#include <iostream>

#include "geometry/hitables/Sphere.hpp"
#include "rendering/Material.hpp"
#include "utility/Stopwatch.hpp"

/**************************************** DEFINE ****************************************/

/**************************************** TYPEDEF ****************************************/

/**************************************** HEADER ****************************************/

/**************************************** GLOBAL ****************************************/

/**************************************** MAIN ****************************************/

int main(int argc, char** argv)
{
	std::vector<std::shared_ptr<srt::geometry::hitables::Hitable>> objects{
		std::make_shared<srt::geometry::hitables::Sphere>(
			srt::geometry::Vector4{ 0.f, 0.f, -1.f, 0.f },
			0.5f,
			std::make_shared<srt::rendering::Diffuse>(srt::rendering::Color{ 1, 0, 0})
		),
		std::make_shared<srt::geometry::hitables::Sphere>(
			srt::geometry::Vector4{ 0.f, -100.5f, -1.f, 0.f },
			100.f,
			std::make_shared<srt::rendering::Diffuse>(srt::rendering::Color{ 0.2f, 1, 0.2f})
		),
		std::make_shared<srt::geometry::hitables::Sphere>(
			srt::geometry::Vector4{ 1.f, 0.f, -1.f, 0.f },
			0.5f,
			std::make_shared<srt::rendering::Metal>(srt::rendering::Color{ 0.8f, 0.6f, 0.2f}, 0.5f)
		),
		std::make_shared<srt::geometry::hitables::Sphere>(
			srt::geometry::Vector4{ -1.f, 0.f, -1.f, 0.f },
			0.5f,
			std::make_shared<srt::rendering::Metal>(srt::rendering::Color{ 0.8f, 0.8f, 0.8f}, 0.f)
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
    const srt::rendering::Camera camera {
        srt::geometry::Vector4{ 0.f, 0.f, 0.f, 0.f },
		srt::geometry::Vector4{ 0.f, 0.f, -1.f, 0.f },
		srt::geometry::Vector4{ 0.f, 1.f, 0.f, 0.f },
		125,
		static_cast<float>(scene.getWidth() / scene.getHeight()),
		0,
		1
    };
    const srt::s_rt_parameter parameters{ 100, 50 };

    srt::utility::Stopwatch sw;

    std::cout << "-------------------------------- START COMPUTING --------------------------------" << std::endl;
    sw.start();
    const auto pixels = srt::raytracing(scene, camera, parameters);
    std::cout << "-------------------------------- END COMPUTING (" << sw.endms() << " ms) --------------------------------" << std::endl;

    std::cout << "-------------------------------- START DRAWING --------------------------------" << std::endl;
    sw.start();
    srt::draw(scene, pixels);
    std::cout << "-------------------------------- END DRAWING (" << sw.endms() << " ms) --------------------------------" << std::endl;


    return 0;
}


/**************************************** FUNCTIONS ****************************************/
