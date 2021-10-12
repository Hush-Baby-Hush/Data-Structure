#include "../cs225/HSLAPixel.h"
#include "../Point.h"

#include "ColorPicker.h"
#include "MyColorPicker.h"

using namespace cs225;

MyColorPicker::MyColorPicker(double decrement)
{
  nhue = 180;
  dec = decrement;
}

/**
 * Picks the color for pixel (x, y).
 * Using your own algorithm
 */
HSLAPixel MyColorPicker::getColor(unsigned x, unsigned y) {
  /* @todo [Part 3] */
  nhue -= dec;
  while (nhue <= 0)
      nhue += 360;
  HSLAPixel pixel(nhue, 1, 0.5);
  return pixel;
}

