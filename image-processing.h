/*
Copyright (C) 2006 Pedro Felzenszwalb

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA
*/

/* basic image I/O */

#ifndef IMAGE_PROCESSING
#define IMAGE_PROCESSING

#include <cstdlib>
#include <climits>
#include <cstring>
#include <fstream>
#include "imconv.h"
#include "image.h"
#include "misc.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image/stb_image.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image/stb_image_write.h"

class image_error {};

static void read_packed(unsigned char *data, int size, std::ifstream &f)    {
    unsigned char c = 0;
    int bitshift = -1;

    for(int i = 0 ; i < size ; ++i) {
        if (bitshift == -1) {
            c = f.get();
            bitshift = 7;
        }
        data[i] = (c >> bitshift) & 1;
        bitshift--;
    }
}
static void write_packed(unsigned char *data, int size, std::ofstream &f)   {
    unsigned char c = 0;
    int bitshift = 7;

    for(int i = 0 ; i < size ; ++i) {
        c = c | (data[i] << bitshift);
        bitshift--;

        if (bitshift < 0 || i == size - 1)  {
            f.put(c);
            bitshift = 7;
            c = 0;
        }
    }
}

image<rgb> *load_image(const char *name)    {
    int width;
    int height;
    int channels;

    uchar *img = stbi_load(name, &width, &height, &channels, 0);

    if (img == NULL)    {
        printf("Unable to load image");
        throw image_error();
    }
    image<rgb> *im = new image<rgb>(width, height, false);

    size_t inp_size = width * height * channels;
    size_t out_size = width * height;

    uchar *ptr_str = img;
    rgb   *ptr_rgb = im -> data;

    for(; ptr_str != img + inp_size ; ptr_str += channels, ptr_rgb++)   {
        if (channels == 3)  {
            ptr_rgb -> r = *ptr_str;
            ptr_rgb -> g = *(ptr_str + 1);
            ptr_rgb -> b = *(ptr_str + 2);
        }
        else    (ptr_rgb -> r) = (ptr_rgb -> g) = (ptr_rgb -> b) = *ptr_str;
    }
    delete [] img;
    return  im;
}
//template<class T>
static void save_image(image<rgb> *im, const char *name)  {
    int width  = im -> width();
    int height = im -> height();
    int channels = 3;

    int img_size = width * height * channels;

    uchar *img = new uchar[img_size];
    uchar *ptr = img;

    for(int y = 0 ; y < height ; ++y)
    for(int x = 0 ; x < width  ; ++x)   {
        *ptr++ = imRef(im, x, y).r;
        *ptr++ = imRef(im, x, y).g;
        *ptr++ = imRef(im, x, y).b;
    }
    std::string extension = "";
    
    extension += name[strlen(name) - 3];
    extension += name[strlen(name) - 2];
    extension += name[strlen(name) - 1];

    printf("%s", extension.c_str());

    if (extension == "jpg") stbi_write_jpg(name, width, height, channels, img, 100);
    if (extension == "png") stbi_write_png(name, width, height, channels, img, 100);

    if (extension != "jpg" && extension != "png")   {
        printf("I dont know how to save image with other extension, sorry");
        throw image_error();
    }
    delete [] img;
}

#endif
