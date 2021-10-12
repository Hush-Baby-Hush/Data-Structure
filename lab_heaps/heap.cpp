
/**
 * @file heap.cpp
 * Implementation of a heap class.
 */
using namespace std;

template <class T, class Compare>
size_t heap<T, Compare>::root() const
{
    // @TODO Update to return the index you are choosing to be your root.
    return 0;
}

template <class T, class Compare>
size_t heap<T, Compare>::leftChild(size_t currentIdx) const
{
    // @TODO Update to return the index of the left child.
    size_t p=1+2*currentIdx;
    return p;
}

template <class T, class Compare>
size_t heap<T, Compare>::rightChild(size_t currentIdx) const
{
    // @TODO Update to return the index of the right child.
    size_t p=2*(currentIdx+1);
    return p;
}

template <class T, class Compare>
size_t heap<T, Compare>::parent(size_t currentIdx) const
{
    // @TODO Update to return the index of the parent.
    size_t p=(currentIdx-1)/2;
    return p;
}

template <class T, class Compare>
bool heap<T, Compare>::hasAChild(size_t currentIdx) const
{
    // @TODO Update to return whether the given node has a child
    return leftChild(currentIdx)<_elems.size();
}

template <class T, class Compare>
size_t heap<T, Compare>::maxPriorityChild(size_t currentIdx) const
{
    // @TODO Update to return the index of the child with highest priority
    ///   as defined by higherPriority()
    if ( _elems.size() <= leftChild(currentIdx)) 
    {
      return 0;
    }
    if (_elems.size() <= rightChild(currentIdx)) 
    {
      return leftChild(currentIdx);
    }
    if (higherPriority(_elems[leftChild(currentIdx)], _elems[rightChild(currentIdx)])) 
    {
      return leftChild(currentIdx);
    }
    return rightChild(currentIdx);
}

template <class T, class Compare>
void heap<T, Compare>::heapifyDown(size_t currentIdx)
{
    if (hasAChild(currentIdx)==false)
    {
        return;
    }

    size_t p = maxPriorityChild(currentIdx);

    if (higherPriority(_elems[p], _elems[currentIdx])==true) 
    {
        swap(_elems[currentIdx], _elems[p]);
        heapifyDown(p);
    }
}

template <class T, class Compare>
void heap<T, Compare>::heapifyUp(size_t currentIdx)
{
    if (currentIdx == root())
        return;
    size_t parentIdx = parent(currentIdx);
    if (higherPriority(_elems[currentIdx], _elems[parentIdx])) {
        std::swap(_elems[currentIdx], _elems[parentIdx]);
        heapifyUp(parentIdx);
    }
}

template <class T, class Compare>
heap<T, Compare>::heap()
{
    // @TODO Depending on your implementation, this function may or may
    ///   not need modifying
}

template <class T, class Compare>
heap<T, Compare>::heap(const std::vector<T>& elems) 
{
    _elems=elems;
    int p=parent(_elems.size()-1);
	for (int i=p; i>=0; i--) 
    {
		heapifyDown(i);
	}
}

template <class T, class Compare>
T heap<T, Compare>::pop()
{
    // @TODO Remove, and return, the element with highest priority
    if (_elems.empty()) 
    {
      return T();
    }
    T p = _elems[0];
    swap(_elems[0], _elems[_elems.size() - 1]);
    _elems.pop_back();
    heapifyDown(0);
    return p;
}

template <class T, class Compare>
T heap<T, Compare>::peek() const
{
    // @TODO Return, but do not remove, the element with highest priority
    if (_elems.empty()) 
    {
      return T();
    }
    return _elems[0];
}

template <class T, class Compare>
void heap<T, Compare>::push(const T& elem)
{
    _elems.push_back(elem);

    heapifyUp(_elems.size()-1);
}

template <class T, class Compare>
void heap<T, Compare>::updateElem(const size_t & idx, const T& elem)
{
    // @TODO In-place updates the value stored in the heap array at idx
    // Corrects the heap to remain as a valid heap even after update
    _elems[idx]=elem;
    if (idx==root()) 
    {
      heapifyDown(idx);
    }
    if (!hasAChild(idx)) 
    {
      heapifyUp(idx);
    }
    T parent = _elems[idx/2];
    if (higherPriority(elem, parent)) 
    {
      heapifyUp(idx);
    } 
    else 
    {
      heapifyDown(idx);
    }

}


template <class T, class Compare>
bool heap<T, Compare>::empty() const
{
    // @TODO Determine if the heap is empty
    bool p=_elems.empty();
    return p;
}

template <class T, class Compare>
void heap<T, Compare>::getElems(std::vector<T> & heaped) const
{
    for (size_t i = root(); i < _elems.size(); i++) {
        heaped.push_back(_elems[i]);
    }
}
