#ifndef SORTS_H
#define SORTS_H
#include <vector>
#include <string>
#include <functional>
#include <algorithm>

class BubbleSort {
public:
    template<typename BidirectionalIterator>
    std::pair<int, int> operator()(BidirectionalIterator first, BidirectionalIterator last) {
        using value_type = typename BidirectionalIterator::value_type;
        int compare_times = 0, assign_times = 0;
        for (; std::distance(first, last) > 1; --last) {
            auto temp_first = first, temp_last = last;
            for (auto current_iter = temp_first, next_iter = ++temp_first;
                distance(current_iter, temp_last) > 1;
                ++current_iter, ++next_iter) {
                compare_times += 1;
                if (*next_iter < *current_iter) {
                    std::swap(*next_iter, *current_iter);
                    assign_times += 3;
                }
            }
        }
        return std::make_pair(compare_times, assign_times);
    }
    template<typename BidirectionalIterator, typename CompareFunctor>
    void operator()(BidirectionalIterator first, BidirectionalIterator last, CompareFunctor compare) {
        using value_type = typename BidirectionalIterator::value_type;
        for (; std::distance(first, last) > 1; --last) {
            auto temp_first = first, temp_last = last;
            for (auto current_iter = temp_first, next_iter = ++temp_first;
                distance(current_iter, temp_last) > 1;
                ++current_iter, ++next_iter) {
                if (compare(*next_iter, *current_iter)) {
                    std::swap(*next_iter, *current_iter);
                }
            }
        }
    }
    const std::string name = "bubble_sort";
};

class IntroSort {
public:
    template<template<typename> typename CompareFunctor = std::less, typename RandomAccessIterator>
    std::pair<int, int> operator()(RandomAccessIterator first, RandomAccessIterator last) {
        sort(first, last);
        return std::make_pair(10, 10);
    }
    const std::string name = "intro_sort";
};

class DoNothingSort {
public:
    template<template<typename> typename CompareFunctor = std::less, typename ForwardIterator>
    std::pair<int, int> operator()(ForwardIterator first, ForwardIterator last) {
        //? do nothing
        return std::make_pair(10, 10);
    }
    const std::string name = "do_nothing_sort";   
};

class ShellSort_GOONER{
public:
    template<template<typename> typename CompareFunctor = std::less, typename RandomAccessIterator>
    std::pair<int, int> operator()(RandomAccessIterator first, RandomAccessIterator last) {
    using value_type = typename RandomAccessIterator::value_type;
    CompareFunctor<value_type> compare;
    auto n = std::distance(first, last);  
    for (auto d = n / 2; d >= 1; d = d / 2) {
        for (auto i = first + d; i != last; ++i){
                auto temp = *i;
                auto k = i - d;
                while (k >= first && *k > temp) {
                    *(k + d) = *k;
                    k = k - d;
                }
                *(k + d) = temp;
                }   
        }
        return std::make_pair(10, 10);
    }
    const std::string name = "ShellSort_GOONER";
};

#endif