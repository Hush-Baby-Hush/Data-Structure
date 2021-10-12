#include <cmath>
#include <iterator>
#include <iostream>

#include "../cs225/HSLAPixel.h"
#include "../cs225/PNG.h"
#include "../Point.h"

#include "ImageTraversal.h"

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

void ImageTraversal::Iterator::add_around(Point point)
{
  Point right(1+point.x , point.y);
  Point below(point.x, 1+point.y );
  Point left(point.x - 1, point.y);
  Point above(point.x, point.y - 1);
  if (right.x < png_.width() && tolerance_ > calculateDelta(png_.getPixel(right.x, right.y), png_.getPixel(start_.x, start_.y)))
  {
      method_->add(right);
  }

  if (below.y < png_.height() && tolerance_ > calculateDelta(png_.getPixel(below.x, below.y), png_.getPixel(start_.x, start_.y)))
  {
      method_->add(below);
  }

  if (left.x < png_.width() && tolerance_ > calculateDelta(png_.getPixel(left.x, left.y), png_.getPixel(start_.x, start_.y)))
  {
      method_->add(left);
  }

  if (above.y < png_.height() && tolerance_ > calculateDelta(png_.getPixel(above.x, above.y), png_.getPixel(start_.x, start_.y)))
  {
      method_->add(above);
  }
}

ImageTraversal::Iterator::Iterator(const PNG &png, const Point &start, double tolerance, ImageTraversal *method)
{
  png_ = png;
  method_ = method;
  start_ = start;
  visit_ = new bool[png_.width() * png_.height()];
  for (unsigned int i = 0; i < png_.width() * png_.height(); i++)
  {
    visit_[i] = false;
  }
  tolerance_ = tolerance;
  method_->add(start_);
  visit_[start_.y * png_.width() + start_.x] = true;
  add_around(start_);
}


/**
 * Default iterator constructor.
 */
ImageTraversal::Iterator::Iterator() {
  /** @todo [Part 1] */

  visit_ = NULL;
  tolerance_ = 0;
  method_ = NULL;
  png_ = PNG();
  start_ = Point();

}

/**
 * Iterator increment opreator.
 *
 * Advances the traversal of the image.
 */
ImageTraversal::Iterator & ImageTraversal::Iterator::operator++() {
  /** @todo [Part 1] */
  if (method_->empty())
  {
      method_ = NULL;
      png_ = PNG();
      start_ = Point();
      delete[] visit_;
      visit_ = NULL;
      tolerance_ = 0;
      return *this;
  }
  Point next = method_->pop();
  while (visit_[next.y * png_.width() + next.x] != false)
  {
      if (method_->empty())
      {
          method_ = NULL;
          png_ = PNG();
          start_ = Point();
          delete[] visit_;
          visit_ = NULL;
          tolerance_ = 0;
          return *this;
      }
      next = method_->pop();
  }
  visit_[next.y * png_.width() + next.x] = true;
  add_around(next);
  return *this;

}

/**
 * Iterator accessor opreator.
 *
 * Accesses the current Point in the ImageTraversal.
 */
Point ImageTraversal::Iterator::operator*() {
  /** @todo [Part 1] */
  return method_->peek();
}

/**
 * Iterator inequality operator.
 *
 * Determines if two iterators are not equal.
 */
bool ImageTraversal::Iterator::operator!=(const ImageTraversal::Iterator &other) {
  /** @todo [Part 1] */
  if (method_ == other.method_ && png_ == other.png_ && start_ == other.start_ &&
    visit_ == other.visit_ && tolerance_ == other.tolerance_)
    {
      return false;
    }
  return true;
}

