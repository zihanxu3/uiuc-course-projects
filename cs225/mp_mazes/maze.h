/* Your code here! */
#include <vector>

using std::vector;

class SquareMaze {
    private:

    public:
        int width_;
        int height_;

        int area_;
        
        vector<bool> downWalls;
        vector<bool> rightWalls;
        // No-parameter constructor. More...
        SquareMaze();

        // Makes a new SquareMaze of the given height and width. More...
        void makeMaze(int width, int height);
        
        // This uses your representation of the maze to determine whether it is possible to travel in the given direction from the square at coordinates (x,y). More...
        bool canTravel(int x, int y, int dir) const;
        
        // Sets whether or not the specified wall exists. More...
        void setWall(int x, int y, int dir, bool exists);
        
        // Solves this SquareMaze. More...
        vector<int> solveMaze();
        
        // Draws the maze without the solution. More...
        PNG *drawMaze() const;
        
        // This function calls drawMaze, then solveMaze; it modifies the PNG from drawMaze to show the solution vector and the exit. More...
        PNG *drawMazeWithSolution();
};  