#ifndef IMAGE_H
#define IMAGE_H

// Structure to encode the Blue Green Red format (used in BMP)
struct BGR{ unsigned char blue, green, red; };

// Image structure which will be used across the entire project
struct Image{
    struct BGR **bgr; // two dimensional structure
    unsigned int width, height; // dimensions of the image
};

#endif