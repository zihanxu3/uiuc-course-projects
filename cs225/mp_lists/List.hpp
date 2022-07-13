/**
 * @file list.cpp
 * Doubly Linked List (MP 3).
 */
#include <iostream>

using std::cout;
using std::endl;
template <class T>
List<T>::List() { 
  // @TODO: graded in MP3.1
  //@DID: deleted ListNode * and add length_
    head_ = NULL;
    tail_ = NULL;
    length_ = 0;
}

/**
 * Returns a ListIterator with a position at the beginning of
 * the List.
 */
template <typename T>
typename List<T>::ListIterator List<T>::begin() const {
  // @TODO: graded in MP3.1
  return List<T>::ListIterator(head_);
}

/**
 * Returns a ListIterator one past the end of the List.
 */
template <typename T>
typename List<T>::ListIterator List<T>::end() const {
  // @TODO: graded in MP3.1
  return List<T>::ListIterator(NULL);
}


/**
 * Destroys all dynamically allocated memory associated with the current
 * List class.
 */
template <typename T>
void List<T>::_destroy() {
  /// @todo Graded in MP3.1

  //for ListNode
  ListNode *temp = head_;
  while (temp != NULL) {
    ListNode *o = temp -> next;
    delete temp;
    temp = o;
  }
  head_ = NULL;
  tail_ = NULL;
  temp = NULL;

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
  ListNode * newNode = new ListNode(ndata);
  newNode -> next = head_;
  newNode -> prev = NULL;
  
  if (head_ != NULL) {
    head_ -> prev = newNode;
    head_ = newNode;
  }
  if (tail_ == NULL) {
    head_ = newNode;
    tail_ = newNode;
  }
  length_++;

}

/**
 * Inserts a new node at the back of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <typename T>
void List<T>::insertBack(const T & ndata) {
  /// @todo Graded in MP3.1

  ListNode * newNode = new ListNode(ndata);
  newNode -> next = NULL;
  newNode -> prev = tail_;

  if (tail_ != NULL) {
    tail_ -> next = newNode;
    tail_ = newNode;
  }
  if (head_ == NULL) {
    head_ = newNode;
    tail_ = newNode;
  }
  length_++;

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
  ListNode * curr = start;


  // ListNode * curr = start;

  // for (int i = 0; i < splitPoint && curr != NULL; i++) {
  //   curr = curr->next;
  // }

  // if (curr != NULL) {
  //     curr->prev->next = NULL;
  //     curr->prev = NULL;
  // }

  // return curr;


  for (int i = 0; i < splitPoint; i++) {
    if (curr == NULL) {
      return NULL;
    } 
    curr = curr->next;
  }

  if (curr != NULL) {
    if (curr -> prev != NULL) {
      curr->prev->next = NULL;
    } else {
      start = NULL;
    }
    curr->prev = NULL;
  }

  return curr;
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
  int times = length_ / 3;
  ListNode *track = NULL;
  ListNode *track_next = NULL;
  if (times >= 1) {
    times--;
    ListNode *tmp = head_;
    // = 1
    track = head_;
    // = 4
    track_next = head_->next->next->next;
    //3 next 1
    head_->next->next->next = head_;  
    //1 prev 3
    head_->prev = head_->next->next;
    //2 is head
    head_ = head_ -> next;
    head_ -> prev = NULL;

    //5 prev 1
    track_next->next->prev = track;
    //1 next 5
    track->next = track_next->next;
  }
  int count = 1;
  while (count <= times) {
    //update track and track next

    // 4
    ListNode *tmp_track = track_next;

    // 7 
    ListNode *tmp_track_next = track->next->next->next;

    //6 next 4
    track_next->next->next -> next = track_next;
    //4 prev 6
    track_next -> prev = track_next->next->next;

    if (tmp_track_next != NULL && tmp_track_next -> next != NULL && tmp_track_next -> next -> next != NULL) {
      //8prev4
      tmp_track_next->next->prev = track;
      //4 next 8
      tmp_track->next = tmp_track_next->next;
    } else if (tmp_track_next == NULL) { // if after 4 nothing exists
      //4
      tail_ = track_next;
      //4 next NULL
      track_next->next = NULL; 
    } else if (tmp_track_next != NULL) {
      //4 next 7
      tmp_track->next = tmp_track_next;
      //7 prev 4
      tmp_track_next -> prev = tmp_track;
    }
    //update track 
    track = tmp_track;
    track_next = tmp_track_next;
    count++;
  }
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
  if (startPoint == NULL || endPoint == NULL) {
    return;
  }
  if (startPoint -> next == NULL || endPoint -> prev == NULL || startPoint == endPoint) {
    return;
  }

  ListNode *start_ = startPoint;
  ListNode *end_ = endPoint;

  ListNode *start_prev = startPoint -> prev;
  ListNode *end_next = endPoint -> next;

  ListNode *temp1 = endPoint;
  ListNode *temp2 = endPoint -> prev;


  while (temp2 != start_prev) {
    ListNode* prev_temp2 = temp2 -> prev;
    temp1 -> next = temp2;
    temp2 -> prev = temp1;

    temp1 = temp2;
    temp2 = prev_temp2;
  }

  // connect head and tail
  if (start_prev == NULL) {
    head_ = end_;
    end_ -> prev = NULL;
    startPoint = head_;
  } else {
    end_ -> prev = start_prev;
    start_prev -> next = end_;
    startPoint = end_;
  }

  if (end_next == NULL) {
    tail_ = start_;
    tail_ -> next = NULL;
    endPoint = tail_;
  } else {
    start_ -> next = end_next;
    end_next -> prev = start_;
    endPoint = start_;
  }



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
  int k = length_ / n;
  int mod = length_ % n;


  ListNode* start = head_;
  ListNode* end = head_;

  if (k > 0) {
    for (int j = 1; j < n; j++) {
      end = end -> next;
    }
    for (int i = 0; i < k; i++) {
      reverse(start, end);
      if (i != k - 1) {
        for (int j = 0; j < n; j++) {
          start = start -> next;
          end = end -> next;
        }
      }
    }
  }
  if (mod != 0) {
    reverse(end -> next, tail_);
  }
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
  /// @todo Graded in MP3.2'
  if (first == NULL) {
    return second;
  } 
  if (second == NULL) {
    return first;
  }

  // f storing the list with head of less value; s storing the other list
  ListNode* f;
  ListNode* s;
  if (first->data < second -> data) {
    f = first;
    s = second;
  } else {
    f = second;
    s = first;
  }


  if (f -> next == NULL) {
    f->next = s;
    s->prev = f;
    return f;
  } 

  for (ListNode *cur = f; cur != NULL; cur = cur -> next) {
    if (cur -> next == NULL && s != NULL) {
      cur -> next = s;
      s -> prev = cur;
      return f;
    } 

    //this is wrong
    ListNode *needs_conn = cur;
    
    while (s != NULL && cur -> next != NULL && s -> data < cur -> next -> data) {

      ListNode *tmp = s -> next;
      cur -> next -> prev = s;

      s -> next = cur -> next;
      needs_conn -> next = s;
      s->prev = needs_conn;

      needs_conn = s;
      s = tmp;

    }

  }
  return f;
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

  if (chainLength == 1 || chainLength == 0) {
    return start;
  }

  ListNode *s = split(start, chainLength / 2);

  return merge(mergesort(start, chainLength / 2), mergesort(s, chainLength % 2 + chainLength / 2));
}
