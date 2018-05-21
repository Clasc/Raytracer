//
// Created by chris on 26.05.17.
//

#ifndef RAYTRACER_MESH_H
#define RAYTRACER_MESH_H

#include <string>
#include "Obj.h"
#include "ray.h"

class Mesh : public Obj {
    std::string objFile;

    using Obj::Obj;
public:
    Mesh();
    bool intersection(Ray ray);
};


#endif //RAYTRACER_MESH_H
