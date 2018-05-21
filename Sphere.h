//
// Created by chris on 26.05.17.
//

#ifndef RAYTRACER_SPHERE_H
#define RAYTRACER_SPHERE_H


#include <ostream>
#include "Obj.h"
#include "ray.h"


class Sphere: public Obj {
    double radius;


    public:
    Sphere();
    Sphere(glm::vec4 pos,int radius,Material m);
    Sphere(glm::vec4 pos,int radius);
    glm::vec3* intersect(std::shared_ptr<Ray> ray);
    glm::vec4 getNormal(glm::vec3 point);

    friend std::ostream &operator<<(std::ostream &os, const Sphere &sphere);


};



#endif //RAYTRACER_SPHERE_H
