#ifndef INFOPROCESSOR_H
#define INFOPROCESSOR_H
#include <iostream>
#include <fstream>
#include <chrono>
#include <memory>
#include <map>
#include "Information.h"

class InfoProcessor {
    using PInfoContainer = typename std::vector<PerforamanceInfo>;
    using InfoPointer = typename std::shared_ptr<SortFunctionInfo>;
public:
    template<typename CurrentFunction>
    void print_data_for_visible_test(const std::string& name, const CurrentFunction&, bool);
    static void print_correctnees(const std::string&, bool);
    static void print_category(const std::string&, short);
    static void print_performance_info(const std::string&, const PInfoContainer&);
    static void write_info_to_file(std::map<std::string, InfoPointer>&);
private:
    static const int NUMBER_OF_DISTRIBUTION = 5;
};

template<typename CurrentFunction>
void InfoProcessor::print_data_for_visible_test(const std::string& name, const CurrentFunction& data, bool before_sort) {
    if (before_sort) {
        std::cout << name << " visible test:" << std::endl;
        std::cout << "Before sorting: ";
    } else {
        std::cout << "After sorting: ";
    }
    for (const auto& i : data) {
        std::cout << i << "\t";
    }
    std::cout << std::endl;
}

#endif