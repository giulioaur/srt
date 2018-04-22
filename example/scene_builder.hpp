#include <vector>
#include <memory>
#include "../src/srt/Scene.hpp"
#include "../src/srt/geometry/shapes/Sphere.hpp"
#include "../src/srt/geometry/shapes/MovingSphere.hpp"
#include "../src/srt/geometry/shapes/AARectangle.hpp"
#include "../src/srt/geometry/shapes/AABox.hpp"
#include "../src/srt/geometry/instances/Translation.hpp"
#include "../src/srt/geometry/instances/Rotation.hpp"
#include "../src/srt/textures/StaticTexture.hpp"
#include "../src/srt/textures/CheckerTexture.hpp"
#include "../src/srt/materials/Lambertian.hpp"
#include "../src/srt/materials/Metal.hpp"
#include "../src/srt/materials/Dielectric.hpp"
#include "../src/srt/materials/lights/DiffuseLight.hpp"

using namespace std;
using namespace srt;
using namespace srt::geometry;
using namespace srt::geometry::shapes;
using namespace srt::geometry::instances;
using namespace srt::textures;
using namespace srt::materials;
using namespace srt::materials::lights;
using namespace srt::ds;

Scene random_scene(const float width, const float height){
    Scene scene{width, height, "result"};
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

Scene my_random_scene(const float width, const float height, const size_t n, const float f = 0.1){
    Scene scene{width, height, "my_random_scene"};
    uint16_t length = 1250, side = sqrt(n);
    float radius = length / (side * 2), dradius = radius * 2;
    float angularFrequency = 2 * M_PI * f;
    vector<shared_ptr<Hitable>> objects;
    objects.reserve(side * side);

    for(size_t i = 0; i < side * side; ++i){
        // Choose an x to be sure the circles are not intersected.
        float x = i / side, z = i % side;
        Vec3 pos{x * dradius, sin( x * angularFrequency) * radius, z * dradius};
        shared_ptr<Material> material = make_shared<Lambertian>(make_shared<StaticTexture>(Vec3{1.f - (x / side), 0, 0 + (z / side)}));
        objects.push_back(make_shared<Sphere>(pos, radius, material));
    }

    // End scene.
    scene.addHitables(objects);
    scene.buildBVH();
    return scene;
}

Scene BVH_scene(const float width, const float height){
    Scene scene{width, height, "BVH_scene"};
    vector<shared_ptr<Hitable>> objects;

    // objects.push_back(make_shared<Sphere>(Vec3{0, 200, 200}, 200, make_shared<Dielectric>(1)));
    // objects.push_back(make_shared<Sphere>(Vec3{0, 100, 500}, 50, make_shared<Lambertian>(make_shared<StaticTexture>(Vec3{drand48()*drand48(), drand48()*drand48(), drand48()*drand48()}))));
    // objects.push_back(make_shared<Sphere>(Vec3{250, 100, 150}, 50, make_shared<Lambertian>(make_shared<StaticTexture>(Vec3{drand48()*drand48(), drand48()*drand48(), drand48()*drand48()}))));

    // objects.push_back(make_shared<AABox>(Vec3{-65, 0, 0}, Vec3{100, 165, 165}, make_shared<Lambertian>(make_shared<StaticTexture>(Vec3{drand48()*drand48(), drand48()*drand48(), drand48()*drand48()}))));
    // objects.push_back(make_shared<AABox>(Vec3{-65, 0, 166}, Vec3{100, 215, 331}, make_shared<Lambertian>(make_shared<StaticTexture>(Vec3{drand48()*drand48(), drand48()*drand48(), drand48()*drand48()}))));
    // objects.push_back(make_shared<AABox>(Vec3{-350, 100, 150}, Vec3{-250, 165, 305}, make_shared<Lambertian>(make_shared<StaticTexture>(Vec3{drand48()*drand48(), drand48()*drand48(), drand48()*drand48()}))));
    // objects.push_back(make_shared<AABox>(Vec3{250, 200, 300}, Vec3{425, 295, 465}, make_shared<Lambertian>(make_shared<StaticTexture>(Vec3{drand48()*drand48(), drand48()*drand48(), drand48()*drand48()}))));
    // objects.push_back(make_shared<AABox>(Vec3{-300, -100, 50}, Vec3{300, -50, 105}, make_shared<Lambertian>(make_shared<StaticTexture>(Vec3{drand48()*drand48(), drand48()*drand48(), drand48()*drand48()}))));
    
    objects.push_back(make_shared<Sphere>(Vec3{0, 100, 500}, 50, make_shared<Lambertian>(make_shared<StaticTexture>(Vec3{drand48()*drand48(), drand48()*drand48(), drand48()*drand48()}))));
    objects.push_back(make_shared<Sphere>(Vec3{200, 175, 350}, 30, make_shared<Lambertian>(make_shared<StaticTexture>(Vec3{drand48()*drand48(), drand48()*drand48(), drand48()*drand48()}))));
    objects.push_back(make_shared<Sphere>(Vec3{-200, 200, 100}, 50, make_shared<Lambertian>(make_shared<StaticTexture>(Vec3{drand48()*drand48(), drand48()*drand48(), drand48()*drand48()}))));
    objects.push_back(make_shared<Sphere>(Vec3{150, -30, 50}, 40, make_shared<Lambertian>(make_shared<StaticTexture>(Vec3{drand48()*drand48(), drand48()*drand48(), drand48()*drand48()}))));
    objects.push_back(make_shared<Sphere>(Vec3{-180, -15, 250}, 70, make_shared<Lambertian>(make_shared<StaticTexture>(Vec3{drand48()*drand48(), drand48()*drand48(), drand48()*drand48()}))));
    objects.push_back(make_shared<Sphere>(Vec3{-30, -150, 50}, 20, make_shared<Lambertian>(make_shared<StaticTexture>(Vec3{drand48()*drand48(), drand48()*drand48(), drand48()*drand48()}))));
    objects.push_back(make_shared<Sphere>(Vec3{-180, -15, 550}, 105, make_shared<Lambertian>(make_shared<StaticTexture>(Vec3{drand48()*drand48(), drand48()*drand48(), drand48()*drand48()}))));
    objects.push_back(make_shared<Sphere>(Vec3{80, 15, 50}, 40, make_shared<Lambertian>(make_shared<StaticTexture>(Vec3{drand48()*drand48(), drand48()*drand48(), drand48()*drand48()}))));

    BVH tempTree{objects, 0, 1};
    vector<shared_ptr<Hitable>> bvhSquares = tempTree.draw();
    objects.insert(objects.end(), bvhSquares.begin(), bvhSquares.end());

    // End scene.
    scene.addHitables(objects);
    scene.buildBVH();
    return scene;
}

Scene light_scene(const float width, const float height){
    Scene scene{width, height, "test_light"};
    vector<shared_ptr<Hitable>> objects;

    objects.push_back(make_shared<Sphere>(Vec3{0,-1000,0}, 1000, make_shared<Lambertian>(make_shared<CheckerTexture>())));
    objects.push_back(make_shared<Sphere>(Vec3{0, 2,0}, 2, make_shared<Lambertian>(make_shared<CheckerTexture>())));
    objects.push_back(make_shared<Sphere>(Vec3{0, 7,0}, 2, make_shared<DiffuseLight>(make_shared<StaticTexture>(Vec3{4, 4, 4}))));
    objects.push_back(make_shared<AARectangle>(AARectangle::XY, 3, 5, 1, 3, -1, make_shared<DiffuseLight>(make_shared<StaticTexture>(Vec3{4, 4, 4}))));

    scene.addHitables(objects);
    scene.buildBVH();
    return scene;
}

Scene cornell_box(const float width, const float height){
    Scene scene{width, height, "cornell_box"};
    vector<shared_ptr<Hitable>> objects;
    auto white = make_shared<Lambertian>(make_shared<StaticTexture>(Vec3{0.73, 0.73, 0.73}));

    // Right wall.
    objects.push_back(make_shared<AARectangle>(AARectangle::YZ, 0, 555, 0, 555, 555, make_shared<Lambertian>(make_shared<StaticTexture>(Vec3{0.65, 0.05, 0.05})), true));
    // Left wall.
    objects.push_back(make_shared<AARectangle>(AARectangle::YZ, 0, 555, 0, 555, 0, make_shared<Lambertian>(make_shared<StaticTexture>(Vec3{0.12, 0.45, 0.15}))));
    // Front wall.
    objects.push_back(make_shared<AARectangle>(AARectangle::XY, 0, 555, 0, 555, 555, white, true));
    // Roof.
    objects.push_back(make_shared<AARectangle>(AARectangle::XZ, 0, 555, 0, 555, 555, white, true));
    // Floor.
    objects.push_back(make_shared<AARectangle>(AARectangle::XZ, 0, 555, 0, 555, 0, white));
    // Light.
    objects.push_back(make_shared<AARectangle>(AARectangle::XZ, 213, 343, 227, 332, 554, make_shared<DiffuseLight>(make_shared<StaticTexture>(Vec3{15, 15, 15})), true));
    // Box1.
    objects.push_back(make_shared<Translation>(make_shared<Rotation>(Rotation::pitch, make_shared<AABox>(Vec3{0, 0, 0}, Vec3{165, 165, 165}, white), 18), Vec3{265, 0, 65}));
    // objects.push_back(make_shared<Rotation>(Rotation::pitch, make_shared<AARectangle>( AARectangle::YZ, 0, 165, 0, 165, 165, white, true), -18));
    // Box2.
    objects.push_back(make_shared<Translation>(make_shared<Rotation>(Rotation::pitch, make_shared<AABox>(Vec3{0, 0, 0}, Vec3{165, 330, 165}, white), -15), Vec3{130, 0, 295}));

    scene.addHitables(objects);
    scene.buildBVH();
    return scene;
}