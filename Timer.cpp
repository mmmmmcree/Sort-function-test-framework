#include "Timer.h"
Timer::Timer(long long& runtime_information): 
    _runtime_information(runtime_information),
    _start_time(std::chrono::steady_clock::now())
{
    
}

Timer::~Timer() {
    auto end_time = std::chrono::steady_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end_time - _start_time);
    _runtime_information = duration.count();
}