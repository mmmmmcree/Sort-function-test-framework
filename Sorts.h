#ifndef SORTS_H
#define SORTS_H
#include <vector>
#include <string>
#include <functional>
#include <algorithm>

class BubbleSort {
public:
    template<template<typename> typename CompareFunctor = std::less, typename BidirectionalIterator>
    void operator()(BidirectionalIterator first, BidirectionalIterator last) {
        using value_type = typename BidirectionalIterator::value_type;
        CompareFunctor<value_type> compare;
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
    void operator()(RandomAccessIterator first, RandomAccessIterator last) {
        sort(first, last);
    }
    const std::string name = "intro_sort";
};

class DoNothingSort {
public:
    template<template<typename> typename CompareFunctor = std::less, typename ForwardIterator>
    void operator()(ForwardIterator first, ForwardIterator last) {
        //? do nothing
    }
    const std::string name = "do_nothing_sort";   
};

class ShellSort_GOONER{
public:
    template<template<typename> typename CompareFunctor = std::less, typename RandomAccessIterator>
    void operator()(RandomAccessIterator first, RandomAccessIterator last) {
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
    }
    const std::string name = "ShellSort_GOONER";
};

#endif