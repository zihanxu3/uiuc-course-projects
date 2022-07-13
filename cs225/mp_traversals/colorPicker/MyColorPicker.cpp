#include "../cs225/HSLAPixel.h"
#include "../Point.h"

#include "ColorPicker.h"
#include "MyColorPicker.h"

using namespace cs225;


MyColorPicker::MyColorPicker() { hue = 20; }
/**
 * Picks the color for pixel (x, y).
 * Using your own algorithm
 */
HSLAPixel MyColorPicker::getColor(unsigned x, unsigned y) {
  /* @todo [Part 3] */
  HSLAPixel pixel(hue, 1, 0.5);
  if (hue >= 360) {
    hue -= 210;
  } else {
    hue += 0.5;
  }
  return pixel;
}
