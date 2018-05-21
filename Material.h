//
// Created by chris on 26.05.17.
//

#ifndef RAYTRACER_MATERIAL_H
#define RAYTRACER_MATERIAL_H


#include <ostream>
#include "glm/vec4.hpp"
#include "Color.h"

class Material {
    Color color;
    glm::vec4 phong;
    int phongExp;
    double reflectance,transmittance,refraction;

public:
    Material();

    Material(const Color &color, const glm::vec4 &phong, int phongExp, double reflectance, double transmittance,
             double refraction);

    Material(const Color &color);

    Material operator=(Material c);

    friend std::ostream &operator<<(std::ostream &os, const Material &material);

    Color getColor() const;

    void setColor(const Color &color);

    double getReflectance() const;

    void setReflectance(double reflectance);

    double getTransmittance() const;

    void setTransmittance(double transmittance);

    double getRefraction() const;

    void setRefraction(double refraction);

};


#endif //RAYTRACER_MATERIAL_H
