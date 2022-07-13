/**
 * @file Image.h
 * Contains your declaration of the interface for the Image class.
 */

#pragma once
#include "cs225/PNG.h"

class Image : public cs225::PNG {
public:
    void lighten();
        //Lighten an Image by increasing the luminance of every pixel by 0.1. More...
     
    void lighten(double amount);
        //Lighten an Image by increasing the luminance of every pixel by amount. More...
     
    void darken();
       //Darken an Image by decreasing the luminance of every pixel by 0.1. More...
     
    void darken(double amount);
        //Darkens an Image by decreasing the luminance of every pixel by amount. More...
     
    void saturate();
        //Saturates an Image by increasing the saturation of every pixel by 0.1. More...
     
    void saturate(double amount);
        //Saturates an Image by increasing the saturation of every pixel by amount. More...
     
    void desaturate();
        //Desaturates an Image by decreasing the saturation of every pixel by 0.1. More...
     
    void desaturate(double amount);
        //Desaturates an Image by decreasing the saturation of every pixel by amount. More...
     
    void grayscale();
        //Turns the image grayscale. More...
     
    void rotateColor(double degrees);
        //Rotates the color wheel by degrees. More...
     
    void illinify();
        //Illinify the image. More...
     
    void scale(double factor);
        //Scale the Image by a given factor. More...
     
    void scale(unsigned w, unsigned h);
        //Scales the image to fit within the size (w x h). More...
};
