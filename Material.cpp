//
// Created by chris on 26.05.17.
//

#include "Material.h"

Material::Material() {
    Color defColor(0,255,255);
    color=defColor;
    this->phong={0,0,0,1};
    phongExp=0;
    reflectance=0;
    transmittance=0;
    refraction=0;
}

Material::Material(const Color &color, const glm::vec4 &phong, int phongExp, double reflectance, double transmittance,
                   double refraction) : color(color), phong(phong), phongExp(phongExp), reflectance(reflectance),
                                        transmittance(transmittance), refraction(refraction) {}

Material::Material(const Color &color) : color(color) {
    phong={0.f,0.f,0.f,1.f};
    phongExp=0;
    reflectance=0;
    transmittance=0;
    refraction=0;
}

Material Material::operator=(Material m){
    this->refraction=m.refraction;
    this->transmittance=m.transmittance;
    this->reflectance=m.reflectance;
    this->phongExp=m.phongExp;
    this->phong=m.phong;
    this->color=m.color;
}

std::ostream &operator<<(std::ostream &os, const Material &material) {
    os << "Material: {"<<std::endl<<"color: " << material.color << " phong: " << material.phong.x<<" "<<material.phong.y<<" "<<material.phong.z << " phongExp: " << material.phongExp
       << " reflectance: " << material.reflectance << " transmittance: " << material.transmittance << " refraction: "
       << material.refraction<<std::endl<<"}"<<std::endl;
    return os;
}

Color Material::getColor() const {
    return color;
}

void Material::setColor(const Color &color) {
    Material::color = color;
}

double Material::getReflectance() const {
    return reflectance;
}

void Material::setReflectance(double reflectance) {
    Material::reflectance = reflectance;
}

double Material::getTransmittance() const {
    return transmittance;
}

void Material::setTransmittance(double transmittance) {
    Material::transmittance = transmittance;
}

double Material::getRefraction() const {
    return refraction;
}

void Material::setRefraction(double refraction) {
    Material::refraction = refraction;
}
