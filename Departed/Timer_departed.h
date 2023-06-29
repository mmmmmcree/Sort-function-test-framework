#ifndef TIMER_H
#define TIMER_H
#include <iostream>
#include <chrono>
#include <vector>
#include <algorithm>
#include <functional>
#include <string>

class Timer {
    using str_list = typename std::initializer_list<std::string>;
    using func_list = typename std::initializer_list<std::function<void()>>;
public:
    Timer(func_list, str_list);
    Timer() = delete;
    Timer(const Timer&) = delete;
    Timer& operator=(const Timer&) = delete;
    ~Timer() = default;
    void get_runtime(); //todo 将在这里把执行时间写入txt或excel
    void show_runtime() const;
private:
    std::vector<long long> _runtime_container;
    const std::vector<std::string> _sort_function_names; //todo Test类写好后把字符串数组移到Test类中
    const std::vector<std::function<void()>> _sort_functions;
};
#endif