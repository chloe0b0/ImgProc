#ifndef IMAGE_H
#define IMAGE_H

#include <stdlib.h>
// Structure to encode the Blue Green Red format (used in BMP)
struct BGR{ unsigned char blue, green, red; };

// Image structure which will be used across the entire project
struct Image{
    struct BGR **bgr; // two dimensional structure
    unsigned int width, height; // dimensions of the image
};

// Free an Image struct from memory
void FreeImage(struct Image img){
    for (int i = 0; i < img.height; ++i){
        free(img.bgr[i]);
    }

    free(img.bgr);
}

#endif