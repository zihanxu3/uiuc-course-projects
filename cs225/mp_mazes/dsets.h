/* Your code here! */
#include <vector>
#include <iostream>

using std::vector;
class DisjointSets {
    private:
        vector<int> data_;

    public:
        // Creates n unconnected root nodes at the end of the vector. More...
        void addelements(int num);
 	
        // This function should compress paths and works as described in lecture. More...
        int find(int elem);

        // This function should be implemented as union-by-size. More...
        void setunion(int a, int b);
 
        // This function should return the number of nodes in the up-tree containing the element. More...
        int size(int elem);
};
