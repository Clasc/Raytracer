//
// Created by chris on 18.05.17.
//

#include "ray.h"
#include <memory>

Ray::Ray() {
        start=glm::vec4(0.0f,0.0f,0.0f,1.0f);
        direction=glm::vec4(0.0f,0.0f,-1.0f,1.0f);

    }
Ray::Ray(glm::vec4 s, glm::vec4 d) {
    start=s;
    direction=glm::normalize(d);

}

bool Ray::cast(Color& c, std::vector<std::shared_ptr<Obj>> objects, std::vector<std::shared_ptr<Light>> lights) {
    bool intersected = false;
    for( auto e : objects) {
        glm::vec3* hitpoint = e->intersect(std::make_shared<Ray>(start, direction));
        if (hitpoint != nullptr) {
            //c = e->getMaterial().getColor();
            Color diffuseColor =  e->getMaterial().getColor();
            for(auto light : lights){
                diffuseColor = diffuseColor * light->diffuse(*hitpoint, e);
            }
            c =  diffuseColor;
            intersected = true;
        }
        delete hitpoint;
    }
    return intersected;
}

std::ostream &operator<<(std::ostream &os, const Ray &ray) {
    os << "Ray {"<<std::endl<<"start: " << ray.start.x <<" "<< ray.start.y << ray.start.z << " direction: " <<  ray.direction.x <<" "<< ray.direction.y << ray.direction.z<<std::endl<<"}"<<std::endl;
    return os;
}

const glm::vec4 &Ray::getOrigin() const {
    return start;
}

const glm::vec4 &Ray::getDirection() const {
    return direction;
}
