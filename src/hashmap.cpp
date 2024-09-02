#include "hashmap.h"


template<typename K, typename V> 
HashMap<K,V>:: HashMap(K key, V value)
{

}

template<typename K, typename V> 
HashMap<K,V>:: ~HashMap()
{
    
}

template<typename K, typename V> 
HashMap<K,V>:: HashMap(const HashMap& hashmap)
{
    
}


template<typename K, typename V> 
HashMap<K,V>& HashMap<K,V> :: operator=(const HashMap& hashmap)
{
    
}

template<typename K, typename V> 
void HashMap<K,V>:: insert(K key, V value)
{
    int key = getHash(key);
    
}

template<typename K, typename V> 
bool HashMap<K,V> :: contains(K key)
{
    
}

template<typename K, typename V> 
void HashMap<K,V> :: remove(K key)
{
    
}