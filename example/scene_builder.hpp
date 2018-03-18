#include <vector>
#include <memory>
#include "../src/srt/Scene.hpp"
#include "../src/srt/geometry/shapes/AARectangle.hpp"
#include "../src/srt/geometry/shapes/Sphere.hpp"
#include "../src/srt/geometry/shapes/MovingSphere.hpp"
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
using namespace srt::textures;
using namespace srt::materials;
using namespace srt::materials::lights;

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

    // Left wall.
    objects.push_back(make_shared<AARectangle>(AARectangle::YZ, 0, 555, 0, 555, 555, make_shared<Lambertian>(make_shared<StaticTexture>(Vec3{0.12, 0.45, 0.15})), true));
    // Right wall.
    objects.push_back(make_shared<AARectangle>(AARectangle::YZ, 0, 555, 0, 555, 0, make_shared<Lambertian>(make_shared<StaticTexture>(Vec3{0.65, 0.05, 0.05}))));
    // Front wall.
    objects.push_back(make_shared<AARectangle>(AARectangle::XY, 0, 555, 0, 555, 555, make_shared<Lambertian>(make_shared<StaticTexture>(Vec3{0.73, 0.73, 0.73})), true));
    // Roof.
    objects.push_back(make_shared<AARectangle>(AARectangle::XZ, 0, 555, 0, 555, 555, make_shared<Lambertian>(make_shared<StaticTexture>(Vec3{0.73, 0.73, 0.73})), true));
    // Floor.
    objects.push_back(make_shared<AARectangle>(AARectangle::XZ, 0, 555, 0, 555, 0, make_shared<Lambertian>(make_shared<StaticTexture>(Vec3{0.73, 0.73, 0.73}))));
    // Light.
    objects.push_back(make_shared<AARectangle>(AARectangle::XZ, 213, 343, 227, 332, 554, make_shared<DiffuseLight>(make_shared<StaticTexture>(Vec3{15, 15, 15})), true));

    scene.addHitables(objects);
    scene.buildBVH();
    return scene;
}