//
// Created by chris on 21.05.17.
//

#include "Raytracer.h"
#include "tinyxml2.h"
#include "Sphere.h"
#include "Light.h"
#include "PointLight.h"
#include "ParallelLight.h"
#include "SpotLight.h"
#include <memory>

Raytracer::Raytracer(std::string xml_filename) {
    parseScene(xml_filename);
}
Raytracer::Raytracer(int width, int height) {
    imgWidth=width;
    imgHeight=height;
    camera.setFOV(width,height,45);
    Color white(255,255,255);
    backgroundColor=white;
    ambientlight=Color(0.3 * 255, 0.3 * 255, 0.3 * 255);
    objects.push_back(std::make_shared<Sphere>());
}

std::string Raytracer::createHeader(){
    //PPM image header:

    std::string header{'P','6','\n'};
    std::string w= std::to_string(imgWidth);
    std::string h=std::to_string(imgHeight);
    w.push_back(' ');
    h.push_back('\n');
    std::string rgb{'2','5','5','\n'};
    std::string buffer=header+w+h+rgb;
   return buffer;
}

std::string Raytracer::start() {

    std::string buffer=createHeader();
    //ray tracing loop

    for(int y=0; y<imgHeight; y++){
        for(int x=0; x<imgWidth; x++){

            Ray ray=camera.constructEyeRay(x,y);
            Color c=backgroundColor;

            if(ray.cast(c,objects,lightsrc)){
                c = c * ambientlight;
            }

           // std::cout<<"R: "<<c.red()<<"G: "<<c.green()<<"B: "<<c.blue()<<std::endl;
            buffer.push_back(c.red());
            buffer.push_back(c.green());
            buffer.push_back(c.blue());
        }
    }
    return buffer;
}

void Raytracer::parseScene(std::string xml){

    std::vector<Obj> objectList;
    tinyxml2::XMLDocument doc;
    tinyxml2::XMLError xmlError=doc.LoadFile(xml.c_str());
    if(xmlError!=tinyxml2::XML_SUCCESS){
        std::cout<<"XML Read error";
        return;
    }
   // std::cout<<"Loading completed. "<<std::endl;
    tinyxml2::XMLNode* root=doc.FirstChild();
    tinyxml2::XMLElement* scene=root->NextSiblingElement();
    tinyxml2::XMLElement* background=scene->FirstChildElement("background_color");
    tinyxml2::XMLElement* camera=scene->FirstChildElement("camera");
    tinyxml2::XMLElement* lights=scene->FirstChildElement("lights");
    tinyxml2::XMLElement* surfaces=scene->FirstChildElement("surfaces");

    const tinyxml2::XMLAttribute* attribute=scene->FirstAttribute();
    outputname=attribute->Value();
    outputname=outputname+".ppm";
    if (background== nullptr||camera== nullptr||lights== nullptr||surfaces== nullptr) std::cout<<"XML Error, parsing Element: "<<tinyxml2::XML_ERROR_PARSING_ELEMENT;
    //std::cout<<"Scene: "<<scene->Value()<<std::endl<<background->Value()<<std::endl<<camera->Value()<<std::endl<<lights->Value()<<std::endl<<surfaces->Value()<<std::endl;
    double r,g,b;
    background->QueryDoubleAttribute("r",&r);
    background->QueryDoubleAttribute("g",&g);
    background->QueryDoubleAttribute("b",&b);
    Color bc(255*r,255*g,255*b);
    backgroundColor=bc;
    //std::cout<<" BC COlor: "<<backgroundColor;
    tinyxml2::XMLElement* camerapos=camera->FirstChildElement("position");

    //////////////////////////parsing Camera

    double x,y,z;
    camerapos->QueryDoubleAttribute("x",&x);
    camerapos->QueryDoubleAttribute("y",&y);
    camerapos->QueryDoubleAttribute("z",&z);
    glm::vec4 cpos(x,y,z,0);
    tinyxml2::XMLElement* XMLlookat = camera->FirstChildElement("lookat");
    XMLlookat->QueryDoubleAttribute("x",&x);
    XMLlookat->QueryDoubleAttribute("y",&y);
    XMLlookat->QueryDoubleAttribute("z",&z);
    glm::vec4 clookat(x,y,z,0);
    tinyxml2::XMLElement* upvec=camera->FirstChildElement("up");
    upvec->QueryDoubleAttribute("x",&x);
    upvec->QueryDoubleAttribute("y",&y);
    upvec->QueryDoubleAttribute("z",&z);
    glm::vec4 up(x,y,z,0);

    int w,h;
    int fov;
    tinyxml2::XMLElement* res = camera->FirstChildElement("resolution");
    tinyxml2::XMLElement* v= camera->FirstChildElement("horizontal_fov");
    v->QueryAttribute("angle",&fov);
    res->QueryAttribute("horizontal",&w);
    res->QueryAttribute("vertical",&h);
    imgHeight=h;
    imgWidth=w;
    Camera c(cpos, up, clookat, w, h, fov);
   // std::cout<<"XML Camera: "<<c;
    this->camera=c;
    //////////////////////////Parsing Lights
    tinyxml2::XMLElement* al=lights->FirstChildElement("ambient_light");
    al->FirstChildElement("color")->QueryDoubleAttribute("r", &r);
    al->FirstChildElement("color")->QueryDoubleAttribute("g", &g);
    al->FirstChildElement("color")->QueryDoubleAttribute("b", &b);
    ambientlight=Color(r * 255 , g  * 255, b * 255);

    glm::vec4 lpos;
    tinyxml2::XMLElement* pl=lights->FirstChildElement("point_light");

    if(pl != nullptr) {
        pl->FirstChildElement("color")->QueryDoubleAttribute("r", &r);
        pl->FirstChildElement("color")->QueryDoubleAttribute("g", &g);
        pl->FirstChildElement("color")->QueryDoubleAttribute("b", &b);

        Color pointColor(r * 255, g * 255, b * 255);

        pl->FirstChildElement("position")->QueryDoubleAttribute("x", &x);
        pl->FirstChildElement("position")->QueryDoubleAttribute("y", &y);
        pl->FirstChildElement("position")->QueryDoubleAttribute("z", &z);
        lpos={x, y, z, 0.0f};

        lightsrc.push_back(std::make_shared<PointLight>(pointColor,lpos));
    }


    tinyxml2::XMLElement* prl=lights->FirstChildElement("parallel_light");
    if(prl != nullptr) {
        prl->FirstChildElement("color")->QueryDoubleAttribute("r", &r);
        prl->FirstChildElement("color")->QueryDoubleAttribute("g", &g);
        prl->FirstChildElement("color")->QueryDoubleAttribute("b", &b);

        prl->FirstChildElement("direction")->QueryAttribute("x", &x);
        prl->FirstChildElement("direction")->QueryAttribute("y", &y);
        prl->FirstChildElement("direction")->QueryAttribute("z", &z);
       // std::cout << "Light direction: " << prl->FirstChildElement("direction")->Value();
        Color prlColor(r * 255, g * 255, b * 255);
       glm::vec4 ldir={x,y,z,1.0f};

        lightsrc.push_back(std::make_shared<ParallelLight>(prlColor,ldir));
    }


    tinyxml2::XMLElement* sl=lights->FirstChildElement("spot_light");
    if(sl!=nullptr) {
        sl->FirstChildElement("color")->QueryAttribute("r", &r);
        sl->FirstChildElement("color")->QueryAttribute("g", &g);
        sl->FirstChildElement("color")->QueryAttribute("b", &b);

        sl->FirstChildElement("position")->QueryAttribute("x", &x);
        sl->FirstChildElement("position")->QueryAttribute("y", &y);
        sl->FirstChildElement("position")->QueryAttribute("z", &z);
        lpos = {x, y, z, 0.0f};
        sl->FirstChildElement("direction")->QueryAttribute("x", &x);
        sl->FirstChildElement("direction")->QueryAttribute("y", &y);
        sl->FirstChildElement("direction")->QueryAttribute("z", &z);
        glm::vec4 ldir(x, y, z, 0.0f);

        sl->FirstChildElement("falloff")->QueryAttribute("alpha1", &x);
        sl->FirstChildElement("falloff")->QueryAttribute("alpha2", &y);
        Color slColor(r,g,b);
        glm::vec2 faloff(x,y);

        lightsrc.push_back(std::make_shared<SpotLight>(Color(r,g,b),lpos, ldir,faloff));
    }


    ////////////////Surfaces

    tinyxml2::XMLElement* sphere=surfaces->FirstChildElement("sphere");
    while(sphere!= nullptr) {
        int rad;
        sphere->QueryAttribute("radius", &rad);
        tinyxml2::XMLElement *pos = sphere->FirstChildElement("position");
        pos->QueryDoubleAttribute("x", &x);
        pos->QueryDoubleAttribute("y", &y);
        pos->QueryDoubleAttribute("z", &z);

        tinyxml2::XMLElement* mat = sphere->FirstChildElement("material_solid");
        mat = mat->FirstChildElement();
        Color sphereColor;
        if(mat!= nullptr){
            //std::cout<<"mat is not nullptr! "<<mat->Value()<<std::endl;
            int ka, kd, ks, exp;
            mat->QueryDoubleAttribute("r", &r);
            mat->QueryDoubleAttribute("g", &g);
            mat->QueryDoubleAttribute("b", &b);
            mat=mat->NextSiblingElement();
            mat->QueryAttribute("ka", &ka);
            mat->QueryAttribute("kd", &kd);
            mat->QueryAttribute("ks", &ks);
            mat->QueryAttribute("exponent",&exp);

            Color s(255*r,255*g,255*b);
            sphereColor=s;
            //std::cout<<"Color spherecolor: "<<sphereColor;
        }
        Material material(sphereColor);
        std::shared_ptr<Sphere> ptr = std::make_shared<Sphere>(glm::vec4(x, y, z, 1.0f), rad, material);
        this->objects.push_back(ptr);
        sphere=sphere->NextSiblingElement();
    }

    return;

}

std::ostream &operator<<(std::ostream &os, const Raytracer &raytracer) {
    os << "Raytracer {"<<"imgWidth: " << raytracer.imgWidth << " imgHeight: " << raytracer.imgHeight
       << " camera: " << raytracer.camera << " backgroundColor: " << raytracer.backgroundColor<<std::endl<<"}"<<std::endl;
    return os;
}

void Raytracer::writePPM(std::string buffer, int size){
    std::FILE * image=std::fopen(outputname.c_str(), "wb");
    std::fwrite(buffer.c_str(),1,size,image);
    std::fclose(image);

}

