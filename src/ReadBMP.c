#include <stdio.h>
#include <stdlib.h>
#include "Image.h"
#include "Filters.h"

/*
                                                                           Wikipedia
                                                            https://en.wikipedia.org/wiki/BMP_file_format


                                                                        File Header
                                                                First 14 bytes of the file
    ________________________________________________________________________________________________________________________________________________________________________
       Offset hex 	Offset dec 	     Size              Purpose                                                                                                             
                                                   BM                                                                                                                     
                                                       Windows 3.1x, 95, NT, ... etc.                                                                                     
                                                   BA                                                                                                                     
                                                       OS/2 struct bitmap array                                                                                           
                                                   CI                                                                                                                     
       00              0           2 bytes             OS/2 struct color icon                                                                                             
                                                   CP                                                                                                                     
                                                       OS/2 const color pointer                                                                                           
                                                   IC                                                                                                                     
                                                       OS/2 struct icon                                                                                                   
                                                   PT                                                                                                                     
                                                     OS/2 pointer                                                                                                         
      ____________________________________________________________________________________________________________________________________________________________________
      02 	            2 	       4 bytes	       The size of the BMP file in bytes                                                                                       
      06 	            6 	       2 bytes	       Reserved; actual value depends on the application that creates the image, if created manually can be 0                  
      08 	            8 	       2 bytes	       Reserved; actual value depends on the application that creates the image, if created manually can be 0                  
      0A 	            10 	       4 bytes	       The offset, i.e. starting address, of the byte where the bitmap image data (pixel array) can be found.                  
   _______________________________________________________________________________________________________________________________________________________________________

*/

// struct to encode information contained in the BMP header detailed above
struct BMP_Header{
    char header_field[2]; // BM
    unsigned int size; // 4 bytes
    int reserved; // Not needed
    unsigned int PixelArrayOffset; // 4 byte offset indicating the start of the pixel array (img data)
};


/*
                                                                    DIB Header
     ________________________________________________________________________________________________________________________________________________
      Offset   Offset    Size           Windows BITMAPINFOHEADER                                                                                   
      (hex)    (dec)    (bytes)                                                                                                                    
                                                                                                                                                   
     0E 	    14 	       4 	    the size of this header, in bytes (40)                                                                          
     12 	    18 	       4 	    the bitmap width in pixels (signed integer)                                                                     
     16 	    22 	       4 	    the bitmap height in pixels (signed integer)                                                                    
     1A 	    26 	       2 	    the number of color planes (must be 1)                                                                          
     1C 	    28 	       2 	    the number of bits per pixel, which is the color depth of the image. Typical values are 1, 4, 8, 16, 24 and 32. 
     1E 	    30 	       4 	    the compression method being used. See the next table for a list of possible values                             
     22 	    34 	       4 	    the image size. This is the size of the raw bitmap data; a dummy 0 can be given for BI_RGB bitmaps.             
     26 	    38 	       4 	    the horizontal resolution of the image. (pixel per metre, signed integer)                                       
     2A 	    42 	       4 	    the vertical resolution of the image. (pixel per metre, signed integer)                                         
     2E 	    46 	       4 	    the number of colors in the color palette, or 0 to default to 2n                                                
     32 	    50 	       4 	    the number of important colors used, or 0 when every color is important; generally ignored                      
    _______________________________________________________________________________________________________________________________________________



                                                                   Offset 30 table
     _____________________________________________________________________________________________________________________________________________                                
      Value   Identified by           Compression Method                        Comments                                                        
        0 	    BI_RGB 	                    none 	                        Most common                                                          
        1 	    BI_RLE8 	                RLE 8-bit/pixel 	            Can be used only with 8-bit/pixel bitmaps                            
        2 	    BI_RLE4 	                RLE 4-bit/pixel 	            Can be used only with 4-bit/pixel bitmaps                            
        3 	    BI_BITFIELDS 	            OS22XBITMAPHEADER: Huffman 1D 	BITMAPV2INFOHEADER: RGB bit field masks, BITMAPV3INFOHEADER+: RGBA   
        4 	    BI_JPEG 	                OS22XBITMAPHEADER: RLE-24 	    BITMAPV4INFOHEADER+: JPEG image for printing                         
        5 	    BI_PNG 		                                                BITMAPV4INFOHEADER+: PNG image for printing                          
        6 	    BI_ALPHABITFIELDS 	        RGBA bit field masks 	        only Windows CE 5.0 with .NET 4.0 or later                           
        11 	    BI_CMYK 	                none 	                    only Windows Metafile CMYK                                           
        12 	    BI_CMYKRLE8 	            RLE-8 	                    only Windows Metafile CMYK                                           
        13 	    BI_CMYKRLE4 	            RLE-4 	                    only Windows Metafile CMYK                                           
    ____________________________________________________________________________________________________________________________________________

*/

struct DIB_Header{
    unsigned int size; // size of the header in bytes
    unsigned int width, height; // width and height in pixels
    unsigned short int Planes; // Number of color planes (unsigned short int is 2 bytes)
    unsigned short int BitsPerPixel; // Number of bits per pixel (color depth)
    unsigned int compression_method; 
    unsigned int image_size;
};

// load bmp image into an Image struct
struct Image LoadBMP(FILE* fp, unsigned int width, unsigned int height){
    struct Image img;
    
    img.width = width;
    img.height = height;

    img.bgr = (struct BGR**)malloc(height * sizeof(void*));
    for (int i = height - 1; i != 0; --i){
        img.bgr[i] = (struct BGR*)malloc(width * sizeof(struct BGR));
        fread(img.bgr[i], width, sizeof(struct BGR), fp);
    }

    return img;
}

void OpenBMP(const char* Path){
    FILE* fp = fopen(Path, "rb");
    if (!fp){
        fprintf(stderr, "Could not open file");
        return;
    }

    struct BMP_Header file_header;
    struct DIB_Header dib_header;

    fread(file_header.header_field, 2, 1, fp); // Read the header field
    fread(&file_header.size, sizeof(int)*3, 1, fp); // Read file size

    printf("Header field: %c%c\n", file_header.header_field[0], file_header.header_field[1]);
    printf("Size of file in bytes: %d\n", file_header.size);
    printf("Offset: %d\n", file_header.PixelArrayOffset);

    // Read the DIB Header
    fread(&dib_header, sizeof(struct DIB_Header), 1, fp);
    printf("Width: %d, Height: %d\n", dib_header.width, dib_header.height);
    printf("Compression Id: %d\n", dib_header.compression_method);

    struct Image img;

    // Get to the Image Data
    fseek(fp, file_header.PixelArrayOffset, SEEK_SET);
    img = LoadBMP(fp, dib_header.width, dib_header.height);

    FreeImage(img);
    fclose(fp);
}

int main(void){
    char buff[100];
    printf("Enter the BMP filepath: ");
    scanf("%s", buff);
    OpenBMP(buff);
}
