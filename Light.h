//
// Created by chris on 03.06.17.
//

#ifndef RAYTRACER_LIGHT_H
#define RAYTRACER_LIGHT_H


#include "Color.h"
#include "ray.h"
#include "Obj.h"

class Obj;

class Light {
protected:
    Color color;

public:
    Light(){
        color=Color();
    }

    Light(Color lightColor){
        color=lightColor;
    }


    virtual  Color diffuse(glm::vec3, std::shared_ptr<Obj>){}
};


#endif //RAYTRACER_LIGHT_H
