#ifndef HASH_RECORD_H
#define HASH_RECORD_H

#include <iostream>

struct HashRecord
{
  int key;
  std::string item;

  HashRecord(int key=-1, std::string item="") : key(key), item(item) {}

  friend std::ostream& operator <<(std::ostream& outs, const HashRecord& h) {
    std::cout << "[" << h.key << ":" << h.item << "]";
    return outs;
  }

  friend bool operator < (const HashRecord& left, const HashRecord& right) {
    return left.key < right.key;
  }

  friend bool operator > (const HashRecord& left, const HashRecord& right) {
    return left.key > right.key;
  }

  friend bool operator == (const HashRecord& left, const HashRecord& right) {
    return left.key == right.key;
  }
};

#endif // HASH_RECORD_H