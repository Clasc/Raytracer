#include <iostream>
#include <math.h>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include "glm/mat4x4.hpp"
#include "tinyxml2.h"

#include "Color.h"
#include "ray.h"
#include "Camera.h"
#include "Raytracer.h"


int main() {
    std::string xml="example2.xml";
    std::string buffer;
    int imgWidth=512;
    int imgHeight=512;

    Raytracer rt(xml);

    buffer=rt.start();
    rt.writePPM(buffer, buffer.size());

    return 0;
}