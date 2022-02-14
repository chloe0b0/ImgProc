#ifndef FILTER_H
#define FILTER_H

#include "Image.h"

// Simple function to convert BGR struct to a Grayscale value
unsigned char GrayScale(struct BGR bgr){
    return (bgr.red + bgr.green + bgr.blue) / 3;
}

#endif