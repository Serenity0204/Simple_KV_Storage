#include "gtest/gtest.h"
#include <iostream>
#include <iomanip>
#include <unordered_set>
//------------------------------------------------------------------------------
//@TODO: include all files we are testing:
#include "../../includes/database/simple_kv_db/header/HashTable/chained_hash.h"



//------------------------------------------------------------------------------

using namespace std;



bool test_hash1(bool debug1 = false, bool debug2 = false)
{
  ChainedHash<HashRecord> hash;
  int size = 25;
  for(int i = 0; i < size; ++i)
  {
    hash.insert(HashRecord(i, string("item__") + to_string(i)));
    bool found = hash.is_present(i);
    if(debug2)
    {
      cout << "Hash is:" << endl;
      cout << hash << endl;
    }
    if(!found) 
    {
      cout << "not found " << i << " when it's present" << endl;
      return false;
    }
  }
  if(debug1)
  {
    cout << "Hash is:" << endl;
    cout << hash << endl;
  }
  if(hash.size() != size) 
  {
    cout << "size error" << endl;
    return false;
  }
  return true;
}

bool test_hash2(bool debug1 = false, bool debug2 = false)
{
  ChainedHash<HashRecord> hash;
  int size = 30;
  for(int i = 0; i < size; ++i)
  {
    int val = (i % 2 == 0) ? i : i * i;
    hash.insert(HashRecord(val, string("item__") + to_string(val)));
    bool found = hash.is_present(val);
    if(debug2)
    {
      cout << "Hash is:" << endl;
      cout << hash << endl;
    }
    if(!found) 
    {
      cout << "not found " << val << " when it's present" << endl;
      return false;
    }
  }
  if(debug1)
  {
    cout << "Hash is:" << endl;
    cout << hash << endl;
  }
  if(hash.size() != size) 
  {
    cout << "size error" << endl;
    return false;
  }
  return true;
}



bool test_hash3(bool debug1 = false, bool debug2 = false)
{
  ChainedHash<HashRecord> hash;
  unordered_set<string> s;
  int size = 10;
  for(int i = 0; i < size; ++i)
  {
    int val = i;
    s.insert(string("item__") + to_string(val * 2));

    hash.insert(HashRecord(val, string("item__") + to_string(val)));
    bool found = hash.is_present(val);
    if(debug2)
    {
      cout << "Hash is:" << endl;
      cout << hash << endl;
    }
    if(!found) return false;
  }
  if(debug1)
  {
    cout << "Hash is:" << endl;
    cout << hash << endl;
  }
  if(hash.size() != size) return false;
  for(int i = 0; i < size; ++i)
  {
    int val = i;
    hash.insert(HashRecord(val, string("item__") + to_string(val * 2)));
    bool found = hash.is_present(val);
    if(debug2)
    {
      cout << "Hash is:" << endl;
      cout << hash << endl;
    }
    if(!found) return false;
    HashRecord hr;
    hash.find(val, found, hr);
    if(!found || !s.count(hr.item)) return false;
  }
  if(debug1)
  {
    cout << "Hash is:" << endl;
    cout << hash << endl;
  }
  if(hash.size() != size) return false;
  return true;
}

// insert duplicate
bool test_hash4(bool debug1=false, bool debug2=false)
{
  ChainedHash<HashRecord> hash;
  int size = 25;
  for(int i = 0; i < size; ++i)
  {
    hash.insert(HashRecord(0, string("item__") + to_string(i)));
    bool found = hash.is_present(i);
    if(debug2)
    {
      cout << "Hash is:" << endl;
      cout << hash << endl;
    }
    if(!found && i == 0) 
    {
      cout << "not found " << 0 << " when it's present in is present" << endl;
      return false;
    }
    if(found && i != 0)
    {
      cout << "found non existing index " << i << endl;
      return false;
    }
  }
  if(debug1)
  {
    cout << "Hash is:" << endl;
    cout << hash << endl;
  }
  if(hash.size() != 1) 
  {
    cout << "size error" << endl;
    return false;
  }
  HashRecord result;
  bool found = false;
  hash.find(0, found, result);
  if(!found) 
  {
    cout << "not found " << 0 << " when it's present in find" << endl;
    return false;
  }
  if(result.item != "item__24")
  {
    cout << "value not correct" << endl;
    return false;
  }
  return true;

}



//------------------------------------------------------------------------------


// Lord help me! 
const bool debug1 = false;
const bool debug2 = false;



TEST(TEST_HASH, TestHash1)
{
  bool success = test_hash1(debug1, debug2);
  EXPECT_EQ(success, true);
}

TEST(TEST_HASH, TestHash2)
{
  bool success = test_hash2(debug1, debug2);
  EXPECT_EQ(success, true);
}

TEST(TEST_HASH, TestHash3)
{
  bool success = test_hash3(debug1, debug2);
  EXPECT_EQ(success, true);
}

TEST(TEST_HASH, TestHash4)
{
  bool success = test_hash4(debug1, debug2);
  EXPECT_EQ(success, true);
}




//------------------------------------------------------------------------------


int main(int argc, char **argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  std::cout<<"\n\n----------running test_chained_hash.cpp---------\n\n"<<std::endl;
  return RUN_ALL_TESTS();
}