#ifndef TIMER_H
#define TIMER_H
#include <chrono>

class Timer {
public:
    Timer(long long&);
    ~Timer();
    Timer() = delete;
    Timer(const Timer&) = delete;
    Timer& operator=(const Timer&) = delete;
private:
    long long& _runtime_information;
    std::chrono::steady_clock::time_point _start_time;
};

#endif