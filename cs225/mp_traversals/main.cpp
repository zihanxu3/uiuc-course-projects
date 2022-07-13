
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

  // @todo [Part 3]
  // - The code below assumes you have an Animation called `animation`
  // - The code provided below produces the `myFloodFill.png` file you must
  //   submit Part 3 of this assignment -- uncomment it when you're ready.
  PNG png;      png.readFromFile("my_traverse.png");
  
  FloodFilledImage image(png);
  BFS bfs(png, Point(70, 70), 0.5);
  DFS dfs(png, Point(140, 80), 0.5);

  BFS bfs2(png, Point(222, 54), 0.5);
  BFS bfs3(png, Point(246, 54), 0.5);
  BFS bfs4(png, Point(284, 54), 0.5);
  BFS bfs5(png, Point(308, 54), 0.5);



  MyColorPicker picker;
  MyColorPicker picker2;
  image.addFloodFill( bfs, picker );
  image.addFloodFill( dfs, picker2 );
  image.addFloodFill( bfs2, picker2 );
  image.addFloodFill( bfs3, picker2 );
  image.addFloodFill( bfs4, picker2 );
  image.addFloodFill( bfs5, picker2 );


  Animation animation = image.animate(200);
  
  PNG lastFrame = animation.getFrame( animation.frameCount() - 1 );
  lastFrame.writeToFile("myFloodFill.png");
  animation.write("myFloodFill.gif");

  return 0;
}
