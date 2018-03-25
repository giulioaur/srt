#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <limits>
#include "../src/srt/paths.h"
#include "parse_scene.hpp"
#include "scene_builder.hpp"
#include "../src/srt/Ray.hpp"
#include "../src/srt/Camera.hpp"
#include "../src/srt/utility/Stopwatch.hpp"
#include "../src/srt/utility/Logger.hpp"
#include "../src/srt/utility/FileManager.hpp"
#include "../src/srt/geometry/shapes/MovingSphere.hpp"
#include "../src/srt/textures/StaticTexture.hpp"
#include "../src/srt/textures/CheckerTexture.hpp"
#include "../src/srt/textures/ImageTexture.hpp"

using namespace std;
using namespace srt;
using namespace srt::geometry;
using namespace srt::geometry::shapes;
using namespace srt::illumination::lights;
using namespace srt::utility;

/**************************************** DEFINE ****************************************/

#define SAMPLES 200

/**************************************** TYPEDEF ****************************************/

typedef vector<Vec3> pixel_vector;

/**************************************** HEADER ****************************************/

pixel_vector raytracing(Scene &scene, const Vec3 &origin = {0, 0, 0});
void draw(const Scene &scene, const pixel_vector &pixels);

/**************************************** GLOBAL ****************************************/

const Vec3 BASE_COLOR{170, 170, 170};
const float MAX_FLOAT = std::numeric_limits<float>::max();

/**************************************** MAIN ****************************************/

int main(int argc, char **argv){
    srand(static_cast <unsigned> (time(0))); // Init random seed.
    Stopwatch sw, sw1;

    cout << "Starting ray tracer..." << endl;

    // Build up the scene.
    //auto files = FileManager::getFiles(FILES_DIR + "scenes/");

    // for(size_t i = 0; i < files.size(); ++i){        
        // Parse the scene.
        sw1.start();
        // PMScene scene{100, 200, "test"};
        // Scene scene = build_scenes(FILES_DIR + "scenes/" + files[i]);

        // Random scene.
        // Scene scene = random_scene();

        // Scene to test texture.
        // Scene scene{400, 400, "image_test"};
        // scene.addHitables({make_shared<Sphere>(Vec3{0, 0, 0}, 2, make_shared<Lambertian>(make_shared<ImageTexture>(FILES_DIR + "textures/earth.jpg")))});
        // scene.buildBVH();

        // Scene to test light.
        // Scene scene = light_scene();

        // Cornell box.
        Scene scene = cornell_box(620, 700);

        cout << "...Ending scene creation in " << sw1.end() << "sec..." << endl;

        // Compute color through raytracing.
        sw1.start();
        pixel_vector pixels = raytracing(scene);
        cout << "...Ending color computation in " << sw1.end() << "sec..." << endl;

        // Render the scene.
        sw1.start();
        draw(scene, pixels);
        cout << "...Ending scene rendering in " << sw1.end() << "sec..." << endl;
    // }

    cout << "...Ending raytracer in " << sw.end() << "sec" << endl;
}


/**************************************** FUNCTIONS ****************************************/

Vec3 color(const Ray &ray, const Scene &scene){
    Ray currRay{ray};
    size_t depth = 0;
    Vec3 color = {1, 1, 1}, attenuation, emission;
    Hitable::hit_record container = scene.intersection(currRay, 0.001, MAX_FLOAT); 
    
    // Compute the attenuation factor of the bouncing ray.
    while(container.hit){
        auto material = container.object->getMaterial();
        Vec3 texturesCoords = container.object->getTextureCoords(container.point);

        // Add emission if one.
        if(!material->emit(container.point, texturesCoords, emission))
            emission = {0, 0, 0};

        if(depth < 50 && material->scatter(currRay, attenuation, container.point, 
                                            container.normal, 
                                            texturesCoords ))
            color = color.multiplication(emission + attenuation); 
        else
            return color.multiplication(emission);

        container = scene.intersection(currRay, 0.001, MAX_FLOAT);
        ++depth;
    }

    // float t = 0.5 * (currRay.getDirection().y() + 1);
    // return color.multiplication((1 - t ) * Vec3{1, 1, 1} + t * Vec3{0.5, 0.7, 1.});
    return {0, 0, 0};
}

pixel_vector raytracing(Scene &scene, const Vec3 &origin){
    // Random scene camera.
    //Vec3 lookFrom{13, 2, 3}, lookAt{0, 0, 0};
    // Cornell box camera.
    Vec3 lookFrom{278, 278, -800}, lookAt{278, 278, 0};
    float focus = 10, aperture = 0, vfov = 40;
    const size_t height = scene.getHeight(), width = scene.getWidth();
    Camera cam{lookFrom, lookAt, {0, 1, 0}, vfov, width / float(height), aperture, focus, 0, 1};
    pixel_vector pixels(height * width);

    // pixels.reserve(height * width * 3);

    #pragma omp parallel for
    for(size_t j = height; j > 0; --j){
        for(size_t i = 0 ; i < width; ++i){
            Vec3 finalColor; 
            // Anti aliasing.
            for(size_t k = 0; k < SAMPLES; ++k){
                float u = ((float)i + drand48()) / width, v = ((float)j + drand48()) / height;

                finalColor += color(cam.get_ray(u, v), scene);
            }

            finalColor /= SAMPLES;
            finalColor = finalColor.map([](float n){return sqrt(n);});
            finalColor *= 255.99;

            pixels[(height - j) * width + i] = finalColor;
            // pixels.push_back(finalColor.x()); pixels.push_back(finalColor.y()); pixels.push_back(finalColor.z());
        }
    }

    return pixels;
}

// Use a ppm files to rended the scenes.
void draw(const Scene &scene, const pixel_vector &pixels){
    // Write on the file.
    ofstream image(FILES_DIR + scene.getName() + ".ppm", ios::out | ios::trunc);
    image << "P3\n" << scene.getWidth() << ' ' << scene.getHeight() << ' ' << "255\n";

    // image.write(pixels.data(), pixels.size());
    for(auto pix : pixels)
        image << short(pix.x()) << ' ' << short(pix.y()) << ' ' << short(pix.z()) << '\n';
    image.close();
}