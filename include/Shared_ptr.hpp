#ifndef SHARED_PTR
#define SHARED_PTR

template <typename T>
class SharedPtr {
  private:
    // Add whatever you want to add.
    T* ptr;          // Raw pointer to the managed object
    int* ref_count; // Pointer to the reference count
  public:
    // Constructors
    SharedPtr() : ptr(nullptr), ref_count(nullptr) {};         // Default constructor
    explicit SharedPtr(T* p) : ptr(p) {
        if (p) {
            ref_count = new int(1);
        } else {
            ref_count = nullptr;
        }
    };            // Constructor from raw pointer
    SharedPtr(const SharedPtr& tmp) : ptr(tmp.ptr), ref_count(tmp.ref_count) {
        if (ptr) {
            ++(*ref_count);
        }
    };     // Copy constructor
    SharedPtr(SharedPtr&& tmp) noexcept : ptr(tmp.ptr), ref_count(tmp.ref_count) {
        tmp.ptr = nullptr;
        tmp.ref_count = nullptr;
    }; // Move constructor

    // Destructor
    ~SharedPtr() {
      if (ref_count) {
          --(*ref_count);    
          if (*ref_count == 0) {
              delete ptr;
              delete ref_count;
          }
      }
      ptr = nullptr;
      ref_count = nullptr;
    }; 

    // Assignment operators
    SharedPtr& operator=(const SharedPtr& temp) {
        if (this != &temp) {
            // Decrement the old reference count
            if (ptr && --(*ref_count) == 0) {
                delete ptr;
                delete ref_count;
            }
            // Copy the data from temp
            ptr = temp.ptr;
            ref_count = temp.ref_count;
            if (ptr) {
                ++(*ref_count);
            }
        }
        return *this;
    };     // Copy assignment operator
    SharedPtr& operator=(SharedPtr&& temp) noexcept {
        if (this != &temp) {
            // Decrement the old reference count
            if (ptr && --(*ref_count) == 0) {
                delete ptr;
                delete ref_count;
            }
            // Move the data from temp
            ptr = temp.ptr;
            ref_count = temp.ref_count;
            temp.ptr = nullptr;
            temp.ref_count = nullptr;
        }
        return *this;
    }; // Move assignment operator

    // Basic operations
    int use_count() const {
        return ref_count ? *ref_count : 0;
    }; // Get the number of shared owners
    T* get() const {
        return ptr;
    };        // Get the raw pointer
    operator bool() const {
        return ptr != nullptr;
    }; // Check if the pointer is not null
    T& operator*() const {
        return *ptr;
    };  // Dereference operator
    T* operator->() const {
        return ptr;
    }; // Arrow operator
    void reset() {
        if (ptr && --(*ref_count) == 0) {
            delete ptr;
            delete ref_count;
        }
        ptr = nullptr;
        ref_count = nullptr;
    };          // Reset to empty state
    void reset(T* p) {
        if (ptr && --(*ref_count) == 0) {
            delete ptr;
            delete ref_count;
        }
        ptr = p;
        if (p) {
            ref_count = new int(1);
        } else {
            ref_count = nullptr;
        }
    };      // Reset with a new raw pointer
};

// Then implement the make_shared function
// I think I'd better leave you to design the prototype :)

// template <?>
//? make_shared(?);

template <typename T, typename... Args>
SharedPtr<T> make_shared(Args&&... args) {
    return SharedPtr<T>(new T(std::forward<Args>(args)...));
}

#endif // SHARED_PTR