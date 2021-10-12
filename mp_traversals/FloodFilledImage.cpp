#include "cs225/PNG.h"
#include <list>
#include <iostream>

#include "colorPicker/ColorPicker.h"
#include "imageTraversal/ImageTraversal.h"

#include "Point.h"
#include "Animation.h"
#include "FloodFilledImage.h"

using namespace cs225;


Animation FloodFilledImage::animate(unsigned frameInterval) const {
  Animation animation;
  /** @todo [Part 2] */
  PNG final_png = PNG(pic);
  for (unsigned i = 0; i < traverse.size(); i++)
  {
      ImageTraversal *traversal = traverse.at(i);
      ColorPicker *colorPicker = copick.at(i);
      unsigned num = frameInterval;
      animation.addFrame(final_png);
      for (const Point &p : *(traversal))
      {
          HSLAPixel &currPixel = final_png.getPixel(p.x, p.y);
          currPixel = colorPicker->getColor(p.x, p.y);
          num--;
          if (num == 0)
          {
              animation.addFrame(final_png);
              num = frameInterval;
          }
      }
      animation.addFrame(final_png);
  }
  return animation;
}

/**
 * Constructs a new instance of a FloodFilledImage with a image `png`.
 * 
 * @param png The starting image of a FloodFilledImage
 */
FloodFilledImage::FloodFilledImage(const PNG & png) {
  /** @todo [Part 2] */
  pic = png;
}

/**
 * Adds a FloodFill operation to the FloodFillImage.  This function must store the operation,
 * which will be used by `animate`.
 * 
 * @param traversal ImageTraversal used for this FloodFill operation.
 * @param colorPicker ColorPicker used for this FloodFill operation.
 */
void FloodFilledImage::addFloodFill(ImageTraversal & traversal, ColorPicker & colorPicker) {
  /** @todo [Part 2] */
  traverse.push_back(&traversal);
  copick.push_back(&colorPicker);  
}


