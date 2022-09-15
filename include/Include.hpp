#ifndef INCLUDE_H
    #include <string>
    #include <cstring>
    #include <vector>
    #include <math.h>
    #include <iostream>
    #include <raylib.h>


    #include "raymath.h"

    #ifndef RLIGHTS_IMPLEMENTATION
        #include "rlights.h"
        #define RLIGHTS_IMPLEMENTATION
    #endif
    // #include <rlights.h>
    #if defined(PLATFORM_DESKTOP)
        #define GLSL_VERSION            330
    #else   // PLATFORM_RPI, PLATFORM_ANDROID, PLATFORM_WEB -> Not supported at this moment
        #define GLSL_VERSION            100
    #endif
    #define INCLUDE_H


    #define PI 3.14159265f

Vector3 rotate(Vector3 center, Vector3 rt, float angle);
float distance(Vector3 pos1, Vector3 pos2);
Mesh GenMeshCustom(void);
float distance_2d(Vector3 pos1, Vector3 pos2);
double interpolated_noise(int i, double x, double y);
double ValueNoise_2D(int rng, double x, double y, int num_octaves);

void set_map(Image &image, Image &color, int rng);
#endif