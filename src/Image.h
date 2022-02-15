#ifndef IMAGE_H
#define IMAGE_H

#include <stdlib.h>
// Structure to encode the Blue Green Red format (used in BMP 24 bit)
struct RGB{ 
    unsigned char blue;
    unsigned char green; 
    unsigned char red;
};

// Image structure which will be used across the entire project
struct Image{
    struct RGB **rgb; // two dimensional structure
    int width, height; // dimensions of the image
};

// Free an Image struct from memory
void FreeImage(struct Image img){
    for (int i = 0; i < img.height; ++i){
        free(img.rgb[i]);
    }

    free(img.rgb);
}

#endif