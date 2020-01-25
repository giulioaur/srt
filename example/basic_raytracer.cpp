#include "../src/srt/srt.h"

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <limits>

#include "../src/srt/paths.h"
#include "scene_builder.hpp"
#include "../src/srt/Ray.hpp"
#include "../src/srt/Camera.hpp"
#include "../src/srt/utility/Stopwatch.hpp"
#include "../src/srt/geometry/shapes/MovingSphere.hpp"
#include "../src/srt/textures/StaticTexture.hpp"
#include "../src/srt/textures/CheckerTexture.hpp"
#include "../src/srt/textures/ImageTexture.hpp"

using namespace std;
using namespace srt;
using namespace srt::geometry;
using namespace srt::geometry::shapes;
using namespace srt::utility;


/**************************************** DEFINE ****************************************/
#define RANDOM_SCENE 0
#define CORNELL_SCENE 1
#define MY_RANDOM_SCENE 2
#define BVH_SCENE 3

#define TARGET_SCENE CORNELL_SCENE

#define SAMPLES 100
#define MAX_DEPTH 50

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

        #if TARGET_SCENE == RANDOM_SCENE
        // Random scene.
        Scene scene = random_scene(512, 384);
        #elif TARGET_SCENE == CORNELL_SCENE
        // Cornell box.
        Scene scene = cornell_box(580, 720);
        #elif TARGET_SCENE == MY_RANDOM_SCENE
        // My random scene.
        Scene scene = my_random_scene(512, 384, 1000);
        #elif TARGET_SCENE == BVH_SCENE
        // BVH scene.
        Scene scene = BVH_scene(512, 384);
        #endif

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

    return 0;
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

        if(depth++ < MAX_DEPTH && material->scatter(currRay, attenuation, container.point, 
                                            container.normal, 
                                            texturesCoords ))
            color = color.multiplication(emission + attenuation); 
        else
            return color.multiplication(emission);

        container = scene.intersection(currRay, 0.001, MAX_FLOAT);
    }


    #if TARGET_SCENE == CORNELL_SCENE
    return {0, 0, 0};
    #else
    float t = 0.5 * (currRay.getDirection().y() + 1);
    return color.multiplication((1 - t ) * Vec3{1, 1, 1} + t * Vec3{0.5, 0.7, 1.});
    #endif
}

pixel_vector raytracing(Scene &scene, const Vec3 &origin){
    #if TARGET_SCENE == RANDOM_SCENE
    // Random scene camera.
    Vec3 lookFrom{13, 2, 3}, lookAt{0, 0, 0};
    #elif TARGET_SCENE == CORNELL_SCENE
    // Cornell box camera.
    Vec3 lookFrom{278, 278, -800}, lookAt{278, 278, 0};
    #elif TARGET_SCENE == MY_RANDOM_SCENE
    // My random scene camera.
    Vec3 lookFrom{560, 850, -1050}, lookAt{560, 250, 0};
    #elif TARGET_SCENE == BVH_SCENE
    // My random scene camera.
    Vec3 lookFrom{0, 150, -600}, lookAt{0, 100, 0};
    #endif
    
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
                float u = ((float)i + rand_float()) / width, v = ((float)j + rand_float()) / height;

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