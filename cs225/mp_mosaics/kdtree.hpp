/**
 * @file kdtree.cpp
 * Implementation of KDTree class.
 */

#include <utility>
#include <algorithm>
#include <cmath>

using namespace std;

template <int Dim>
bool KDTree<Dim>::smallerDimVal(const Point<Dim>& first,
                                const Point<Dim>& second, int curDim) const
{
    /**
     * @todo Implement this function!
     */
    if (first[curDim] < second[curDim]) {
      return true;
    } 
    if (first[curDim] > second[curDim]) {
      return false;
    } 
    if (first[curDim] == second[curDim]) { 
      return first < second;
    }
    return true;
}

template <int Dim>
bool KDTree<Dim>::shouldReplace(const Point<Dim>& target,
                                const Point<Dim>& currentBest,
                                const Point<Dim>& potential) const
{
    /**
     * @todo Implement this function!
     */
    double sum_po = 0;
    double sum_cur = 0;
    for (int i = 0; i < Dim; i++) {
      sum_po += (potential[i] - target[i]) * (potential[i] - target[i]);
      sum_cur += (currentBest[i] - target[i]) * (currentBest[i] - target[i]);
    }
    if (sum_po == sum_cur) {
      return potential < currentBest;
    } else if (sum_po < sum_cur) {
      return true;
    }
    return false;
}

template <int Dim>
KDTree<Dim>::KDTree(const vector<Point<Dim>>& newPoints)
{
    /**
     * @todo Implement this function!
     */
    vect_points = newPoints;
    vector<Point<Dim>> ctor_vec = newPoints;
    root = ctor_vec.size() == 0 ? NULL : _construct(ctor_vec, 0, ctor_vec.size() - 1, 0);
}
template <int Dim>
typename KDTree<Dim>::KDTreeNode * KDTree<Dim>::_construct(vector<Point<Dim>>& ctor_points, int left, int right, int dimension) {
  
  if (left == right) { // reach a leaf
    return new KDTreeNode(ctor_points[left]);
  }

  if (left > right) { // has go over the leaf
    return NULL;
  } 
  // calculate midpoint
  int midpoint = std::floor((left + right) / 2); 
  int newDimension = (dimension + 1) % Dim;
  Point<Dim> pt = select(ctor_points, left, right, midpoint, dimension);
  KDTreeNode *croot = new KDTreeNode(pt);
  croot -> left = _construct(ctor_points, left, midpoint - 1, newDimension);
  croot -> right = _construct(ctor_points, midpoint + 1, right, newDimension);
  return croot;
}

template <int Dim>
KDTree<Dim>::KDTree(const KDTree<Dim>& other) {
  /**
   * @todo Implement this function!
   */
  _copy(other);
}

template <int Dim>
const KDTree<Dim>& KDTree<Dim>::operator=(const KDTree<Dim>& rhs) {
  /**
   * @todo Implement this function!
   */
  if (rhs != *this) {
    this -> _destroy();
    _copy(rhs);
  }
  return *this;
}

template <int Dim>
void KDTree<Dim>::_destroy() { 
  for (unsigned i = 0; i < vect_points.size(); i++) {
    vect_points.pop_back();
  }
  _destroyy(root);
}

template <int Dim>
void KDTree<Dim>::_destroyy(KDTreeNode *croot) {
  if (croot == NULL) { return; }
  _destroyy(croot -> left);
  _destroyy(croot -> right);
  delete croot;
  croot = NULL;
}

template <int Dim>
KDTree<Dim> KDTree<Dim>::_copy(const KDTree<Dim>& rhs) {
  this = new KDTree(rhs.vect_points);
}

template <int Dim>
KDTree<Dim>::~KDTree() {
  /**
   * @todo Implement this function!
   */
   _destroy();
}

template <int Dim>
Point<Dim> KDTree<Dim>::findNearestNeighbor(const Point<Dim>& query) const
{
    /**
     * @todo Implement this function!
     */
    return _findNearestNeighbor(root, query, 0);
    
}

template <int Dim>
Point<Dim> KDTree<Dim>::_findNearestNeighbor(KDTree<Dim>::KDTreeNode *croot, const Point<Dim>& query, int dimension) const {
  int newDimension = (dimension + 1) % Dim;
  if (croot -> left == NULL && croot -> right == NULL) { // reached a leaf node
    return croot -> point; 
  } 
  Point<Dim> leaf = croot->point; 
  if (smallerDimVal(query, croot->point, dimension)) {
    if (croot -> left != NULL) {
      leaf = _findNearestNeighbor(croot -> left, query, newDimension);
    } else if (croot -> right != NULL) {
      Point<Dim> temp = _findNearestNeighbor(croot -> right, query, newDimension);
      leaf = _replace(query, leaf, temp);
    }
  } else if (!smallerDimVal(query, croot->point, dimension)) {
    if (croot -> right != NULL) {
      leaf = _findNearestNeighbor(croot -> right, query, newDimension);
    } else if (croot -> left != NULL) {
      Point<Dim> temp = _findNearestNeighbor(croot -> left, query, newDimension);
      leaf = _replace(query, leaf, temp);
    }
  }
  Point<Dim> best = leaf; 
  Point<Dim> parent = croot->point;


  best = _replace(query, best, parent);
  if (_distance(best, query) >= (double) (query[dimension] - parent[dimension])*(query[dimension] - parent[dimension])) {
    if (smallerDimVal(query, parent, dimension) && croot->right != NULL) {
      parent = _findNearestNeighbor(croot->right, query, newDimension);
      best = _replace(query, best, parent);
    }
    if (!smallerDimVal(query, parent, dimension) && croot->left != NULL) {
      parent = _findNearestNeighbor(croot->left, query, newDimension);
      best = _replace(query, best, parent);
    }
  }
  return best;
}

template <int Dim>
Point<Dim> KDTree<Dim>::_replace(const Point<Dim>& target, const Point<Dim>& currentBest, const Point<Dim>& potential) const {
  if (shouldReplace(target, currentBest, potential)) {
    return potential;
  } else {
    return currentBest;
  }
}


template <int Dim>
int KDTree<Dim>::_partition(vector<Point<Dim>>& ctor_points, int left, int right, int pivotIndex, int dimension) {
  Point<Dim> pivotValue = ctor_points[pivotIndex];
  // swap
  Point<Dim> temp = ctor_points[pivotIndex];
  ctor_points[pivotIndex] = ctor_points[right];
  ctor_points[right] = temp;
  
  int storeIndex = left;

  for (int i = left; i < right; i++) { // right - 1 ?
    if (smallerDimVal(ctor_points[i], pivotValue, dimension)) {
        Point<Dim> temp = ctor_points[storeIndex];
        ctor_points[storeIndex] = ctor_points[i];
        ctor_points[i] = temp;
        storeIndex++;
    }
  }
  temp = ctor_points[right];
  ctor_points[right] = ctor_points[storeIndex];
  ctor_points[storeIndex] = temp;
  return storeIndex;
}

template <int Dim>
Point<Dim> KDTree<Dim>::select(vector<Point<Dim>>& ctor_points, int left, int right, int k, int dimension) {
  if (left == right) {
    return ctor_points[left];
  }
  int pivotIndex = right - 1;
  pivotIndex = _partition(ctor_points, left, right, pivotIndex, dimension); 
  if (pivotIndex == k) {
    return ctor_points[k];
  } else if (k < pivotIndex) {
    return select(ctor_points, left, pivotIndex - 1, k, dimension);
  } else {
    return select(ctor_points, pivotIndex + 1, right, k, dimension);
  }
}

template <int Dim>
double  KDTree<Dim>::_distance(const Point<Dim>& point1, const Point<Dim>& point2) const {
  double sum = 0;
  double count = 0;

  while (count < Dim) {
    sum += (point1[count] - point2[count]) * (point1[count] - point2[count]);
    count++;
  }
  return sum;
}