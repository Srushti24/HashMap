#include <cstddef>    // For size_t
#include <functional> // For std::hash
#include <iostream>

template <typename K, typename V> class HashMapV2 {
  public:
    HashMapV2() {}

    // Copy constructor
    HashMapV2(const HashMapV2& hashmapv2) {
        currentSize = hashmapv2.currentSize;
        arraySize   = hashmapv2.arraySize;
        if (hashmapv2.array != nullptr) {
            array = new LinkedList[arraySize];
            for (size_t i = 0; i < arraySize; i++) {
                LinkedList* curr = hashmapv2.array[i].next;
                LinkedList* temp = nullptr;
                while (curr != nullptr) {
                    LinkedList* temp1 = new LinkedList(curr->key_, curr->value_);
                    if (temp == nullptr) {
                        temp = temp1;
                    } else {
                        temp->next = temp1;
                        temp       = temp->next;
                    }
                    curr = curr->next;
                }
                array[i].next = temp;
            }
        }
    }

    // Copy Assignment operator
    HashMapV2 operator=(const HashMapV2& hashmapv2) {
        destroy();
        arraySize   = hashmapv2.arraySize;
        currentSize = hashmapv2.currentSize;
        if (hashmapv2.array != nullptr) {
            array = new LinkedList[arraySize];
            for (size_t i = 0; i < arraySize; i++) {
                LinkedList* curr = hashmapv2.array[i].next;
                LinkedList* temp = nullptr;
                while (curr != nullptr) {
                    LinkedList* temp1 = new LinkedList(curr->key_, curr->value_);
                    if (temp == nullptr) {
                        temp = temp1;
                    } else {
                        temp->next = temp1;
                        temp       = temp->next;
                    }
                    curr = curr->next;
                }
                array[i].next = temp;
            }
        }
        return *this;
    }

    // Move Constructor
    HashMapV2(HashMapV2&& hashmapv2) : arraySize(hashmapv2.arraySize), currentSize(hashmapv2.currentSize) {
        array                 = hashmapv2.array;
        hashmapv2.arraySize   = 10;
        hashmapv2.currentSize = 0;
        hashmapv2.array       = nullptr;
    }

    // Move Assignment operator
    HashMapV2 operator=(HashMapV2&& hashmapv2) {
        destroy();
        arraySize             = hashmapv2.arraySize;
        currentSize           = hashmapv2.currentSize;
        array                 = hashmapv2.array;
        hashmapv2.arraySize   = 10;
        hashmapv2.currentSize = 0;
        hashmapv2.array       = nullptr;
        return *this;
    }

    void destroy() {
        if (array != nullptr) {
            for (int i = 0; i < arraySize; i++) {
                LinkedList* linkedList = array[i].next;
                while (linkedList != nullptr) {
                    LinkedList* nextLinkedList = linkedList->next;
                    delete linkedList;
                    linkedList = nextLinkedList;
                }
            }
            delete[] array;
        }
    }

    ~HashMapV2() { destroy(); }

    void contruct() { array = new LinkedList[arraySize]; }

    // Random hash
    size_t hash(const K& key) {
        const unsigned char* data = reinterpret_cast<const unsigned char*>(&key);
        size_t               size = sizeof(K);

        size_t hash = 14695981039346656037ULL; 
        for (size_t i = 0; i < size; ++i) {
            hash ^= static_cast<size_t>(data[i]);
            hash *= 1099511628211ULL;
        }

        return hash;
    }

    void insert(K k, V v) {
        if (array == nullptr) {
            contruct();
        }
        int randomNumber = hash(k);
        int index        = randomNumber % arraySize;
        LinkedList* newNode = new LinkedList(k, v);
        newNode->next       = array[index].next;
        array[index].next   = newNode;
        currentSize++;
    }

    bool find(K k, V& v) {
        int         randomNumber = hash(k);
        int         index        = randomNumber % arraySize;
        LinkedList* temp         = &array[index];
        while (temp != nullptr) {
            if (temp->key_ == k) {
                v = temp->value_;
                return true;
            }
            temp = temp->next;
        }
        return false;
    }

    bool remove(K k) {
        int         randomNumber = hash(k);
        int         index        = randomNumber % arraySize;
        LinkedList* temp         = array[index].next;
        LinkedList* previous     = &array[index];
        while (temp != nullptr) {
            if (temp->key_ == k) {
                previous->next = temp->next;
                delete temp;
                currentSize--;
                return true;
            }
            previous = temp;
            temp     = temp->next;
        }
        return false;
    }

    int size() { return currentSize; }

  private:
    int arraySize   = 10;
    int currentSize = 0;
    struct LinkedList {
        K           key_;
        V           value_;
        LinkedList* next;
        LinkedList() { next = nullptr; }
        LinkedList(K& key, V& value) {
            key_   = key;
            value_ = value;
            next   = nullptr;
        }
        ~LinkedList() {}
    };
    LinkedList* array = nullptr;
};