//
// Created by chris on 20.05.17.
//

#include "Color.h"

/*Color::Color(const Color &rhs) {
    r=rhs.r;
    b=rhs.b;
    g=rhs.g;
}*/

Color::Color(double red, double green, double blue) {
    int r,g,b;
    r = red;
    g = green;
    b = blue;
    clamp(r, g, b);

    this->r = r;
    this->g = g;
    this->b = b;

}
Color::Color(int red, int green, int blue) {
    clamp(red, green, blue);
    r = red;
    g = green;
    b = blue;

}

Color Color::operator+(Color c){
   // std::cout<<"in operator+"<<std::endl;
    Color fin;
    fin.r = r / 2 + c.r / 2;
    fin.g = g / 2 + c.g / 2;
    fin.b = b / 2 + c.b / 2;

    //std::cout<<"OriginColor: "<<*this<<" AmbientColor: "<<c<<std::endl;
    return fin;
}

std::ostream &operator<<(std::ostream &os, const Color &color) {
    os << "Color {"<<std::endl<<"r: " << (int) color.r << " g: " << (int) color.g<< " b: " << (int) color.b<<std::endl<<"}"<<std::endl;
    return os;
}

Color Color::operator=(Color c) {
   // std::cout<<"in operator= "<<c.r<<std::endl;
    r=c.red();
    g=c.green();
    b=c.blue();
    return c;
}

Color Color::operator*(Color rc) {
    Color result;

    result.r = (double) r * (double)rc.r / 255;
    result.g = (double) g * (double)rc.g / 255;
    result.b = (double) b * (double)rc.b / 255;


    return result;
}

void Color::clamp(int& r, int& g, int& b) {
    if(r > 255) {
        r = 255;
    }
    if(r < 0){
        r=0;
    }
    if(g > 255){
        g=255;
    }
    if(g < 0){
        g=0;
    }
    if(b > 255){
        b=255;
    }
    if(b<0){
        b=0;
    }
}