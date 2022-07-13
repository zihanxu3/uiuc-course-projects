#include <cmath>
#include <iterator>
#include <iostream>

#include "../cs225/HSLAPixel.h"
#include "../cs225/PNG.h"
#include "../Point.h"

#include "ImageTraversal.h"

using std::cout;
using std::endl;

/**
 * Calculates a metric for the difference between two pixels, used to
 * calculate if a pixel is within a tolerance.
 *
 * @param p1 First pixel
 * @param p2 Second pixel
 * @return the difference between two HSLAPixels
 */
double ImageTraversal::calculateDelta(const HSLAPixel & p1, const HSLAPixel & p2) {
  double h = fabs(p1.h - p2.h);
  double s = p1.s - p2.s;
  double l = p1.l - p2.l;

  // Handle the case where we found the bigger angle between two hues:
  if (h > 180) { h = 360 - h; }
  h /= 360;

  return sqrt( (h*h) + (s*s) + (l*l) );
}

/**
 * Default iterator constructor.
 */
ImageTraversal::Iterator::Iterator() {
  /** @todo [Part 1] */
  position_ = Point((unsigned) -1, (unsigned) -1);
  start_ = Point((unsigned) -1, (unsigned) -1);
  traverse_ = NULL;
  tolerance_ = 0.0;
}


ImageTraversal::Iterator::Iterator(ImageTraversal* image_traversal, Point start, double tol, const PNG *png) {
  traverse_ = image_traversal;
  start_ = start;
  png_ = png;
  tolerance_ = tol;
  position_ = start;
  visited.resize(png_->width());
  for (unsigned i = 0; i < visited.size(); i++) {
    visited[i].resize(png_->height());
    for (unsigned j = 0; j < visited[i].size(); j++) {
      visited[i][j] = false;
    }
  }
}

/**
 * Iterator increment opreator.
 *
 * Advances the traversal of the image.
 */
ImageTraversal::Iterator & ImageTraversal::Iterator::operator++() {
  /** @todo [Part 1] */
  traverse_->pop();
  visited[position_.x][position_.y] = true;
  if (position_.x + 1 < png_->width()) {
    Point po(position_.x + 1, position_.y);
    if (validPoint(po)) {
      traverse_->add(po);
    }
  }
  if (position_.y + 1 < png_->height()) {
    Point po(position_.x, position_.y + 1);
    if (validPoint(po)) {
      traverse_->add(po);
    }
  }
  if (((int) position_.x) - 1 >= 0) {
    Point po(((int) position_.x) - 1, position_.y);
    if (validPoint(po)) {
      traverse_->add(po);
    }
  }
  if (((int) position_.y) - 1 >= 0) {
    Point po(position_.x, ((int) position_.y) - 1);
    if (validPoint(po)) {
      traverse_->add(po);
    }
  }  
  while (!traverse_ -> empty()) {
    position_ = traverse_->peek();
    if (vis_before(position_)) {
      position_ = traverse_->pop();
    } else {
      break;
    }
  }
  position_ = traverse_->peek();
  if (traverse_ -> empty()) {
    position_.x = -1;
    position_.y = -1;
    return *this;
  }
  return *this;
}

/**
 * Iterator accessor opreator.
 *
 * Accesses the current Point in the ImageTraversal.
 */
Point ImageTraversal::Iterator::operator*() {
  /** @todo [Part 1] */
  return traverse_->peek();
}

/**
 * Iterator inequality operator.
 *
 * Determines if two iterators are not equal.
 */
bool ImageTraversal::Iterator::operator!=(const ImageTraversal::Iterator &other) {
  /** @todo [Part 1] */
  return (this -> position_.x != other.position_.x) || (this -> position_.y != other.position_.y);
}

bool ImageTraversal::Iterator::validPoint(Point & pt) {
  //test if is within the tolerance
  const HSLAPixel &p1 = png_->getPixel(start_.x, start_.y);
  const HSLAPixel &p2 = png_->getPixel(pt.x, pt.y);
  if (!visited[pt.x][pt.y]) {
    if (calculateDelta(p1, p2) <= tolerance_) {
      return true;
    }
  }
  return false;
}

bool ImageTraversal::Iterator::vis_before(Point & pt) {
  return visited[pt.x][pt.y];
}



