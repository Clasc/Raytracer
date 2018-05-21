//
// Created by chris on 24.05.17.
//

#ifndef RAYTRACER_OBJ_H
#define RAYTRACER_OBJ_H


#include <initializer_list>
#include <ostream>
#include <memory>
#include "glm/vec4.hpp"
#include "Material.h"
#include "glm/detail/type_mat.hpp"
#include "glm/detail/type_mat4x4.hpp"
#include "ray.h"

class Ray;

class Obj {
protected:
    glm::vec4 position;
    Material material;
public:
    virtual  std::ostream &operator<<(std::ostream &os);

    Obj(glm::vec4 pos);
    Obj(glm::vec4 pos, Material m);
    Obj();

    const glm::vec4 &getPosition() const;

    virtual glm::vec3 * intersect(std::shared_ptr<Ray> ray) {
    }

    const Material &getMaterial() const;

    static double dot(glm::vec4, glm::vec4);

    virtual glm::vec4 getNormal(glm::vec3 point){return  glm::vec4(point, 1.f);}
};


#endif //RAYTRACER_OBJ_H
