#include <utility>
#ifndef WEAK_PTR
#define WEAK_PTR

#include "Shared_ptr.hpp" // Include SharedPtr definition
// When submitting to damn ACMOJ, please replace this with the content inside Shared_ptr.hpp

template <typename T>
class WeakPtr {
  private:
    // Add whatever you want to add.
    T* ptr;        // Pointer to the managed object
    int* ref_count; // Pointer to the SHARED reference count
    int* weak_count; // Pointer to the WEAK reference count
    friend class SharedPtr<T>; // Declare SharedPtr as a friend class
  public:
    // Constructors
    WeakPtr() : ptr(nullptr), ref_count(nullptr), weak_count(nullptr) {};                         // Default constructor
    WeakPtr(const SharedPtr<T>& temp) : ptr(temp.get()), ref_count(temp.use_count_ptr()), weak_count(temp.weak_count_ptr()) {
        if (weak_count) {
            ++(*weak_count);
        }
    }; // Constructor from SharedPtr
    WeakPtr(const WeakPtr& temp) : ptr(temp.ptr), ref_count(temp.ref_count), weak_count(temp.weak_count) {
      if (weak_count) {
          ++(*weak_count);
      }
    };      // Copy constructor
    WeakPtr(WeakPtr&& temp) noexcept : ptr(temp.ptr), ref_count(temp.ref_count), weak_count(temp.weak_count) {
      temp.ptr = nullptr;
      temp.ref_count = nullptr;
      temp.weak_count = nullptr;
    };           // Move constructor

    // Destructor
    ~WeakPtr() {
      if (ref_count && weak_count) {
          --(*weak_count);
          if (*weak_count == 0 && *ref_count == 0) {
              delete weak_count;
              delete ref_count;
          }
      }
      ptr = nullptr;
      ref_count = nullptr;
      weak_count = nullptr;
    };

    // Assignment operators
    
    WeakPtr& operator=(const WeakPtr& temp) {
      if (this != &temp) {
        if (ref_count && weak_count) {
          --(*weak_count);
          if (*weak_count == 0 && *ref_count == 0) {
              delete weak_count;
              delete ref_count;
          }
        }
        // Copy the data from temp
        ptr = temp.ptr;
        ref_count = temp.ref_count;
        weak_count = temp.weak_count;
        if (weak_count) {
            ++(*weak_count);
        }
      }
      return *this;
    };      // Copy assignment operator
    WeakPtr& operator=(const SharedPtr<T>& temp) {
      if (ref_count && weak_count) {
          --(*weak_count);
          if (*weak_count == 0 && *ref_count == 0) {
              delete weak_count;
              delete ref_count;
          }
      }
      // Copy the data from temp
      ptr = temp.get();
      ref_count = temp.use_count_ptr();
      weak_count = temp.weak_count_ptr();
      if (weak_count) {
          ++(*weak_count);
      }
      return *this;
    }; // Assignment from SharedPtr
    WeakPtr& operator=(WeakPtr&& temp) {
      if (this != &temp) {
        if (ref_count && weak_count) {
            --(*weak_count);
            if (*weak_count == 0 && *ref_count == 0) {
                delete weak_count;
                delete ref_count;
            }
        }
        // Move the data from temp
        ptr = temp.ptr;
        ref_count = temp.ref_count;
        weak_count = temp.weak_count;
        temp.ptr = nullptr;
        temp.ref_count = nullptr;
        temp.weak_count = nullptr;
      }
      return *this;
    };           // Move assignment operator

    // Basic operations
    int use_count() const {
      return ref_count ? *ref_count : 0;
    };     // Get the number of shared owners
    bool expired() const {
      return use_count() == 0;
    };      // Check if the managed object was deleted
    operator bool() const {
        return !expired();
    }; // Check if the pointer is not null
    SharedPtr<T> lock() const {
      if (expired()) {
        return SharedPtr<T>();
      } else {
        return SharedPtr<T>(*this);
      }
    }; // Get a SharedPtr to the managed object
    void reset() {
      if (weak_count) {
          --(*weak_count);
          if (*weak_count == 0 && *ref_count == 0) {
              delete weak_count;
              delete ref_count;
          }
      }
      ptr = nullptr;
      ref_count = nullptr;
      weak_count = nullptr;
    };        // Reset to empty state

    // Utility functions
    void swap(WeakPtr& other) noexcept {
      std::swap(ptr, other.ptr);
      std::swap(ref_count, other.ref_count);
      std::swap(weak_count, other.weak_count);
    }; // Swap with another WeakPtr
};

// Non-member swap function
template <typename T>
void swap(WeakPtr<T>& lhs, WeakPtr<T>& rhs) noexcept {
    lhs.swap(rhs);
}

template <typename T>
SharedPtr<T>::SharedPtr(const WeakPtr<T>& temp_wp) : ptr(temp_wp.ptr), ref_count(temp_wp.ref_count), weak_count(temp_wp.weak_count) {
    if (ptr && ref_count) {
        ++(*ref_count);
    }
}; // Constructor from WeakPtr

#endif // WEAK_PTR
