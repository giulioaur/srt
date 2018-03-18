#include "json.hpp"
#include "../src/srt/Scene.hpp" 
#include "../src/srt/geometry/shapes/Circle.hpp"
#include "../src/srt/geometry/shapes/Sphere.hpp"
#include "../src/srt/geometry/shapes/Rectangle.hpp"
#include "../src/srt/textures/StaticTexture.hpp"
#include "../src/srt/materials/Lambertian.hpp"
#include "../src/srt/materials/Metal.hpp"
#include "../src/srt/materials/Dielectric.hpp"
#include "../src/srt/materials/lights/DiffuseLight.hpp"


using namespace std;
using json = nlohmann::json;
using namespace srt;
using namespace srt::geometry;
using namespace srt::geometry::shapes;
using namespace srt::illumination::lights;
using namespace srt::textures;
using namespace srt::materials;
using namespace srt::materials::lights;

Scene build_scenes(const string &file);
shared_ptr<Hitable> parse_shape(const json::value_type &shapeToParse);
// shared_ptr<Light> parse_light(const json::value_type &lightToParse);
shared_ptr<Material> parse_material(const json::value_type &materialToParse);

Scene build_scenes(const string &file){
    ifstream sceneFile(file);
    json scene;
    sceneFile >> scene;

    // Create the scenes.
    const float height = scene["height"], width = scene["width"];
    const string filename = file.substr(file.find_last_of('/') + 1);
    Scene currScene{height, width, filename.substr(0, filename.find_last_of('.'))};
    vector<shared_ptr<Hitable>> shapesVec;
    vector<shared_ptr<Light>> lightsVec;
    auto walls = scene["walls"];
    auto shapes = scene["shapes"];
    auto lights = scene["lights"];

    // Set number of photons.
    //currScene.setPhotonToShot(scene["photons"]);

    // Add walls.
    for(size_t j = 0; j < walls.size(); ++j){
        vector<float> normal = walls[j]["normal"], point = walls[j]["point"], color = walls[j]["color"];
        // shapesVec.push_back(shared_ptr<Hitable>{new Rectangle({Vec3{normal}, Vec3{point}}, Vec3{color})});
    }

    // Add the shapes to the scene.
    for(size_t j = 0; j < shapes.size(); ++j)
        shapesVec.push_back(parse_shape(shapes[j]));

    // // Add the lights to the scene.
    // for(size_t j = 0; j < lights.size(); ++j)
    //     lightsVec.push_back(parse_light(lights[j]));

    // currScene.addLights(lightsVec);
    currScene.addHitables(shapesVec);

    // Create the bvh.
    currScene.buildBVH();

    return currScene; 
}

shared_ptr<Hitable> parse_shape(const json::value_type &shapeToParse){
    shared_ptr<Hitable> shape;
    const string type = shapeToParse["type"];

    if(type == "circle"){
        vector<float> center = shapeToParse["center"], plane = shapeToParse["plane"];
        // shape = shared_ptr<Hitable>{new Circle(Vec3{center}, shapeToParse["ray"], Vec3{plane}, Vec3{color})};
    }
    else if(type == "sphere"){
        vector<float> center = shapeToParse["center"];
        shape = shared_ptr<Hitable>{new Sphere(Vec3{center}, shapeToParse["ray"], parse_material(shapeToParse["material"]))};
    }
    else if(type == "rectangle"){
        vector<float> a = shapeToParse["a"], b = shapeToParse["b"], c = shapeToParse["c"],
                        d = shapeToParse["d"];
        // shape = shared_ptr<Hitable>{new Rectangle(Vec3{a}, Vec3{b}, Vec3{c}, Vec3{d}, Vec3{color})};
    }
    else
        throw std::domain_error("The type of the shape " + type + " cannot be found");

    return shape;
}


// shared_ptr<Light> parse_light(const json::value_type &lightToParse){
//     shared_ptr<Light> light;
//     const vector<float> position = lightToParse["position"], color = lightToParse["color"];
//     const shared_ptr<Hitable> shape = parse_shape(lightToParse["shape"]); 
//     const string type = lightToParse["type"];

//     if(type == "point")
//         light = shared_ptr<Light>{new Light(shape, position, color)};
//     else if(type == "spotlight"){
//         const vector<float> dir = lightToParse["direction"];
//         const float cutOff = lightToParse["cutOff"];
//         light = shared_ptr<Light>{new Spotlight(shape, Vec3{position}, Vec3{dir}, cutOff, color)};
//     }

//     return light;
// }


shared_ptr<Material> parse_material(const json::value_type &materialToParse){
    shared_ptr<Material> material;
    const string type = materialToParse["type"];

    if(type == "lambertian"){
        vector<float> albedo = materialToParse["albedo"];
        material = shared_ptr<Material>(new Lambertian{shared_ptr<Texture>{new StaticTexture{albedo}}});
    }
    else if(type == "metal"){
        vector<float> albedo = materialToParse["albedo"];
        material = shared_ptr<Material>(new Metal{Vec3{albedo}, materialToParse["fuziness"]});
    }
    else if(type == "dielectric"){
        float refractivity = materialToParse["refractivity"];
        material = shared_ptr<Material>(new Dielectric{refractivity});
    }

    return material;
}