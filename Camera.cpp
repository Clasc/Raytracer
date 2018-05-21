//
// Created by chris on 21.05.17.
//

#include "Camera.h"
#include "glm/gtc/matrix_transform.hpp"

#include <math.h>
Camera::Camera() {
    lookat = glm::vec4(0.0f,0.0f,-1.0f,1.0f);
    position = glm::vec4(0.0f,0.0f,0.0f,1.0f);
    up = glm::normalize(glm::vec4(0.0f,1.0f,0.0f,0.0f));
    direction = glm::normalize(lookat-position);

    worldMatrix = glm::lookAt(glm::vec3(position),glm::vec3(lookat),glm::vec3(up));
    setFOV(1,1,45);
}

Camera::Camera(int width, int height) {

    position=glm::vec4(0.0f,0.0f,0.0f,1.0f);
    up=glm::vec4(0.0f,1.0f,0.0f,0.0f);
    lookat = glm::vec4(0.0f,0.0f,-1.0f,1.0f);
    direction=glm::normalize(lookat-position);
    worldMatrix = glm::lookAt(glm::vec3(position),glm::vec3(lookat),glm::vec3(up));
    setFOV(width,height,45);
}

Camera::Camera(glm::vec4 pos, glm::vec4 u, glm::vec4 look, int width, int height, double fov) {
    lookat=look;
    position=pos;
    up=glm::normalize(u);
    direction=glm::normalize(lookat-position);
    worldMatrix = glm::lookAt(glm::vec3(position) * -1.f,glm::vec3(lookat),glm::vec3(up));
    setFOV(width,height,fov);
}

Camera Camera::operator=(Camera c) {
    position=c.position;
    up=c.up;
    direction=c.direction;
    lookat=c.lookat;
    width=c.width;
    height=c.height;
    worldMatrix=c.worldMatrix;
    fovx=c.fovx;
    fovy=c.fovy;
}

Ray Camera::constructEyeRay(int x, int y) {
    double w = double(width);
    double h = double(height);
    double ratio = w / h;
    double planeHeight = tan(fovx * 1.4);

    double u=(2 * (x / w) - 1) * ratio * planeHeight;
    double v= (1 - (2 * (y / h))) * planeHeight;



    glm::vec4 raydirection = worldMatrix * glm::normalize(glm::vec4(u,v,-1.f,0.f) - position);
    Ray r(position,raydirection);
    return r;
}

std::ostream &operator<<(std::ostream &os, const Camera &camera) {
    os << "Camera {"<<std::endl<<"position: " << camera.position.x<<" "<<camera.position.y<<" "<<camera.position.z<<" up: " << camera.up.x<<" "<<camera.up.y<<" "<<camera.up.z<< " direction: " <<  camera.direction.x<<" "<<camera.direction.y<<" "<<camera.direction.z << " lookat: "
       <<  camera.lookat.x<<" "<<camera.lookat.y<<" "<<camera.lookat.z << " fovx: " << camera.fovx << " fovy: " << camera.fovy << " width: " << camera.width
       << " height: " << camera.height<<std::endl<<"}"<<std::endl;
    return os;
}

void Camera::setFOV(int w, int h, double fovx) {
    width=w;
    height=h;
    this->fovx=M_PI/180*fovx;
    fovy=(double(width)/double(height))*this->fovx;
}