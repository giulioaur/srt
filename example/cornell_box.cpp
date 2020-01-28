#include "Raytracer.h"

#include <iostream>

#include "geometry/hitables/Sphere.hpp"
#include "utility/Stopwatch.hpp"

/**************************************** DEFINE ****************************************/

/**************************************** TYPEDEF ****************************************/

/**************************************** HEADER ****************************************/

/**************************************** GLOBAL ****************************************/

/**************************************** MAIN ****************************************/

int main(int argc, char** argv)
{
    srt::ds::Scene scene{ 200, 100, "Test" };
    const srt::rendering::Camera camera {
        srt::geometry::Vector4{ 0.f, 0.f, 0.f, 0.f },
        srt::geometry::Vector4{ 4.f, 0.f, 0.f, 0.f },
        srt::geometry::Vector4{ 0.f, 2.f, 0.f, 0.f },
        srt::geometry::Vector4{ -2.f, -1.f, -1.f, 0.f }
    };
    const srt::s_rt_parameter parameters{ 100, 10 };

    scene.addHitables({
        std::make_shared<srt::geometry::hitables::Sphere>(srt::geometry::Vector4{ 0.f, 0.f, -1.f, 0.f }, 0.5f),
        std::make_shared<srt::geometry::hitables::Sphere>(srt::geometry::Vector4{ 0.f, -100.5f, -1.f, 0.f }, 100.f)
    });

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
