cmake_minimum_required(VERSION 3.7)
project(Raytracer)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp ray.cpp ray.h Color.cpp Color.h tinyxml2.h tinyxml2.cpp Raytracer.cpp Raytracer.h Camera.cpp Camera.h Obj.cpp Obj.h Material.cpp Material.h Sphere.cpp Sphere.h Mesh.cpp Mesh.h Light.cpp Light.h PointLight.cpp PointLight.h ParallelLight.cpp ParallelLight.h SpotLight.cpp SpotLight.h)
add_executable(Raytracer ${SOURCE_FILES} Color.cpp Color.h Obj.cpp Obj.h)