#include "thread_pool.hpp"
#include <iostream>
#include <chrono>
#include <vector>

int main()
{
    std::cout << "线程池使用示例" << std::endl;

    // 创建一个有4个工作线程的线程池
    ThreadPool pool(4);

    std::cout << "主线程ID: " << std::this_thread::get_id() << std::endl;

    // 示例1: 提交简单任务
    std::cout << "\n示例1: 提交简单任务" << std::endl;
    std::vector<std::future<int>> results;

    for (int i = 0; i < 8; ++i)
    {
        results.emplace_back(
            pool.enqueue([i]() -> int
                         {
                std::cout << "任务 " << i << " 在线程 " 
                          << std::this_thread::get_id() << " 上执行" << std::endl;
                std::this_thread::sleep_for(std::chrono::milliseconds(100));
                return i * i; }));
    }

    // 获取所有结果
    std::cout << "\n任务结果:" << std::endl;
    for (size_t i = 0; i < results.size(); ++i)
    {
        std::cout << "任务 " << i << " 结果: " << results[i].get() << std::endl;
    }

    // 示例2: 提交不同类型的任务
    std::cout << "\n示例2: 提交不同类型的任务" << std::endl;

    // 字符串处理任务
    auto string_task = pool.enqueue([](const std::string &str) -> std::string
                                    { return "处理后的: " + str; }, std::string("Hello"));

    // 数学计算任务
    auto math_task = pool.enqueue([](double x, double y) -> double
                                  { return x * y + 10.0; }, 3.14, 2.0);

    // 无返回值任务
    auto void_task = pool.enqueue([]()
                                  { std::cout << "这是一个没有返回值的任务" << std::endl; });

    // 获取结果
    std::cout << "字符串任务结果: " << string_task.get() << std::endl;
    std::cout << "数学任务结果: " << math_task.get() << std::endl;
    void_task.get(); // 等待无返回值任务完成

    std::cout << "\n所有任务完成！" << std::endl;

    return 0;
}
