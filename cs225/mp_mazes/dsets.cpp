/* Your code here! */
#include "dsets.h"

using std::vector;

// Creates n unconnected root nodes at the end of the vector. More...
void DisjointSets::addelements(int num) {
    for (int i = 0; i < num; i++) {
        data_.push_back(-1);
    }
}

// This function should compress paths and works as described in lecture. More...
int DisjointSets::find(int elem) {
    if (data_[elem] < 0) {
        return elem;
    } else {
        int root = find(data_[elem]);
        data_[elem] = root;
        return root;
    }
}

// This function should be implemented as union-by-size. More...
void DisjointSets::setunion(int a, int b) {
    a = find(a);
    b = find(b);
    int newSize = data_[a] + data_[b];
    if (data_[a] < data_[b]) {
        data_[b] = a;
        data_[a] = newSize;
    } else {
        data_[a] = b;
        data_[b] = newSize;
    }
}

// This function should return the number of nodes in the up-tree containing the element. More...
int DisjointSets::size(int elem) {
    int subroot = find(elem);
    return -data_[subroot];
}