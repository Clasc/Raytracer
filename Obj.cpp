//
// Created by chris on 24.05.17.
//

#include "Obj.h"
Obj::Obj() {
    position=glm::vec4(0.0f,0.0f,-4.0f,1.0f);
    Material m;
    material=m;
}

const Material &Obj::getMaterial() const {
    return material;
}

Obj::Obj(glm::vec4 pos) {
    position=pos;
    Material m;
    material=m;
}

Obj::Obj(glm::vec4 pos, Material m) {
    position=pos;
    material=m;
}

std::ostream& Obj::operator<<(std::ostream &os) {
    os<<"Object: {"<<std::endl<<"Material:"<<this->material<<"Position: "<<this->position.x<<" "<<this->position.y<<" "<<this->position.z<<std::endl;
    return os;
}

const glm::vec4 &Obj::getPosition() const {
    return position;
}


double Obj::dot(glm::vec4 left, glm::vec4 right){
    return left.x * right.x + left.y * right.y + left.z * right.z;
}