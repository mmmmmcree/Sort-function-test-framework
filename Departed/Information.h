#ifndef INFORMATION_H
#define INFORMATION_H
#include <functional>
#include <string>

struct Information {
    Information(
            std::function<void()> sort_func,
            std::string distribute_t,
            std::string container_t,
            std::string value_t,
            long long scale, 
            long long time
        ):
        sort_function(sort_func),
        distribute_type(distribute_t),
        container_type(container_t),
        value_type(value_t),
        data_scale(scale),
        runtime(time)
    {}
    std::function<void()> sort_function;
    std::string distribute_type;
    std::string container_type;
    std::string value_type;
    long long data_scale;
    long long runtime;
};

#endif
