#ifndef HASHMAP_H
#define HASHMAP_H

#include <iostream>
using namespace std;
#include <list>


template<typename K, typename V>
class HashMap{

    public:
    HashMap(K key, V value);
    ~HashMap();
    void insert(K key, V value);
    bool contains(K key);
    void remove(K key);
    HashMap(const HashMap& hashmap);
    HashMap& operator=(const HashMap& hashmap);

    private:
    K key;
    V value;
    int MAX_SIZE = 10;
    
    struct HashNode
    {
        K key;
        V value;
        HashNode* next;
    };
    list<HashNode> hashList;
    int getHash(K key);
};

#endif