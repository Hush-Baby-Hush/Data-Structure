/**
 * @file list.cpp
 * Doubly Linked List (MP 3).
 */

template <class T>
List<T>::List() 
{ 
  // @TODO: graded in MP3.1
  head_ = NULL;
  tail_ = NULL;
  length_ = 0;
}

/**
 * Returns a ListIterator with a position at the beginning of
 * the List.
 */
template <typename T>
typename List<T>::ListIterator List<T>::begin() const 
{
  // @TODO: graded in MP3.1
  return List<T>::ListIterator(head_);}

/**
 * Returns a ListIterator one past the end of the List.
 */
template <typename T>
typename List<T>::ListIterator List<T>::end() const {
  // @TODO: graded in MP3.1
  return List<T>::ListIterator(NULL);
}

/**
 * Reverses blocks of size n in the current List. You should use your
 * reverse( ListNode * &, ListNode * & ) helper function in this method!
 *
 * @param n The size of the blocks in the List to be reversed.
 */
template <typename T>
void List<T>::reverseNth(int n) {
  /// @todo Graded in MP3.2
  if (n==1 || n<0 || !n  )
  {
    return;
  }
  if (n>=length_)
  {
    reverse();
    return;
  }
  int block = length_/n;
  int the_rest = length_%n;
  ListNode* curr = head_;
  ListNode* temp = curr;
  for (int i = 0; i < block; i++)
  {
    for (int j = 0; j < n-1; j++)
    {
      temp = temp->next;
    }
    if (!i)
    {
      reverse(head_, temp);
    }
    else
    {
      reverse(curr, temp);      
    }
    curr = temp->next;
    temp = curr;    
  }
  reverse(curr, tail_);
  return;
}

/**
 * Destroys all dynamically allocated memory associated with the current
 * List class.
 */
template <typename T>
void List<T>::_destroy() {
  /// @todo Graded in MP3.1
  if (!tail_ && !head_ )
  {
    return;
  }
  ListNode* curr = head_;
  ListNode* temp = head_->next;
  while (temp)
  {
    delete curr;
    curr = temp;
    temp = temp->next;
  }
  delete curr;
  length_ = 0;
  head_ = NULL;
  tail_ = NULL;
  return;
}



/**
 * Helper function to split a sequence of linked memory at the node
 * splitPoint steps **after** start. In other words, it should disconnect
 * the sequence of linked memory after the given number of nodes, and
 * return a pointer to the starting node of the new sequence of linked
 * memory.
 *
 * This function **SHOULD NOT** create **ANY** new List or ListNode objects!
 *
 * This function is also called by the public split() function located in
 * List-given.hpp
 *
 * @param start The node to start from.
 * @param splitPoint The number of steps to walk before splitting.
 * @return The starting node of the sequence that was split off.
 */
template <typename T>
typename List<T>::ListNode * List<T>::split(ListNode * start, int splitPoint) {
  /// @todo Graded in MP3.1
  if ( splitPoint<0 || !start || !splitPoint )
  {
    return start;
  }
  ListNode * curr = start;
  for (int i = 0; curr != NULL && i < splitPoint ; i++) 
  {
    curr = curr->next;
  }
  if (curr != NULL) 
  {
      curr->prev->next = NULL;
      curr->prev = NULL;
      return curr;
  }
  return NULL;
}


/**
 * Inserts a new node at the back of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <typename T>
void List<T>::insertBack(const T & ndata) {
  ListNode * new_data = new ListNode(ndata);
  new_data -> next = NULL;
  new_data -> prev = tail_;
  if (tail_ != NULL) 
  {
    tail_->next = new_data;
    tail_ = new_data;
  }
  if (head_ == NULL) 
  {
    tail_ = new_data;
    head_ = new_data;
  }
  length_++;
  return;
}


/**
  * Modifies List using the rules for a TripleRotate.
  *
  * This function will to a wrapped rotation to the left on every three 
  * elements in the list starting for the first three elements. If the 
  * end of the list has a set of 1 or 2 elements, no rotation all be done 
  * on the last 1 or 2 elements.
  * 
  * You may NOT allocate ANY new ListNodes!
  */
template <typename T>
void List<T>::tripleRotate() {
  // @todo Graded in MP3.1
  if ( length_ < 3 )
  {
    return;
  }
  int group = length_/3;
  int the_rest = length_%3;
  ListNode * curr = head_;
  ListNode * temp = head_->next;
  head_ = temp;
  for (int i = 0; i < group; i++)
  {
    temp->prev = curr->prev;
    if (curr->prev)
    {
      curr->prev->next = temp;
    }
    temp = temp->next;
    curr->prev = temp;
    if (temp->next)
    {
      temp->next->prev = curr;
    }
    curr->next = temp->next;
    temp->next = curr;
    curr = curr->next;
    if (curr!=nullptr)
    {
      temp = curr->next;
    }
  }
  for (int j = 0; j < the_rest; j++)
  {
    curr = curr->next;
  }
  tail_ = curr;
  return;
}
/**
 * Inserts a new node at the front of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <typename T>
void List<T>::insertFront(T const & ndata) {
  /// @todo Graded in MP3.1
  ListNode * new_data = new ListNode(ndata);
  new_data -> next = head_;
  new_data -> prev = NULL;
  if (head_ != NULL) 
  {
    head_ -> prev = new_data;
    head_ = new_data;
  }
  if (tail_ == NULL) 
  {
    tail_ = new_data;
    head_ = new_data;
  }
  length_++;
  return;

}



/**
 * Reverses the current List.
 */
template <typename T>
void List<T>::reverse() {
  reverse(head_, tail_);
}

/**
 * Helper function to reverse a sequence of linked memory inside a List,
 * starting at startPoint and ending at endPoint. You are responsible for
 * updating startPoint and endPoint to point to the new starting and ending
 * points of the rearranged sequence of linked memory in question.
 *
 * @param startPoint A pointer reference to the first node in the sequence
 *  to be reversed.
 * @param endPoint A pointer reference to the last node in the sequence to
 *  be reversed.
 */
template <typename T>
void List<T>::reverse(ListNode *& startPoint, ListNode *& endPoint) {
  /// @todo Graded in MP3.2
  if (!endPoint || !startPoint ||  startPoint == endPoint )
  {
    return;
  }
  ListNode* curr = startPoint->next;
  ListNode* temp = curr->next;
  while (curr != endPoint)
  {
    curr->next = curr->prev;
    curr->prev = temp;
    curr = temp;
    temp = temp->next;
  }

  curr->next = curr->prev;
  if (startPoint->prev)
  {
    curr->prev = startPoint->prev; 
    startPoint->prev->next = curr;
  }
  else
  {
    curr->prev = NULL;
  }
  startPoint->prev = startPoint->next;
  if (temp)
  {
    temp->prev = startPoint;
    startPoint->next = temp;
  }
  else
  {
    startPoint->next = NULL;
  }

  temp = startPoint;
  startPoint = endPoint;
  endPoint = temp;
  return;

}


/**
 * Helper function to merge two **sorted** and **independent** sequences of
 * linked memory. The result should be a single sequence that is itself
 * sorted.
 *
 * This function **SHOULD NOT** create **ANY** new List objects.
 *
 * @param first The starting node of the first sequence.
 * @param second The starting node of the second sequence.
 * @return The starting node of the resulting, sorted sequence.
 */
template <typename T>
typename List<T>::ListNode * List<T>::merge(ListNode * first, ListNode* second) {
  /// @todo Graded in MP3.2
  if (!first)
  {
    return second;
  }
  if (!second)
  {
    return first;
  }
  ListNode* temp = second;
  ListNode* temp2;
  ListNode* curr = first;
  while (temp)
  {
    temp2 = temp->next;
    if (curr->data < temp->data)
    {
      if (!curr->next)
      {
        curr->next = temp;
        temp->prev = curr;
        return first;
      }
      else
      {
        curr = curr->next;
        continue;
      }
    }
    else
    {
      if (curr->prev)
      {
        curr->prev->next = temp;
        temp->prev = curr->prev;
        temp->next = curr;
        curr->prev = temp;
        temp = temp2;
        continue;
      }
      else
      {
        temp->next = curr;
        curr->prev = temp;
        temp->prev = nullptr;
        first = temp;
        temp = temp2;
        continue;
      }
    }
  }
  
return first;
}

/**
 * Sorts a chain of linked memory given a start node and a size.
 * This is the recursive helper for the Mergesort algorithm (i.e., this is
 * the divide-and-conquer step).
 *
 * Called by the public sort function in List-given.hpp
 *
 * @param start Starting point of the chain.
 * @param chainLength Size of the chain to be sorted.
 * @return A pointer to the beginning of the now sorted chain.
 */
template <typename T>
typename List<T>::ListNode* List<T>::mergesort(ListNode * start, int chainLength) {
  /// @todo Graded in MP3.2
  if (chainLength<=0 || !start )
  {
    return NULL;
  }
  if (chainLength==1)
  {
    return start;
  }
  int first_ = chainLength/2;
  int second_ = chainLength - first_;
  ListNode* second = split(start, first_);

  ListNode* l1 = mergesort(start, first_);
  ListNode* l2 = mergesort(second, second_);
  ListNode* newlist = merge(l1, l2);
  return newlist;
}

/**
 * Merges the given sorted list into the current sorted list.
 *
 * @param otherList List to be merged into the current list.
 */
template <typename T>
void List<T>::mergeWith(List<T> & otherList) {
    // set up the current list
    head_ = merge(head_, otherList.head_);
    tail_ = head_;

    // make sure there is a node in the new list
    if (tail_ != NULL) {
        while (tail_->next != NULL)
            tail_ = tail_->next;
    }
    length_ = length_ + otherList.length_;

    // empty out the parameter list
    otherList.head_ = NULL;
    otherList.tail_ = NULL;
    otherList.length_ = 0;
}