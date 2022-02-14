#ifndef FILTER_H
#define FILTER_H

#include "Image.h"

// Simple function to convert BGR struct to a Grayscale value
unsigned char GrayScale(struct BRG brg){
    return (brg.red + brg.green + brg.blue) / 3;
}

// Function to convert BGR struct to Grayscale value with Red, Blue, and Green weights
unsigned char WeightedGrayScale(struct BRG brg, float rw, float gw, float bw){
    return ( (brg.red * rw) + (brg.green * gw) + (brg.blue * bw) ) / 3;
}

// Converts an Image struct to grayscale (in-place)
void GrayScaleImage(struct Image img){
    for (int i = 0; i < img.height; ++i){
        for (int j = 0; j < img.width; ++j){
            img.brg[i][j].blue = img.brg[i][j].green = img.brg[i][j].red = GrayScale(img.brg[i][j]); 
        }
    }
}

#endif