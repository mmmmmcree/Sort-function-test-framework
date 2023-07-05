#ifndef SORTS_H
#define SORTS_H
#include <vector>
#include <list>
#include <set>
#include <string>
#include <functional>
#include <algorithm>
#include <execution>
#include "ParallelSort.h"

struct BubbleSort {
    template<typename RandomAccessIterator>
    std::pair<long long, long long> operator()(RandomAccessIterator first, RandomAccessIterator last) {
        int compare_times = 0, assign_times = 0;
        bool is_swaped = false;
        for (; first != last - 1; --last) {
            is_swaped = false;
            for (auto iter = first; iter != last - 1; ++iter) {
                compare_times += 1;
                if (*(iter + 1) < *iter) {
                    std::swap(*iter, *(iter + 1));
                    assign_times += 1;
                    is_swaped = true;
                }
            }
            if (!is_swaped) {break;}
        }
        return std::make_pair(compare_times, assign_times);
    }
    template<typename RandomAccessIterator, typename CompareFunctor>
    void operator()(RandomAccessIterator first, RandomAccessIterator last, CompareFunctor compare) {
        bool is_swaped = false;
        for (; first != last - 1; --last) {
            is_swaped = false;
            for (auto iter = first; iter != last - 1; ++iter) {
                if (compare(*(iter + 1) , *iter)) {
                    std::swap(*iter, *(iter + 1));
                    is_swaped = true;
                }
            }
            if (!is_swaped) {break;}
        }
    }
    const std::string name = "bubble_sort";
};

struct CocktailShakerSort {
    template<typename RandomAccessIterator>
    std::pair<long long, long long> operator()(RandomAccessIterator first, RandomAccessIterator last) {
        long long compare_times = 0, assign_times = 0;
        bool is_swapped = false;
        for (; last != first; ++first, --last) {
            is_swapped = false;
            for (auto iter = last - 1; iter != first; --iter) {
                compare_times += 1;
                if (*iter < *(iter - 1)) {
                    std::swap(*iter, *(iter - 1));
                    assign_times += 1;
                    is_swapped = true;
                }
            }
            for (auto iter = first; iter != last - 1; ++iter) {
                compare_times += 1;
                if (*(iter + 1) < *iter) {
                    std::swap(*iter, *(iter + 1));
                    assign_times += 1;
                    is_swapped = true;
                }
            }
            if (!is_swapped) {
                break;
            }
        }
        return std::make_pair(compare_times, assign_times);
    }
    template<typename RandomAccessIterator, typename CompareFunctor>
    void operator()(RandomAccessIterator first, RandomAccessIterator last, CompareFunctor compare) {
        bool is_swapped = false;
        for (; last != first; ++first, --last) {
            is_swapped = false;
            for (auto iter = last - 1; iter != first; --iter) {
                if (compare(*iter, *(iter - 1))) {
                    std::swap(*iter, *(iter - 1));
                    is_swapped = true;
                }
            }
            for (auto iter = first; iter != last - 1; ++iter) {
                if (compare(*(iter + 1), *iter)) {
                    std::swap(*iter, *(iter + 1));
                    is_swapped = true;
                }
            }
            if (!is_swapped) {
                break;
            }
        }
    }
    const std::string name = "cocktail_shaker_sort";
};

struct DoubleSort {
    template<typename RandomAccessIterator>
    std::pair<long long, long long> operator()(RandomAccessIterator first, RandomAccessIterator last) {
        long long compare_times = 0, assign_times = 0;
        for (; first != last; ++first, --last) {
            for (auto iter_1 = first, iter_2 = last - 1; iter_1 != last - 1; ++iter_1, --iter_2) {
                compare_times += 1;
                if (*(iter_1 + 1) < *iter_1) {
                    std::swap(*iter_1, *(iter_1 + 1));
                    assign_times += 1;
                }
                compare_times += 1;
                if (*iter_2 < *(iter_2 - 1)) {
                    std::swap(*iter_2, *(iter_2 - 1));
                    assign_times += 1;
                }
            }
        }
        return std::make_pair(compare_times, assign_times);
    }
    template<typename RandomAccessIterator, typename CompareFunctor>
    void operator()(RandomAccessIterator first, RandomAccessIterator last, CompareFunctor compare) {
        for (; first != last; ++first, --last) {
            for (auto iter_1 = first, iter_2 = last - 1; iter_1 != last - 1; ++iter_1, --iter_2) {
                if (compare(*(iter_1 + 1), *iter_1)) {
                    std::swap(*iter_1, *(iter_1 + 1));
                }
                if (compare(*iter_2, *(iter_2 - 1))) {
                    std::swap(*iter_2, *(iter_2 - 1));
                }
            }
        }
    }
    const std::string name = "double_sort";
};

struct CombSort {
    template<typename RandomAccessIterator>
    std::pair<long long, long long> operator()(RandomAccessIterator first, RandomAccessIterator last) {
        long long compare_times = 0, assign_times = 0;
        const double shrink_factor = 1.3;
        long gap = std::distance(first, last);
        while (gap > 1) {
            gap /= shrink_factor;
            for (auto iter = first; iter + gap < last; ++iter) {
                compare_times += 1;
                if (*(iter + gap) < *iter) {
                    std::swap(*iter, *(iter + gap));
                    assign_times += 1;
                }
            }
        }
        return std::make_pair(compare_times, assign_times);
    }
    template<typename RandomAccessIterator, typename CompareFunctor>
    void operator()(RandomAccessIterator first, RandomAccessIterator last, CompareFunctor compare) {
        const double shrink_factor = 1.3;
        long gap = std::distance(first, last);
        while (gap > 1) {
            gap /= shrink_factor;
            for (auto iter = first; iter + gap < last; ++iter) {
                if (compare(*(iter + gap), *iter)) {
                    std::swap(*iter, *(iter + gap));
                }
            }
        }
    }
    const std::string name = "comb_sort";
};

struct StoogeSort {
    template<typename RandomAccessIterator>
    std::pair<long long, long long> operator()(RandomAccessIterator first, RandomAccessIterator last){
        long size = std::distance(first, last);
        if (size <= 1) {return std::make_pair(-1, -1);}
        if (*(last - 1) < *first) {
            std::swap(*first, *(last - 1));
        }
        if (size > 2) {
            long one_third_of_size = size / 3;
            this->operator()(first, last - one_third_of_size);
            this->operator()(first + one_third_of_size, last);
            this->operator()(first, last - one_third_of_size);
        }
        return std::make_pair(-1, -1);
    }
    template<typename RandomAccessIterator, typename CompareFunctor>
    void operator()(RandomAccessIterator first, RandomAccessIterator last, CompareFunctor compare) {
        long size = std::distance(first, last);
        if (size <= 1) {return;}
        if (compare(*(last - 1), *first)) {
            std::swap(*first, *(last - 1));
        }
        if (size > 2) {
            long one_third_of_size = size / 3;
            this->operator()(first, last - one_third_of_size, compare);
            this->operator()(first + one_third_of_size, last, compare);
            this->operator()(first, last - one_third_of_size, compare);
        }
    }
    const std::string name = "stooge_sort";
};

struct OddEvenSort {
    template<typename RandomAccessIterator>
    std::pair<long long, long long> operator()(RandomAccessIterator first, RandomAccessIterator last){
        long long compare_times = 0, assign_times = 0;
        bool is_sorted = false;
        while (!is_sorted) {
            is_sorted = true;
            for (auto iter = first; iter < last - 1; iter += 2)  {
                compare_times += 1;
                if (*(iter + 1) < *iter) {
                    std::swap(*iter, *(iter + 1));
                    assign_times += 1;
                    is_sorted = false;
                }
            }
            for (auto iter = first + 1; iter < last - 1; iter += 2) {
                compare_times += 1;
                if (*(iter + 1) < *iter) {
                    std::swap(*iter, *(iter + 1));
                    assign_times += 1;
                    is_sorted = false;
                }
            }
        }
        return std::make_pair(compare_times, assign_times);
    }
    template<typename RandomAccessIterator, typename CompareFunctor>
    void operator()(RandomAccessIterator first, RandomAccessIterator last, CompareFunctor compare) {
        bool is_sorted = false;
        while (!is_sorted) {
            is_sorted = true;
            for (auto iter = first; iter < last - 1; iter += 2)  {
                if (compare(*(iter + 1), *iter)) {
                    std::swap(*iter, *(iter + 1));
                    is_sorted = false;
                }
            }
            for (auto iter = first + 1; iter < last - 1; iter += 2) {
                if (compare(*(iter + 1), *iter)) {
                    std::swap(*iter, *(iter + 1));
                    is_sorted = false;
                }
            }
        }
    }
    std::string name = "odd_even_sort";
};

struct SelectSort {
    template<typename RandomAccessIterator>
    std::pair<long long, long long> operator()(RandomAccessIterator first, RandomAccessIterator last) {
        long long compare_times = 0, assign_times = 0;
        for (; first != last - 1; ++first) {
            auto exchange_iter = first;
            for (auto iter = first + 1; iter != last; ++iter) {
                compare_times += 1;
                if (*iter < *exchange_iter) {
                    exchange_iter = iter;
                }
            }
            std::swap(*first, *exchange_iter);
            assign_times += 1;
        }
        return std::make_pair(compare_times, assign_times);
    }
    template<typename RandomAccessIterator, typename CompareFunctor>
    void operator()(RandomAccessIterator first, RandomAccessIterator last, CompareFunctor compare) {
        for (; first != last - 1; ++first) {
            auto exchange_iter = first;
            for (auto iter = first + 1; iter != last; ++iter) {
                if (compare(*iter , *exchange_iter)) {
                    exchange_iter = iter;
                }
            }
            std::swap(*first, *exchange_iter);
        }
    }
    const std::string name = "select_sort";
};

struct BinarySelectSort {
    template<typename RandomAccessIterator>
    std::pair<long long, long long> operator()(RandomAccessIterator first, RandomAccessIterator last) {
        long long compare_times = 0, assign_times = 0;
        for (; first != last; ++first, --last) {
            auto min_exchange_iter = first, max_exchange_iter = first;
            for (auto iter = first + 1; iter != last; ++iter) {
                compare_times += 1;
                if (*iter < *min_exchange_iter) {
                    min_exchange_iter = iter;
                }
                compare_times += 1;
                if (*max_exchange_iter < *iter) {
                    max_exchange_iter = iter;
                }
            }
            std::swap(*first, *min_exchange_iter);
            if (max_exchange_iter == first) {
                std::swap(*(last - 1), *min_exchange_iter);
            } else {
                std::swap(*(last - 1), *max_exchange_iter);
            }
            assign_times += 2;
        }
        return std::make_pair(compare_times, assign_times);
    }
    template<typename RandomAccessIterator, typename CompareFunctor>
    void operator()(RandomAccessIterator first, RandomAccessIterator last, CompareFunctor compare) {
        for (; first != last; ++first, --last) {
            auto min_exchange_iter = first, max_exchange_iter = first;
            for (auto iter = first + 1; iter != last; ++iter) {
                if (compare(*iter, *min_exchange_iter)) {
                    min_exchange_iter = iter;
                }
                if (compare(*max_exchange_iter, *iter)) {
                    max_exchange_iter = iter;
                }
            }
            std::swap(*first, *min_exchange_iter);
            if (max_exchange_iter == first) {
                std::swap(*(last - 1), *min_exchange_iter);
            } else {
                std::swap(*(last - 1), *max_exchange_iter);
            }
        }
    }
    const std::string name = "binary_select_sort";
};

struct InsertionSort {
    template<typename RandomAccessIterator>
    std::pair<long long, long long> operator()(RandomAccessIterator first, RandomAccessIterator last) {
        long long compare_times = 0, assign_times = 0;
        for (auto iter_1 = first; iter_1 != last; ++iter_1) {
            auto iter_2 = iter_1;
            auto temp_value = *iter_1;
            for (; iter_2 != first && temp_value< *(iter_2 - 1); --iter_2) {
                    compare_times += 1;
                    *iter_2  = *(iter_2 - 1);
                    assign_times += 1;
            }
            *iter_2 = temp_value;
            assign_times += 1;
        }
        return std::make_pair(compare_times, assign_times);
    }
    template<typename RandomAccessIterator, typename CompareFunctor>
    void operator()(RandomAccessIterator first, RandomAccessIterator last, CompareFunctor compare) {
        for (auto iter_1 = first; iter_1 != last; ++iter_1) {
            auto iter_2 = iter_1;
            auto temp_value = *iter_1;
            for (; iter_2 != first && compare(temp_value, *(iter_2 - 1)); --iter_2) {
                    *iter_2  = *(iter_2 - 1);
            }
            *iter_2 = temp_value;
        }
    }
    const std::string name = "insertion_sort";
};

struct BinaryInsertionSort {
    template<typename RandomAccessIterator>
    std::pair<long long, long long> operator()(RandomAccessIterator first, RandomAccessIterator last){
        long long compare_times = 0, assign_times = 0;
        for (auto iter_1 = first; iter_1 != last; ++iter_1) {
            auto temp_value = *iter_1;
            auto low_iter = first, high_iter = iter_1 - 1, mid_iter = low_iter + std::distance(low_iter, high_iter) / 2;
            while (low_iter <= high_iter) {
                compare_times += 1;
                if (temp_value < *mid_iter) {
                    high_iter = mid_iter - 1;
                } else {
                    low_iter = mid_iter + 1;
                }
                mid_iter = low_iter + std::distance(low_iter, high_iter) / 2;
            }
            for (auto iter_2 = iter_1; iter_2 != low_iter; --iter_2) {
                *iter_2 = *(iter_2 - 1);
                assign_times += 1;
            }
            *low_iter = temp_value;
        }
        return std::make_pair(compare_times, assign_times);
    }
    template<typename RandomAccessIterator, typename CompareFunctor>
    void operator()(RandomAccessIterator first, RandomAccessIterator last, CompareFunctor compare) {
        for (auto iter_1 = first; iter_1 != last; ++iter_1) {
            auto temp_value = *iter_1;
            auto insert_position =  std::upper_bound(first, iter_1, *iter_1, compare);
            for (auto iter_2 = iter_1; iter_2 != insert_position; --iter_2) {
                *iter_2 = *(iter_2 - 1);
            }
            *insert_position = temp_value;
        }
    }
    const std::string name = "binary_insertion_sort";
};

struct ShellSort {
    template<typename RandomAccessIterator>
    std::pair<long long, long long> operator()(RandomAccessIterator first, RandomAccessIterator last) {
        long long compare_times = 0, assign_times = 0;
        const std::vector<int> gaps{701, 301, 132, 57, 23, 10, 4, 1};
        for (const int gap : gaps) {
            for (auto iter_1 = first + gap; iter_1 < last; ++iter_1) {
                auto temp_value = *iter_1;
                auto iter_2 = iter_1;
                while (iter_2 - gap >= first && temp_value < *(iter_2 - gap)) {
                    compare_times += 1;
                    *iter_2 = *(iter_2 - gap); 
                    assign_times += 1;
                    iter_2 -= gap;
                }
                *iter_2 = temp_value;
                assign_times += 1;
            }
        }
        return std::make_pair(compare_times, assign_times);
    }
    template<typename RandomAccessIterator, typename CompareFunctor>
    void operator()(RandomAccessIterator first, RandomAccessIterator last, CompareFunctor compare) {
        const std::vector<int> gaps{701, 301, 132, 57, 23, 10, 4, 1};
        for (const int gap : gaps) {
            for (auto iter_1 = first + gap; iter_1 < last; ++iter_1) {
                auto temp_value = *iter_1;
                auto iter_2 = iter_1;
                while (iter_2 - gap >= first && compare(temp_value, *(iter_2 - gap))) {
                    *iter_2 = *(iter_2 - gap); 
                    iter_2 -= gap;
                }
                *iter_2 = temp_value;
            }
        }
    }
    const std::string name = "shell_sort";
};


struct ShellShrinkSort {
    template<typename RandomAccessIterator>
    std::pair<long long, long long> operator()(RandomAccessIterator first, RandomAccessIterator last) {
        long long compare_times = 0, assign_times = 0;
        const double shrink_factor = 1.3;
        long gap = std::distance(first, last);
        while (gap > 1) {
            gap /= shrink_factor;
            for (auto iter_1 = first + gap; iter_1 < last; ++iter_1) {
                auto temp_value = *iter_1;
                auto iter_2 = iter_1;
                while (iter_2 - gap >= first && temp_value < *(iter_2 - gap)) {
                    compare_times += 1;
                    *iter_2 = *(iter_2 - gap);
                    iter_2 -= gap;
                    assign_times += 1;
                }
                *iter_2 = temp_value;
                assign_times += 1;
            }
        }
        return std::make_pair(compare_times, assign_times);
    }
    template<typename RandomAccessIterator, typename CompareFunctor>
    void operator()(RandomAccessIterator first, RandomAccessIterator last, CompareFunctor compare) {
        const double shrink_factor = 1.3;
        long gap = std::distance(first, last);
        while (gap > 1) {
            gap /= shrink_factor;
            for (auto iter_1 = first + gap; iter_1 < last; ++iter_1) {
                auto temp_value = *iter_1;
                auto iter_2 = iter_1;
                while (iter_2 - gap >= first && compare(temp_value, *(iter_2 - gap))) {
                    *iter_2 = *(iter_2 - gap);
                    iter_2 -= gap;
                }
                *iter_2 = temp_value;
            }
        }
    }
    const std::string name = "shell_shrink_sort";
};

struct MergeSort {
    template<typename RandomAccessIterator>
    std::pair<long, long> operator()(RandomAccessIterator first, RandomAccessIterator last) {
        long size = std::distance(first, last);
        auto mid_iter = first + size / 2;
        if (size > 1) {
            this->operator()(first, mid_iter);
            this->operator()(mid_iter, last);
            std::inplace_merge(first, mid_iter, last);
        }
        return std::make_pair(-1, -1);
    }
    template<typename RandomAccessIterator, typename CompareFunctor>
    void operator()(RandomAccessIterator first, RandomAccessIterator last, CompareFunctor compare) {
        long size = std::distance(first, last);
        auto mid_iter = first + size / 2;
        if (size > 1) {
            this->operator()(first, mid_iter, compare);
            this->operator()(mid_iter, last, compare);
            std::inplace_merge(first, mid_iter, last, compare);
        }
    }
    const std::string name = "merge_sort"; 
};

struct InterativeMergeSort {
    template<typename RandomAccessIterator>
    std::pair<long long, long long> operator()(RandomAccessIterator first, RandomAccessIterator last) {
        long size = std::distance(first, last);
        if (size <= 1) {return std::make_pair(-1, -1);}
        long merge_scale = 2;
        while (merge_scale < size) {
            for (auto iter = first; iter + merge_scale <= last; iter += merge_scale) {
                std::inplace_merge(iter, iter + merge_scale / 2, iter + merge_scale);
                if (iter + merge_scale > last) {
                    std::inplace_merge(iter, iter + merge_scale / 2, last);
                }
            }
            merge_scale *= 2;
        }
        std::inplace_merge(first, first + merge_scale / 2, last);
        return std::make_pair(-1, -1);
    }
    template<typename RandomAccessIterator, typename CompareFunctor>
    void operator()(RandomAccessIterator first, RandomAccessIterator last, CompareFunctor compare) {
        long size = std::distance(first, last);
        if (size <= 1) {return;}
        long merge_scale = 2;
        while (merge_scale < size) {
            for (auto iter = first; iter + merge_scale <= last; iter += merge_scale) {
                std::inplace_merge(iter, iter + merge_scale / 2, iter + merge_scale, compare);
                if (iter + merge_scale > last) {
                    std::inplace_merge(iter, iter + merge_scale / 2, last, compare);
                }
            }
            merge_scale *= 2;
        }
        std::inplace_merge(first, first + merge_scale / 2, last, compare);
    }
    const std::string name = "interative_merge_sort";
};

struct QuickSort {
    template<typename RandomAccessIterator>
    std::pair<long long, long long> operator()(RandomAccessIterator first, RandomAccessIterator last) {
        long size =  std::distance(first, last);
        if (size <= 1) {return std::make_pair(-1, -1);}
        auto pivot_iter = first + size / 2;
        std::nth_element(first, pivot_iter, last);
        this->operator()(first, pivot_iter);
        this->operator()(pivot_iter + 1, last);
        return std::make_pair(-1, -1);
    }
    template<typename RandomAccessIterator, typename CompareFunctor>
    void operator()(RandomAccessIterator first, RandomAccessIterator last, CompareFunctor compare) {
        long size =  std::distance(first, last);
        if (size <= 1) {return;}
        auto pivot_iter = first + size / 2;
        std::nth_element(first, pivot_iter, last, compare);
        this->operator()(first, pivot_iter, compare);
        this->operator()(pivot_iter + 1, last, compare);
    }
    const std::string name = "quick_sort";
};

struct IntroSort {
    template<typename RandomAccessIterator>
    std::pair<long long, long long> operator()(RandomAccessIterator first, RandomAccessIterator last) {
        sort(first, last);
        return std::make_pair(-1, -1);
    }
    template<typename RandomAccessIterator, typename CompareFunctor>
    void operator()(RandomAccessIterator first, RandomAccessIterator last, CompareFunctor compare) {
        sort(first, last, compare);
    }
    const std::string name = "intro_sort";
};

struct ParallelIntroSort {
    template<typename RandomAccessIterator>
    std::pair<long long, long long> operator()(RandomAccessIterator first, RandomAccessIterator last) {
        std::sort(std::execution::par, first, last);
        return std::make_pair(-1, -1);
    }
    template<typename RandomAccessIterator, typename CompareFunctor>
    void operator()(RandomAccessIterator first, RandomAccessIterator last, CompareFunctor compare) {
        std::sort(std::execution::par, first, last, compare);
    }
    const std::string name = "parallel_intro_sort";
};

struct HeapSort {
    template<typename RandomAccessIterator>
    std::pair<long long, long long> operator()(RandomAccessIterator first, RandomAccessIterator last) {
        std::make_heap(first, last);
        std::sort_heap(first, last);
        return std::make_pair(-1, -1);
    }
    template<typename RandomAccessIterator, typename CompareFunctor>
    void operator()(RandomAccessIterator first, RandomAccessIterator last, CompareFunctor compare) {
        std::make_heap(first, last);
        std::sort_heap(first, last, compare);
    }
    const std::string name = "heap_sort";       
};

struct TreeSort {
    template<typename RandomAccessIterator>
    std::pair<long long, long long> operator()(RandomAccessIterator first, RandomAccessIterator last) {
        std::multiset<typename RandomAccessIterator::value_type> temp_container(first, last);
        std::copy(temp_container.begin(), temp_container.end(), first);
        return std::make_pair(-1, -1);
    }
    template<typename RandomAccessIterator, typename CompareFunctor>
    void operator()(RandomAccessIterator first, RandomAccessIterator last, CompareFunctor compare) {
        std::multiset<typename RandomAccessIterator::value_type, CompareFunctor> temp_container(first, last);
        std::copy(temp_container.begin(), temp_container.end(), first);
    }
    const std::string name = "tree_sort";           
};

struct BucketSort {
    template<typename RandomAccessIterator>
    std::pair<long long, long long> operator()(RandomAccessIterator first, RandomAccessIterator last) {
        auto min_iter = std::min_element(first, last), max_iter = std::max_element(first, last);
        long bucket_count = *max_iter - *min_iter;
        std::vector<std::multiset<typename RandomAccessIterator::value_type>> buckets(bucket_count + 1);
        for (auto iter = first; iter != last; ++iter) {
            buckets[*iter - *min_iter].insert(*iter);
        }
        for (const auto& bucket : buckets) {
            for (const auto& element : bucket) {
                *(first++) = element;
            }
        }
        return std::make_pair(-1, -1);
    }
    std::string name = "bucket_sort";
};

struct DoNothingSort {
    template<typename RandomAccessIterator>
    std::pair<long long, long long> operator()(RandomAccessIterator first, RandomAccessIterator last) {
        //? do nothing
        return std::make_pair(-1, -1);
    }
    template<typename RandomAccessIterator, typename CompareFunctor>
    void operator()(RandomAccessIterator first, RandomAccessIterator last, CompareFunctor compare) {
        //? do nothing
    }
    const std::string name = "do_nothing_sort";   
};

struct CycleSort {
    template<typename RandomAccessIterator>
    std::pair<long long, long long> operator()(RandomAccessIterator first, RandomAccessIterator last) {
        long long compare_times = 0, assign_times = 0;
        for (auto cycle_start_iter = first; cycle_start_iter < last - 1; ++cycle_start_iter) {
            auto temp_value = *cycle_start_iter;
            auto pos_iter = cycle_start_iter;
            for (auto iter = cycle_start_iter + 1; iter < last; ++iter) {
                compare_times += 1;
                if (*iter < temp_value) {++pos_iter;}
            }
            if (pos_iter == cycle_start_iter) {continue;}
            while (temp_value == *pos_iter) {++pos_iter;}
            std::swap(*pos_iter, temp_value);
            assign_times += 1;
            while (pos_iter != cycle_start_iter) {
                pos_iter = cycle_start_iter;
                for (auto iter = cycle_start_iter + 1; iter < last; ++iter) {
                    compare_times += 1;
                    if (*iter < temp_value) {++pos_iter;}
                }
                while (temp_value == *pos_iter) {++pos_iter;}
                std::swap(*pos_iter, temp_value);
                assign_times += 1;
            }
        }
        return std::make_pair(compare_times, assign_times);
    }
    template<typename RandomAccessIterator, typename CompareFunctor>
    void operator()(RandomAccessIterator first, RandomAccessIterator last, CompareFunctor compare) {
        for (auto cycle_start_iter = first; cycle_start_iter < last - 1; ++cycle_start_iter) {
            auto temp_value = *cycle_start_iter;
            auto pos_iter = cycle_start_iter;
            for (auto iter = cycle_start_iter + 1; iter < last; ++iter) {
                if (compare(*iter, temp_value)) {++pos_iter;}
            }
            if (pos_iter == cycle_start_iter) {continue;}
            while (temp_value == *pos_iter) {++pos_iter;}
            std::swap(*pos_iter, temp_value);
            while (pos_iter != cycle_start_iter) {
                pos_iter = cycle_start_iter;
                for (auto iter = cycle_start_iter + 1; iter < last; ++iter) {
                    if (compare(*iter, temp_value)) {++pos_iter;}
                }
                while (temp_value == *pos_iter) {++pos_iter;}
                std::swap(*pos_iter, temp_value);
            }
        }
    }
    std::string name = "cycle_sort";
};

struct BeadSort {
    template<typename RandomAccessIterator>
    std::pair<long long, long long> operator()(RandomAccessIterator first, RandomAccessIterator last) {
        long long compare_times = 0, assign_times = 0;
        for (; first != last; --last) {
            for (auto iter = first; iter + 1 != last; ++iter) {
                compare_times += 1;
                if (*(iter + 1) < *iter) {
                    auto temp_value = *(iter + 1) - *iter;
                    *iter += temp_value;
                    *(iter + 1) -= temp_value;
                    assign_times += 2;
                }
            }
        }
        return std::make_pair(compare_times, assign_times);
    }
    template<typename RandomAccessIterator, typename CompareFunctor>
    void operator()(RandomAccessIterator first, RandomAccessIterator last, CompareFunctor compare) {
        for (; first != last; --last) {
            for (auto iter = first; iter + 1 != last; ++iter) {
                if (compare(*(iter + 1), *iter)) {
                    auto temp_value = *(iter + 1) - *iter;
                    *iter += temp_value;
                    *(iter + 1) -= temp_value;
                }
            }
        }
    }
    const std::string name = "bead_sort";
};

struct BogoSort {
    template<typename RandomAccessIterator>
    void operator()(RandomAccessIterator first, RandomAccessIterator last) {
        while (!std::is_sorted(first, last)) {
            std::random_shuffle(first, last);
        }
    }
    template<typename RandomAccessIterator, typename CompareFunctor>
    void operator()(RandomAccessIterator first, RandomAccessIterator last, CompareFunctor compare) {
        while (!std::is_sorted(first, last, compare)) {
            std::random_shuffle(first, last);
        }
    }
    const std::string name = "bogo_sort";
};

struct CircleSort {
    template<typename RandomAccessIterator, typename CompareFunctor>
    bool circle_sort_util(RandomAccessIterator first, RandomAccessIterator last, CompareFunctor compare) {
        bool is_swapped = false;
            auto begin = first, end = last - 1;
            if (begin >= end) {return is_swapped;}
            for (; begin < end; ++begin, --end) {
                if (compare(*end, *begin)) {
                    std::swap(*begin, *end);
                    is_swapped = true;
                }
            }
            if (begin == end && compare(*(begin), *(begin - 1))) {
                std::swap(*begin, *(begin - 1));
                is_swapped = true;
            }
            auto iter_mid = first + std::distance(first, last) / 2;
            return is_swapped || circle_sort_util(first, iter_mid, compare) || circle_sort_util(iter_mid, last, compare);
    }
    template<typename RandomAccessIterator>
    std::pair<long long, long long> operator()(RandomAccessIterator first, RandomAccessIterator last) {
        this->operator()(first, last, std::less<typename RandomAccessIterator::value_type>());
        return std::make_pair(-1, -1);
    }
    template<typename RandomAccessIterator, typename CompareFunctor>
    void operator()(RandomAccessIterator first, RandomAccessIterator last, CompareFunctor compare) {
        if (std::distance(first, last) <= 1) {return;} 
        while (circle_sort_util(first, last, compare));
    }
    const std::string name = "circle_sort";
};

struct PancakeSort {
    template<typename RandomAccessIterator>
    std::pair<long, long> operator()(RandomAccessIterator first, RandomAccessIterator last) {
        for (; first != last; --last) {
            auto reverse_position = std::max_element(first, last);
            std::reverse(first, reverse_position + 1);
            std::reverse(first, last);
        }
        return std::make_pair(-1, -1);
    }
    template<typename RandomAccessIterator, typename CompareFunctor>
    void operator()(RandomAccessIterator first, RandomAccessIterator last, CompareFunctor compare) {
        for (; first != last; --last) {
            auto reverse_position = std::max_element(first, last, compare);
            std::reverse(first, reverse_position + 1);
            std::reverse(first, last);
        }
    }    
    const std::string name = "pancke_sort";
};

#endif