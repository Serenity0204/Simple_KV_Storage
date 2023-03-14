#ifndef CHAINED_HASH_H
#define CHAINED_HASH_H

#include <cstdlib>    // Provides size_t
#include <cassert>    // Provides assert
#include <iomanip>    // Provides std::setw
#include <iostream>   // Provides std::cout
#include "hash_record.h"
#include "../AVL/avl_tree.h"


using namespace std;

template <class RecordType>
class ChainedHash
{
public:
  // TYPEDEF
  typedef RecordType record_type;
  // MEMBER CONSTANT
  static const std::size_t CAPACITY = 811;  
  // CONSTRUCTORS AND DESTRUCTOR
  ChainedHash();
  ChainedHash(const ChainedHash& source);
  ~ChainedHash();
  ChainedHash& operator = (const ChainedHash& source);
  // MODIFICATION MEMBER FUNCTIONS
  void insert(const RecordType& entry);
  void remove(int key);
  // CONSTANT MEMBER FUNCTIONS
  bool is_present(const int key) const;
  void find(int key, bool& found, RecordType& result) const;
  std::size_t size() const { return _size;}
  std::size_t capacity() const { return CAPACITY; }
  // OVERLOAD OPERATOR FUNCTIONS
  template<class U>
  friend std::ostream& operator << (std::ostream& outs, const ChainedHash<U>& hash);
private:
  // MEMBER VARIABLES
  AVL<RecordType> data[CAPACITY];
  std::size_t _size;
  // HELPER MEMBER FUNCTION
  std::size_t hash(int key) const;
  void print_hash(std::ostream& outs = std::cout) const;
};


// Implementation MEMBER FUNCTIONS

// TODO
template <class RecordType>
ChainedHash<RecordType>::ChainedHash()
{
    for(int i = 0; i < ChainedHash::CAPACITY; ++i) this->data[i] = AVL<RecordType>();
    this->_size = 0;   
}

template <class RecordType>
ChainedHash<RecordType>::ChainedHash(const ChainedHash<RecordType>& source)
{
    this->_size = source._size;
    for(int i = 0; i < this->_size; ++i) this->data[i] = source.data[i];
}

template <class RecordType>
ChainedHash<RecordType>::~ChainedHash(){}

template <class RecordType>
ChainedHash<RecordType>& ChainedHash<RecordType>::operator = (const ChainedHash<RecordType>& source)
{
    if(this == &source) return *this;
    this->_size = source._size;
    for(int i = 0; i < this->_size; ++i) this->data[i] = source.data[i];
    return *this;
}

// MODIFICATION MEMBER FUNCTIONS
template <class RecordType>
void ChainedHash<RecordType>::insert(const RecordType& entry)
{
  int key = entry.key;
  bool found = false;
  int index = this->hash(key);
  RecordType temp(entry.key);
  this->find(key, found, temp);
  // if not found, then just insert
  if(!found)
  {
    this->data[index].insert(entry);
    this->_size++;
    return;
  }
  // if found, then delete it first, then insert
  this->data[index].erase(temp);
  this->data[index].insert(entry);
}

template <class RecordType>
void ChainedHash<RecordType>::remove(int key)
{
  bool found = false;
  int index = this->hash(key);
  RecordType temp(key);
  this->find(key, found, temp);
  if(!found) return;
  // else found
  this->data[index].erase(temp);
  this->_size--;  
}
// CONSTANT MEMBER FUNCTIONS

template <class RecordType>
bool ChainedHash<RecordType>::is_present(const int key) const
{
  bool found = false;
  RecordType temp;
  this->find(key, found, temp);
  if(found) return true;
  return false;
}

template <class RecordType>
void ChainedHash<RecordType>::find(int key, bool& found, RecordType& result) const
{
  int index = this->hash(key);
  found = false;
  binary_tree_node<RecordType>* find = this->data[index].search(RecordType(key));
  if(find == nullptr) 
  {
    result = RecordType();
    return;
  }
  result = find->data();
  found = true;
}

template<class U>
std::ostream& operator << (std::ostream& outs, const ChainedHash<U>& hash)
{
  hash.print_hash(outs);
  return outs;
}

template <class RecordType>
std::size_t ChainedHash<RecordType>::hash(int key) const
{
  return key % ChainedHash::CAPACITY;
}


template <class RecordType>
void ChainedHash<RecordType>::print_hash(std::ostream& outs) const
{
  for (int i = 0; i < ChainedHash::CAPACITY; i++) {
      outs << '[' << std::setfill('0') << std::setw(3) << i << "] ";
      if(this->data[i].root() == nullptr) outs << "empty";
      print_inorder(this->data[i].root());
      outs << std::endl;
  }
  outs << "hashmap size:" << this->size() << endl;
}


#endif // CHAINED_HASH_H