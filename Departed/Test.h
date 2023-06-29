#ifndef TEST_H
#define TEST_H
#include <iostream>
#include <initializer_list>
#include <vector>
#include <list>
#include <map>
#include <utility>
#include <typeinfo>
#include "Timer.h"
#include "DataGenerator.h"
#include "Information.h"
#include "bubble_sort.h"


class Test {
    using str_list = typename std::initializer_list<std::string>;
    using func_list = typename std::initializer_list<std::function<void()>>;
public:
    Test();
    void get_runtime();
    std::map<std::string, Information> pass_information();//todo 把该函数移动到Printer类
    template<
        typename ValueType = long long,
        template<typename> typename DistributionType = std::uniform_int_distribution,
        template<typename> typename Container = std::vector
    > void set(long long);
private:
    std::map<std::string, Information> _sort_function_container;
    bool _getable;
    //todo 为适配不同迭代器的算法做分类
};

template<
    typename ValueType,
    template<typename> typename DistributionType,
    template<typename> typename Container
> void Test::set(long long data_scale) {
    _sort_function_container.clear();
    DataGenerator<Container> data_generator;
    data_generator.set_data_scale(data_scale);
    Container<ValueType> data =  data_generator.template get_data<ValueType, DistributionType>();
    str_list sort_names{
        "bubble_sort",
        "std::sort"
    };
    func_list sort_functions{
        [data = data]() mutable {bubble_sort(data.begin(), data.end());},
        [data = data]() mutable {std::sort(data.begin(), data.end());}
    };
    if (sort_names.size() != sort_functions.size()) {throw "Sizes Mismatch";}
    str_list::iterator names_iter = sort_names.begin(), names_end = sort_names.end();
    func_list::iterator functions_iter = sort_functions.begin();
    for (; names_iter != names_end; ++names_iter, ++functions_iter) {
        _sort_function_container.insert(
            std::make_pair(
                *names_iter, 
                Information(
                    *functions_iter,
                    typeid(DistributionType<ValueType>).name(),
                    typeid(Container<ValueType>).name(),
                    typeid(ValueType).name(),
                    data_scale,
                    -1
                )
            )
        );
    }
    _getable = true;
}

#endif