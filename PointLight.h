//
// Created by chris on 06.06.17.
//

#ifndef RAYTRACER_POINTLIGHT_H
#define RAYTRACER_POINTLIGHT_H


#include "Light.h"
#include "glm/vec4.hpp"

class PointLight : public Light {
protected:
    glm::vec4 position;

public:
    PointLight(){
        position={1.0f,1.0f,1.0f,1.0f};
    }

    PointLight(Color color, glm::vec4 pos){
        this->color=color;
        position=pos;
    }

};


#endif //RAYTRACER_POINTLIGHT_H
