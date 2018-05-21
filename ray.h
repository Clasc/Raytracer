//
// Created by chris on 18.05.17.
//

#ifndef RAYTRACER_RAY_H
#define RAYTRACER_RAY_H


#include <vector>
#include <ostream>
#include "glm/vec3.hpp"
#include "glm/geometric.hpp"
#include "Color.h"
#include "Obj.h"
#include "Light.h"
#include <memory>

class Light;
class Obj;

class Ray {
    glm::vec4 start;
    glm::vec4 direction;

public:
    Ray();
    Ray(glm::vec4, glm::vec4);
    bool cast(Color&,std::vector<std::shared_ptr<Obj>>, std::vector<std::shared_ptr<Light>>);

    const glm::vec4 &getOrigin() const;

    const glm::vec4 &getDirection() const;

    friend std::ostream &operator<<(std::ostream &os, const Ray &ray);
};


#endif //RAYTRACER_RAY_H
