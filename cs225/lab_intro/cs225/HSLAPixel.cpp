/**
 * @file HSLAPixel.cpp
 * Implementation of the HSLAPixel class for use in with the PNG library.
 *
 * @author CS 225: Data Structures
 * @version 2018r1-lab1
 */

#include "HSLAPixel.h"
#include <cmath>
#include <iostream>
using namespace std;

namespace cs225 {
    HSLAPixel::HSLAPixel() {
        l = 1.0;
        a = 1.0;
    }
    HSLAPixel::HSLAPixel(double hue, double saturation, double luminance) {
        if (h >= 0 && h <= 360) {
            h = hue;
        }
        if (s >= 0 && s <= 1) {
            s = saturation;
        }
        if (s >= 0 && s <= 1) {
            l = luminance;
        }
        a = 1.0;
    }
    HSLAPixel::HSLAPixel(double hue, double saturation, double luminance, double alpha) {
        if (h >= 0 && h <= 360) {
            h = hue;
        }
        if (s >= 0 && s <= 1) {
            s = saturation;
        }
        if (s >= 0 && s <= 1) {
            l = luminance;
        }
        if (s >= 0 && s <= 1) {
            a = alpha;
        }
    }
}
