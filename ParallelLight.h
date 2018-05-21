//
// Created by chris on 06.06.17.
//

#ifndef RAYTRACER_PARALLELLIGHT_H
#define RAYTRACER_PARALLELLIGHT_H


#include "Light.h"
#include "glm/vec4.hpp"
#include "glm/geometric.hpp"

class ParallelLight: public Light {
    glm::vec4 direction;

public:

    ParallelLight() {
        direction=glm::normalize(glm::vec4{-1.0f,-1.0f,0.3f,1.0f});
    }

    ParallelLight(const glm::vec4 &direction) : direction(direction) {}

    ParallelLight(Color color, glm::vec4 dir);


    Color diffuse(glm::vec3, std::shared_ptr<Obj>);
};


#endif //RAYTRACER_PARALLELLIGHT_H
