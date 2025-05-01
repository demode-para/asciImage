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

int width = 0; 
int height = 0;
int components_per_pixel = 0;


char pixel_to_symbol(struct rgba_pixel px){
    float avg = (px.r + px.g + px.b)/3;
    float normalized_avg = avg /255;
    normalized_avg *= (N_OF_SYMBOLS - 1);
    int index = (int)normalized_avg;
    return symbols[index];
}


void print_image_pixels(struct rgba_pixel* data_in_pixel, int width, int height){
    for(int i = 0; i <width*height; i+= 4){
        printf(" %c ", pixel_to_symbol(data_in_pixel[i]));
        if(i % width == 0) printf("\n");
    }    
}

// chose a better name
struct rgba_pixel round_pixel(struct rgba_pixel* data_in_pixel, size_t index, uint8_t sizex, uint8_t sizey){
    
    uint32_t r = 0;
    uint32_t g = 0;
    uint32_t b = 0;
    
    for(int j = 0; j < sizey; j++){
        if((int)(index/width) + j >= height) j-=1;
        for(int i = 0; i < sizex; i++){
            if(index%width + i >= width) i-=1;
            r+=data_in_pixel[index + (j*width) + i].r;
            g+=data_in_pixel[index + (j*width) + i].g;
            b+=data_in_pixel[index + (j*width) + i].b;
        }
        
    }
    r/=(sizex*sizey);
    g/=(sizex*sizey);
    b/=(sizex*sizey);
    
    return (struct rgba_pixel){r, g, b, (uint8_t)255};
}

int main(int argc, char **argv){
    int sizex;
    int sizey;
    

    if(argc == 2){
        sizex = 1;
        sizey = 1;
    } else if(argc == 4){
        sizex = atoi(argv[2]);
        sizey = atoi(argv[3]);
    } else {
        fprintf(stderr, "\nWrong Usage \n\t[executable] [fileimage] [sizex] [sizey]");
        return 1;
    }

    const char *filename = argv[1];
     
    unsigned char *data = NULL;
    data = stbi_load(filename, &width, &height, &components_per_pixel, 4);

    if(data == NULL) {
        fprintf(stderr, "Failed to load image \n");
        return 1;
    }

    struct rgba_pixel* data_in_pixel = (struct rgba_pixel*)data;
    if(argc==2){
        print_image_pixels(data_in_pixel, width, height);
        free(data);
        return 0;
    }
    
    struct rgba_pixel* reduced_image = (struct rgba_pixel*)malloc(sizeof(struct rgba_pixel) * width * height / (sizex * sizey));

    for(int i = 0; i < width/sizex; i+=1){
        for(int j = 0; j < height/sizey; j+=1){
            size_t index = i*sizex + (j*width*sizey);
            reduced_image[(j*width/sizex) + i] = round_pixel(data_in_pixel, index, sizex, sizey);
        }
    }
    print_image_pixels(reduced_image, width/sizex , height/sizey);
        
    free(data);
    free(reduced_image);
    return 0;
}
