#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"

#include <string>

using namespace cs225;

void rotate(std::string inputFile, std::string outputFile) {
  // TODO: Part 2

  PNG* given = new PNG();
  given->readFromFile(inputFile);
  unsigned width = given->width();
  unsigned height = given->height();
  PNG* output = new PNG(width, height);
  for (unsigned y = 0; y < height; y++) 
  {
      for (unsigned x = 0; x < width; x++) 
      {
          HSLAPixel& curr = given->getPixel(x, y);
          HSLAPixel& rotat = output->getPixel(width - x -1, height - y -1);
          rotat = curr;
      }
  }
  output->writeToFile(outputFile);
  delete output;
  delete given;

}

cs225::PNG myArt(unsigned int width, unsigned int height) {
  cs225::PNG png(width, height);
  // TODO: Part 3
  int color = 8;
  int block = height / 100;
  for (unsigned y = 0; y < width; y++) 
  {
    for (unsigned x = 0; x < height; x++) 
    {
      int num = y / block;
      HSLAPixel& curr = png.getPixel(x, y);
      HSLAPixel* prev = new HSLAPixel(color + num, 0.8, 0.5);
      curr = *prev;
      if(y!=0 && y!= height-1 && y%(height/4)==0)
      {
        if((x/(width/4))<3 && (x/(width/4))>=1)
        {
          HSLAPixel& curr = png.getPixel(x, y);
          HSLAPixel* prev = new HSLAPixel(0,0.5,0.5,1);
          curr = *prev;
        }
      }
    }
  }
  return png;
}
