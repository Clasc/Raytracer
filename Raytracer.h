//
// Created by chris on 21.05.17.
//

#ifndef RAYTRACER_RAYTRACER_H
#define RAYTRACER_RAYTRACER_H


#include <vector>
#include <ostream>
#include <memory>
#include "Color.h"
#include "ray.h"
#include "Camera.h"
#include "Light.h"

class Raytracer {
    int imgWidth;
    int imgHeight;
    Camera camera;
    Color backgroundColor;
    Color ambientlight;
    std::string outputname;
    std::vector<std::shared_ptr<Obj>> objects;
    std::vector<std::shared_ptr<Light>> lightsrc;

public:
    Raytracer(int, int);
    Raytracer(std::string xml_filename);
    std::string start();
    std::string createHeader();
    void parseScene(std::string);

    friend std::ostream &operator<<(std::ostream &os, const Raytracer &raytracer);

    void writePPM(std::string buffer, int size);
};


#endif //RAYTRACER_RAYTRACER_H
