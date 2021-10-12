/**
 * @file kdtree.cpp
 * Implementation of KDTree class.
 */

#include <utility>
#include <algorithm>
#include <math.h>

using namespace std;

template <int Dim>
bool KDTree<Dim>::smallerDimVal(const Point<Dim>& first,
                                const Point<Dim>& second, int curDim) const
{
    /**
     * @todo Implement this function!
     */

    if(first[curDim] == second[curDim])
    {
      return first < second;
    }
	  else 
    {
      return first[curDim] < second[curDim];
    }
}

template <int Dim>
bool KDTree<Dim>::shouldReplace(const Point<Dim>& target,
                                const Point<Dim>& currentBest,
                                const Point<Dim>& potential) const
{
    /**
     * @todo Implement this function!
     */

    double curDis = 0;
    double bestDis = 0;
    for(int curDim = 0; curDim < Dim; curDim ++)
    {
      bestDis += (currentBest[curDim] - target[curDim]) * (currentBest[curDim] - target[curDim]);
      curDis += (potential[curDim] - target[curDim]) * (potential[curDim] - target[curDim]); 
    }

    if(curDis == bestDis)
    {
      return potential < currentBest;
    }
      
    else 
    {
      return curDis < bestDis;
    }
}

template <int Dim>
KDTree<Dim>::KDTree(const vector<Point<Dim>>& newPoints)
{
    /**
     * @todo Implement this function!
     */
    if (newPoints.empty()) root = new KDTreeNode();
    else
    {
      vector<Point<Dim>> copyVector;

      for (size_t i = 0; i < newPoints.size(); i++)
      {
        copyVector.push_back(newPoints[i]);
      }

      root = _KDTree(copyVector, 0);
    }
}

template <int Dim>
typename KDTree<Dim>::KDTreeNode* KDTree<Dim>::_KDTree(vector<Point<Dim>> copyvector, int curDim)
{
	if(copyvector.empty())
	{
		return NULL;
	}
	if(copyvector.size() == 1)
	{
		KDTreeNode *newNode= new KDTreeNode(copyvector[0]);
		return newNode;
	}

	size_t median = (copyvector.size() + 1) / 2;

	Point<Dim> midPoint = kthSmallest(copyvector, 0 , copyvector.size() - 1 , median, curDim);

	vector<Point<Dim>> rightPoints;
	for (size_t i=median; i < copyvector.size(); i++) rightPoints.push_back(copyvector[i]);
	vector<Point<Dim>> leftPoints;
	for (size_t i = 0; i < median - 1; i++) leftPoints.push_back(copyvector[i]);

	KDTree<Dim>::KDTreeNode* newNode= new KDTreeNode(copyvector[median - 1]);
	newNode->left = _KDTree(leftPoints, (curDim + 1) % Dim);
	newNode->right = _KDTree(rightPoints,(curDim + 1) % Dim);

	return newNode;
}

template <int Dim>
Point<Dim> KDTree<Dim>::kthSmallest(vector<Point<Dim>>& Points, size_t left, size_t right, size_t k, int curDim)
{
	
	if(left == right) return Points[left];

	size_t index = partition(Points, left, right, curDim); 

	if(index - left == k - 1)
	{
		return Points[index];
	}
	if(index - left > k - 1)
	{
		return kthSmallest(Points, left, index - 1, k, curDim);
	}
	return kthSmallest(Points, index + 1, right, k - index + left - 1, curDim);
}
	

template <int Dim>
int KDTree<Dim>::partition(vector<Point<Dim>>& Points, size_t left, size_t right, int curDim)
{
	Point<Dim> pivot = Points[right];

	size_t i = left;
	for(size_t p = left; p <= right - 1; p++)
	{
		if(smallerDimVal(Points[p], pivot, curDim))
		{
			Point<Dim> tmp = Points[p];
			Points[p] = Points[i];
			Points[i] = tmp;
			i ++;
		}
	}
	Point<Dim> tmp = Points[right];
	Points[right] = Points[i];
	Points[i] = tmp;

	return i; 
}

template <int Dim>
KDTree<Dim>::KDTree(const KDTree& other) {
  /**
   * @todo Implement this function!
   */
  	root = _copy(other.root);

}

template <int Dim>
typename KDTree<Dim>::KDTreeNode* KDTree<Dim>::_copy(const KDTreeNode* subRoot)
{
	if (subRoot==NULL) return NULL;

	KDTreeNode* newNode = new KDTreeNode(subRoot->point);
	newNode->right = _copy(subRoot->right);
	newNode->left = _copy(subRoot->left);	
	return newNode;
}

template <int Dim>
const KDTree<Dim>& KDTree<Dim>::operator=(const KDTree& rhs) {
  /**
   * @todo Implement this function!
   */
	if(this != &rhs)
	{
		_destroy(root);
		root = _copy(rhs.root);
	}

	else return *this;
}

template <int Dim>
KDTree<Dim>::~KDTree() {
  /**
   * @todo Implement this function!
   */
	_destroy(root);
}

template <int Dim>
void KDTree<Dim>:: _destroy(KDTreeNode * subRoot)
{
	if(subRoot==NULL) return;

	_destroy(subRoot->left);
	_destroy(subRoot->right);

	delete subRoot;
}

template <int Dim>
Point<Dim> KDTree<Dim>::findNearestNeighbor(const Point<Dim>& query) const
{
    if (root == NULL) return Point<Dim>();
    else return _findNearest(query, root, root, 0)->point;
}

template <int Dim>
typename KDTree<Dim>::KDTreeNode* KDTree<Dim>::_findNearest(const Point<Dim>& query, KDTreeNode* curNode, KDTreeNode* bestNode, int curDim) const
{
    if (curNode->left == NULL && curNode->right == NULL) return curNode;

    if (smallerDimVal(query, curNode->point, curDim))
    {
      if(curNode->left != NULL)
      {
        bestNode = _findNearest(query, curNode->left, bestNode, (curDim + 1) % Dim);
      }
      else bestNode = curNode;
    }
    else
    {
		if(curNode->right != NULL)
		{
			bestNode = _findNearest(query, curNode->right, bestNode, (curDim + 1) % Dim);
		}
		else bestNode = curNode;
    }
	if (curNode->point == query) return curNode;

    if (shouldReplace(query, bestNode->point, curNode->point)) bestNode = curNode;
    

    double radius = distance(query, bestNode->point);
    double x = query[curDim] + radius;
	   
	if ((x >= curNode->point[curDim]))
    {
		if(curNode->right != NULL)
		{
			KDTreeNode* candidate = _findNearest(query, curNode->right, bestNode, (curDim + 1) % Dim);
       	 	if(shouldReplace(query, bestNode->point, candidate->point)) bestNode = candidate;
		}
    }

	radius = distance(query, bestNode->point);
	double y = query[curDim] - radius;
    if ((y <= curNode->point[curDim]))
    {
		if(curNode->left != NULL)
		{
			KDTreeNode* candidate = _findNearest(query, curNode->left, bestNode, (curDim + 1) % Dim);
        	if(shouldReplace(query, bestNode->point, candidate->point)) bestNode = candidate;
		}
    }
    return bestNode;
}


template <int Dim>
double KDTree<Dim>::distance(Point<Dim> p1, Point<Dim> p2) const
{
	double curDist = 0;

	for (int i = 0; i < Dim; i++)
	{
		curDist += (p1[i] - p2[i]) * (p1[i] - p2[i]);
	}
	
	curDist = sqrt(curDist);

	return curDist;
}