//
// Created by chris on 21.05.17.
//

#ifndef RAYTRACER_CAMERA_H
#define RAYTRACER_CAMERA_H

#include <ostream>
#include "glm/vec3.hpp"
#include "glm/geometric.hpp"
#include "ray.h"

class Camera {
    glm::vec4 position;
    glm::vec4 up;
    glm::vec4 direction;
    glm::vec4 lookat;
    glm::mat4 worldMatrix;
    double fovx;
    double fovy;
    int width;
    int height;

public:
    Camera();
    Camera(int width, int height);
    Camera(glm::vec4 pos, glm::vec4 u, glm::vec4 look, int width, int height, double fov);

    Camera operator=(Camera c);

    Ray constructEyeRay(int x, int y);
    void setFOV(int w, int h, double fovx);

    friend std::ostream &operator<<(std::ostream &os, const Camera &camera);
};



#endif //RAYTRACER_CAMERA_H
