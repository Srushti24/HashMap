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
    
    

}

template<typename K, typename V> 
bool HashMap<K,V> :: contains(K key)
{
    
}

template<typename K, typename V> 
void HashMap<K,V> :: remove(K key)
{
    
}

template<typename K, typename V> 
int HashMap<K,V> :: getHash(K key)
{
    return reinterpret_cast<int>(key) % MAX_SIZE;
}

template<typename K, typename V> 
std::list<HashMap<K,V>::HashNode*>::iterator HashMap<K,V> :: find(K key)
{
    HashNode head = bucket[getHash(key)];
    while(head!=NULL)
    {
        if(head->key == key)
        {
            return head;
        }
        head = head->next;
    }
        return bucket[getHash(key)].end();
}