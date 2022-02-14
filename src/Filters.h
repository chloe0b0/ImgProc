#ifndef FILTER_H
#define FILTER_H

#include "Image.h"

// Simple function to convert BGR struct to a Grayscale value
unsigned char GrayScale(struct BGR bgr){
    return (bgr.red + bgr.green + bgr.blue) / 3;
}

// Function to convert BGR struct to Grayscale value with Red, Blue, and Green weights
unsigned char WeightedGrayScale(struct BGR bgr, float rw, float gw, float bw){
    return ( (bgr.red * rw) + (bgr.green * gw) + (bgr.blue * bw) ) / 3;
}

// Converts an Image struct to grayscale (in-place)
void GrayScaleImage(struct Image img){
    for (int i = 0; i < img.height; ++i){
        for (int j = 0; j < img.width; ++j){
            img.bgr[i][j].blue = img.bgr[i][j].green = img.bgr[i][j].red = GrayScale(img.bgr[i][j]);
        }
    }
}

#endif