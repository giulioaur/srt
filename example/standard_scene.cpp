#include "Raytracer.h"

#include <iostream>

#include "geometry/hitables/Sphere.hpp"
#include "geometry/hitables/AARectangle.hpp"
#include "rendering/Material.hpp"
#include "utility/Stopwatch.hpp"

void base_scene();
void cornell_box();

/**************************************** MAIN ****************************************/

int main(int argc, char** argv)
{
	base_scene();

    return 0;
}


/**************************************** FUNCTIONS ****************************************/


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



	std::cout << "-------------------------------- START COMPUTING --------------------------------" << std::endl;
	sw.start();
	const auto pixels = srt::raytracing(scene, camera, parameters);
	std::cout << "-------------------------------- END COMPUTING (" << sw.endms() << " ms) --------------------------------" << std::endl << std::endl;



	std::cout << "-------------------------------- START DRAWING --------------------------------" << std::endl;
	sw.start();
	srt::draw(scene, pixels);
	std::cout << "-------------------------------- END DRAWING (" << sw.endms() << " ms) --------------------------------" << std::endl << std::endl;
}

void cornell_box()
{
	using e_rect_type = srt::geometry::hitables::AARectangle::e_type;
	srt::utility::Stopwatch sw;

	std::cout << "-------------------------------- CORNELL BOX --------------------------------" << std::endl << std::endl;
	std::cout << "-------------------------------- START BUILDING --------------------------------" << std::endl;
	sw.start();
	const auto whiteMaterial = std::make_shared<srt::rendering::Diffuse>(
		std::make_shared<srt::rendering::Texture>(srt::rendering::Color{ 0.73f, 0.73f, 0.73f })
	);
	std::vector<std::shared_ptr<srt::geometry::hitables::Hitable>> objects{
		std::make_shared<srt::geometry::hitables::AARectangle>(
			e_rect_type::YZ,
			0, 555,
			0, 555,
			555,
			std::make_shared<srt::rendering::Diffuse>(
				std::make_shared<srt::rendering::Texture>(
					srt::rendering::Texture{ srt::rendering::Color{ 0.65f, 0.05f, 0.05f} })),
			true
		),
		std::make_shared<srt::geometry::hitables::AARectangle>(
			e_rect_type::YZ,
			0, 555,
			0, 555,
			0,
			std::make_shared<srt::rendering::Diffuse>(
				std::make_shared<srt::rendering::Texture>(
					srt::rendering::Texture{ srt::rendering::Color{ 0.12f, 0.45f, 0.15f} }))
		),
		std::make_shared<srt::geometry::hitables::AARectangle>(
			e_rect_type::XY,
			0, 555,
			0, 555,
			555,
			whiteMaterial,
			true
		),
		std::make_shared<srt::geometry::hitables::AARectangle>(
			e_rect_type::XZ,
			0, 555,
			0, 555,
			555,
			whiteMaterial,
			true
		),
		std::make_shared<srt::geometry::hitables::AARectangle>(
			e_rect_type::XZ,
			0, 555,
			0, 555,
			0,
			whiteMaterial
		),
		std::make_shared<srt::geometry::hitables::AARectangle>(
			e_rect_type::XZ,
			213, 343,
			227, 332,
			554,
			std::make_shared<srt::rendering::DiffuseLight>(
				srt::rendering::Color{ 15, 15, 15})
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



	std::cout << "-------------------------------- START COMPUTING --------------------------------" << std::endl;
	sw.start();
	const auto pixels = srt::raytracing(scene, camera, parameters);
	std::cout << "-------------------------------- END COMPUTING (" << sw.endms() << " ms) --------------------------------" << std::endl << std::endl;



	std::cout << "-------------------------------- START DRAWING --------------------------------" << std::endl;
	sw.start();
	srt::draw(scene, pixels);
	std::cout << "-------------------------------- END DRAWING (" << sw.endms() << " ms) --------------------------------" << std::endl;
}