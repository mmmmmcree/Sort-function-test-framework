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
    static void print_correctnees(const std::string&, bool);
    static void print_category(const std::string&, short);
    static void print_performance_info(const std::string&, const PInfoContainer&);
    static void write_info_to_file(std::map<std::string, InfoPointer>&);
};

#endif