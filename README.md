# 🧵 C++ 线程池 (ThreadPool)

一个高效、易用的C++线程池实现，支持任意函数和参数的异步执行。🚀

## ✨ 特性

- 🔧 支持任意函数和参数的异步执行
- 🔮 使用 `std::future` 获取异步任务的返回值
- 🔒 线程安全的任务队列
- 🔄 自动线程生命周期管理
- ⚠️ 支持异常处理
- 🆕 现代C++17特性

## 📖 使用方法

### 🎯 基本用法

```cpp
#include "thread_pool.hpp"

// 创建有4个工作线程的线程池
ThreadPool pool(4);

// 提交任务并获取future
auto result = pool.enqueue([](int x, int y) {
    return x + y;
}, 10, 20);

// 获取结果
int sum = result.get(); // sum = 30
```

### 🛠️ 支持的任务类型

#### 1️⃣ 有返回值的函数
```cpp
int add(int a, int b) {
    return a + b;
}

auto future = pool.enqueue(add, 5, 10);
int result = future.get(); // 15
```

#### 2️⃣ 无返回值的函数
```cpp
void print_message(const std::string& msg) {
    std::cout << msg << std::endl;
}

auto future = pool.enqueue(print_message, "Hello World");
future.get(); // 等待任务完成
```

#### 3️⃣ Lambda表达式
```cpp
auto future = pool.enqueue([](int x) -> int {
    return x * x;
}, 5);
int result = future.get(); // 25
```

#### 4️⃣ 类成员函数
```cpp
class Calculator {
public:
    int multiply(int a, int b) { return a * b; }
};

Calculator calc;
auto future = pool.enqueue(&Calculator::multiply, &calc, 3, 4);
int result = future.get(); // 12
```

## ⚙️ 编译要求

- 📋 C++17 或更高版本
- 🧵 支持pthread的编译器

### 🔨 编译命令
```bash
g++ -std=c++17 -pthread -O2 -o your_program your_program.cpp
```

## 📚 API 参考

### 🏗️ 构造函数
```cpp
ThreadPool(size_t num_threads)
```
创建指定数量工作线程的线程池。

### 📝 enqueue 方法
```cpp
template<class F, class... Args>
auto enqueue(F&& f, Args&&... args) -> std::future<typename std::invoke_result<F, Args...>::type>
```
向线程池提交任务，返回一个 `std::future` 对象用于获取结果。

**📥 参数:**
- `f`: 要执行的函数或可调用对象
- `args`: 函数参数

**📤 返回值:**
- `std::future<return_type>`: 用于获取异步执行结果的future对象

**🚫 异常:**
- 如果线程池已经停止，会抛出 `std::runtime_error`

## 🏗️ 设计原理

### 🔧 核心组件

1. **🧵 工作线程向量** (`workers`): 存储所有工作线程
2. **📋 任务队列** (`tasks`): 线程安全的任务队列
3. **🔒 互斥锁** (`queue_mutex`): 保护任务队列的访问
4. **📢 条件变量** (`condition`): 用于线程间的同步
5. **🛑 停止标志** (`stop`): 控制线程池的生命周期

### 🔄 工作流程

1. 🚀 构造时创建指定数量的工作线程
2. ⏳ 工作线程循环等待任务队列中的任务
3. 📦 `enqueue` 方法将任务包装成 `std::packaged_task` 并加入队列
4. ⚡ 工作线程从队列中取出任务并执行
5. 🏁 析构时设置停止标志，等待所有线程完成

## 🧪 测试

项目包含完整的测试用例：

```bash
# 🔨 编译测试程序
g++ -std=c++17 -pthread -O2 -o test_thread_pool test_thread_pool.cpp

# 🚀 运行测试
./test_thread_pool
```

测试包括：
- ✅ 基本功能测试
- 🔀 并发任务测试  
- 🏃‍♂️ 性能测试
- ⚠️ 异常处理测试
- 💀 线程池销毁测试
- 🔧 Lambda表达式测试

## ⚠️ 注意事项

1. **🧵 线程数量**: 通常设置为 CPU 核心数或稍多一些
2. **⚖️ 任务粒度**: 避免提交过于细粒度的任务，会增加调度开销
3. **⚠️ 异常处理**: 任务中的异常会被传播到 `future.get()` 调用处
4. **♻️ 生命周期**: 确保线程池对象的生命周期覆盖所有使用期间

## 🚀 性能特点

- ⚡ 低延迟的任务调度
- 💾 高效的内存使用
- 🔥 支持高并发任务执行
- ⚖️ 自动负载均衡

## 📄 许可证

📃 MIT License
