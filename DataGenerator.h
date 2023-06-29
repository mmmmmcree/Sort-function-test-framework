#ifndef DATAGENERATOR_H
#define DATAGENERATOR_H
#include <vector>
#include <random>
#include <algorithm>

template<template<typename> typename Container = std::vector>
class DataGenerator {
public:
    using iterator_category = typename Container<int>::iterator::iterator_category; //先放着
    DataGenerator();
    long long get_data_scale() const;
    void set_data_scale(long long);
    Container<int> get_reversed_data();
    template<
        typename ValueType = int,
        template<typename> typename DistributionType = std::uniform_int_distribution
    > Container<ValueType> get_data();
private:
    long long _data_scale;
};

template<template<typename> typename Container>
DataGenerator<Container>::DataGenerator(): _data_scale(10)
{

}

template<template<typename> typename Container>
long long DataGenerator<Container>::get_data_scale() const {
    return _data_scale;
}

template<template<typename> typename Container>
void DataGenerator<Container>::set_data_scale(long long  data_scale) {
    _data_scale =  data_scale;
}

template<template<typename> typename Container>
template<typename ValueType, template<typename> typename DistributionType>
Container<ValueType> DataGenerator<Container>::get_data() {
    Container<ValueType> data(_data_scale);
    DistributionType<ValueType> distributor(-_data_scale / 4, _data_scale / 4);
    std::default_random_engine engine(1349751341);
    std::generate(data.begin(), data.end(), [&distributor, &engine](){return distributor(engine);});
    return data;
}

template<template<typename> typename Container>
Container<int> DataGenerator<Container>::get_reversed_data() {
    Container<int> data(_data_scale);
    int i = _data_scale;
    std::generate(data.begin(), data.end(), [&i](){return --i;});
    return data;
}

#endif