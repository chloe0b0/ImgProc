#ifndef FILTER_H
#define FILTER_H

#include "Image.h"

// Simple function to convert BGR struct to a Grayscale value
unsigned char GrayScale(struct RGB rgb){
    return (rgb.red + rgb.green + rgb.blue) / 3;
}

// Function to convert BGR struct to Grayscale value with Red, Blue, and Green weights
unsigned char WeightedGrayScale(struct RGB rgb, float rw, float gw, float bw){
    return ( (rgb.red * rw) + (rgb.green * gw) + (rgb.blue * bw) ) / 3;
}

// Converts an Image struct to grayscale (in-place)
void GrayScaleImage(struct Image *img){
    for (int i = 0; i < img->height; ++i){
        for (int j = 0; j < img->width; ++j){
            img->rgb[i][j].blue = img->rgb[i][j].green = img->rgb[i][j].red = GrayScale(img->rgb[i][j]);
        }
    }
}

#endif