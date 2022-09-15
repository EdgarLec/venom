#include <iostream>
#include <math.h>
#include <raylib.h>
#include "Include.hpp"

union color_u {
    struct {
        unsigned char r, g, b, a;
    };
    unsigned int value;
};

void set_map(Image &image, Image &color, int rng)
{
    char *pixels = new char[400 * 400];
    int *pixels_clr = new int[400 * 400];
    unsigned char noise = 0;
    Image grad = LoadImage("gradient.png");
    image.format = PIXELFORMAT_UNCOMPRESSED_GRAYSCALE;
    image.mipmaps = true;
    color.format = PIXELFORMAT_UNCOMPRESSED_R8G8B8A8;
    color.mipmaps = true;
    int test = 0;
    float zoom = 1.0;
    for (int i = 0; i < 400; i++)
        for (int j = 0; j < 400; j++) {
            noise = ((ValueNoise_2D(rng, i / zoom, j / zoom, 5)) + 1) * 127;
            noise = noise / 255.0 * 127;
            pixels[i * 400 + j] = noise;
    }
    int max = 0;
    int min = 255;
    for (int i = 0; i < 400; i++)
        for (int j = 0; j < 400; j++) {
            if (pixels[i * 400 + j] > max)
                max = pixels[i * 400 + j];
            if (pixels[i * 400 + j] < min)
                min = pixels[i * 400 + j];
        }
    for (int i = 0; i < 400; i++)
        for (int j = 0; j < 400; j++) {
            pixels[i * 400 + j] = (pixels[i * 400 + j] - min) / float(max - min) * 255;
        }
    for (int i = 0; i < 400; i++)
        for (int j = 0; j < 400; j++) {
            noise = pixels[i * 400 + j];
            color_u tmp;
            tmp.value = 0;//rgba(121,4,235,255)
            tmp.r = 0;
            tmp.g = (255 - noise) / 255.0 * 255;
            tmp.b = (255 - noise) / 255.0 * 255;
            pixels_clr[i * 400 + j] = (255) << 24 | tmp.value;
    }
    pixels[0] = 1;
    image.data = pixels;
    image.height = 400;
    image.width = 400;
    color.data = pixels_clr;
    color.height = 400;
    color.width = 400;
}