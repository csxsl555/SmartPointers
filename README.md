# Project 2: $\mathrm{Smart Pointer}$

> SJTU CS1958-01 2025Fall 第二次大作业

请先阅读[智能指针那些事儿](https://notes.sjtu.edu.cn/feladvRRTXSjGqzARi9Kxg?both),:)
    
# `Unique_ptr`
    
你需要构造的 `unique_ptr` 模版类的要求包括：
    
- 有名为 `T* _p`（T 是模板参数）的成员变量来存储给定的指针
    
- 要求实现能够将 `_p` 置为 `nullptr` 的默认构造函数
    
     ``` 
    UniquePtr<int> ptr;
    ```
    
- 要求实现能够支持将普通指针转换成 `unique_ptr` 的构造函数,注意传入的参数的值类别形式：
    
     ```
    UniquePtr<int> ptr{new int{10}};
    ```
    
- 要求实现 `unique_ptr` 间的移动构造函数，并禁止拷贝构造函数的存在
    
     ```
     UniquePtr<int> ptr2{ptr1};//编译错误
    ```
    
- 在类外编写类似于 `std::make_unique` 的函数模版，要求能够支持形如
    ```
    UniquePtr<int> ptr{make_unique<int>(10)};
    UniquePtr<std::vector<int>> ptr2{make_unique<std::vector<int>>(2,3)};
    ```
    的构造方式，注意传入的参数的个数以及值类别形式。
    
- 要求拥有析构函数 `~UniquePtr()` 删除动态指针并将其置为 `nullptr`(思考：为什么要置空)
    
- 要求重载解引用运算符 `operator*`，实现与普通指针相同的功能
    ```
     UniquePtr<int> ptr{new int{10}};
     std::cout << *ptr << std::endl; // output: 10
    ```
    
- 要求重载间接引用运算符 `operator->`，实现与普通指针相同的功能
     ```
      UniquePtr<std::string> ptr{new std::string{"hello"}};
      std::cout << ptr->length() << std::endl; // output: 5
     ```
    
- 要求重载类型转换符 `bool()` 来判断指针是否为空，非空返回 true,空返回 false
     ```
      UniquePtr<std::string> ptr{new std::string{"hello"}};
      std::cout << bool(ptr) << std::endl; // output: true
     ```
    
- 要求重载运算符 `operator=`，实现 `unique_ptr` 间的移动赋值并禁止拷贝赋值
     ```
     UniquePtr<int> ptr1{new int{10}};
     UniquePtr<int> ptr2{new int{11}};
     ptr2 = ptr1;// 编译错误
     ```
    
- 要求实现 `get()` 函数用以返回存储在类中的原始指针

     ```
      UniquePtr<int> ptr{new int{10}};
      std::cout << ptr.get() << std::endl; // output: raw pointer stored in the class
     ```
- 要求实现 `reset()` 函数，包括实现以下两种参数形式：
     1.    `void reset();` 删除原有指针并分配 `nullptr` 给它；
     2.    `void reset(T* p)` 删除原有指针并分配 `p` 给它
 
     ```
     UniquePtr<std::string> ptr{new std::string{"hello"}};
     ptr.reset(new std::string{"nice"});
     std::cout << *ptr << std::endl; // output: nice
     ```
    
- 要求实现 `release` 函数用以返回一个指向原对象的普通指针，同时让对象脱离 `unique_ptr` 的管理。在此期间，`unique_ptr` 类不删除原有指针。
     ```
     UniquePtr<double> ptr{new double{1.567}};
     double *tmp{ptr.release()};
     std::cout << *tmp << std::endl; // output: 1.567
     delete tmp; // manual deletion
     ```


# `Shared_ptr`
    
`shared_ptr` 中你需要实现:
    
- 有名为 `T* _p`（T 是模板参数）的成员变量来存储给定的指针
    
- 要求实现能够将 ```_p``` 置为 `nullptr` 的默认构造函数
    
     ``` 
     SharedPtr<int> ptr;
    ```
    
- 要求实现能够支持将普通指针和 `unique_ptr` 转换成 `shared_ptr` 的构造函数,注意传入的参数的值类别形式：
    
     ```
     UniquePtr<int> ptr{new int{1}};
     SharedPtr<int> sp1{new int{10}};
     SharedPtr<int> sp2{ptr};
    ```
    
- 要求实现 `shared_ptr` 间的移动构造函数与拷贝构造函数
    
     ```
     SharedPtr<int> ptr2{ptr1};//编译成功
    ```
    
- 在类外编写类似于 `std::make_shared` 的函数模版，要求能够支持形如
    ```
     SharedPtr<int> ptr{make_shared<int>(10)};
    ```
    的构造方式，注意传入的参数的个数以及值类别形式。
    
- 要求拥有析构函数 `~SharedPtr()` 删除动态指针并将其置为 `nullptr`
    
- 要求重载解引用运算符 `operator*`，实现与普通指针相同的功能
    
     ```
      SharedPtr<int> ptr{new int{10}};
      std::cout << *ptr << std::endl; // output: 10
     ```
    
- 要求重载间接引用运算符 `operator->`，实现与普通指针相同的功能
     ```
      SharedPtr<std::string> ptr{new std::string{"hello"}};
      std::cout << ptr->length() << std::endl; // output: 5
     ```
    
- 要求重载运算符 `operator=`，实现 `shared_ptr` 间的移动赋值与拷贝赋值
     ```
      SharedPtr<int> ptr1{new int{10}};
      SharedPtr<int> ptr2{new int{11}};
      ptr2 = ptr1;
     ```
- 要求重载类型转换符 `bool()` 来判断指针是否为空，非空返回 true,空返回 false;
     ```
      SharedPtr<std::string> ptr{new std::string{"hello"}};
      std::cout << bool(ptr) << std::endl; // output: true
     ```
    
- 要求实现 `get()` 函数用以返回存储在类中的原始指针
     ```
       SharedPtr<int> ptr{new int{10}};
       std::cout << ptr.get() << std::endl; // output: raw pointer of the class
     ```
- 要求实现 `reset()` 函数，包括实现以下两种参数形式：
     1.    `void reset();` 删除原有指针并分配 `nullptr` 给它；
     2.    `void reset(T* p)` 删除原有指针并分配 `p` 给它
 
     ```
      SharedPtr<std::string> ptr{new std::string{"hello"}};
      ptr.reset(new std::string{"nice"});
      std::cout << *ptr << std::endl; // output: nice
     ```
    
- 要求实现 `use_count()` 函数用以返回指向当前的对象的所有 `shared_ptr` 实例数
     ```
      SharedPtr<int> ptr1{make_shared<int>(10)};
      std::cout << ptr1.use_count() << std::endl; // output: 1
      SharedPtr<int> ptr2{ptr1};
      std::cout << ptr1.use_count() << std::endl; // output: 2
      std::cout << ptr2.use_count() << std::endl; // output: 2
     ```

# `Weak_ptr` 
为此，你需要构造的 `weak_ptr` 模版类的要求包括：
    
- 有名为 `T* _p`（T 是模板参数）的成员变量来存储给定的指针
    
- 要求实现能够将 `_p` 置为 `nullptr` 的默认构造函数
    
     ``` 
    WeakPtr<int> wp;
    ```
    
- 要求实现能够支持将 `shared_ptr` 转换成 `weak_ptr` 的构造函数,注意传入的参数的值类别形式：
    
     ```
    SharedPtr<int> sp{new int{10}};
    WeakPtr<int> wp{sp};
    ```
    
- 要求实现移动构造函数与拷贝构造函数，注意在拷贝构造中可以通过 `shared_ptr` 构造 `weak_ptr`
    
     ```
     WeakPtr<int> wp1{sp};
    WeakPtr<int> wp2{wp1};//编译成功
    WeakPtr<int> wp2{std::move(wp1)};//编译成功
    ```
    
- 要求拥有析构函数 `~WeakPtr()` 删除动态指针并将其置为 `nullptr`
    
- 要求重载运算符 `operator=`，实现移动赋值与拷贝赋值，注意在拷贝赋值中可以将 `shared_ptr` 赋给 `weak_ptr`
     ```
     WeakPtr<int> wp1, wp2;
     SharedPtr<int> sp{new int{10}};
     wp1 = sp;//编译成功
     wp2 = wp1;//编译成功
     WeakPtr<int> wp1{sp}, wp2;
     wp2 = std::move(wp1);//编译成功
     ```
- 要求重载类型转换符 `bool()` 来判断指针是否为空，非空返回 true,空返回 false;
     ```
      WeakPtr<int> wp;
      SharedPtr<int> sp{new int{10}};
      wp = sp;
      std::cout << bool(wp) << std::endl; // output: true
     ```    

- 要求实现 `lock()` 函数用以转换 `weak_ptr` 为 `shared_ptr`。如果对象已被删除，则返回一个空的 `shared_ptr`。
     ```
      WeakPtr<int> wp{sp};
      SharedPtr<int> sp2 = wp.lock();
      if(sp2) {
          std::cout << *sp2 << std::endl;  // Use the object safely
      }
     ```
- 要求实现 `expired()` 函数用以检查 `weak_ptr` 所指向的对象是否已被删除，返回 `true` 表示被删除，返回 `false` 表示没有被删除
     ```
      WeakPtr<int> wp{sp};
      if(!wp.expired()) {
          SharedPtr<int> sp2 = wp.lock();
      // Use sp2...
      }
     ```
- 要求实现 `reset()` 函数，删除原有指针并分配 `nullptr` 给它；
     ```    
     WeakPtr<int> wp{sp};
     wp.reset();  // wp no longer references anything
     ```
    
- 要求实现 `use_count()` 函数用以返回指向当前的对象的所有 `shared_ptr` 实例数
     ```
      SharedPtr<int> ptr1{make_shared<int>(10)};
      std::cout << ptr1.use_count() << std::endl; // output: 1
      SharedPtr<int> ptr2{ptr1};
      std::cout << ptr1.use_count() << std::endl; // output: 2
      std::cout << ptr2.use_count() << std::endl; // output: 2
     ```
    
- 要求实现 `swap()` 函数，交换两个 `weak_ptr` 对象
     ```
     WeakPtr<int> wp1{sp1}, wp2{sp2};
     wp1.swap(wp2);  // wp1 now watches sp2's object, wp2 watches sp1's
     ```
    
# 注意事项
    
1. 在完成本次大作业时，请对三个智能指针全部有所了解之后再开始设计，以避免不必要的局部修改或整体重构 (尤其是 `shared_ptr` 与 `weak_ptr`)
   
2. 注意函数实现中的细节，譬如 `const`，`noexpect`,`explicit` 等（这些请自行查询资料了解），有时需要将这些关键词添加到适当函数处使智能指针可以正常运行，并且注意这些都有可能成为 `Code Review` 中考察的对象。
    
# Bonus
    
以下挑战完全是可选的，不会被测试或评分：
- 为 `weak_ptr` 实现线程安全的引用计数。
- 支持数组并使其与自定义删除器兼容。例如：
```cpp
  void TEST10(double& score) {
	    // Test weak_ptr with arrays
	    SharedPtr<int[]> sp1{new int[5]{1, 2, 3, 4, 5}};
	    WeakPtr<int[]> wp1(sp1);
	
	    // Test that after move, the moved-from weak_ptr is expired
	    WeakPtr<int[]> wp2(std::move(wp1));
	    // A moved-from weak_ptr should be expired
	    if (!wp1.expired()) {
	        result = false;
	        return;
	    }
	
	    // Test that the moved-to weak_ptr works correctly
	    SharedPtr<int[]> sp2 = wp2.lock();
	    if (!sp2 || sp2[0] != 1 || sp2[1] != 2) {
	        result = false;
	        return;
	    }
	
	    sp1.reset();
	    wp2.reset();  // Need to reset wp2 explicitly
	    if (wp2.lock()) {
	        result = false;
	        return;
	    }
	
	    score += 0.055;
    }
```
- 添加 `owner_before()` 成员函数以实现关联容器中的一致排序。
    
- 在 `if` 条件中使用自定义智能指针。如果智能指针包含 `nullptr` ，则该条件返回 `false` 否则返回 `true`。


	```cpp
	UniquePtr<double> ptr{new double{1.567}};
    if(ptr) // => true
        // something
	ptr.reset();
	if(ptr) // => false
        // some other thing
	```
	使其对 `UniquePtr`, `SharedPtr` and `WeakPtr` 都生效.
    
    
## 须知

### 截止时间

第五周周日（10/26）24:00

### 编译与运行

本项目需要自行构建样例的 `cpp` 文件用以调试，善用 `valgrind`，这会有所帮助。

### 提交方式

请各位自行测试无误后将对应的 `hpp` 文件提交到 ACMOJ 对应渠道即可.

### 评分规则

对于 `Basic` 部分：

`Unique_ptr`: 25 `pts`

`Shared_ptr`: 25 `pts`

`Weak_ptr`: 30 `pts`

对于 `Extension` 部分，`ACMOJ` 上的 `Allocator` 计 5pts ， 其余部分酌情加 0-5 pts；

对于 Code Review 部分，占 10 `pts`.

本项目的得分上限是 100 `pts`，不会溢出。
    
## Acknowledgement
    
特别感谢 `Amirkabir University of Technology 1400-2 —— Advanced Programming Course Project 4 'Smart Pointers'` .

感谢 2022 级汪畋宇学长创建了这个项目。

感谢 2025 级黄捷航修正了 `README.md`。

如有问题请联系本项目的发布者 `PhantomPhoenix`, 他的邮箱地址是: `logic_1729@sjtu.edu.cn`；负责人 `cyl06`，他的邮箱地址是: `ocwzazure@sjtu.edu.cn`。

## Notes

explicit noexcept const 的用法：

这三个关键字在C++中用途明确且场景具体，下面逐个掰开揉碎了讲，附代码例子，保证你看完就懂怎么用。


### 一、`explicit`：禁止隐式类型转换，只允许显式构造  
**核心作用**：阻止编译器对构造函数或转换函数进行「隐式类型转换」，避免意外的类型转换导致逻辑错误。  


#### 1. 用于单参数构造函数（最常见场景）  
如果一个类的构造函数只有一个参数（或除第一个参数外其余参数都有默认值），编译器会默认允许「隐式转换」：用该参数类型直接初始化对象。而`explicit`会禁用这种隐式转换，强制要求显式构造。  

**反例（不加`explicit`的风险）**：  
```cpp
class MyInt {
public:
    // 单参数构造函数，未加explicit
    MyInt(int value) : m_value(value) {} 
    int get() const { return m_value; }
private:
    int m_value;
};

void printMyInt(MyInt num) {  // 函数参数为MyInt类型
    cout << num.get() << endl;
}

int main() {
    // 隐式转换：编译器自动将int转为MyInt对象
    printMyInt(10);  // 等价于 printMyInt(MyInt(10))，但这可能是开发者没预料到的
    return 0;
}
```  
这里`printMyInt(10)`能编译通过，是因为编译器自动用`10`隐式构造了一个`MyInt`对象。如果开发者本意是`printMyInt`只接受显式创建的`MyInt`，这种隐式转换就可能导致逻辑错误。  


**加`explicit`后的正确用法**：  
```cpp
class MyInt {
public:
    explicit MyInt(int value) : m_value(value) {}  // 加explicit
    int get() const { return m_value; }
private:
    int m_value;
};

void printMyInt(MyInt num) {}

int main() {
    printMyInt(10);  // 编译报错！禁止隐式转换
    printMyInt(MyInt(10));  // 正确：显式构造，允许
    printMyInt({10});  // 正确：C++11后的列表初始化也算显式
    return 0;
}
```  
加`explicit`后，必须显式写出构造过程，避免了意外的隐式转换。  


#### 2. 用于多参数构造函数（C++11后）  
如果多参数构造函数中，除第一个参数外其余参数有默认值，也可能被隐式转换。`explicit`同样可以禁用这种转换：  
```cpp
class Point {
public:
    // 多参数，但y有默认值，本质可被当作"单参数构造函数"使用
    explicit Point(int x, int y = 0) : m_x(x), m_y(y) {}  // 加explicit
private:
    int m_x, m_y;
};

int main() {
    Point p = 10;  // 编译报错！禁止隐式转换（原本会被转为Point(10, 0)）
    Point p2(10);  // 正确：显式构造
    return 0;
}
```  


#### 3. 用于转换函数（C++11后）  
C++允许类定义「转换函数」（operator 目标类型()），用于将类对象隐式转为其他类型。`explicit`也可修饰转换函数，禁止隐式转换：  
```cpp
class MyInt {
public:
    MyInt(int value) : m_value(value) {}
    // 转换函数：将MyInt转为int，加explicit禁止隐式转换
    explicit operator int() const { return m_value; } 
private:
    int m_value;
};

int main() {
    MyInt num(10);
    int x = num;  // 编译报错！禁止隐式转换（MyInt→int）
    int y = static_cast<int>(num);  // 正确：显式转换
    return 0;
}
```  


**总结`explicit`用法**：  
- 只修饰「单参数构造函数」「带默认值的多参数构造函数」「转换函数」。  
- 目的：禁止编译器自动进行的隐式类型转换，强制显式构造/转换，减少意外。  


### 二、`noexcept`：声明函数不会抛出异常  
**核心作用**：告诉编译器“这个函数绝对不会抛出异常”，帮助编译器优化代码，并明确函数的异常安全承诺。  


#### 1. 基本用法：`noexcept`与`noexcept(true/false)`  
- `noexcept` 等价于 `noexcept(true)`：声明函数不会抛异常。  
- `noexcept(表达式)`：表达式为`true`则不抛异常，`false`则可能抛（等价于不写`noexcept`）。  

```cpp
// 声明"不会抛异常"
void func1() noexcept {
    // 如果这里抛出异常（如throw 1;），程序会直接调用std::terminate()终止，不会走异常处理
}

// 声明"可能抛异常"（等价于不写noexcept）
void func2() noexcept(false) {
    throw 1;  // 允许抛出，可被try-catch捕获
}

// 条件性noexcept：根据模板参数T的移动构造是否noexcept来决定
template <typename T>
void move_obj(T& a, T& b) noexcept(noexcept(T(std::move(a)))) {
    // ...
}
```  


#### 2. 为什么要用`noexcept`？  
- **编译器优化**：知道函数不抛异常后，编译器可以省略异常处理相关的代码（如栈展开准备），生成更高效的机器码。  
- **影响标准库行为**：标准库中很多函数（如容器的`push_back`、`resize`）会根据元素的「移动构造函数是否`noexcept`」决定行为。例如：  
  - 如果元素的移动构造是`noexcept`，容器扩容时会用「移动」（高效）；  
  - 如果不是，会用「复制」（低效但安全，避免移动中抛异常导致数据丢失）。  

**示例：移动构造函数加`noexcept`的意义**  
```cpp
class MyData {
public:
    MyData() = default;
    // 移动构造函数声明为noexcept，告诉容器"移动时不会抛异常"
    MyData(MyData&&) noexcept { 
        // 实际移动资源（如堆内存）
    }
    // 如果不加noexcept，容器可能会用复制而非移动
};

int main() {
    vector<MyData> vec;
    vec.reserve(100);  // 扩容时，因MyData移动构造noexcept，会用移动而非复制
    return 0;
}
```  


#### 3. 哪些函数默认是`noexcept`？  
- 析构函数：默认`noexcept(true)`（除非用户手动声明为`noexcept(false)`）。  
- 编译器生成的特殊成员函数（默认构造、复制/移动构造、赋值）：如果其内部调用的所有函数都是`noexcept`，则默认`noexcept`。  


**总结`noexcept`用法**：  
- 用于明确函数“不抛异常”的承诺（一旦抛了就会终止程序）。  
- 优先给「移动操作、析构函数、简单的工具函数」加`noexcept`，帮助编译器优化和标准库高效调用。  


### 三、`const`：常量修饰符，保证“只读”性  
**核心作用**：修饰变量、指针、函数参数、成员函数等，表明其“只读”属性，防止意外修改，增强代码安全性和可读性。  


#### 1. 修饰普通变量：值不可修改  
```cpp
const int a = 10;  // a是常量，初始化后不能改
a = 20;  // 编译报错！

// 注意：必须初始化
const int b;  // 编译报错！未初始化
```  


#### 2. 修饰指针：区分“指针本身不可改”和“指向的内容不可改”  
指针有两个部分：「指针变量本身（存地址）」和「指向的内存（存数据）」。`const`的位置决定了修饰哪部分：  

- **`const int* p`**：指向“常量int”的指针（指向的内容不可改，指针本身可改）。  
  ```cpp
  int x = 10, y = 20;
  const int* p = &x;  // p指向x，x的值不可通过p修改
  *p = 30;  // 编译报错！不能改指向的内容
  p = &y;   // 允许：指针本身可以改指向
  ```  

- **`int* const p`**：“常量指针”（指针本身不可改，指向的内容可改）。  
  ```cpp
  int x = 10, y = 20;
  int* const p = &x;  // p的指向不能改
  p = &y;  // 编译报错！指针本身不可改
  *p = 30; // 允许：指向的内容可以改（x变成30）
  ```  

- **`const int* const p`**：指向“常量int”的“常量指针”（两者都不可改）。  
  ```cpp
  const int* const p = &x;
  p = &y;   // 错：指针本身不可改
  *p = 30;  // 错：指向的内容不可改
  ```  


#### 3. 修饰函数参数：保证参数在函数内不被修改  
常用于避免参数被意外修改，尤其是传递大对象时（配合引用更高效）：  

```cpp
// 修饰普通参数：值传递，本身修改不影响外部，加const意义不大（但可防止函数内误改）
void print1(const int num) {
    num = 20;  // 编译报错！防止函数内修改
}

// 修饰引用参数：避免修改原对象，同时避免复制（高效）
void print2(const string& str) {  // str是原字符串的引用，且不可改
    str += "abc";  // 编译报错！不能修改原字符串
    cout << str << endl;
}
```  


#### 4. 修饰类的成员函数：保证函数不修改类的成员变量  
在成员函数后加`const`，表明该函数是“只读函数”：  
- 不能修改类的非静态成员变量（除非变量被`mutable`修饰）。  
- 不能调用类的非`const`成员函数（防止间接修改成员）。  
- `const`对象只能调用`const`成员函数（非`const`对象两者都能调用）。  

**示例**：  
```cpp
class Student {
private:
    string m_name;
    mutable int m_age;  // mutable变量：即使在const函数中也能修改
public:
    Student(string name, int age) : m_name(name), m_age(age) {}

    // const成员函数：只读，不修改成员
    string getName() const {
        // m_name = "abc";  // 编译报错！不能修改非mutable成员
        return m_name;
    }

    // const成员函数：可以修改mutable成员
    void increaseAge() const {
        m_age++;  // 允许：m_age是mutable
    }

    // 非const成员函数：可以修改成员
    void setName(string name) {
        m_name = name;
    }
};

int main() {
    const Student s1("张三", 18);  // const对象
    s1.getName();       // 允许：const对象调用const成员函数
    s1.increaseAge();   // 允许：const对象调用const成员函数（修改mutable）
    s1.setName("李四"); // 编译报错！const对象不能调用非const成员函数

    Student s2("李四", 20);  // 非const对象
    s2.getName();       // 允许：非const对象可调用const函数
    s2.setName("王五"); // 允许：非const对象可调用非const函数
    return 0;
}
```  


**总结`const`用法**：  
- 修饰变量：值不可改，必须初始化。  
- 修饰指针：根据位置区分“指向内容不可改”还是“指针本身不可改”。  
- 修饰函数参数：防止函数内修改参数（尤其引用传递时）。  
- 修饰成员函数：保证不修改成员变量（除`mutable`），`const`对象只能调用。  


### 最后一句话总结  
- `explicit`：别瞎转换，我要显式构造！  
- `noexcept`：我保证不抛异常，编译器放心优化！  
- `const`：这玩意儿不能改，谁改谁报错！