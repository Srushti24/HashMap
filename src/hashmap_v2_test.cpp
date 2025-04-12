#include "hashmap_v2.hpp"
#include <cassert>
#include <iostream>

void testHashMapInt() {
    HashMapV2<int, int> hashmap; // Default constructor
    hashmap.insert(2, 3);
    hashmap.insert(4, 2);
    hashmap.insert(6, 5);
    assert(hashmap.size() == 3);

    // Copy constructor
    HashMapV2<int, int> hashmap1(hashmap);
    assert(hashmap.size() == 3);
    int  value = 0;
    bool find  = false;
    find       = hashmap1.find(6, value);
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
    HashMapV2<int, int> hashmap2 = hashmap1;
    assert(hashmap2.size() == 3);
    value = 0;
    find  = false;
    find  = hashmap2.find(6, value);
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
    HashMapV2<int, int> hashmap3(std::move(hashmap));
    assert(hashmap.size() == 0);
    assert(hashmap3.size() == 3);
    value = 0;
    find  = false;
    find  = hashmap3.find(6, value);
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
    HashMapV2<int, int> hashmap4 = std::move(hashmap3);
    assert(hashmap3.size() == 0);
    assert(hashmap4.size() == 3);
    value = 0;
    find  = false;
    find  = hashmap4.find(6, value);
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

void stressTestRemoval() {
    HashMapV2<int, int> stressMap;
    for (int i = 0; i < 10000; i++) {
        stressMap.insert(i, i * 2);
    }
    for (int i = 0; i < 10000; i += 2) {
        bool ans = stressMap.remove(i);
    }
    assert(stressMap.size() == 5000);

    int  value = 0;
    bool find  = 0;
    find       = stressMap.find(2, value);
    assert(find == false);
    find = stressMap.find(3, value);
    assert(find == true);
    assert(value == 6);
}

int main() {
    testHashMapInt();
    stressTestRemoval();
    return 0;
}