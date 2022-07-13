/* Your code here! */
#include <maze.h>

// No-parameter constructor. More...
SquareMaze::SquareMaze() {
    width_ = 0;
    height_ = 0;
}

// Makes a new SquareMaze of the given height and width. More...
void SquareMaze::makeMaze(int width, int height) {
    downWalls.clear();
    rightWalls.clear(); 
    width_ = width;
    height_ = height;
    area_ = width_*height_;

    for (int i = 0; i < area_; i++) {
        downWalls.push_back(true);
        rightWalls.push_back(true);
    }
}

// This uses your representation of the maze to determine whether it is possible to travel in the given direction from the square at coordinates (x,y). More...
bool SquareMaze::canTravel(int x, int y, int dir) const {

}

// Sets whether or not the specified wall exists. More...
void SquareMaze::setWall(int x, int y, int dir, bool exists) {

}

// Solves this SquareMaze. More...
vector<int> SquareMaze::solveMaze() {

}

// Draws the maze without the solution. More...
PNG* SquareMaze::drawMaze() const {

}

// This function calls drawMaze, then solveMaze; it modifies the PNG from drawMaze to show the solution vector and the exit. More...
PNG* SquareMaze::drawMazeWithSolution() {

}