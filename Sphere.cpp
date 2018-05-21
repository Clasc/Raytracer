//
// Created by chris on 26.05.17.
//

#include "Sphere.h"




Sphere::Sphere(glm::vec4 pos, int radius): Obj(pos){
    this->radius = radius;
}

Sphere::Sphere(glm::vec4 pos, int radius, Material m) : Obj(pos,m) {
    this->radius = radius;
}

Sphere::Sphere():Obj() {
    this->radius = 1;
}

glm::vec3* Sphere::intersect(std::shared_ptr<Ray> ray) {

    glm::vec4 origin = ray->getOrigin();
    glm::vec4 direction = ray->getDirection();

    glm::normalize(direction);
    glm::vec4 op = origin - position;
    float dotOp = dot(op,op);


    float b = 2.f * (dot(direction, op));
    float c = dotOp - radius * radius;

    float a = dot(direction, direction);

    float discriminant = b * b - 4  *  a * c ;
    if(discriminant < 0){
        return nullptr;
        }

    double t = (-0.5f) * (b + discriminant) / a;

    glm::vec3 d = glm::vec3 (ray->getDirection());
    glm::vec3 o= glm::vec3 (ray->getOrigin());
    if (t > 0.0f) {
        glm::vec3* hitpoint =  new glm::vec3(o.x + d.x * t, o.y + d.y * t, o.z + d.z * t);
        return hitpoint;
    }
    else
    return nullptr;

}

glm::vec4 Sphere::getNormal(glm::vec3 point) {
   glm::vec4 normal((point.x - position.x) /radius, (point.y - position.y) /radius, (point.z - position.z) /radius, 1.0f);
    return glm::normalize(normal);
}

std::ostream &operator<<(std::ostream &os, const Sphere &sphere) {
    os << "Material:"<<sphere.material<<"Position: "<<sphere.position.x<<" "<<sphere.position.y<<" "<<sphere.position.z<<std::endl<<" radius: " << sphere.radius<<std::endl;
    return os;
}

