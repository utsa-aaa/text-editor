#ifndef LIST_HPP
#define LIST_HPP
/* List.hpp
 *
 * doubly-linked, double-ended list with Iterator interface
 * EECS 280 Project 4
 */

#include <iostream>
#include <iterator> //std::bidirectional_iterator_tag
#include <cassert>  //assert


template <typename T>
class List {
  //OVERVIEW: a doubly-linked, double-ended list with Iterator interface
public:
//default constructor
List()
:first(nullptr), last(nullptr), _size(0){}

//copy constructor
List(const List &other)
:first(nullptr), last(nullptr), _size(0){
  copy_all(other);
}

~List(){
  clear();
}

//asignment operator
List &operator=(const List &rhs){
  if(this==&rhs){
    return *this;
  }
  clear();
  copy_all(rhs);
  return *this;
}

  //EFFECTS:  returns true if the list is empty
  bool empty() const{
    return first==nullptr;
  }

  //EFFECTS: returns the number of elements in this List
  //HINT:    Traversing a list is really slow. Instead, keep track of the size
  //         with a private member variable. That's how std::list does it.
  int size() const{
    return _size;
  }

  //REQUIRES: list is not empty
  //EFFECTS: Returns the first element in the list by reference
  T & front(){
    assert(!empty());
    return first->datum;
  }

  //REQUIRES: list is not empty
  //EFFECTS: Returns the last element in the list by reference
  T & back(){
    assert(!empty());
    return last->datum;
  }

  //EFFECTS:  inserts datum into the front of the list
  void push_front(const T &datum){
    Node *p = new Node;
    p->datum = datum;
    if(empty()){
      p->next = nullptr;
      p->prev = nullptr;
      first = p;
      last = p;
    }
    else{
      p->next = first;
      first->prev = p;
      first = p;
    }
    _size++;
  }

  //EFFECTS:  inserts datum into the back of the list
  void push_back(const T &datum){
    Node *p = new Node;
    p->datum = datum;
    if(empty()){
      p->next = nullptr;
      p->prev = nullptr;
      first = p;
      last = p;
    }
    else{
      p->next = nullptr;
      p->prev = last;
      last->next = p;
      last = p;
    }
      _size++;
  }

  //REQUIRES: list is not empty
  //MODIFIES: may invalidate list iterators
  //EFFECTS:  removes the item at the front of the list
  void pop_front(){
    assert(!empty());

    if(_size!=1){
      Node *new_first = first->next;  
      delete first;
      first = new_first;
    }
    else{
      delete first;
      first = nullptr;
    }
    _size--;
  }

  //REQUIRES: list is not empty
  //MODIFIES: may invalidate list iterators
  //EFFECTS:  removes the item at the back of the list
  void pop_back(){
    assert(!empty());
    Node *new_last = last->prev;
    delete last;
    last = new_last;
    if(_size!=1){
      last->next=nullptr;
    }
    else{
      first = nullptr;
    }
    _size--;
  }

  //MODIFIES: may invalidate list iterators
  //EFFECTS:  removes all items from the list
  void clear(){
    while (!empty()) {
      pop_front();
    }
  }

  // You should add in a default constructor, destructor, copy constructor,
  // and overloaded assignment operator, if appropriate. If these operations
  // will work correctly without defining these, you should omit them. A user
  // of the class must be able to create, copy, assign, and destroy Lists.

private:
  //a private type
  struct Node {
    Node *next;
    Node *prev;
    T datum;
  };

  //REQUIRES: list is empty
  //EFFECTS:  copies all nodes from other to this
  void copy_all(const List<T> &other){
    assert(empty());
    for(Node *ptr=other.first;ptr!=nullptr;ptr=ptr->next){
      push_back(ptr->datum);
    }
  }

  Node *first;   // points to first Node in list, or nullptr if list is empty
  Node *last;    // points to last Node in list, or nullptr if list is empty
  int _size;
public:
  ////////////////////////////////////////
  class Iterator {
  public:
    //OVERVIEW: Iterator interface to List


    // Add a default constructor here. The default constructor must set both
    // pointer members to null pointers.
  Iterator()
  : list_ptr(nullptr), node_ptr(nullptr) {}
  


    // Add custom implementations of the destructor, copy constructor, and
    // overloaded assignment operator, if appropriate. If these operations
    // will work correctly without defining these, you should omit them. A user
    // of the class must be able to copy, assign, and destroy Iterators.
  // Iterator(const Iterator &other)
  // : list_ptr(other.list_ptr), node_ptr(other.node_ptr) {}



    // Your iterator should implement the following public operators:
    // *, ++ (both prefix and postfix), == and !=.
    // Equality comparisons must satisfy the following rules:
    // - two default-constructed iterators must compare equal
    // - a default-constructed iterator must compare unequal to an
    //   iterator obtained from a list, even if it is the end iterator
    // - two iterators to the same location in the same list must
    //   compare equal
    // - two iterators to different locations in the same list must
    //   compare unequal
    // - comparing iterators obtained from different lists results in
    //   undefined behavior
    //   - Your implementation can handle this however you like, but
    //     don't assume any particular behavior in your test cases --
    //     comparing iterators from different lists essentially
    //     violates the REQURES clause.
    // Note: comparing both the list and node pointers should be
    // sufficient to meet these requirements.

  
  T &operator*() const{
    return node_ptr->datum;
  }

  //prefix
  Iterator& operator++(){
   assert(node_ptr);
   node_ptr = node_ptr->next;
   return *this;
  }

  //postfix
  Iterator operator++(int){
   Iterator copy = *this;
   node_ptr=node_ptr->next;
   return copy;
  }

bool operator==(Iterator rhs) const{
  return(list_ptr==rhs.list_ptr && node_ptr==rhs.node_ptr);
 }

  bool operator!=(Iterator rhs) const{
    if(list_ptr==rhs.list_ptr && node_ptr!=rhs.node_ptr){
      return true;
    }
    if(list_ptr!=rhs.list_ptr && node_ptr!=rhs.node_ptr){
      return true;
    }
    if(list_ptr!=rhs.list_ptr && node_ptr==rhs.node_ptr){
      return true;
    }
    return false;
  }



    // Type aliases required to work with STL algorithms. Do not modify these.
    using iterator_category = std::bidirectional_iterator_tag;
    using value_type = T;
    using difference_type = std::ptrdiff_t;
    using pointer = T*;
    using reference = T&;

    // This operator will be used to test your code. Do not modify it.
    // REQUIRES: Iterator is either dereferenceable or an end Iterator
    // EFFECTS:  moves this Iterator to point to the previous element
    //           and returns a reference to this Iterator
    Iterator& operator--() { // prefix -- (e.g. --it)
      assert(list_ptr);
      if (node_ptr) {
        node_ptr = node_ptr->prev;
      } 
      else { // decrementing an end Iterator moves it to the last element
        node_ptr = list_ptr->last;
      }
      return *this;
    }

    // This operator will be used to test your code. Do not modify it.
    // REQUIRES: Iterator is either dereferenceable or an end Iterator
    // EFFECTS:  moves this Iterator to point to the previous element
    //           and returns a copy of the original Iterator
    Iterator operator--(int /*dummy*/) { // postfix -- (e.g. it--)
      Iterator copy = *this;
      operator--();
      return copy;
    }

    // REQUIRES: Iterator is dereferenceable
    // EFFECTS: returns the underlying element by pointer
    // NOTE: T must be a class type to use the syntax it->. If T has a
    //       member variable f, then it->f accesses f on the
    //       underlying T element.
    T* operator->() const {
      return &operator*();
    }

  private:
    const List *list_ptr; //pointer to the List associated with this Iterator
    Node *node_ptr; //current Iterator position is a List node
    // add any additional necessary member variables here


    // add any friend declarations here
    friend class List;


    // construct an Iterator at a specific position in the given List
    Iterator(const List *lp, Node *np)
    :list_ptr(lp),node_ptr(np){}

  };//List::Iterator
  ////////////////////////////////////////

  // return an Iterator pointing to the first element
  Iterator begin() const{
    return Iterator(this,first);
  }

  // return an Iterator pointing to "past the end"
  Iterator end() const{
    return Iterator(this,nullptr);
  }

  //REQUIRES: i is a valid, dereferenceable iterator associated with this list
  //MODIFIES: may invalidate other list iterators
  //EFFECTS: Removes a single element from the list container.
  //         Returns An iterator pointing to the element that followed the
  //         element erased by the function call
  Iterator erase(Iterator i){
    //removing from front
    if(i.node_ptr == first){
      Node *following = i.node_ptr->next;
      first = following;
      delete i.node_ptr;
      return Iterator(i.list_ptr,following);
    }

    //removing from end
    if(i.node_ptr == last){
      Node *previous = i.node_ptr->prev;
      last = previous;
      delete i.node_ptr;
      return Iterator(i.list_ptr,nullptr);
    }
    
    else{
      Node *previous = i.node_ptr->prev;
      Node *following = i.node_ptr->next;
      previous->next = following;
      following->prev = previous;
      delete i.node_ptr;
      return Iterator(i.list_ptr,following);
    }
  }

  //REQUIRES: i is a valid iterator associated with this list
  //EFFECTS: Inserts datum before the element at the specified position.
  //         Returns an iterator to the the newly inserted element.
Iterator insert(Iterator i, const T &datum){
  Node *in = new Node;
  in->datum = datum;
  //inserting at end
  if(i.node_ptr==nullptr){
    last->next = in;
    in->next = nullptr;
    in->prev = last;
    last = in;
    return Iterator(i.list_ptr,in);
  }
  //inserting into empty list
  if(first==nullptr){
    first = in;
    last = in;
    in->next = nullptr;
    return Iterator(i.list_ptr,in);
  }

  //inserting at beginning
  if(i.node_ptr==first){
    in->next = first;
    first = in;
    return Iterator(i.list_ptr,in);
  }

  //inserting normally
  else{
    in->prev = i.node_ptr->prev;
    i.node_ptr->prev = in;
    in->next = i.node_ptr;
    return Iterator(i.list_ptr,in);
  }
  
}
  

};//List


////////////////////////////////////////////////////////////////////////////////
// Add your member function implementations below or in the class above
// (your choice). Do not change the public interface of List, although you
// may add the Big Three if needed.  Do add the public member functions for
// Iterator.


#endif // Do not remove this. Write all your code above this line.
