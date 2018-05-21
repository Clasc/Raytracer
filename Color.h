//
// Created by chris on 20.05.17.
//

#ifndef RAYTRACER_COLOR_H
#define RAYTRACER_COLOR_H



#include <cmath>
#include <iostream>

class Color {
    unsigned char r, g, b;


    public:
    Color(){r='0'; g='0'; b='0';}
    Color(unsigned char red, unsigned char green, unsigned char blue){r=red; g=green; b=blue;}
    Color (double, double , double);
    Color (int, int, int);
    //Color(const Color& rhs);

    Color operator+(Color c);
    Color operator= (Color c);
    Color operator*(Color rc);
    void clamp(int&, int&, int&);
    unsigned  char red(){return r;}
    unsigned  char green(){return g;}
    unsigned  char blue(){return b;}

    friend std::ostream &operator<<(std::ostream &os, const Color &color);
};


#endif //RAYTRACER_COLOR_H
