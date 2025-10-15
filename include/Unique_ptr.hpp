#ifndef UNIQUE_PTR
#define UNIQUE_PTR
#include <iostream>

template <typename T>

class UniquePtr {
  private:
    // Add whatever you want to add.
    T* ptr; // Raw pointer to managed object

  public:
    // Constructors
    UniquePtr() {ptr = nullptr;};                          // Default constructor
    explicit UniquePtr(T* p) noexcept : ptr(p) {};             // Constructor from raw pointer
    UniquePtr(const UniquePtr& other) = delete; // Copy constructor is deleted
    UniquePtr(UniquePtr&& other) noexcept : ptr(other.ptr) { // Move constructor
      other.ptr = nullptr;
    }        

    // Destructor
    ~UniquePtr(){delete ptr; ptr = nullptr;};

    // Assignment operators
    UniquePtr& operator=(UniquePtr& other) = delete; // Copy assignment operator is deleted
    UniquePtr& operator=(UniquePtr&& other) noexcept{
        if (this != &other) {
            delete ptr; // Free existing resource
            ptr = other.ptr; // Transfer ownership
            other.ptr = nullptr; // Leave other in a valid state
        }
        return *this;
    } // Move assignment operator

    // Basic operations
    T* get() const {return ptr;};                 // Get the raw pointer
    explicit operator bool() const {return ptr != nullptr;}; // Check if the pointer is not null
    T& operator*() const {return *ptr;};           // Dereference operator
    T* operator->() const {return ptr;};          // Arrow operator
    void reset() {delete ptr; ptr = nullptr;};                   // Reset to empty state
    void reset(T* p) {delete ptr; ptr = p;};               // Reset with a new raw pointer
    T* release() {T* temp = ptr; ptr = nullptr; return temp;};  // Release ownership of the managed object
};

// A tricky question: to implement the make_unique function
// template <?>
//? make_unique(?);

template <typename T, typename... Args>
UniquePtr<T> make_unique(Args&&... args) {
    return UniquePtr<T>(new T(std::forward<Args>(args)...));
}

#endif // UNIQUE_PTR
