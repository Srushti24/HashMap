#include <cstddef>    // For size_t
#include <functional> // For std::hash
#include <iostream>

template <typename K, typename V> class HashMapV1 {
  public:
    HashMapV1() {}

    void destroy() {
        if (elements_size_ != 0) {
            for (size_t i = 0; i < array_size_; i++) {
                LinkedList* current_node = array_[i].next_;
                while (current_node != nullptr) {
                    LinkedList* next_node = current_node->next_;
                    delete current_node->key_;
                    delete current_node->value_;
                    delete current_node;
                    current_node = next_node;
                }
            }
            delete[] array_;
        }
    }

    ~HashMapV1() { destroy(); }

    void construct() { array_ = new LinkedList[array_size_]; }

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
    HashMapV1(const HashMapV1& hashmapv1)
        : array_size_(hashmapv1.array_size_), elements_size_(hashmapv1.elements_size_) {
        construct();
        for (size_t i = 0; i < array_size_; i++) {
            LinkedList* hashmapv1_current_node = hashmapv1.array_[i].next_;
            LinkedList* currrent_node          = &array_[i];
            while (hashmapv1_current_node != nullptr) {
                currrent_node->next_ =
                    new LinkedList(*(hashmapv1_current_node->key_), *(hashmapv1_current_node->value_));
                currrent_node          = currrent_node->next_;
                hashmapv1_current_node = hashmapv1_current_node->next_;
            }
        }
    }

    // Copy Assignment operator
    HashMapV1& operator=(const HashMapV1& hashmapv1) {
        destroy();
        array_size_    = hashmapv1.array_size_;
        elements_size_ = hashmapv1.elements_size_;
        construct();
        for (size_t i = 0; i < array_size_; i++) {
            LinkedList* hashmapv1_current_node = hashmapv1.array[i].next_;
            LinkedList* currrent_node          = &array_[i];
            while (hashmapv1_current_node != nullptr) {
                currrent_node->next_ =
                    new LinkedList(*(hashmapv1_current_node->key_), *(hashmapv1_current_node->value_));
                currrent_node          = currrent_node->next_;
                hashmapv1_current_node = hashmapv1_current_node->next_;
            }
        }
        return *this;
    }

    // Move constructor
    HashMapV1(HashMapV1&& hashmapv1) : array_size_(hashmapv1.array_size_), elements_size_(hashmapv1.elements_size_) {
        array_                   = hashmapv1.array_;
        hashmapv1.array_         = nullptr;
        hashmapv1.elements_size_ = 0;
        hashmapv1.array_size_    = 10;
    }

    // Move Assignment operator
    HashMapV1& operator=(HashMapV1&& hashmapv1) {
        array_size_              = hashmapv1.array_size_;
        elements_size_           = hashmapv1.elements_size_;
        array_                   = hashmapv1.array_;
        hashmapv1.array_         = nullptr;
        hashmapv1.elements_size_ = 0;
        hashmapv1.array_size_    = 10;
        return *this;
    }

    bool find(const K& key, V& value) {
        size_t      random_number = hash(key);
        size_t      index         = random_number % array_size_;
        LinkedList* current_node  = array_[index].next_;
        while (current_node != nullptr) {
            if (*(current_node->key_) == key) {
                value = *(current_node->value_);
                return true;
            }
            current_node = current_node->next_;
        }
        return false;
    }

    bool remove(const K& key) {
        if (array_ != nullptr) {
            size_t      random_number = hash(key);
            size_t      index         = random_number % array_size_;
            LinkedList* current_node  = array_[index].next_;
            LinkedList* previous_node = &array_[index];
            while (current_node != nullptr) {
                if (*(current_node->key_) == key) {
                    previous_node->next_ = current_node->next_;
                    delete current_node->key_;
                    delete current_node->value_;
                    elements_size_--;
                    return true;
                }
                current_node  = current_node->next_;
                previous_node = previous_node->next_;
            }
        }
        return false;
    }

    void insert(const K& key, const V& value) {
        if (array_ == nullptr) {
            construct();
        }
        size_t      random_number = hash(key);
        size_t      index         = random_number % array_size_;
        LinkedList* current_node  = array_[index].next_;
        while (current_node != nullptr) {
            if (*(current_node->key_) == key) {
                delete current_node->value_;
                current_node->value_ = new V(value);
                return;
            }
            current_node = current_node->next_;
        }
        LinkedList* new_node = new LinkedList(key, value);
        new_node->next_      = array_[index].next_;
        array_[index].next_  = new_node;
        elements_size_++;
    }

    size_t size() { return elements_size_; }

  private:
    int array_size_    = 10;
    int elements_size_ = 0;
    struct LinkedList {
        K*          key_;
        V*          value_;
        LinkedList* next_;

        LinkedList() : next_(nullptr) {}
        LinkedList(const K& m_key, const V& v_value) {
            key_   = new K(m_key);
            value_ = new V(v_value);
            next_  = nullptr;
        }

        ~LinkedList() {}
    };
    LinkedList* array_ = nullptr;
};