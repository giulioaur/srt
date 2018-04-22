#include <cmath>

using namespace srt::geometry;
using namespace srt::geometry::shapes;
using namespace std;

/**************************************** HEADER ****************************************/

void shot_photons(PMScene &scene);
Vec3 phong_model(const PMScene &scene, const Shape &shape, const Vec3 &hitPoint);
Vec3 gather_photons(const PMScene &scene, const Shape &shape, const Vec3 &hitPoint);

/**************************************** CONST ****************************************/

const size_t MAX_PHOTON_BOUNCES = 3;

/**************************************** FUNCTIONS ****************************************/

void shot_photons(PMScene &scene){
    auto randomDir = [](){
        return Vec3{
            1 - static_cast <float> (rand()) / static_cast <float> (RAND_MAX/2),
            1 - static_cast <float> (rand()) / static_cast <float> (RAND_MAX/2),
            1 - static_cast <float> (rand()) / static_cast <float> (RAND_MAX/2)
        }.normalize();
    };
    auto lights = scene.getLights();
    size_t photonPerLight = scene.getPhotonToShot() / lights.size();

    // For each light, fire a bunch of photons.
    for(auto light : lights){
        Vec3 basicColor = light->getColor();

        for(size_t i = 0; i < photonPerLight; ++i){
            Vec3 photonColor = basicColor, photonStart = light->getPosition();
            // The photon is fired in a random direction that is illuminated by that light.
            Vec3 photonDir = randomDir();
            if(!light->illuminate(photonDir))   photonDir = -photonDir;
            size_t currBounce = 0;
            int hitLight;

            // Check if the photon intersect something.
            auto hitObj = scene.intersection({photonStart, photonDir}, hitLight);

            while (hitObj != nullptr && ++currBounce <= MAX_PHOTON_BOUNCES){
                const float destiny = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
                photonStart = *hitObj->intersection({photonStart, photonDir}); // The new start point is the intersection one.
                photonColor = photonColor.multiplication( 
                    1.f / currBounce * hitObj->getColor(photonStart)); 

                // Store the photon only if it came from indirect illumination.
                if(currBounce > 1)  
                    scene.storePhoton({photonStart, photonDir, photonColor});

                if(destiny <= 0.5){ // Absorbed.
                    hitObj = {};
                }
                else{ // Diffused
                    // Compute new random direction of reflection (Lambert's law)
                    photonDir = randomDir();
                    // Be sure the photon does not bounce behind the object.
                    if(hitObj->getNormal(photonStart) * photonDir < 0)   photonDir = -photonDir;
                    hitObj = scene.intersection({photonStart, photonDir}, hitLight);
                }
            }
        }
    }

}

Vec3 phong_model(const PMScene &scene, const Shape &shape, const Vec3 &hitPoint){
    Vec3 finalColor;
    Vec3 viewDir = (hitPoint - scene.getEyesPos()).normalize();

    // For each light compute the three components of the Phong model.
    auto lights = scene.getLights();
    for(auto light = lights.begin(); light < lights.end(); ++light){
        int app;
        Vec3 lightPos = (*light)->getPosition(), 
             lightDir = (hitPoint - lightPos).normalize();
        
        // If the light illuminate that point, use Phong model without ambient.
        if((*light)->illuminate(lightDir)){ 
            Vec3 lightColor = (*light)->getColor(),
            normal = shape.getNormal(hitPoint),
            reflectionDir = (lightDir - (normal * (lightDir * normal)) * 2).normalize(),
            diffuse = max(normal * -lightDir, 0.f) * lightColor,
            specular = 0.5 * pow(max(viewDir * reflectionDir, 0.f), 32) * lightColor;

            //If the light hits another points before the one considered, it is shadowed.
            const float distance = lightPos.distance(hitPoint);
            const bool isShadowed = scene.intersection({lightPos, lightDir}, app, *light, distance) != nullptr;
            const float shadowFactor = isShadowed ? 0.3 : 1;
            const float attenuation = (*light)->getAttenuation(distance);

            // Update color.
            Vec3 phongLight = diffuse + specular;
            Vec3 currColor = shape.getColor(hitPoint).multiplication(phongLight) * attenuation;
            //finalColor += currColor * shadowFactor;
        }
        else // Else use only ambient color.
            finalColor = shape.getColor(hitPoint) * 0.1;
        
    }

    finalColor.clamp(0, 1);
    finalColor = finalColor * 255;
    finalColor.makeInteger();
    return finalColor;
}


Vec3 gather_photons(const PMScene &scene, const Shape &shape, const Vec3 &hitPoint){
    const float maxDist = 5;
    auto photons = scene.gatherPhotons(hitPoint, {shape.getNormal(hitPoint), hitPoint}, maxDist);
    Vec3 finalColor;

    for(auto photon : *photons){
        finalColor += (-photon->getDirection() * shape.getNormal(hitPoint)) * 
            shape.getColor(hitPoint).multiplication(photon->getColor());
    }

    // *finalColor = finalColor->multiplication(*shape.getColor(hitPoint));
    finalColor *= 255;
    finalColor.makeInteger();
    return finalColor;
}