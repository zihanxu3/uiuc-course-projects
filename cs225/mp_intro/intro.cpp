#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"

#include <string>

using namespace cs225;
 

//adding some nonsense comment
void rotate(std::string inputFile, std::string outputFile) {
    PNG *image = new PNG();
    bool flag = image->readFromFile(inputFile);
    if (flag) {
        double width = image->width();
        double height = image->height();
        PNG *newImage = new PNG(width, height);
        for (unsigned x = 0; x < width; x++) {
          for (unsigned y = 0; y < height; y++) {
              HSLAPixel &pixel = image->getPixel(width - 1 - x, height - 1 - y);
              HSLAPixel &newPixel = newImage->getPixel(x, y);
              newPixel.h = pixel.h;
              newPixel.s = pixel.s;
              newPixel.l = pixel.l;
              newPixel.a = pixel.a;
          }
        }
        delete image;
        newImage -> writeToFile(outputFile);
        delete newImage;
    }
}

cs225::PNG myArt(unsigned int width, unsigned int height) {
  PNG png(width, height);
  // TODO: Part 3
    
//    double i = 0;
//    int k = 0;
//    unsigned int a = width / 4;
    int m = 30;
    for (unsigned i = 0; i <= width - (width / 4); i += width / 4) {
        for (unsigned x = i; x < i + width / 4; x++) {
            for (unsigned y = 0; y < height; y++) {
                HSLAPixel &pixel = png.getPixel(x, y);
                pixel.l = 0.7;
                pixel.s = 0.5;
                pixel.a = 1;
                pixel.h = m;
            }
        }
        m += 50;
    }
  return png;
}
