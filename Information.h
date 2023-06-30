#ifndef INFORMATION_H
#define INFORMATION_H
#include <string>
#include <vector>

struct PerforamanceInfo {
    PerforamanceInfo();
    PerforamanceInfo(const std::string&, const std::string&, long long);
    std::string distribute_type;
    std::string value_type;
    long long data_scale;
    long long runtime;
    std::pair<int, int> compare_assign_times;
};

struct SortFunctionInfo {
    SortFunctionInfo();
    enum class IteratorCategory {
        UnknownOrBad,
        ForwardIterator,
        BidirectionalIterator,
        RandomAccessIterator
    };
    bool is_correct;
    IteratorCategory suitable_iterator_category;
    std::vector<PerforamanceInfo> performance_info_container;
};

#endif