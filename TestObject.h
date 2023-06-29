#ifndef TESTOBJECT_H
#define TESTOBJECT_H
#include <string>
#include <map>
#include <vector>
#include <list>
#include <forward_list>
#include <memory>
#include <random>
#include <algorithm>
#include "DataGenerator.h"
#include "Information.h"
#include "InfoProcessor.h"
#include "Timer.h"
#include <iostream>

class TestObject {
    friend InfoProcessor;
    using InfoPointer = typename std::shared_ptr<SortFunctionInfo>;
public:
    TestObject() =default;
    template<typename CurrentFunction, typename... RestFuctions>
    bool correctness_test();
    template<typename CurrentFunction, typename... RestFuctions>
    void suitable_category_test();
    template<typename CurrentFunction, typename... RestFuctions>
    void performance_test();
    template<typename CurrentFunction, typename... RestFuctions>
    void easy_test();
    void write_to_file();
private:
    template<typename CurrentFunction> void _prepare();
    static std::map<std::string, InfoPointer> info_map;
};

template<typename CurrentFunction>
void TestObject::_prepare() {
    CurrentFunction sort_function;
    std::map<std::string, InfoPointer>::iterator iter = info_map.find(sort_function.name);
    InfoPointer info_ptr = (iter != info_map.end() ? iter->second : std::make_shared<SortFunctionInfo>());
    if (iter == info_map.end()) {
        info_map.insert(std::make_pair(sort_function.name, info_ptr));
    }
}

template<typename CurrentFunction, typename... RestFuctions>
bool TestObject::correctness_test() {
    _prepare<CurrentFunction>();
    CurrentFunction sort_function;
    std::map<std::string, InfoPointer>::iterator iter = info_map.find(sort_function.name);
    bool is_correct = false;
    if (iter->second->is_correct) {
        is_correct = true;
    } else {
        std::vector<int> test_container = DataGenerator().get_data();
        sort_function(test_container.begin(), test_container.end());
        is_correct = std::is_sorted(test_container.begin(), test_container.end());
        info_map[sort_function.name]->is_correct = is_correct;
        if (is_correct) {
            iter->second->suitable_iterator_category = SortFunctionInfo::IteratorCategory::RandomAccessIterator;
        }
    }
    InfoProcessor::print_correctnees(sort_function.name, is_correct);
    if constexpr(sizeof...(RestFuctions) > 0) {
        correctness_test<RestFuctions...>();
    }
    return is_correct;
}

template<typename CurrentFunction, typename... RestFuctions>
void TestObject::suitable_category_test() {
    bool is_correct = correctness_test<CurrentFunction>();
    CurrentFunction sort_function;
    if (is_correct) {
        InfoProcessor::print_category(
            sort_function.name, 
            static_cast<short>(SortFunctionInfo::IteratorCategory::RandomAccessIterator)
        );
        auto foward_test_container = DataGenerator<std::forward_list>().get_data();
        auto bidirection_test_container = DataGenerator<std::list>().get_data();
        auto f_begin = foward_test_container.begin(), f_end = foward_test_container.end();
        auto b_begin = bidirection_test_container.begin(), b_end = bidirection_test_container.end();
        try{
            sort_function(b_begin, b_end);
            info_map[sort_function.name]->suitable_iterator_category = 
                    SortFunctionInfo::IteratorCategory::BidirectionalIterator;
            InfoProcessor::print_category(
                sort_function.name, 
                static_cast<short>(SortFunctionInfo::IteratorCategory::BidirectionalIterator)
            );
        }catch(...) {};
        // try {
        //     sort_function(f_begin, f_end);
        // } catch(...) {};
    }
    if constexpr(sizeof...(RestFuctions) > 0) {
        correctness_test<RestFuctions...>();
    }
}

template<typename CurrentFunction, typename... RestFuctions>
void TestObject::performance_test() {
    bool is_correct = correctness_test<CurrentFunction>();
    CurrentFunction sort_function;
    if (is_correct) {
        DataGenerator data_generator;
        std::vector<PerforamanceInfo>& p_info_container = info_map[sort_function.name]->performance_info_container;
        for (int i = 10; i <= 12; ++i) {
            long long data_scale = static_cast<long long >(pow(2, i));
            data_generator.set_data_scale(data_scale);
            {
                std::vector<int> test_container = data_generator.template get_data<int, std::uniform_int_distribution>();
                PerforamanceInfo performance_info(
                    "uniform_int_distribution",
                    "int",
                    data_scale
                );
                p_info_container.push_back(performance_info);
                Timer timer(p_info_container.back().runtime);
                sort_function(test_container.begin(), test_container.end());
            }
            {
                std::vector<double> test_container = data_generator.template get_data<double, std::uniform_real_distribution>();
                PerforamanceInfo performance_info(
                    "uniform_real_distribution",
                    "double",
                    data_scale
                );
                p_info_container.push_back(performance_info);
                Timer timer(p_info_container.back().runtime);
                sort_function(test_container.begin(), test_container.end());                
            }
            {
                std::vector<double> test_container = data_generator.template get_data<double, std::normal_distribution>();
                PerforamanceInfo performance_info(
                    "normal_distribution",
                    "double",
                    data_scale
                );
                p_info_container.push_back(performance_info);
                Timer timer(p_info_container.back().runtime);
                sort_function(test_container.begin(), test_container.end());                   
            }
            {
                std::vector<int> test_container = data_generator.get_reversed_data();
                PerforamanceInfo performance_info(
                    "reversed_distribution",
                    "int",
                    data_scale
                );
                p_info_container.push_back(performance_info);
                Timer timer(p_info_container.back().runtime);
                sort_function(test_container.begin(), test_container.end());                   
            }
        }
        InfoProcessor::print_performance_info(sort_function.name, p_info_container);
    }
    if constexpr(sizeof...(RestFuctions) > 0) {
        performance_test<RestFuctions...>();
    }
}

#endif

