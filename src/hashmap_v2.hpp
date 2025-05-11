#include <cstddef>    // For size_t
#include <functional> // For std::hash
#include <iostream>

template <typename K, typename V> class HashMapV2 {
public:
  HashMapV2() {}

  // Copy constructor
  HashMapV2(const HashMapV2& hashmapv2) {
    elements_size_ = hashmapv2.elements_size_;
    array_size_ = hashmapv2.array_size_;
    if (hashmapv2.array_ != nullptr) {
      array_ = new LinkedList[array_size_];
      for (size_t i = 0; i < array_size_; i++) {
        LinkedList* hashmapv2_current_node = hashmapv2.array_[i].next_;
        LinkedList* current_node = &array_[i];
        while (hashmapv2_current_node != nullptr) {
          LinkedList* new_node = new LinkedList(hashmapv2_current_node->key_,
                                                hashmapv2_current_node->value_);
          current_node->next_ = new_node;
          current_node = current_node->next_;
          hashmapv2_current_node = hashmapv2_current_node->next_;
        }
      }
    }
  }

  // Copy Assignment operator
  HashMapV2& operator=(const HashMapV2& hashmapv2) {
    destroy();
    array_size_ = hashmapv2.array_size_;
    elements_size_ = hashmapv2.elements_size_;
    if (hashmapv2.array_ != nullptr) {
      array_ = new LinkedList[array_size_];
      for (size_t i = 0; i < array_size_; i++) {
        LinkedList* hashmapv2_current_node = hashmapv2.array_[i].next_;
        LinkedList* current_node = &array_[i];
        while (hashmapv2_current_node != nullptr) {
          LinkedList* new_node = new LinkedList(hashmapv2_current_node->key_,
                                                hashmapv2_current_node->value_);
          current_node->next_ = new_node;
          current_node = current_node->next_;
          hashmapv2_current_node = hashmapv2_current_node->next_;
        }
      }
    }
    return *this;
  }

  // Move Constructor
  HashMapV2(HashMapV2&& hashmapv2)
      : array_size_(hashmapv2.array_size_),
        elements_size_(hashmapv2.elements_size_) {
    array_ = hashmapv2.array_;
    hashmapv2.array_size_ = 10;
    hashmapv2.elements_size_ = 0;
    hashmapv2.array_ = nullptr;
  }

  // Move Assignment operator
  HashMapV2& operator=(HashMapV2&& hashmapv2) {
    destroy();
    array_size_ = hashmapv2.array_size_;
    elements_size_ = hashmapv2.elements_size_;
    array_ = hashmapv2.array_;
    hashmapv2.array_size_ = 10;
    hashmapv2.elements_size_ = 0;
    hashmapv2.array_ = nullptr;
    return *this;
  }

  void destroy() {
    if (array_ != nullptr) {
      for (int i = 0; i < array_size_; i++) {
        LinkedList* current_node = array_[i].next_;
        while (current_node != nullptr) {
          LinkedList* next_node = current_node->next_;
          delete current_node;
          current_node = next_node;
        }
      }
      delete[] array_;
    }
  }

  ~HashMapV2() { destroy(); }

  void construct() { array_ = new LinkedList[array_size_]; }

  // Random hash
  size_t hash(const K& key) {
    std::hash<K> hasher;
    return hasher(key);
  }

  void resize() {
    std::cout << "resize called" << std::endl;
    size_t new_size = array_size_ * 10;
    LinkedList* new_array = new LinkedList[new_size];
    for (size_t i = 0; i < array_size_; i++) {
      LinkedList* node = array_[i].next_;

      while (node != nullptr) {
        size_t random_number = hash(node->key_);
        size_t index = random_number % new_size;
        LinkedList* new_node = new LinkedList(node->key_, node->value_);
        new_node->next_ = new_array[index].next_;
        new_array[index].next_ = new_node;
        node = node->next_;
      }
    }
    array_size_ = new_size;
    array_ = std::move(new_array);
  }

  void insert(const K& key, const V& value) {
    if (array_ == nullptr) {
      construct();
    }
    if (elements_size_ == array_size_ * 10) {
      resize();
    }
    size_t random_number = hash(key);
    size_t index = random_number % array_size_;
    LinkedList* current_node = array_[index].next_;
    while (current_node != nullptr) {
      if (current_node->key_ == key) {
        current_node->value_ = value;
        return;
      }
      current_node = current_node->next_;
    }
    LinkedList* new_node = new LinkedList(key, value);
    new_node->next_ = array_[index].next_;
    array_[index].next_ = new_node;
    elements_size_++;
  }

  bool find(const K& key, V& value) {
    if (array_ == nullptr) {
      return false;
    }
    size_t random_number = hash(key);
    size_t index = random_number % array_size_;
    LinkedList* current_node = array_[index].next_;
    while (current_node != nullptr) {
      if (current_node->key_ == key) {
        value = current_node->value_;
        return true;
      }
      current_node = current_node->next_;
    }
    return false;
  }

  bool remove(const K& key) {
    if (array_ == nullptr) {
      return false;
    }
    size_t random_number = hash(key);
    size_t index = random_number % array_size_;
    LinkedList* current_node = array_[index].next_;
    LinkedList* previous_node = &array_[index];
    while (current_node != nullptr) {
      if (current_node->key_ == key) {
        previous_node->next_ = current_node->next_;
        delete current_node;
        elements_size_--;
        return true;
      }
      previous_node = current_node;
      current_node = current_node->next_;
    }
    return false;
  }

  int size() { return elements_size_; }

private:
  int array_size_ = 10;
  int elements_size_ = 0;
  struct LinkedList {
    K key_;
    V value_;
    LinkedList* next_;
    LinkedList() { next_ = nullptr; }
    LinkedList(const K& key, const V& value) {
      key_ = key;
      value_ = value;
      next_ = nullptr;
    }
    ~LinkedList() {}
  };
  LinkedList* array_ = nullptr;
};