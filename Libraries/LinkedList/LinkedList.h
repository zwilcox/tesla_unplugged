#pragma once
#include <Arduino.h>

template<typename T>
struct Node
{
    T value;
    Node<T> * next;
    Node<T> * prev;
};

template<typename T>
class LinkedList
{

  public:
    LinkedList();
    void insert(T object);

    template<typename TT>
    friend class ListIterator;    

    void clear();
    uint16_t size();
    uint16_t isEmpty();
  
  private:
    Node<T> * remove(Node<T> * node);
    Node<T> * root;
    Node<T> * end;
    uint32_t _size;
    
};

template<typename T>
class ListIterator
{
  public:
    ListIterator(LinkedList<T> * list);
    
    T current();
    void removeCurrent();
    bool hasNext();
    bool hasPrev();
    bool moveNext();
    bool movePrev();
    bool isEmpty();
 
  private:
    Node<T> * _current;
    LinkedList<T> * _list;

};

template <typename T>
LinkedList<T>::LinkedList() : root(0), end(0)
{

}

template <typename T>
void LinkedList<T>::insert(T object)
{
  Node<T>* node = (Node<T>*)malloc(sizeof(Node<T>));
  node->value = object;
  node->next = 0;
  node->prev = 0;
 
  if(!root)
  {
    Serial.println("List empty, creating root node");
    root = node;
  }
  
  if(end)
  {
    Serial.println("Adding at end of list");
    end->next = node;
    node->prev = end;
  }

  _size++;
  end = node;
  Serial.println("assigning end to new node");
}

template <typename T>
void LinkedList<T>::clear()
{
  while(root)
  {
    Node<T> * tmp = root;
    root = root->next;
    delete(tmp);
  }
  _size = 0;
}

template <typename T>
Node<T> * LinkedList<T>::remove(Node<T> * node)
{
  Node<T> * toReturn = 0;
  if (node)
  {   
    if(node->next != 0 && node->prev != 0 )
    {
      node->next->prev = node->prev;
      node->prev->next = node->next;
      toReturn = node->next;
    }
    
    else if (node == end && node == root)
    {
      Serial.print("Removing only node... ");
    
      root = node->next;
      end = node->prev;
      toReturn = 0;
      
      
      Serial.print("Current is now: ");
      Serial.println((toReturn) ? true : false);
      
    }
    
    else if(node == root)
    {

      node->next->prev = 0; //null
      root = node->next;
      toReturn = root;
    }
    
    else if(node == end)
    {
      node->prev->next = 0; //null
      end = node->prev;
      toReturn = end;
    }
    _size--;
    delete node;
  }
  return toReturn;
}

template <typename T>
uint16_t LinkedList<T>::size()
{
  return _size;
}

template <typename T>
uint16_t LinkedList<T>::isEmpty()
{
  return (_size == 0);
}

template <typename T>
ListIterator<T>::ListIterator(LinkedList<T> *list) : _current(list->root), _list(list)
{

}

template <typename T>
T ListIterator<T>::current()
{
  return _current->value;
}

template <typename T>
bool ListIterator<T>::isEmpty()
{
  return (!_current);
}

template <typename T>
bool ListIterator<T>::moveNext()
{
  if (!_current) return false;
  if (_current->next)
  {
    _current = _current->next;
    return true;
  }

  return false;
}
template <typename T>
bool ListIterator<T>::hasNext()
{
  if (_current)
    return (_current->next);
  else
    return false;
}

template <typename T>
bool ListIterator<T>::hasPrev()
{
  if(_current)
    return (_current->prev);
  else
    return false;
}

template <typename T>
void ListIterator<T>::removeCurrent()
{
  _current = _list->remove(_current);
}

template <typename T>
bool ListIterator<T>::movePrev()
{
  if (!_current) return false;
  if (_current->prev)
  {
    _current = _current->prev;
    return true;
  }

  return false;
}