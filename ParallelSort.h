#ifndef PARALLEL_H
#define PARALLEL_H
#include <thread>
#include <mutex>
#include <algorithm>
#include <vector>
#include "Sorts.h"

template<typename SortFunctor>
struct ParallelSort {
    void num_threads_calculate(long long);
    template<typename RandomAccessIterator, typename CompareFunctor>
    void selectional_sort(RandomAccessIterator first, RandomAccessIterator last, CompareFunctor compare);
    template<typename RandomAccessIterator, typename CompareFunctor>
    void selectional_merge(RandomAccessIterator first, RandomAccessIterator last, CompareFunctor compare);
    template<typename RandomAccessIterator>
    std::pair<long long, long long> operator()(RandomAccessIterator first, RandomAccessIterator last);
    template<typename RandomAccessIterator, typename CompareFunctor>
    void operator()(RandomAccessIterator first, RandomAccessIterator last, CompareFunctor compare);
    const std::string name = "parallel_sort(loaded with " + SortFunctor().name + ")";
private:
    std::pair<int, long long> num_info;
};

template<typename SortFunctor>
void ParallelSort<SortFunctor>::num_threads_calculate(long long size) {
    int num_sort_threads = 0; // 设为奇数
    int gear = ((size / 4096) + 1) / 2;
    switch(gear) {
        case 0 : num_sort_threads = 0; break;
        case 1 : num_sort_threads = 1; break;
        case 2 : num_sort_threads = 3; break;
        default : num_sort_threads = 7;
    }
    long long sort_block_size = size / (num_sort_threads + 1);
    num_info.first = num_sort_threads;
    num_info.second = sort_block_size;
}

template<typename SortFunctor>
template<typename RandomAccessIterator, typename CompareFunctor>
void ParallelSort<SortFunctor>::selectional_sort(RandomAccessIterator first, RandomAccessIterator last, CompareFunctor compare) {
    std::mutex mtx;
    std::vector<std::thread> sort_threads;
    const int num_threads = num_info.first, sort_block_size = num_info.second;
    auto block_begin = first, block_end = first + sort_block_size;
    for (int i = 0; i < num_threads; ++i, block_begin = block_end,  block_end += sort_block_size) {
        sort_threads.emplace_back(
            [compare, &mtx, block_begin, block_end]() {
                // std::lock_guard<std::mutex> lock(mtx);
                SortFunctor()(block_begin, block_end, compare);
            }
        );
    }
    for (auto& thread : sort_threads) {thread.join();}
    SortFunctor()(block_begin, last, compare);
}

template<typename SortFunctor>
template<typename RandomAccessIterator, typename CompareFunctor>
void ParallelSort<SortFunctor>::selectional_merge(RandomAccessIterator first, RandomAccessIterator last, CompareFunctor compare) {
    const int num_threads = num_info.first, sort_block_size = num_info.second;
    if (num_threads == 0) {return;}
    if (num_threads == 1) {std::inplace_merge(first, first +  sort_block_size, last, compare);}
    else {
        std::mutex mtx;
        const int merge_block_size = num_info.second * 2;
        auto block_begin = first, block_mid = first + sort_block_size, block_end = first + merge_block_size;
        if (num_threads == 3) {
            std::thread t(
                [compare, &mtx, block_begin, block_mid, block_end]() {
                    // std::lock_guard<std::mutex> lock(mtx);
                    std::inplace_merge(block_begin, block_mid, block_end, compare);
                }
            );
            
            std::inplace_merge(block_end, block_end + sort_block_size, last, compare);
            t.join();
            std::inplace_merge(first, block_end, last, compare);
        } else if (num_threads == 7) {
            std::vector<std::thread> merge_threads;
            for (int i = 0; i < 3; ++i) {
                merge_threads.emplace_back(
                    [compare, &mtx, block_begin, block_mid, block_end]() {
                        // std::lock_guard<std::mutex> lock(mtx);
                        std::inplace_merge(block_begin, block_mid, block_end, compare);
                    }
                );
                block_begin += merge_block_size;
                block_mid += merge_block_size;
                block_end += merge_block_size;
            }     
            std::inplace_merge(block_begin, block_mid, last, compare);
            for (int i = 0; i < 3; ++i) {
                merge_threads[i].join();
            }
            {
                std::thread t(
                    [compare, &mtx, first, merge_block_size]() {
                        std::lock_guard<std::mutex> lock(mtx);
                        std::inplace_merge(first, first + merge_block_size, first + 2 *merge_block_size, compare);
                    }
                );
                std::inplace_merge(first + 2 *merge_block_size, first + 3 *merge_block_size, last, compare);
                t.join();
            }
            std::inplace_merge(first, first + 2 *merge_block_size, last, compare);
        }
    }
}

template<typename SortFunctor>
template<typename RandomAccessIterator>
std::pair<long long, long long> ParallelSort<SortFunctor>::operator()(RandomAccessIterator first, RandomAccessIterator last) {
    long size = std::distance(first, last);
    if (size <= 1) {return std::make_pair(-1, -1);}
    auto compare = std::less<typename RandomAccessIterator::value_type>();
    num_threads_calculate(size);
    selectional_sort(first, last, compare);
    selectional_merge(first, last, compare);
    return std::make_pair(-1, -1);
}

template<typename SortFunctor>
template<typename RandomAccessIterator, typename CompareFunctor>
void ParallelSort<SortFunctor>::operator()(RandomAccessIterator first, RandomAccessIterator last, CompareFunctor compare) {
    long size = std::distance(first, last);
    if (size <= 1) {return;}
    num_threads_calculate(size);
    selectional_sort(first, last, compare);
    selectional_merge(first, last, compare);
}

#endif