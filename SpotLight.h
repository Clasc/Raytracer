//
// Created by chris on 06.06.17.
//

#ifndef RAYTRACER_SPOTLIGHT_H
#define RAYTRACER_SPOTLIGHT_H


#include "Light.h"
#include "PointLight.h"
#include "glm/vec2.hpp"
#include "glm/geometric.hpp"

class SpotLight: public PointLight {
    glm::vec4 direction;
    glm::vec2 falloff;


public:
    SpotLight(const Color &color, const glm::vec4 &pos, const glm::vec4 &direction, const glm::vec2 &falloff)
            : PointLight(color, pos), direction(direction), falloff(falloff) {}


    SpotLight(){
        direction=glm::normalize(glm::vec4(-1.0f,-1.0f,0.3f,1.0f));
        falloff={1.0f,1.0f};
    }
};


#endif //RAYTRACER_SPOTLIGHT_H
