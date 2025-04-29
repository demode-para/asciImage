#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

struct rgba_pixel {
    uint8_t r;
    uint8_t g;
    uint8_t b;
    uint8_t a;
};

#define N_OF_SYMBOLS 7
char *symbols = ".,:;!a#";

char pixel_to_symbol(struct rgba_pixel px){
    float avg = (px.r + px.g + px.b)/3;
    float normalized_avg = avg /255;
    normalized_avg *= (N_OF_SYMBOLS - 1);
    int index = (int)normalized_avg;
    return symbols[index];
}

int main(int argc, char **argv){

    const char *filename = argv[1];
    int width = 0; 
    int height = 0;
    int pixel_per_components = 8;
    
        
    unsigned char *data = (unsigned char*)malloc(width * height * pixel_per_components * 4);
    data = stbi_load(filename, &width, &height, &pixel_per_components, 4);

    if(data == NULL) {
        fprintf(stderr, "Failed to load image \n");
        return 1;
    }

    struct rgba_pixel* data_in_pixel = (struct rgba_pixel*)data;
    
        
    for(int i = 0; i <width*height; i+= 4){
        printf(" %c ", pixel_to_symbol(data_in_pixel[i]));
        if(i % width == 0) printf("\n");
    }    
 
    return 0;
}



