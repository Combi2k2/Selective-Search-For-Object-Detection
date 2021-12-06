#include <stdio.h>
#include <stdlib.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image/stb_image.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image/stb_image_write.h"

typedef unsigned char uchar;

int main(void)  {
    int width, height, channels;
    
    uchar *img = stbi_load("2.jpg", &width, &height, &channels, 0);
    if (img == NULL)    {
        printf("Unable to load the image");
        exit(1);
    }
    printf("Load image with a width of %dpx, a height of %dpx and %d channels", width, height, channels);
}

