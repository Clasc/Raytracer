//
// Created by chris on 06.06.17.
//

#include "ParallelLight.h"
#include "Sphere.h"

ParallelLight::ParallelLight(Color color, glm::vec4 dir) {
    this->color=color;
    direction=glm::normalize(dir);
}

Color ParallelLight::diffuse(glm::vec3 hitpoint, std::shared_ptr<Obj> object) {
    glm::vec4 normal = object->getNormal(hitpoint);
    double diffuseFactor = Obj::dot(normal, -direction);
    Color result(diffuseFactor * 255, diffuseFactor * 255, diffuseFactor * 255);
    return result;
}