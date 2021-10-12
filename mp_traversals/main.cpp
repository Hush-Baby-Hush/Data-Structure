
#include "cs225/PNG.h"
#include "FloodFilledImage.h"
#include "Animation.h"

#include "imageTraversal/DFS.h"
#include "imageTraversal/BFS.h"

#include "colorPicker/RainbowColorPicker.h"
#include "colorPicker/GradientColorPicker.h"
#include "colorPicker/GridColorPicker.h"
#include "colorPicker/SolidColorPicker.h"
#include "colorPicker/MyColorPicker.h"

using namespace cs225;

int main() {
  PNG pic;
  pic.readFromFile("tests/pacman.png");
  FloodFilledImage image(pic);
  BFS bfs(pic, Point(100, 50), 0.2);
  MyColorPicker MyRainbow(10);
  image.addFloodFill(bfs, MyRainbow);
  DFS dfs(pic, Point(100, 50), 0.2);
  HSLAPixel MyColor(10, 1, 0.5);
  SolidColorPicker MySolid(MyColor);
  image.addFloodFill(dfs, MySolid);
  Animation animation = image.animate(500);
  PNG lastFrame = animation.getFrame(animation.frameCount() - 1);
  lastFrame.writeToFile("myFloodFill.png");
  animation.write("myFloodFill.gif");
}
