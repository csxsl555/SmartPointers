#ifndef SHARED_PTR
#define SHARED_PTR

template <typename T>
class SharedPtr {
  private:
    // Add whatever you want to add.
  public:
    // Constructors
    SharedPtr();                         // Default constructor
    explicit SharedPtr(T* p);            // Constructor from raw pointer
    SharedPtr(const SharedPtr& tmp);     // Copy constructor
    SharedPtr(SharedPtr&& tmp) noexcept; // Move constructor

    // Destructor
    ~SharedPtr();

    // Assignment operators
    SharedPtr& operator=(const SharedPtr& temp);     // Copy assignment operator
    SharedPtr& operator=(SharedPtr&& temp) noexcept; // Move assignment operator

    // Basic operations
    int use_count() const; // Get the number of shared owners
    T* get() const;        // Get the raw pointer
    operator bool() const; // Check if the pointer is not null
    T& operator*() const;  // Dereference operator
    T* operator->() const; // Arrow operator
    void reset();          // Reset to empty state
    void reset(T* p);      // Reset with a new raw pointer
};

// Then implement the make_shared function
// I think I'd better leave you to design the prototype :)

// template <?>
//? make_shared(?);

#endif // SHARED_PTR