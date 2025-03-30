#include <cstddef>    // For size_t
#include <functional> // For std::hash
#include <iostream>

template <typename K, typename V> class HashMapV1 {
  public:
    HashMapV1() {}

    void destroy() {
        if (numberOfElements != 0) {
            for (size_t i = 0; i < arraySize; i++) {
                LinkedList* temp = array[i].next;
                while (temp != nullptr) {
                    LinkedList* nextPointer = temp->next;
                    delete temp->key;
                    delete temp->value;
                    delete temp;
                    temp = nextPointer;
                }
            }
            delete[] array;
        }
    }

    ~HashMapV1() { destroy(); }

    void construct() { array = new LinkedList[arraySize]; }

    // Random hash
    size_t hash(const K& key) {
        // Convert the object to a byte array and hash it
        const unsigned char* data = reinterpret_cast<const unsigned char*>(&key);
        size_t               size = sizeof(K);

        // FNV-1a hash algorithm
        size_t hash = 14695981039346656037ULL; // FNV offset basis
        for (size_t i = 0; i < size; ++i) {
            hash ^= static_cast<size_t>(data[i]);
            hash *= 1099511628211ULL; // FNV prime
        }

        return hash;
    }

    // Copy constructor
    HashMapV1(const HashMapV1& hashmapv1) : arraySize(hashmapv1.arraySize), numberOfElements(hashmapv1.numberOfElements) {
        construct();
        for (size_t i = 0; i < arraySize; i++) {
            LinkedList* temp         = hashmapv1.array[i].next;
            LinkedList* currrentNode = &array[i];
            while (temp != nullptr) {
                currrentNode->next = new LinkedList(*(temp->key), *(temp->value));
                currrentNode       = currrentNode->next;
                temp               = temp->next;
            }
        }
    }

    // Copy Assignment operator
    HashMapV1 operator=(const HashMapV1& hashmapv1) {
        destroy();
        arraySize   = hashmapv1.arraySize;
        numberOfElements = hashmapv1.numberOfElements;
        construct();
        for (size_t i = 0; i < arraySize; i++) {
            LinkedList* temp         = hashmapv1.array[i].next;
            LinkedList* currrentNode = &array[i];
            while (temp != nullptr) {
                currrentNode->next = new LinkedList(*(temp->key), *(temp->value));
                currrentNode       = currrentNode->next;
                temp               = temp->next;
            }
        }
        return *this;
    }

    // Move constructor
    HashMapV1(HashMapV1&& hashmapv1) : arraySize(hashmapv1.arraySize), numberOfElements(hashmapv1.numberOfElements) {
        array                 = hashmapv1.array;
        hashmapv1.array       = nullptr;
        hashmapv1.numberOfElements = 0;
        hashmapv1.arraySize   = 10;
    }

    // Move Assignment operator
    HashMapV1 operator=(HashMapV1&& hashmapv1) {
        arraySize             = hashmapv1.arraySize;
        numberOfElements           = hashmapv1.numberOfElements;
        array                 = hashmapv1.array;
        hashmapv1.array       = nullptr;
        hashmapv1.numberOfElements = 0;
        hashmapv1.arraySize   = 10;
        return *this;
    }

    bool find(K key, V& value) {
        size_t      randomNumber = hash(key);
        size_t      index        = randomNumber % arraySize;
        LinkedList* temp         = array[index].next;
        while (temp != nullptr) {
            if (*(temp->key) == key) {
                value = *(temp->value);
                return true;
            }
            temp = temp->next;
        }
        return false;
    }

    bool remove(K key) {
        if (array != nullptr) {
            size_t      randomNumber = hash(key);
            size_t      index        = randomNumber % arraySize;
            LinkedList* list         = array[index].next;
            LinkedList* prev         = &array[index];
            while (list != nullptr) {
                if (*(list->key) == key) {
                    prev->next = list->next;
                    delete list->key;
                    delete list->value;
                    numberOfElements--;
                    return true;
                }
                list = list->next;
                prev = prev->next;
            }
        }
        return false;
    }

    void insert(const K& key, const V& value) {
        if (array == nullptr) {
            construct();
        }
        size_t      randomNumber = hash(key);
        size_t      index        = randomNumber % arraySize;
        LinkedList* current      = array[index].next;
        while (current != nullptr) {
            if (*(current->key) == key) {
                delete current->value;
                current->value = new V(value);
                return;
            }
            current = current->next;
        }
        LinkedList* temp  = new LinkedList(key, value);
        temp->next        = array[index].next;
        array[index].next = temp;
        numberOfElements++;
    }

    size_t size() { return numberOfElements; }

  private:
    int arraySize   = 10;
    int numberOfElements = 0;
    struct LinkedList {
        K*          key;
        V*          value;
        LinkedList* next;

        LinkedList() : next(nullptr) {}
        LinkedList(const K& m_key, const V& v_value) {
            key   = new K(m_key);
            value = new V(v_value);
            next  = nullptr;
        }

        ~LinkedList() {}
    };
    LinkedList* array = nullptr;
};