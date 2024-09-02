#ifndef HASHMAP_H
#define HASHMAP_H

#include <iostream>
#include <list>


template<typename K, typename V>
class HashMap{
    struct HashNode
    {
        K key;
        V value;
        HashNode* next;
    };

    public:
    HashMap(K key, V value);
    ~HashMap();
    void insert(K key, V value);
    bool contains(K key);
    void remove(K key);
    std::list<HashNode*>::iterator find(K key);
    HashMap(const HashMap& hashmap);
    HashMap& operator=(const HashMap& hashmap);

    private:
    int MAX_SIZE = 10;
    std::list<HashNode*> bucket;
    int getHash(K key);
};

#endif