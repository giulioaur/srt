#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <limits>
#include "../src/srt/paths.h"
#include "parse_scene.hpp"
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

/**************************************** TYPEDEF ****************************************/

typedef vector<Vec3> pixel_vector;

/**************************************** HEADER ****************************************/

Scene random_scene();
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

        // Test scene.
        Scene scene{400, 400, "image_test"};
        scene.addHitables({make_shared<Sphere>(Vec3{0, 0, 0}, 2, make_shared<Lambertian>(make_shared<ImageTexture>(FILES_DIR + "textures/earth.jpg")))});
        scene.buildBVH();

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

Scene random_scene(){ 
    Scene scene{400, 800, "result"};
    int n = 500;
    vector<shared_ptr<Hitable>> spheres;
    spheres.reserve(n+1);
    spheres.push_back(make_shared<Sphere>(Vec3{0,-1000,0}, 1000, make_shared<Lambertian>(make_shared<CheckerTexture>())));

    for (short a = -11; a < 11; a++) {
        for (short b = -11; b < 11; b++) {
            float choose_mat = drand48();
            Vec3 center{a+0.9*drand48(),0.2,b+0.9*drand48()}; 
            if ((center-Vec3(4,0.2,0)).length() > 0.9) { 
                shared_ptr<Material> material;
                if (choose_mat < 0.8) {         // Diffuse 
                    material = make_shared<Lambertian>(make_shared<StaticTexture>(Vec3{drand48()*drand48(), drand48()*drand48(), drand48()*drand48()}));
                }
                else if (choose_mat < 0.95) {   // Metal
                    material = make_shared<Metal>(Vec3{0.5*(1 + drand48()), 0.5*(1 + drand48()), 0.5*(1 + drand48())},  0.5*drand48());
                }
                else {                          // Glass
                    material = make_shared<Dielectric>(1.5);
                }

                if(false && choose_mat < 0.8)
                    spheres.push_back(make_shared<MovingSphere>(center, center.multiplication(Vec3{1, 0.5 * drand48(), 1}), 0, 1, 0.2, material));
                else
                    spheres.push_back(make_shared<Sphere>(center, 0.2, material));
            }
        }
    }

    spheres.push_back(make_shared<Sphere>(Vec3{0, 1, 0}, 1.0, make_shared<Dielectric>(1.5)));
    spheres.push_back(make_shared<Sphere>(Vec3{-4, 1, 0}, 1.0, make_shared<Lambertian>(make_shared<StaticTexture>(Vec3{0.4, 0.2, 0.1}))));
    spheres.push_back(make_shared<Sphere>(Vec3{4, 1, 0}, 1.0, make_shared<Metal>(Vec3{0.7, 0.6, 0.5}, 0.0)));

    scene.addHitables(spheres);
    scene.buildBVH();
    return scene;
}

Vec3 color(const Ray &ray, const Scene &scene){
    int isLight;
    Ray currRay{ray};
    size_t depth = 0;
    Vec3 totAtt = {1, 1, 1}, currAtt;
    Hitable::hit_record container = scene.intersection(currRay, 0.001, MAX_FLOAT, isLight); 
    
    // Compute the attenuation factor of the bouncing ray.
    while(container.hitted){
        if(depth < 50 && container.object->scatter(currRay, currAtt, currRay.getPoint(container.t)))
            totAtt = totAtt.multiplication(currAtt); 
        else
            return {0, 0, 0};

        container = scene.intersection(currRay, 0.001, MAX_FLOAT, isLight);
        ++depth;
    }

    float t = 0.5 * (currRay.getDirection().y() + 1);
    return totAtt.multiplication((1 - t ) * Vec3{1, 1, 1} + t * Vec3{0.5, 0.7, 1.});
}

pixel_vector raytracing(Scene &scene, const Vec3 &origin){
    Vec3 lookFrom{13, 2, 3}, lookAt{0, 0, 0};
    float focus = 10, aperture = 0;
    const size_t height = scene.getHeight(), width = scene.getWidth();
    Camera cam{lookFrom, lookAt, {0, 1, 0}, 20, width / (float)height, aperture, focus, 0, 1};
    pixel_vector pixels(height * width);
    size_t sample = 100; 

    // pixels.reserve(height * width * 3);

    #pragma omp parallel for
    for(size_t j = height; j > 0; --j){
        for(size_t i = 0 ; i < width; ++i){
            Vec3 finalColor;
            // Anti aliasing.
            for(size_t k = 0; k < sample; ++k){
                float u = ((float)i + drand48()) / width, v = ((float)j + drand48()) / height;

                finalColor += color(cam.get_ray(u, v), scene);
            }

            finalColor /= sample;
            finalColor = finalColor.map([](float n){return sqrt(n);});
            finalColor *= 255.99;
            finalColor.makeInteger();
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
        image << pix.x() << ' ' << pix.y() << ' ' << pix.z() << '\n';
    image.close();
}