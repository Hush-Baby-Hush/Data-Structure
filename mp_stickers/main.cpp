#include "Image.h"
#include "StickerSheet.h"

int main() {

  //
  // Reminder:
  //   Before exiting main, save your creation to disk as myImage.png
  //
  Image pic1;
  pic1.readFromFile("1.png");
  Image pic2;
  pic2.readFromFile("2.png");
  Image pic3;
  pic3.readFromFile("3.png");
  Image pic4;
  pic4.readFromFile("4.png");
  pic4.scale(0.2);
  pic3.scale(0.5);
  pic2.scale(500,150);

  StickerSheet stik(pic1, 3);
  stik.addSticker(pic2, 350, 400);
  stik.addSticker(pic3, 25, 350);
  stik.addSticker(pic4, 25, 25);

  Image pic = stik.render();
  pic.writeToFile("myImage.png");


  return 0;
}
