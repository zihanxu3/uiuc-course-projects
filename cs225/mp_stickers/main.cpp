#include "Image.h"
#include "StickerSheet.h"

int main() {

  //
  // Reminder:
  //   Before exiting main, save your creation to disk as myImage.png
  //
    Image base; base.readFromFile("base.png");
    Image st1;    st1.readFromFile("veri.png");
    Image st2; st2.readFromFile("cs.png");
    Image st3;    st3.readFromFile("gtk.png");
    Image st4;    st4.readFromFile("Seg.png");


    st3.scale(0.5);
    st4.scale(0.6);
    StickerSheet sheet(base, 5);
    sheet.addSticker(st1, 100, 300);
    sheet.addSticker(st2, 40, 100);
    sheet.addSticker(st3, 600, 600);
    sheet.addSticker(st4, 600, 100);


    sheet.render().writeToFile("myImage.png");
  return 0;
}
