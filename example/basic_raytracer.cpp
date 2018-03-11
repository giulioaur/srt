#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <limits>
#include "../src/srt/paths.h"
#include "parse_scene.hpp"
// #include "raytracer.hpp"
#include "../src/srt/Ray.hpp"
#include "../src/srt/Camera.hpp"
#include "../src/srt/utility/Stopwatch.hpp"
#include "../src/srt/utility/Logger.hpp"
#include "../src/srt/utility/FileManager.hpp"
#include "../src/srt/geometry/shapes/MovingSphere.hpp"

using namespace std;
using namespace srt;
using namespace srt::geometry;
using namespace srt::geometry::shapes;
using namespace srt::illumination::lights;
using namespace srt::utility;

/**************************************** HEADER ****************************************/

Scene random_scene();
vector<Vec3> raytracing(Scene &scene, const Vec3 &origin = {0, 0, 0});
void draw(const Scene &scene, const vector<Vec3> &pixels);

/**************************************** GLOBAL ****************************************/

const Vec3 BASE_COLOR{170, 170, 170};
const float MAX_FLOAT = std::numeric_limits<float>::max();

/**************************************** MAIN ****************************************/

int main(int argc, char **argv){
    srand(static_cast <unsigned> (time(0))); // Init random seed.
    Stopwatch sw;

    cout << "Starting ray tracer..." << endl;

    // Build up the scene.
    auto files = FileManager::getFiles(FILES_DIR + "scenes/");

    for(size_t i = 0; i < 1; ++i){        
        // Parse the scene and shot photons.
        // PMScene scene{100, 200, "test"};
        // Scene scene = build_scenes(FILES_DIR + "scenes/" + files[i]);
        Scene scene = random_scene();
        //shot_photons(scene);

        // Compute color through raytracing.
        vector<Vec3> pixels = raytracing(scene);

        // Render the scene.
        draw(scene, pixels);
    }

    cout << "...Ending raytracer in " << sw.end() << "sec" << endl;
}


/**************************************** FUNCTIONS ****************************************/

Scene random_scene(){
    Scene scene{400, 800, "result"};
    int n = 500;
    vector<shared_ptr<Hitable>> spheres;
    spheres.reserve(n+1);
    spheres.push_back(shared_ptr<Hitable>{new Sphere({0,-1000,0}, 1000, shared_ptr<Material>{new Lambertian({0.5, 0.5, 0.5})})});

    for (short a = -11; a < 11; a++) {
        for (short b = -11; b < 11; b++) {
            float choose_mat = drand48();
            Vec3 center{a+0.9*drand48(),0.2,b+0.9*drand48()}; 
            if ((center-Vec3(4,0.2,0)).length() > 0.9) { 
                shared_ptr<Material> material;
                if (choose_mat < 0.8) {         // Diffuse
                    material = shared_ptr<Material>{new Lambertian{{drand48()*drand48(), drand48()*drand48(), drand48()*drand48()}}};
                }
                else if (choose_mat < 0.95) {   // Metal
                    material = shared_ptr<Material>{new Metal{{0.5*(1 + drand48()), 0.5*(1 + drand48()), 0.5*(1 + drand48())},  0.5*drand48()}};
                }
                else {                          // Glass
                    material = shared_ptr<Material>{new Dielectric{1.5}};
                }

                if(false && choose_mat < 0.8)
                    spheres.push_back(shared_ptr<Hitable>{new MovingSphere{center, center.multiplication(Vec3{1, 0.5 * drand48(), 1}), 0, 1, 0.2, material}});
                else
                    spheres.push_back(shared_ptr<Hitable>{new Sphere{center, 0.2, material}});
            }
        }
    }

    spheres.push_back(shared_ptr<Hitable>{new Sphere({0, 1, 0}, 1.0, shared_ptr<Material>{new Dielectric{1.5}})});
    spheres.push_back(shared_ptr<Hitable>{new Sphere({-4, 1, 0}, 1.0, shared_ptr<Material>{new Lambertian({0.4, 0.2, 0.1})})});
    spheres.push_back(shared_ptr<Hitable>{new Sphere({4, 1, 0}, 1.0, shared_ptr<Material>{new Metal({0.7, 0.6, 0.5}, 0.0)})});

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

vector<Vec3> raytracing(Scene &scene, const Vec3 &origin){
    Vec3 lookFrom{13, 2, 3}, lookAt{0, 0, 0};
    float focus = 10, aperture = 0;
    const size_t height = scene.getHeight(), width = scene.getWidth();
    Camera cam{lookFrom, lookAt, {0, 1, 0}, 20, width / (float)height, aperture, focus, 0, 1};
    vector<Vec3> pixels(height * width);
    size_t sample = 100; 

    // pixels.reserve(height * width);

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
        }
    }

    return pixels;
}

// Use a ppm files to rended the scenes.
void draw(const Scene &scene, const vector<Vec3> &pixels){
    // Write on the file.
    ofstream image(FILES_DIR + scene.getName() + ".ppm", ios::out | ios::trunc);
    image << "P3\n" << scene.getWidth() << ' ' << scene.getHeight() << ' ' << "255\n";

    //image.write(pixels.data(), pixels.size());
    for(auto pix : pixels)
        image << pix.x() << ' ' << pix.y() << ' ' << pix.z() << '\n';
    image.close();
}