#include "hashmap_v1.hpp"
#include <cassert>
#include <iostream>

void testHashMapInt() {
  HashMapV1<int, int> hashmap; // Default constructor
  hashmap.insert(2, 3);
  hashmap.insert(4, 2);
  hashmap.insert(6, 5);
  assert(hashmap.size() == 3);

  // Copy constructor
  HashMapV1<int, int> hashmap1(hashmap);
  assert(hashmap.size() == 3);
  int value = 0;
  bool find = false;
  find = hashmap1.find(6, value);
  assert(find == true);
  assert(value == 5);

  find = hashmap1.find(2, value);
  assert(find == true);
  assert(value == 3);

  find = hashmap1.find(4, value);
  assert(find == true);
  assert(value == 2);

  find = hashmap1.find(7, value);
  assert(find == false);

  // Copy Assignment operator
  HashMapV1<int, int> hashmap2 = hashmap1;
  assert(hashmap2.size() == 3);
  value = 0;
  find = false;
  find = hashmap2.find(6, value);
  assert(find == true);
  assert(value == 5);

  find = hashmap2.find(2, value);
  assert(find == true);
  assert(value == 3);

  find = hashmap2.find(4, value);
  assert(find == true);
  assert(value == 2);

  find = hashmap2.find(7, value);
  assert(find == false);

  // Move constructor
  HashMapV1<int, int> hashmap3(std::move(hashmap));
  assert(hashmap.size() == 0);
  assert(hashmap3.size() == 3);
  value = 0;
  find = false;
  find = hashmap3.find(6, value);
  assert(find == true);
  assert(value == 5);

  find = hashmap3.find(2, value);
  assert(find == true);
  assert(value == 3);

  find = hashmap3.find(4, value);
  assert(find == true);
  assert(value == 2);

  find = hashmap3.find(7, value);
  assert(find == false);

  // Move Assignment operator
  HashMapV1<int, int> hashmap4 = std::move(hashmap3);
  assert(hashmap3.size() == 0);
  assert(hashmap4.size() == 3);
  value = 0;
  find = false;
  find = hashmap4.find(6, value);
  assert(find == true);
  assert(value == 5);

  find = hashmap4.find(2, value);
  assert(find == true);
  assert(value == 3);

  find = hashmap4.find(4, value);
  assert(find == true);
  assert(value == 2);

  find = hashmap4.find(7, value);
  assert(find == false);
}

void testHashMapWithStruct() {
  int constructor = 0;
  int destructor = 0;
  struct S {
    S(int& constructor, int& destructor)
        : m_constructor(constructor), m_destructor(destructor) {
      m_constructor++;
    }

    S& operator=(const S& copy) {
      m_constructor = copy.m_constructor;
      m_destructor = copy.m_destructor;
      m_constructor++;
      return *this;
    }

    bool operator==(const S& other) const {
      return m_constructor == other.m_constructor &&
             m_destructor == other.m_destructor;
    }

    S(const S& copy)
        : m_constructor(copy.m_constructor), m_destructor(copy.m_destructor) {
      m_constructor++;
    }

    ~S() { m_destructor++; }

    int& m_constructor;
    int& m_destructor;
  };
  {
    {
      HashMapV1<S, int> hashmap1;
      S s1(constructor, destructor);
      S s2(constructor, destructor);
      hashmap1.insert(s1, 1);
      hashmap1.insert(s2, 2);
      HashMapV1<S, int> hashmap2;
      assert(constructor == 3);
      assert(destructor == 0);
      {
        HashMapV1<S, int> hashmap2;
        S s3(constructor, destructor);
        S s4(constructor, destructor);
        hashmap2.insert(s3, 3);
        hashmap2.insert(s4, 4);
        assert(constructor == 6);
        assert(destructor == 0);
        {
          HashMapV1<S, int> hashmap3;
          S s5(constructor, destructor);
          S s6(constructor, destructor);
          hashmap3.insert(s5, 5);
          hashmap3.insert(s6, 6);
          assert(constructor == 9);
          assert(destructor == 0);
          {
            S s7(constructor, destructor);
            S s8(constructor, destructor);
            HashMapV1<S, int> hashmap4;
            hashmap4.insert(s7, 7);
            hashmap4.insert(s8, 8);
            assert(constructor == 12);
          }
          assert(constructor == 12);
          assert(destructor == 3);
        }
        assert(constructor == 12);
        assert(destructor == 6);
      }
      assert(constructor == 12);
      assert(destructor == 9);
    }
    assert(constructor == 12);
    assert(destructor == 12);
  }
}

void stressTestRemoval() {
  HashMapV1<int, int> stressMap;
  for (int i = 0; i < 10000; i++) {
    stressMap.insert(i, i * 2);
  }
  for (int i = 0; i < 10000; i += 2) {
    bool ans = stressMap.remove(i);
  }
  assert(stressMap.size() == 5000);

  int value = 0;
  bool find = 0;
  find = stressMap.find(2, value);
  assert(find == false);
  find = stressMap.find(3, value);
  assert(find == true);
  assert(value == 6);
}

void testDuplicateInsertion() {
  int constructorValue = 0;
  int destructorValue = 0;

  struct ReferenceStruct {
    ReferenceStruct(int& constructor, int& destructor)
        : constructorValue_(constructor), destructorValue_(destructor) {
      constructorValue_++;
    }
    ~ReferenceStruct() { destructorValue_++; }
    bool operator==(const ReferenceStruct& ref) const {
      return constructorValue_ == ref.constructorValue_ &&
             destructorValue_ == ref.destructorValue_;
    }
    int& constructorValue_;
    int& destructorValue_;
  };

  HashMapV1<int, ReferenceStruct> hashMap;
  ReferenceStruct s1(constructorValue, destructorValue);
  for (int i = 0; i < 10; i++) {
    hashMap.insert(1, s1);
  }
  assert(hashMap.size() == 1);
  assert(destructorValue == 9);
}

int main() {
  testHashMapInt();
  testHashMapWithStruct();
  stressTestRemoval();
  testDuplicateInsertion();
  return 0;
}