#include "cs225/PNG.h"
#include "Image.h"


void Image::lighten() {
    //Lighten an Image by increasing the luminance of every pixel by 0.1. More...
    for (unsigned x = 0; x < width(); x++) {
        for (unsigned y = 0; y < height(); y++) {
            cs225::HSLAPixel &pixel = getPixel(x, y);
            if (pixel.l + 0.1 <= 1.0) {
                pixel.l += 0.1;
            } else {
                pixel.l = 1;
            }
        }
    }
}

void Image::lighten(double amount) {
    //Lighten an Image by increasing the luminance of every pixel by amount. More...
    for (unsigned x = 0; x < width(); x++) {
        for (unsigned y = 0; y < height(); y++) {
            cs225::HSLAPixel &pixel = getPixel(x, y);
            if (pixel.l + amount <= 1.0) {
                pixel.l += amount;
            } else {
                pixel.l = 1;
            }
        }
    }
}

void Image::darken() {
   //Darken an Image by decreasing the luminance of every pixel by 0.1. More...
    for (unsigned x = 0; x < width(); x++) {
        for (unsigned y = 0; y < height(); y++) {
            cs225::HSLAPixel &pixel = getPixel(x, y);
            if (pixel.l - 0.1 >= 0.0) {
                pixel.l -= 0.1;
            } else {
                pixel.l = 0;
            }
        }
    }
}

void Image::darken(double amount) {
    //Darkens an Image by decreasing the luminance of every pixel by amount. More...
    for (unsigned x = 0; x < width(); x++) {
        for (unsigned y = 0; y < height(); y++) {
            cs225::HSLAPixel &pixel = getPixel(x, y);
            if (pixel.l - amount >= 0.0) {
                pixel.l -= amount;
            } else {
                pixel.l = 0;
            }
        }
    }
}

void Image::saturate() {
    //Saturates an Image by increasing the saturation of every pixel by 0.1. More...
    for (unsigned x = 0; x < width(); x++) {
        for (unsigned y = 0; y < height(); y++) {
            cs225::HSLAPixel &pixel = getPixel(x, y);
            if (pixel.s + 0.1 <= 1.0) {
                pixel.s += 0.1;
            } else {
                pixel.s = 1;
            }
        }
    }
}

void Image::saturate(double amount) {
    //Saturates an Image by increasing the saturation of every pixel by amount. More...
    for (unsigned x = 0; x < width(); x++) {
        for (unsigned y = 0; y < height(); y++) {
            cs225::HSLAPixel &pixel = getPixel(x, y);
            if (pixel.s + amount <= 1.0) {
                pixel.s += amount;
            } else {
                pixel.s = 1;
            }
        }
    }
}

void Image::desaturate() {
    //Desaturates an Image by decreasing the saturation of every pixel by 0.1. More...
    for (unsigned x = 0; x < width(); x++) {
        for (unsigned y = 0; y < height(); y++) {
            cs225::HSLAPixel &pixel = getPixel(x, y);
            if (pixel.s - 0.1 >= 0.0) {
                pixel.s -= 0.1;
            } else {
                pixel.s = 0;
            }
        }
    }
}

void Image::desaturate(double amount) {
    //Desaturates an Image by decreasing the saturation of every pixel by amount. More...
    for (unsigned x = 0; x < width(); x++) {
        for (unsigned y = 0; y < height(); y++) {
            cs225::HSLAPixel &pixel = getPixel(x, y);
            if (pixel.s - amount >= 0.0) {
                pixel.s -= amount;
            } else {
                pixel.s = 0;
            }
        }
    }
}

void Image::grayscale() {
    for (unsigned int x = 0; x < width(); x++) {
      for (unsigned int y = 0; y < height(); y++) {

        // Get a reference to the pixel at (x, y):
        cs225::HSLAPixel & pixel = getPixel(x, y);

        // Set the pixel's saturation to 0:
        pixel.s = 0;
      }
    }
}
 
void Image::rotateColor(double degrees) {
    //Rotates the color wheel by degrees. More...
    for (unsigned int x = 0; x < width(); x++) {
      for (unsigned int y = 0; y < height(); y++) {
          
        cs225::HSLAPixel & pixel = getPixel(x, y);
        if (pixel.h + degrees >= 360) {
            pixel.h += degrees - 360;
        } else if (pixel.h + degrees < 0) {
            pixel.h = 360 + (pixel.h + degrees);
        } else {
            pixel.h += degrees;
        }
      }
    }
}

void Image::illinify() {
    //Illinify the image. More...
    for (unsigned x = 0; x < width(); x++) {
        for (unsigned y = 0; y < height(); y++) {
            cs225::HSLAPixel & pixel = getPixel(x, y);
            if (pixel.h <= 114 || pixel.h >= 330) {
                pixel.h = 11;
            } else {
                pixel.h = 216;
            }
        }
    }
}
 
void Image::scale(double factor) {
    //Scale the Image by a given factor. More...
    PNG *png = new PNG(width()*factor, height()*factor);
    for (unsigned x = 0; x < png->width(); x++) {
        for (unsigned y = 0; y < png->height(); y++) {
            cs225::HSLAPixel & pixel = png->getPixel(x, y);
            cs225::HSLAPixel & old_pixel = getPixel(x / factor, y / factor);
            
            pixel.h = old_pixel.h;
            pixel.s = old_pixel.s;
            pixel.l = old_pixel.l;
            pixel.a = old_pixel.a;
        }
    }
    resize(width()*factor, height()*factor);
    for (unsigned x = 0; x < width(); x++) {
        for (unsigned y = 0; y < height(); y++) {
            cs225::HSLAPixel & old_pixel = png->getPixel(x, y);
            cs225::HSLAPixel & pixel = getPixel(x, y);
            
            pixel.h = old_pixel.h;
            pixel.s = old_pixel.s;
            pixel.l = old_pixel.l;
            pixel.a = old_pixel.a;
        }
    }
    delete png;
}
 
void Image::scale(unsigned w, unsigned h) {
    //Scales the image to fit within the size (w x h). More...
    if ((w / h) > (width() / height())) {
        scale((double) h/height());
    } else {
        scale((double) w/width());
    }
}
